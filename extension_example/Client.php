<?php
/**
 *  Exemple of extend to extention
 *
 *  @author valmat <ufabiz@gmail.com>
 *  @github https://github.com/valmat/rocksdbphp
 */
namespace RocksServer\extension_example;

class Client extends \RocksServer\Client
{
    function __construct($host='localhost', $port = 5533) {
        parent::__construct($host, $port);
    }
    
    /**
      *  Backup deletion
      *  @return bool
      */
    public function bkDel($key) {
        return $this->httpPost('backup/del', $key )->isOk();
    }
    
    /**
      *  Multi deletions backups
      *  @return BoolIterator
      */
    public function bkMdel($keys) {
        return new \RocksServer\BoolIterator( $this->httpPost('backup/mdel', implode("\n", $keys) ) );
    }
    
    /**
      *  ping
      *  @return string
      */
    public function ping() {
        return $this->httpGet('ping')->read();
    }
    
    /**
      *  wstats -- wide statistic
      *
      *  Valid property names include:
      *
      *  "rocksdb.num-files-at-level<N>" - return the number of files at level <N>,
      *     where <N> is an ASCII representation of a level number (e.g. "0").
      *  "rocksdb.stats" - returns a multi-line string that describes statistics
      *     about the internal operation of the DB.
      *  "rocksdb.sstables" - returns a multi-line string that describes all
      *     of the sstables that make up the db contents.
      *
      *  Possible requests:
      *  http://127.0.0.1:5577/wstats?stats
      *  http://127.0.0.1:5577/wstats?sstables
      *  http://127.0.0.1:5577/wstats?num-files-at-level0
      *  http://127.0.0.1:5577/wstats?num-files-at-level1
      *  etc...
      *  @return string
      */
    public function wstats($key = NULL) {
        return is_null($key) ?
                        $this->httpGet('wstats')->raw() :
                        $this->httpGet('wstats', $key)->raw();
    }
    public function filesAtlevel($level) {
        return (int)$this->wstats('num-files-at-level' . $level);
    }
    public function sstables() {
        return $this->wstats('sstables');
    }
    
}