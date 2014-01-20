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


using namespace std;

class RocksDBPHP : public Php::Base {
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



public:

    RocksDBPHP() {

    }

    /*
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

    /*
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

    /*
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

    /*
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

    /*
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

        Php::Value array(params[0]), rez;
        const Php::Value  phpnull;
        unsigned int arrSize = array.size();
        std::string key, val;

        for (unsigned int i = 0; i < arrSize; i++) {
            key   = (const char *) array[i];
            this->status = db->Get(rocksdb::ReadOptions(), key, &val);

            //std::cout << "Get(" << key <<") = " << val << std::endl;

            if (!this->status.ok()) {
                rez[i] = phpnull;
            } else {
                rez[i] = val;
            }
        }
        return rez;
    }

    /*
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

    /*
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

    /*
     * function getStatus
     * @param void
     * @return string status.ToString()
     */
    Php::Value getStatus() {
        return  this->status.ToString();
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


            }));


        // return the extension module
        return extension.module();
    }
}
