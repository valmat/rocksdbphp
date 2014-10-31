--TEST--
Test multi set
--DESCRIPTION--
Testing $db->mset()
--FILEEOF--
<?php
require dirname(__FILE__) . '/../include/inc.php';

$key1 = 'mskey1';
$key2 = 'mskey2';
$key3 = 'mskey3';

$db->del($key1);
$db->del($key2);
$db->del($key3);

$db->mget([$key1,$key2, $key3])->show();

echo PHP_EOL, PHP_EOL;
var_export($db->mset([$key1 => 'ms:v1', $key2 => 'ms:v2', $key3 => 'ms:v3']));

echo PHP_EOL, PHP_EOL;
$db->mget([$key1, $key2, $key3])->show();


--EXPECT--
mskey1	=>	NULL
mskey2	=>	NULL
mskey3	=>	NULL


true

mskey1	=>	string(5) "ms:v1"
mskey2	=>	string(5) "ms:v2"
mskey3	=>	string(5) "ms:v3"