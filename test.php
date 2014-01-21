<?php
        
    header("Expires: Tue, 1 Jan 2000 00:00:00 GM");
    header("Last-Modified: " . gmdate("D, d M Y H:i:s") . " GMT");
    header("Cache-Control: no-store, no-cache, must-revalidate");
    header("Pragma: no-cache");
    header('Content-Type: text/html; charset=utf-8');
################################################################################
$memory_get_usage_start = (memory_get_usage()/1024);

function microtime_float(){
    list($usec, $sec) = explode(" ", microtime());
    return ((float)$usec + (float)$sec);
   }
$time_start = microtime_float();
################################################################################
    
    function s($a) {
	echo '<hr><pre>';
	var_export($a);
	echo '</pre><hr>';
    }
    
    //var_export(new RocksDB());
    
    
    
    $rocks = new RocksDB('/tmp/wwwdb');
    s($rocks);
    s($rocks->getStatus());
    
    //s($rocks->get());	s($rocks->getStatus());
    
    s($rocks->get('key1'));
    s($rocks->getStatus());

    //s($rocks->set());	s($rocks->getStatus());

    //s($rocks->set('key1'));	s($rocks->getStatus());

    s($rocks->set('key1', 'sdfsdf'));
    s($rocks->getStatus());

    s($rocks->get('key1'));
    s($rocks->getStatus());
    
    //unset($scr);
    
    
################################################################################

echo '<br>';
//echo '<hr>time: '.ceil( 1000*(microtime_float() - $time_start)*1000 ).' MicroSec<br>';
echo '<hr>time: '.ceil( (microtime_float() - $time_start)*1000 ).' mSec<br>';

echo '<hr>memory usage: '.ceil( (memory_get_usage()/1024-$memory_get_usage_start)*10)/10 .'Kb<br>';
echo '<hr>memory peak_usage: '.ceil( (memory_get_peak_usage()/1024-$memory_get_usage_start)*10)/10 .'Kb<br>';

?>
</body>
</html>