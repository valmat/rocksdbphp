--TEST--
Test incriment
--DESCRIPTION--
Testing $db->incr()
--FILEEOF--
<?php
require dirname(__FILE__) . '/../include/inc.php';

# Test incr
$db->del('incrtest');

var_export($db->get('incrtest'));
echo PHP_EOL;

var_export($db->incr('incrtest'));
echo PHP_EOL;

var_export($db->get('incrtest'));
echo PHP_EOL;

var_export($db->incr('incrtest', 7));
echo PHP_EOL;

var_export($db->get('incrtest'));
echo PHP_EOL;

var_export($db->incr('incrtest', -2));
echo PHP_EOL;

var_export($db->get('incrtest'));
echo PHP_EOL;

--EXPECT--
NULL
true
'1'
true
'8'
true
'6'