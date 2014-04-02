/**
 *  rocksdbphp.cpp
 *  app RocksDB
 *  implementation fast key/value storage RocksDB for php
 *  @author valmat <ufabiz@gmail.com>
 *  @github https://github.com/valmat/rocksdbphp
 */


#include <string>
#include <iostream>

// PHP-CPP
#include <phpcpp.h>
// RocksDB
#include "rocksdb/db.h"
#include "rocksdb/write_batch.h"
#include "rocksdb/merge_operator.h"

// includes
#include "include/Int64Incrementor.h"
#include "include/MultiGetResult.h"
#include "include/Driver.h"


// Symbols are exported according to the "C" language
extern "C" 
{
    // export the "get_module" function that will be called by the Zend engine
    PHPCPP_EXPORT void *get_module()
    {
        // create extension
        static Php::Extension extension("RocksDBphp","0.2");


        // add the class to the extension
        extension.add(std::move( 
        	Php::Class<RocksDBPHP::Driver>("RocksDB")

	        	.method("__construct", &RocksDBPHP::Driver::__construct, {
		            Php::ByVal("path", Php::Type::String),
		            Php::ByVal("cifm", Php::Type::Bool)
		        })

		        // GET
		        .method("get", &RocksDBPHP::Driver::get, {
		            Php::ByVal("key", Php::Type::String)
		        })
		        .method("__get", &RocksDBPHP::Driver::get, {
		            Php::ByVal("key", Php::Type::String)
		        })
		        .method("mget", &RocksDBPHP::Driver::mget, {
		            Php::ByVal("keys", Php::Type::Object)
		        })
		        .method("mgetArray", &RocksDBPHP::Driver::mgetArrray, {
		            Php::ByVal("keys", Php::Type::Object)
		        })


		        // DEL
		        .method("del", &RocksDBPHP::Driver::del, {
		            Php::ByVal("key", Php::Type::String)
		        })
		        .method("__unset", &RocksDBPHP::Driver::del, {
		            Php::ByVal("key", Php::Type::String)
		        })
		        .method("mdel", &RocksDBPHP::Driver::mdel, {
		            Php::ByVal("keys", Php::Type::Array)
		        })

		        // SET
		        .method("set", &RocksDBPHP::Driver::set, {
		            Php::ByVal("key", Php::Type::String),
		            Php::ByVal("val", Php::Type::String)
		        })
		        .method("__set", &RocksDBPHP::Driver::set, {
		            Php::ByVal("key", Php::Type::String),
		            Php::ByVal("val", Php::Type::String)
		        })
		        .method("mset", &RocksDBPHP::Driver::mset, {
		            Php::ByVal("keys", Php::Type::Object)
		        })
		        // OTHER
		        .method("getStatus", &RocksDBPHP::Driver::getStatus)

		        .method("incr", &RocksDBPHP::Driver::incr, {
		            Php::ByVal("key", Php::Type::String),
		            Php::ByVal("incrVal", Php::Type::Numeric)
		        })

		        .method("isset", &RocksDBPHP::Driver::isset, {
		            Php::ByVal("key", Php::Type::String),
		            Php::ByRef("val", Php::Type::String, false)
		        })
		        .method("__isset", &RocksDBPHP::Driver::isset, {
		            Php::ByVal("key", Php::Type::String)
		        })
		    ));


        // add the class to the extension
        extension.add(std::move( 
        	Php::Class<RocksDBPHP::MultiGetResult>("RocksDB\\MultiGetResult")
	        	// Prohibited to create instances of this class by other way than through method RocksDB::mget()
	        	.method("__construct", &RocksDBPHP::MultiGetResult::__construct, Php::Private)
		));

        // return the extension module
        return extension;
    }
}