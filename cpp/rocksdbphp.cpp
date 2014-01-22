/**
 *  myscrnav.cpp
 *  app myScrNav
 *  Печать, навигационной строки для листания экранов (pageinator),
 *  Расчет стартовой точки и лимита для постраничного вывода элементов
 *  @author valmat <ufabiz@gmail.com>
 *  @github https://github.com/valmat/myscrnav
 */



#include <string>
#include <iostream>
#include <phpcpp.h>
#include "rocksdb/db.h"
#include "rocksdb/write_batch.h"
#include "rocksdb/merge_operator.h"

//#include <php5/Zend/zend_iterators.h>
/**
 *  PHP includes
 */
//#include <php.h>
//#include "zend_iterators.h"
#include <regex>



using namespace std;

//namespace rocksdb {
class UInt64AddOperator : public rocksdb::AssociativeMergeOperator {
 public:
    virtual bool Merge(
        const rocksdb::Slice& key,
        const rocksdb::Slice* existing_value,
        const rocksdb::Slice& value,
        std::string* new_value,
        rocksdb::Logger* logger) const override {

        // assuming 0 if no existing value
        int64_t existing = 0;
        if (existing_value) {
             //existing = atoi(existing_value.ToString().c_str());
             existing = std::strtoull(existing_value->ToString().c_str(),0,10);

            /*
            if (!Deserialize(*existing_value, &existing)) {
                // if existing_value is corrupted, treat it as 0
                Log(logger, "existing value corruption");
                existing = 0;
            }
            */
        }

        //uint64_t oper;
        //uint64_t oper = atoi(value.ToString().c_str());
        int64_t oper = std::strtoull(value.ToString().c_str(),0,10);

        /*
        if (!Deserialize(value, &oper)) {
            // if operand is corrupted, treat it as 0
            Log(logger, "operand value corruption");
            oper = 0;
        }
        */


        int64_t newval = existing + oper;
        //*new_value = Serialize(new);
        *new_value = std::to_string(newval);
        return true;        // always return true for this, since we treat all errors as "zero".
    }

    virtual const char* Name() const override {
        return "UInt64AddOperator";
    }

};
//}


class RocksDBPHPCounter : public Php::Base {

public:
    RocksDBPHPCounter() = default;

    RocksDBPHPCounter(rocksdb::DB* db, rocksdb::Options *poptions, std::string k) :
    key(k)
    {
        auto f = [](int x, int y) -> int { int z = x + y; return z; };
        std::cout << f(5,6) << std::endl;

        this->db = db;
        this->poptions = poptions;
    }

    virtual ~RocksDBPHPCounter() {}

    /**
     * get value by key
     * function get
     * @param string key
     * @return string value or NULL (if not key exist)
     */
     /*
    Php::Value get(Php::Parameters &params) {
        if (params.size() < 1) {
            throw Php::Exception("Requires 1 parameters: key");
            return false;
        }
        return params[0];
    }
    */
    //Php::Value incr(Php::Parameters &params) {
    void incr(Php::Parameters &params) {
        int64_t iv = 1;
        if (params.size() > 0) {
            iv = (int)params[0];
        }

        string serialized =std::to_string(iv);

        //db->Merge(*poptions, key, serialized);
        db->Merge(rocksdb::WriteOptions(), key, serialized);
    }

//private:
    /**
     * function __construct
     * @param string path
     * @param bool create_if_missing
     */
    virtual void __construct() {
        std::cout << "__construct" << std::endl;
    };
    virtual void __destruct() {
        std::cout << "__destruct" << std::endl;
    }
private:
    std::string key;
    rocksdb::DB* db;
    rocksdb::Options *poptions;


};


class RocksDBPHP : public Php::Base//, public zend_object_iterator
{
private:
    /**
     * db
     */
    rocksdb::DB* db;

    /**
     * db path distantion
     */
    string dbpath;

    /**
     * db path distantion
     */
    rocksdb::Options dboptions;

    /**
     * last opreation status
     */
    rocksdb::Status status;

    /**
     * last opreation status
     */
    bool counter_option_seted = false;



public:

    RocksDBPHP() = default;

    /**
     * function __construct
     * @param string path
     * @param bool create_if_missing
     */
    virtual void __construct(Php::Parameters &params) {

        if (params.size() < 1) {
            throw Php::Exception("Requires parameter path");
            return;
        }
        this->dbpath = (new Php::Value(params[0]))->stringValue();
        bool create_if_missing = true;
        if (params.size() > 1) {
            create_if_missing = (bool)params[1];
        }

        this->dboptions.create_if_missing = create_if_missing;
        this->dboptions.merge_operator.reset(new UInt64AddOperator);

        this->status = rocksdb::DB::Open(this->dboptions, this->dbpath, &this->db);
        std::cerr << this->status.ToString() << std::endl;

        if (!this->status.ok())  {
            throw Php::Exception(   this->status.ToString()  );
        }

    }

    virtual ~RocksDBPHP() {
        delete db;
    }
    virtual void __destruct() {}

    /**
     * set value by key
     * function set
     * @param string key
     * @param string value
     * @return bool rezult
     */
    Php::Value set(Php::Parameters &params) {
        if (params.size() < 2) {
            throw Php::Exception("Requires 2 parameters: key and value");
            return false;
        }
        std::string key, value;
        key   = (new Php::Value(params[0]))->stringValue();
        value = (new Php::Value(params[1]))->stringValue();

        this->status = db->Put(rocksdb::WriteOptions(), key, value);

        return static_cast<bool>(this->status.ok());
    }

    /**
     * set array values by array keys
     * function mset
     * @param Php::Array keys
     * @param Php::Array values
     * @return bool rezult status
     */
    Php::Value mset(Php::Parameters &params) {
        if (params.size() < 2) {
            throw Php::Exception("Requires 2 parameter: array keys and array values");
            return false;
        }
        if(!params[0].isArray() || !params[1].isArray() ) {
            throw Php::Exception("Required parameters are arrays");
            return false;
        }
        if(params[0].size() != params[1].size() ) {
            throw Php::Exception("Dimensions do not match");
            return false;
        }

        unsigned int arrSize = params[0].size();
        rocksdb::WriteBatch batch;
        std::string key, val;

        for (unsigned int i = 0; i < arrSize; i++) {
            key = (const char *) params[0][i];
            val = (const char *) params[1][i];
            batch.Put(key, val);
        }
        this->status = db->Write(rocksdb::WriteOptions(), &batch);

        return static_cast<bool>(this->status.ok());
    }


    /**
     * set array values by array keys
     * function mset
     * @param Php::Array keys
     * @param Php::Array values
     * @return bool rezult status
     */
    /*
    Php::Value mset1(Php::Parameters &params) {
        if (params.size() < 1) {
            throw Php::Exception("Requires 1 parameter");
            return false;
        }
        if(!params[0].isObject()) {
            throw Php::Exception("Required parameters are object");
            return false;
        }

        Php::Member m = params[0];
        for (auto iter = m.begin(); iter != m.end(); iter++) {
            //iter->declare(entry);
            std::cout << "#" << std::endl;
        }
    }
    */

    /**
     * get value by key
     * function get
     * @param string key
     * @return string value or NULL (if not key exist)
     */
    Php::Value get(Php::Parameters &params) {
        if (params.size() < 1) {
            throw Php::Exception("Requires 1 parameters: key");
            return false;
        }
        std::string key, value;
        key   = (new Php::Value(params[0]))->stringValue();
        const Php::Value  phpnull;

        this->status = db->Get(rocksdb::ReadOptions(), key, &value);
        std::cout << "Get(" << key <<") = " << value << std::endl;
        if (!this->status.ok()) {
            return phpnull;
        }
        return value;
    }

    /**
     * get array values by array keys
     * function mget
     * @param Php::Array keys
     * @return Php::Array rezult
     */
    Php::Value mget(Php::Parameters &params) {
        if (params.size() < 1) {
            throw Php::Exception("Requires 1 parameters: array keys");
            return false;
        }
        if(!params[0].isArray()) {
            throw Php::Exception("Requires array");
            return false;
        }

        Php::Value rez;
        const Php::Value  phpnull;
        unsigned int arrSize = params[0].size();

        std::vector<rocksdb::Slice> keys(arrSize);
        std::vector<std::string> values(arrSize);
        std::vector<rocksdb::Status> statuses(arrSize);

        for (unsigned int i = 0; i < arrSize; i++) {
            keys[i] = (const char *) params[0][i];
        }

        statuses = db->MultiGet(rocksdb::ReadOptions(), keys, &values);

        for (unsigned int i = 0; i < arrSize; i++) {
            rez[keys[i].ToString()] = (statuses[i].ok()) ? (Php::Value) values[i] : phpnull;
        }
        return rez;
    }

    /**
     * remove key from db
     * function del
     * @param string key
     * @return bool status rezult
     */
    Php::Value del(Php::Parameters &params) {
        if (params.size() < 1) {
            throw Php::Exception("Requires 1 parameters: key");
            return false;
        }

        this->status = db->Delete(rocksdb::WriteOptions(), (new Php::Value(params[0]))->stringValue());
        return static_cast<bool>(this->status.ok());
    }

    /**
     * remove keys from db
     * function mdel
     * @param Php::Array keys
     * @return bool status rezult
     */
    Php::Value mdel(Php::Parameters &params) {
        if (params.size() < 1) {
            throw Php::Exception("Requires 1 parameters: array keys");
            return false;
        }
        if(!params[0].isArray()) {
            throw Php::Exception("Requires array");
            return false;
        }

        unsigned int arrSize = params[0].size();
        rocksdb::WriteBatch batch;
        std::string key;

        for (unsigned int i = 0; i < arrSize; i++) {
            key = (const char *) params[0][i];
            batch.Delete(key);
        }
        this->status = db->Write(rocksdb::WriteOptions(), &batch);

        return static_cast<bool>(this->status.ok());
    }

    /**
     * function getStatus
     * @param void
     * @return string status.ToString()
     */
    Php::Value getStatus() {
        return  this->status.ToString();
    }


    /**
     * function getStatus
     * @param void
     * @return string status.ToString()
     */
    Php::Value Counter(Php::Parameters &params) {
        if (params.size() < 1) {
            throw Php::Exception("Requires parameter: key");
            return false;
        }
        if(!counter_option_seted) {
            counter_option_seted = true;
            //this->dboptions.merge_operator.reset(new UInt64AddOperator);
        }

        Php::Value ret;

        /*

        RocksDBPHPCounter *q = new RocksDBPHPCounter(db, &this->dboptions, params[0].stringValue());

        ret = (php::Base)RocksDBPHPCounter(db, &this->dboptions, params[0].stringValue());
        //ret.setType(Php::Type::objectType);

        std::cout << ret.type() << std::endl;
        */
        return ret;
    }

    void incr(Php::Parameters &params) {
        if (params.size() < 1) {
            throw Php::Exception("Requires parameter: key");
            return;
        }

        int64_t iv = 1;
        if (params.size() > 1) {
            iv = params[1].numericValue();
        }


        if(!counter_option_seted) {
            counter_option_seted = true;
            this->dboptions.merge_operator.reset(new UInt64AddOperator);
        }



        string val =std::to_string(iv);

        //db->Merge(*poptions, key, serialized);
        this->status = db->Merge(rocksdb::WriteOptions(), params[0].stringValue(), val);
    }

};




extern "C"
{
    // export the "get_module" function that will be called by the Zend engine
    PHPCPP_EXPORT void *get_module()
    {
        // create extension
        static Php::Extension extension("RocksDBphp","0.1");

        // add the custom class ot the extension
        extension.add("RocksDB", Php::Class<RocksDBPHP>({
                Php::Public("__construct", Php::Method<RocksDBPHP>(&RocksDBPHP::__construct), {
                    Php::ByVal("path", Php::stringType),
                    Php::ByVal("cifm", Php::boolType)
                }),

                // GET
                Php::Public("get", Php::Method<RocksDBPHP>(&RocksDBPHP::get), {
                    Php::ByVal("key", Php::stringType)
                }),
                Php::Public("mget", Php::Method<RocksDBPHP>(&RocksDBPHP::mget), {
                    Php::ByVal("keys", Php::arrayType)
                }),

                // DEL
                Php::Public("del", Php::Method<RocksDBPHP>(&RocksDBPHP::del), {
                    Php::ByVal("key", Php::stringType)
                }),
                Php::Public("mdel", Php::Method<RocksDBPHP>(&RocksDBPHP::mdel), {
                    Php::ByVal("keys", Php::arrayType)
                }),

                // SET
                Php::Public("set", Php::Method<RocksDBPHP>(&RocksDBPHP::set), {
                    Php::ByVal("key", Php::stringType),
                    Php::ByVal("val", Php::stringType)
                }),
                Php::Public("mset", Php::Method<RocksDBPHP>(&RocksDBPHP::mset), {
                    Php::ByVal("keys", Php::arrayType),
                    Php::ByVal("vals", Php::arrayType)
                }),
                // OTHER
                Php::Public("getStatus", Php::Method<RocksDBPHP>(&RocksDBPHP::getStatus)),
                Php::Public("Counter", Php::Method<RocksDBPHP>(&RocksDBPHP::Counter), {
                    Php::ByVal("key", Php::stringType)
                }),

                Php::Public("incr", Php::Method<RocksDBPHP>(&RocksDBPHP::incr), {
                    Php::ByVal("key", Php::stringType),
                    Php::ByVal("incrVal", Php::numericType)
                }),


            }));

        extension.add("RocksDBCounter", Php::Class<RocksDBPHPCounter>({
                Php::Protected("__construct", Php::Method<RocksDBPHPCounter>(&RocksDBPHPCounter::__construct), {
                }),
                // GET
                /*
                Php::Public("get", Php::Method<RocksDBPHPCounter>(&RocksDBPHPCounter::get), {
                    Php::ByVal("key", Php::stringType)
                }),
                */
                Php::Public("incr", Php::Method<RocksDBPHPCounter>(&RocksDBPHPCounter::incr), {
                    Php::ByVal("incrVal", Php::numericType)
                }),


            }));


        // return the extension module
        return extension.module();
    }
}
