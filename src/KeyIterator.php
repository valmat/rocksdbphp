<?php
/**
 *  Key iterator
 *  The iterator for progressive output
 *
 *  @author valmat <ufabiz@gmail.com>
 *  @github https://github.com/valmat/rocksdbphp
 */
namespace RocksServer;

class KeyIterator implements \Iterator {
    
    /**
      *   Response object
      */
    protected $_resp;
    
    /**
      *   Current value
      */
    protected $_val;
    
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
        return NULL;
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
        $this->setValue();
    }

    /**
      *   Checks if current position is valid
      */
    public function valid() {
        return $this->_valid;
    }
        
    /**
      *   Set current value
      *   This method can be overloaded in derived classes
      */
    protected function setValue() {
        $this->_val = $this->_resp->read();
    }
    
    
    /**
      *  Show debug info
      */
    public function show() {
        foreach($this as $value) {
            var_dump($value);
        }
    }
    
}


