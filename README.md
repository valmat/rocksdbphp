This is a PHP driver for RocksDB.

## Install

First, you need to install RocksDB server [RocksServer](https://github.com/valmat/RocksServer)

## Usage

```php
<?php
    require "Rocks.php";
    require 'MgetIterator.php';
    require 'Response.php';

    // Init
    $rocks = new RocksServer\Client();
    
    // get
    // if key not exist, return NULL
    echo $rocks->get('key1');

    // set
    $rocks->set('key1', 'value1');
    
    // delete
    $rocks->del('key2');
    
    // multiset
    $rocks->mset( array('skey1'=>'val1','skey2'=>'val2','skey3'=>'val3','skey4'=>'val4')  );
    
    // multiget
    $rocks->mget(array('skey1','skey2','skey3','skey4'));
    
    // isset
    // fast check exist key
    $rocks->keyExist('key1');
    // fast check and retrive
    $rocks->keyExist('key1', $val);
    
    // incr
    // incriment/decriment (integer counter)
    $rocks->incr('ckey1');
    $rocks->incr('ckey2', 5);
    $rocks->incr('ckey2', -2);
```

## License
BSD
