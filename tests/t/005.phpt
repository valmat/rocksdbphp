--TEST--
Test del
--DESCRIPTION--
Testing $db->del()
--FILEEOF--
<?php
require dirname(__FILE__) . '/../include/inc.php';

# Test del

var_export($db->set('test1', 'val1'));
echo PHP_EOL;
var_export($db->get('test1'));
echo PHP_EOL;
var_export($db->del('test1'));
echo PHP_EOL;
var_export($db->get('test1'));
echo PHP_EOL;


var_export($db->get('noexist'));
echo PHP_EOL;
var_export($db->del('noexist'));
echo PHP_EOL;
var_export($db->get('noexist'));


--EXPECT--
true
'val1'
true
NULL
NULL
true
NULL