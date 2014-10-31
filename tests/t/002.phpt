--TEST--
Test set #2
--DESCRIPTION--
Testing $db->set()
--FILE--
<?php
require dirname(__FILE__) . '/../include/inc.php';


$k = 'test:set:2' ;
$v = 'v:6a9aeddfc689c1d0e3b9ccc3ab651bc5';

var_export($db->set($k, $v));
echo PHP_EOL;
var_export($db->get($k));

--EXPECT--
true
'v:6a9aeddfc689c1d0e3b9ccc3ab651bc5'