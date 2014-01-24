## Install

First, you need to install [PHP-CPP](https://github.com/CopernicaMarketingSoftware/PHP-CPP)
and
[RocksDB](https://github.com/facebook/rocksdb/)

Builds shared library for RocksDB, exec `make librocksdb.so` and `sudo cp librocksdb.so /usr/lib/librocksdb.so`.


After compile and install rocksdbphp:
exec `make` and `sudo make install`

## Usage
    
    // Init
    $rocks = new RocksDB('/tmp/wwwdb');
    
    // get
    // if key not exist, return NULL
    echo $rocks->get('key1');
    //same:
    echo $rocks->key1;
    echo $rocks->getStatus();

    // set
    $rocks->set('key1', 'sdfsdf');
    //same:
    $rocks->key1 = 'sdfsdf';
    echo $rocks->getStatus();
    
    // delete
    $rocks->del('key2');
    //same:
    unset($rocks->skey2);
    echo $rocks->getStatus();
    
    // multiset
    $toSet = array('skey1'=>'val1','skey2'=>'val2','skey3'=>'val3','skey4'=>'val4');
    $rocks->mset( array_keys($toSet), array_values($toSet)  );
    echo $rocks->getStatus();
    
    // multiget
    $rocks->mget(array('skey1','skey2','skey3','skey4'));
    //echo $rocks->getStatus(); // not supported for mget
    
    // isset
    // fast check exist key
    $rocks->isset('key1');
    //same:
    isset($rocks->key1);
    //echo $rocks->getStatus(); // not supported for isset
    
    // incr
    // incriment/decriment (integer counter)
    $rocks->incr('ckey1');
    $rocks->incr('ckey2', 5);
    $rocks->incr('ckey2', -2);
    echo $rocks->getStatus();


## Note
Currently under development

## License
BSD
