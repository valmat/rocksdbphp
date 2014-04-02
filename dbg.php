<?php
        
   
    function s($a, $msg = NULL) {
	if($msg) {
	    echo  PHP_EOL, "\x1b[1;31m$msg:\x1b[0m";
	}
	echo  PHP_EOL;
	var_export($a);
    }
    function printIterable($obj, $msg = NULL) {
	if($msg) {
	    echo  PHP_EOL, "\x1b[1;31m$msg:\x1b[0m";
	}
	foreach($obj as $k => $v) {
	    echo "\x1b[1;34m\n rez[$k] = $v\x1b[0m";
	}
	echo PHP_EOL;
    }
    

    $rocks = new RocksDB('/tmp/rockstest');
    
    
    
    //s($rocks);
    //s($rocks->getStatus());
    
    //s($rocks->get());	s($rocks->getStatus());
    
    s($rocks->get('key1'), 'rocks->get(key1)');
    s($rocks->getStatus());
    
    s($rocks->get('NoExistingKey'), 'rocks->get(NoExistingKey)');
    s($rocks->getStatus());

    //s($rocks->set());	s($rocks->getStatus());
    //s($rocks->set('key1'));	s($rocks->getStatus());

    s($rocks->set('key2', 'Привет'));
    s($rocks->getStatus());

    
    s($rocks->mset( array('skey1'=>'val1','skey2'=>'val2','skey3'=>'val3','skey4'=>'val4') ), 'mSet');
    s($rocks->getStatus());
    
    //exit;
    s($rocks->mgetArray((object)array('skey1','skey2','skey3','skey4','skey5')), 'mgetArray');
    s($rocks->getStatus());

    $rez = $rocks->mget(array('skey1','skey2','skey5','skey3','skey4'));
    s($rez, 'mGet');
    //s($rez['skey2'], '$rez[skey2]');
    s(count($rez), 'count($rez)');
    
    printIterable($rez);
    
    s($rocks->getStatus());
    
    
    
    s($rocks->del('skey2'));
    s($rocks->getStatus());
    
    s($rocks->del('skey2'));
    s($rocks->getStatus());
    
    s($rocks->mdel(  array('skey1','skey2','skey3')  ), 'mdel');
    s($rocks->getStatus());
    
    printIterable(
		    $rocks->mget( array('skey1','skey2','skey3','skey4','skey5') ),
		    'mgetArray'
		);
    
    s($rocks->getStatus());
    
    
    s($rocks->isset('skey3'), "rocks->isset('skey3')");
    s($rocks->isset('skey4'), "rocks->isset('skey4')");


    s($rocks->isset('skey3', $val), "rocks->isset('skey3')");
    s($val, "isset ---> val");
    s($rocks->isset('skey4', $val), "rocks->isset('skey4')");
    s($val, "isset ---> val");
    
    //s(isset($rocks['skey3']), "isset(rocks['skey3'])");
    //s(isset($rocks['skey4']), "isset(rocks['skey4'])");
    


    
