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
    
    function s($rocks) {
	echo '<hr><pre>';
	var_export($rocks);
	echo '</pre><hr>';
    }
    
    //var_export(new RocksDB());
    
    
    
    $rocks = new RocksDB('/tmp/wwwdb');

    //$rocks->del('cntr1');
    s($rocks->getStatus());
    $rocks->incr('cntr1');
    s($rocks->getStatus());
    $rocks->incr('cntr2',-2);
    
    $rocks->set('cntr3', -10);
    $rocks->incr('cntr3');
    
    s($rocks->mget(array('cntr1','cntr2','cntr3','cntr4')));
    s($rocks->getStatus());
    



   
   
   
   
   
   
   
   
  /* 
class myIterator implements Iterator {
    private $position = 0;
    private $rocksrray = array(
        "firstelement",
        "secondelement",
        "lastelement",
    );  

    public function __construct() {
        $this->position = 0;
    }

    function rewind() {
        var_dump(__METHOD__);
        $this->position = 0;
    }

    function current() {
        var_dump(__METHOD__);
        return $this->array[$this->position];
    }

    function key() {
        var_dump(__METHOD__);
        return $this->position;
    }

    function next() {
        var_dump(__METHOD__);
        ++$this->position;
    }

    function valid() {
        var_dump(__METHOD__);
        return isset($this->array[$this->position]);
    }
}

$it = new myIterator;

foreach($it as $key => $value) {
    var_dump($key, $value);
    echo "\n";
}
    */
    
    
################################################################################

echo '<br>';
//echo '<hr>time: '.ceil( 1000*(microtime_float() - $time_start)*1000 ).' MicroSec<br>';
echo '<hr>time: '.ceil( (microtime_float() - $time_start)*1000 ).' mSec<br>';

echo '<hr>memory usage: '.ceil( (memory_get_usage()/1024-$memory_get_usage_start)*10)/10 .'Kb<br>';
echo '<hr>memory peak_usage: '.ceil( (memory_get_peak_usage()/1024-$memory_get_usage_start)*10)/10 .'Kb<br>';

?>
</body>
</html>