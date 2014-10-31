<?php

require dirname(__FILE__) . '/../../Rocks.php';
require dirname(__FILE__) . '/../../MgetIterator.php';
require dirname(__FILE__) . '/../../Response.php';


$db = new RocksServer\Client('localhost', 5533);


//echo var_dump(ScreenNav::pageNo('part')) .PHP_EOL;