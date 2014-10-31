<?php

require dirname(__FILE__) . '/../../src/Rocks.php';
require dirname(__FILE__) . '/../../src/MgetIterator.php';
require dirname(__FILE__) . '/../../src/Response.php';


$db = new RocksServer\Client('localhost', 5533);


//echo var_dump(ScreenNav::pageNo('part')) .PHP_EOL;