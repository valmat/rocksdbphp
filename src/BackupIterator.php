<?php
/**
 *  Backups iterator
 *
 *  @author valmat <ufabiz@gmail.com>
 *  @github https://github.com/valmat/rocksdbphp
 */
namespace RocksServer;

class BackupInfo
{
    /**
      *   Backup ID
      */
    private $_id;
    
    /**
      *   When backup was created
      */
    private $_time;
    
    /**
      *   Backup in bytes
      */
    private $_size;
    
    public function __construct($id, $time, $size) {
        $this->_time = $time;
        $this->_id   = $id;
        $this->_size = $size;
    }
    
    public function id() {
        return $this->_id;
    }
    public function time() {
        return $this->_time;
    }
    public function size() {
        return $this->_size;
    }
}


class BackupIterator implements \Iterator, \Countable  {
    
    /**
      *   Response object
      */
    private $_resp;
    
    /**
      *   Current value
      */
    private $_val;
    
    /**
      *   Iterator is valid
      */
    private $_valid;
    
    /**
      *   Iterator is valid
      */
    private $_size;
    
    
    public function __construct(Response $resp) {
        $this->_resp = $resp;
        $this->_size = (int)$resp->read();
    }
    
    /**
      *   Backups count
      */
    public function size() {
        return $this->_size;
    }
    
    /**
      *   Backups count
      */
    public function count()
    {
        return $this->_size;
    } 
    
    /**
      *   Return the current element
      */
    public function current() {
        return $this->_val;
    }

    /**
      *   Return the key of the current element
      */
    public function key() {
        return $this->_val->id();
    }
    
    /**
      *  Rewind the Iterator to the first element 
      */
    public function rewind() {
        $this->next();
    }

    /**
      *   Move forward to next element
      */
    public function next() {
        if( !($this->_valid = $this->_resp->isValid() ) ){
            return;
        }
        $id   = (int)substr($this->_resp->read(), 4);
        $time = (int)substr($this->_resp->read(), 11);
        $this->_resp->read();
        $size = (int)substr($this->_resp->read(), 6);
        $this->_resp->read();
        
        $this->_val = new BackupInfo($id, $time, $size);
    }

    /**
      *   Checks if current position is valid
      */
    function valid() {
        return $this->_valid;
    }
        
    
    /**
      *  Show debug info
      */
    public function show() {
        foreach($this as $key => $value) {
            echo "\n[$key]:\n";
            var_export($value);
        }
    }
    
}


