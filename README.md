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
    $rocks->get('key1');
    echo $rocks->getStatus();

    // set
    $rocks->set('key1', 'sdfsdf')
    echo $rocks->getStatus();
    
    // delete
    $rocks->del('skey2');
    echo $rocks->getStatus();
    
    // multiset
    $toSet = array('skey1'=>'val1','skey2'=>'val2','skey3'=>'val3','skey4'=>'val4');
    $rocks->mset( array_keys($toSet), array_values($toSet)  );
    echo $rocks->getStatus();
    
    // multiget
    $rocks->mget(array('skey1','skey2','skey3','skey4'));
    echo $rocks->getStatus();
    
    // multidel
    $rocks->mdel(  array('skey1','skey2','skey3')  );
    echo $rocks->getStatus();
    


Currently under development

License BSD
