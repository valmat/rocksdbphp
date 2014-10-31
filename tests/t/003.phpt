--TEST--
Test get #1
--DESCRIPTION--
Testing $db->get()
--FILEEOF--
<?php
require dirname(__FILE__) . '/../include/inc.php';

$db->set('key1', 'val1');
var_export($db->get('key1'));
echo PHP_EOL;
var_export($db->get('noexist'));
echo PHP_EOL;
var_export($db->get(''));

--EXPECT--
'val1'
NULL
NULL