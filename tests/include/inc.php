<?php

require dirname(__FILE__) . '/../../src/Client.php';
require dirname(__FILE__) . '/../../src/MgetIterator.php';
require dirname(__FILE__) . '/../../src/Response.php';


$db = new RocksServer\RocksDB\Client('localhost', 5533);


//echo var_dump(ScreenNav::pageNo('part')) .PHP_EOL;