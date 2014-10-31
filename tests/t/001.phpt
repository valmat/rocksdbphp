--TEST--
Test set #1
--DESCRIPTION--
Testing $db->set()
--FILE--
<?php
require dirname(__FILE__) . '/../include/inc.php';

var_export($db->set('empty', ''));
echo PHP_EOL;
var_export($db->set('key1', 'val1'));
echo PHP_EOL;
var_export($db->set('key4', "val4\tval4-1\nval4-2\nval4-3\nval4-4"));
echo PHP_EOL;
var_export($db->set('key4', 'val4'));
echo PHP_EOL;
var_export($db->get('key1'));

--EXPECT--
true
true
true
true
'val1'