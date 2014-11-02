--TEST--
Test multi del
--DESCRIPTION--
Testing $db->mdel()
--FILEEOF--
<?php
require dirname(__FILE__) . '/../include/inc.php';

# Test mdel

$key1 = 'mdkey1';
$key2 = 'mdkey2';
$key3 = 'mdkey3';

$db->mset([$key1 => 'md:v1', $key2 => 'md:v2', $key3 => 'md:v3']);

$db->mget([$key1,$key2,$key3])->show();
echo PHP_EOL;

var_export($db->mdel([$key1,$key2,$key3]));
echo PHP_EOL,PHP_EOL;

$db->mget([$key1,$key2,$key3])->show();


--EXPECT--
[mdkey1]	=>	string(5) "md:v1"
[mdkey2]	=>	string(5) "md:v2"
[mdkey3]	=>	string(5) "md:v3"

true

[mdkey1]	=>	NULL
[mdkey2]	=>	NULL
[mdkey3]	=>	NULL