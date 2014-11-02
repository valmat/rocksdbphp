--TEST--
Test prefix iterator
--DESCRIPTION--
Testing $db->prefit()
--FILEEOF--
<?php
require dirname(__FILE__) . '/../include/inc.php';

# Test prefit (prefix iterator)

$prefix = 'pref-test:';
$key1 = $prefix . 'key1';
$key2 = $prefix . 'key2';
$key3 = $prefix . 'key3';

$db->mset([$key1 => 'value:1', $key2 => 'value:2', $key3 => 'value:3']);
$db->prefit($prefix)->show();
echo PHP_EOL;
$prefix .= "~";
$db->prefit($prefix)->show();


--EXPECT--
[pref-test:key1]	=>	string(7) "value:1"
[pref-test:key2]	=>	string(7) "value:2"
[pref-test:key3]	=>	string(7) "value:3"

