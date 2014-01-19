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
    //rocksdb::Options dboptions;


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

        if (params.size() != 1) {
            throw Php::Exception("Requires 1 parameters");
            //this->pageNo  = 0;
            return;
        }
        //this->Count   = (new Php::Value(params[1]))->numericValue();
        this->dbpath = (new Php::Value(params[0]))->stringValue();


        std::cout << "Test rocksdb work!" << std::endl;


        const char * fnm = "/tmp/testdb";

        //this->dboptions.create_if_missing = true;
        rocksdb::Options dboptions;
        /*
        rocksdb::Status status = rocksdb::DB::Open(this->dboptions, fnm,
                                                                   //this->dbpath,
                                                                   &this->db);

        if (!status.ok())  {
            std::cerr << status.ToString() << std::endl;
            throw Php::Exception(   status.ToString()  );
        }
        */

    }

    ~RocksDBPHP() {
        //delete db;
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
    void showCount(Php::Parameters &params) {
        if (params.size() == 0) {
            return;
        }
        //this->_showCount = (bool)params[0]; //(new Php::Value(params[0]))->boolValue();
    }

    // GETERS
    /*
     * Номер начального элемента
     * function getStartPos
     * @return int
     */
    Php::Value getStartPos() {
    	//this->init();
        //return this->startPos;
        return 0;
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
                })

                //GETERS
                //Php::Public("getStartPos", Php::Method<RocksDBPHP>(&RocksDBPHP::getStartPos)),


                // SETERS
                /*
                Php::Public("showCount", Php::Method<RocksDBPHP>(&RocksDBPHP::showCount), {
                    Php::ByVal("sc", Php::boolType)
                })
                */


            }));




        // return the extension module
        return extension.module();
    }
}
