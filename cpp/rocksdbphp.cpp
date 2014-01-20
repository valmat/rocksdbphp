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
     *
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
     * db path distantion
     */
    rocksdb::Status status;



public:

    RocksDBPHP() {

    }

    /*
     * function __construct
     * @param int $pageNo
     * @param int $Count
     * @param string $curPath
     */
    virtual void __construct(Php::Parameters &params) {

        if (params.size() < 1) {
            throw Php::Exception("Requires parameter path");
            //this->pageNo  = 0;
            return;
        }
        //this->Count   = (new Php::Value(params[1]))->numericValue();
        this->dbpath = (new Php::Value(params[0]))->stringValue();
        bool create_if_missing = true;
        if (params.size() > 1) {
            create_if_missing = (bool)params[1]; //(new Php::Value(params[1]))->boolValue();
        }


        std::cout << "Test rocksdb work!" << std::endl;


        this->dboptions.create_if_missing = create_if_missing;

        this->status = rocksdb::DB::Open(this->dboptions, this->dbpath, &this->db);
        std::cerr << this->status.ToString() << std::endl;

        if (!this->status.ok())  {
            throw Php::Exception(   this->status.ToString()  );
        }

    }

    virtual ~RocksDBPHP() {
        std::cout << "delete db" << std::endl;
        delete db;
    }
    virtual void __destruct() {}

    // SETERS
    /*
     * function setSpace
     * @param string $space
     */
    /*
    void setSpace(Php::Parameters &params) {
        _set_param(params, &this->space);
    }
    */


    /*
     * function showCount
     * set showCount
     * @param bool $sc
     */
    Php::Value set(Php::Parameters &params) {
        if (params.size() < 2) {
            throw Php::Exception("Requires 2 parameters");
            return false;
        }
        std::string key, value;
        key   = (new Php::Value(params[0]))->stringValue();
        value = (new Php::Value(params[1]))->stringValue();

        this->status = db->Put(rocksdb::WriteOptions(), key, value);

        return static_cast<bool>(this->status.ok());
    }

    /*
     * function showCount
     * set showCount
     * @param bool $sc
     */
    Php::Value mset(Php::Parameters &params) {
        if (params.size() < 2) {
            throw Php::Exception("Requires 2 parameter");
            return false;
        }
        if(!params[0].isArray() || !params[1].isArray() ) {
            throw Php::Exception("Requires parameters arrays");
            return false;
        }
        if(params[0].size() != params[1].size() ) {
            throw Php::Exception("Dimensions do not match");
            return false;
        }

        int arrSize = params[0].size();
        rocksdb::WriteBatch batch;
        std::string key, val;

        for (int i = 0; i < arrSize; i++) {
            key = (const char *) params[0][i];
            val = (const char *) params[1][i];
            batch.Put(key, val);
        }
        this->status = db->Write(rocksdb::WriteOptions(), &batch);

        return static_cast<bool>(this->status.ok());
    }

    // GETERS
    /*
     * Номер начального элемента
     * function getStartPos
     * @return int
     */
    Php::Value get(Php::Parameters &params) {
    	//this->init();
        //return this->startPos;
        if (params.size() < 1) {
            throw Php::Exception("Requires 1 parameters");
            return false;
        }

        /*
        if(params[0].isString()) {
            std::cout << "isString" << std::endl;
        }
        if(params[0].isArray()) {
            std::cout << "isArray" << std::endl;
        }
        */



        std::string key, value;
        key   = (new Php::Value(params[0]))->stringValue();

        this->status = db->Get(rocksdb::ReadOptions(), key, &value);
        std::cout << "Get(" << key <<") = " << value << std::endl;
        if (!this->status.ok()) {
            //return false;
            return static_cast<bool>(false);
        }
        return value;

    }

    /*
     * Номер начального элемента
     * function getStartPos
     * @return int
     */
    Php::Value del(Php::Parameters &params) {
        if (params.size() < 1) {
            throw Php::Exception("Requires 1 parameters");
            return false;
        }

        //std::string key;
        //key   = (new Php::Value(params[0]))->stringValue();

        this->status = db->Delete(rocksdb::WriteOptions(), (new Php::Value(params[0]))->stringValue());
        return static_cast<bool>(this->status.ok());
    }

    /*
     * function showCount
     * set showCount
     * @param bool $sc
     */
    Php::Value mdel(Php::Parameters &params) {
        if (params.size() < 1) {
            throw Php::Exception("Requires 1 parameters");
            return false;
        }
        if(!params[0].isArray()) {
            throw Php::Exception("Requires array");
            return false;
        }

        int arrSize = params[0].size();
        rocksdb::WriteBatch batch;
        std::string key;

        for (int i = 0; i < arrSize; i++) {
            key = (const char *) params[0][i];
            batch.Delete(key);
        }
        this->status = db->Write(rocksdb::WriteOptions(), &batch);

        return static_cast<bool>(this->status.ok());
    }

    /*
     * Номер начального элемента
     * function getStartPos
     * @return int
     */
    Php::Value mget(Php::Parameters &params) {
    	//this->init();
        //return this->startPos;
        if (params.size() < 1) {
            throw Php::Exception("Requires 1 parameters");
            return false;
        }
        if(!params[0].isArray()) {
            throw Php::Exception("Requires array");
            return false;
        }

        Php::Value array(params[0]), rez;
        const Php::Value  phpnull;//.setType(Php::stringType);;
        int arrSize = array.size();

        //vector<string> rez(arrSize);

        cout << "array.size: " << arrSize << endl;


        std::string key, val;
        rocksdb::Status s;
        for (unsigned int i = 0; i < arrSize; i++) {
            cout << "The array: " << array[i] << endl;

            //key   = (new Php::Value(array[i]))->stringValue();
            //key   = array[i]->stringValue();
            //array[i]->setType(Php::stringType);

            //.stringValue()
            //key   = array[i].value();
            //key   = array[i].rawValue();

            key   = (const char *) array[i];

            //key   = array[i];


            s = db->Get(rocksdb::ReadOptions(), key, &val);
            std::cout << "Get(" << key <<") = " << val << std::endl;
            if (!s.ok()) {
                rez[i] = phpnull;//static_cast<bool>(false);
            } else {
                rez[i] = val;
            }



        }

        return rez;

    }

    /*
     * Номер начального элемента
     * function getStartPos
     * @return int
     */
    Php::Value getStatus() {
        return  this->status.ToString();
    }



private:

    /*
     * function _set_param
     * default int seter
     */
    void _set_param(Php::Parameters &params, int *var) {
        if (params.size() == 0 || (int)params[0] < 0) {
            return;
        }
        *var = (new Php::Value(params[0]))->numericValue();
    }

};



// Symbols are exported according to the "C" language
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
                    //Php::ByVal("Count",   Php::numericType),
                    Php::ByVal("path", Php::stringType)
                }),

                //GETERS
                Php::Public("get", Php::Method<RocksDBPHP>(&RocksDBPHP::get), {
                    Php::ByVal("key", Php::stringType)
                }),
                Php::Public("mget", Php::Method<RocksDBPHP>(&RocksDBPHP::mget), {
                    Php::ByVal("keys", Php::arrayType)
                }),

                Php::Public("getStatus", Php::Method<RocksDBPHP>(&RocksDBPHP::getStatus)),

                Php::Public("del", Php::Method<RocksDBPHP>(&RocksDBPHP::del), {
                    Php::ByVal("key", Php::stringType)
                }),
                Php::Public("mdel", Php::Method<RocksDBPHP>(&RocksDBPHP::mdel), {
                    Php::ByVal("keys", Php::arrayType)
                }),

                // SETERS
                /*
                Php::Public("showCount", Php::Method<RocksDBPHP>(&RocksDBPHP::showCount), {
                    Php::ByVal("sc", Php::boolType)
                })
                */
                Php::Public("set", Php::Method<RocksDBPHP>(&RocksDBPHP::set), {
                    Php::ByVal("key", Php::stringType),
                    Php::ByVal("val", Php::stringType)
                }),
                Php::Public("mset", Php::Method<RocksDBPHP>(&RocksDBPHP::mset), {
                    Php::ByVal("keys", Php::arrayType),
                    Php::ByVal("vals", Php::arrayType)
                }),


            }));




        // return the extension module
        return extension.module();
    }
}
