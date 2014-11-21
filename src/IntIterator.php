<?php
/**
 *  Key iterator for integer values
 *
 *  @author valmat <ufabiz@gmail.com>
 *  @github https://github.com/valmat/rocksdbphp
 */
namespace RocksServer;

class IntIterator extends KeyIterator {
       
    /**
      *   Checks if current position is valid
      */
    protected function setValue() {
        $this->_val = (int)$this->_resp->read();
    }

    
}


