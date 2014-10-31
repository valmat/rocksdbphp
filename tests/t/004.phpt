--TEST--
Test keyExist
--DESCRIPTION--
Testing $db->keyExist()
--FILEEOF--
<?php
require dirname(__FILE__) . '/../include/inc.php';

# Test keyExist

$db->set('key1', 'val1');
var_export($db->get('key1'));
echo PHP_EOL;
var_export([$db->keyExist('key1', $value), $value]);
echo PHP_EOL;


$key = md5( mt_rand(555555, 999999) );
$db->set($key, 'value2');
var_export([$db->keyExist($key, $value), $value]);
echo PHP_EOL;
var_export([$db->keyExist('noexist', $value), $value]);
echo PHP_EOL;
var_export([$db->keyExist('', $value), $value]);
echo PHP_EOL;

--EXPECT--
'val1'
array (
  0 => true,
  1 => 'val1',
)
array (
  0 => true,
  1 => 'value2',
)
array (
  0 => false,
  1 => NULL,
)
array (
  0 => false,
  1 => NULL,
)