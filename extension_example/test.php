#!/usr/bin/php
<?php

require '../src/Rocks.php';
require '../src/MgetIterator.php';
require '../src/Response.php';
require '../src/KeyIterator.php';
require '../src/BoolIterator.php';

require 'Client.php';



$db = new RocksServer\extension_example\Client('localhost', 5533);

# Multi deletions backups
//var_export($db->bkDel(12));

# Multi deletions backups
//$db->bkMdel([11,13,15])->show();

# ping
//var_export($db->ping());


# wstats
/*
echo $db->wstats(), PHP_EOL, PHP_EOL;
echo $db->wstats('stats'), PHP_EOL, PHP_EOL;
echo $db->filesAtlevel(0), PHP_EOL, PHP_EOL;
echo $db->filesAtlevel(1), PHP_EOL, PHP_EOL;
echo $db->filesAtlevel(2), PHP_EOL, PHP_EOL;
echo $db->sstables(), PHP_EOL, PHP_EOL;
*/




//echo PHP_EOL, PHP_EOL;