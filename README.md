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
$rocks->mset( array('key1'=>'val1','key2'=>'val2','key3'=>'val3','key4'=>'val4')  );
// or if class CustomIterator implements Traversable
$rocks->mset( new CustomIterator() );

// multiget
$iter = $rocks->mget(array('key1','key2','key3','key4'));
foreach($iter as $key => $value) {
    echo "$key => $value\n";
}

// isset
// fast check exist key
$rocks->keyExist('key1');
// fast check and retrive
$rocks->keyExist('key1', $val);

// incr
// incriment/decriment (integer counter)
$rocks->incr('key1');
$rocks->incr('key2', 5);
$rocks->incr('key2', -2);

// prefix iterator (key-value pairs by key-prefix)
$iter = $rocks->getall('pref:');
foreach($iter as $key => $value) {
    echo "$key => $value\n";
}
// or so (all key-value pairs):
foreach($rocks->getall() as $key => $value) {
    echo "$key => $value\n";
}

```

## License
BSD
