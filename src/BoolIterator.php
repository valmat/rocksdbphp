<?php
/**
 *  Key iterator for boolean values
 *
 *  @author valmat <ufabiz@gmail.com>
 *  @github https://github.com/valmat/rocksdbphp
 */
namespace RocksServer\RocksDB;

class BoolIterator extends KeyIterator {
       
    /**
      *   Checks if current position is valid
      */
    protected function setValue() {
        $this->_val = $this->_resp->isOk();
    }

    
}


