--TEST--
Test multiget
--DESCRIPTION--
Testing $db->mget()
--FILEEOF--
<?php
require dirname(__FILE__) . '/../include/inc.php';


$db->set('key1', 'val1');
$db->set('key2', 'val2');
$db->set('key3', 'val3');


$db->mget(['key1','key2','key3'])->show();

echo PHP_EOL, PHP_EOL;
$db->mget(['key1','','key2','noexist','key3'])->show();

echo PHP_EOL, PHP_EOL;
$db->mget(['key1'])->show();

echo PHP_EOL, PHP_EOL, 'mget([]):';
$db->mget([])->show();


--EXPECT--
key1	=>	string(4) "val1"
key2	=>	string(4) "val2"
key3	=>	string(4) "val3"


key1	=>	string(4) "val1"
	=>	NULL
key2	=>	string(4) "val2"
noexist	=>	NULL
key3	=>	string(4) "val3"


key1	=>	string(4) "val1"


mget([]):