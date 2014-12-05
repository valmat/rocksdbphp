<?php
/**
 *  API for RocksServer
 *  Multi get result iterator
 *
 *  @author valmat <ufabiz@gmail.com>
 *  @github https://github.com/valmat/rocksdbphp
 */
namespace RocksServer\RocksDB;

class MgetIterator implements \Iterator {
    
    /**
      *   Response object
      */
    protected $_resp = NULL;
    
    /**
      *   Current key and value
      */
    private $_key;
    private $_val;
    
    /**
      *   Iterator is valid
      */
    private $_valid;
    
    
    public function __construct(Response $resp) {
        $this->_resp = $resp;
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
        return $this->_key;
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
            return false;
        }
        $this->_key = substr($this->_resp->read(), 0, -1);
        $this->_val = $this->_resp->getValue();
        return true;
    }

    /**
      *   Checks if current position is valid
      */
    public function valid() {
        return $this->_valid;
    }
    
    /**
      *  Show debug info
      */
    public function show() {
        foreach($this as $key => $value) {
            echo "[$key]\t=>\t";
            var_dump($value);
        }
    }
    
}


