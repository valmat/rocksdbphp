/**
 *  MultiGetResult.h
 *  The iterator returned as the result of the method mget
 *  
 *  @author valmat <ufabiz@gmail.com>
 *  @github https://github.com/valmat/rocksdbphp
 */



namespace RocksDBPHP {

    // forward declaration
    class MultiGetIterator;

    /**
     *  A sample MultiGetResult class, that can be used to map string-to-strings
     */
    class MultiGetResult : 
                            public Php::Base, 
                            public Php::Countable, 
                            public Php::ArrayAccess,
                            public Php::Traversable
    {
    private:
        // Internally, a C++ unordered_map is used
        std::unordered_map<std::string, unsigned int> accessMap;
        
        // size of keys array
        unsigned int arrSize;
        
        // keys array
        std::vector<std::string> strKeys;
        
        // result values
        std::vector<std::string> values;
        
        // result statuses
        std::vector<rocksdb::Status> statuses;
    
    public:
        /**
         *  C++ constructor
         */
        MultiGetResult(const Php::Parameters &params, rocksdb::DB* db)
        {
            // Slice keys that only refers to string strKeys!
            std::vector<rocksdb::Slice> keys;
            // If param is array and its size is defined
            if(!params[0].isArray()) {
                unsigned int arrSize = params[0].size();
                keys.reserve(arrSize);
                strKeys.reserve(arrSize);
                accessMap.reserve(arrSize);
            }
            // iterate over param to filling keys
            unsigned int ind = 0;
            for(auto &iter: params[0])
            {
                strKeys.push_back( iter.second.stringValue() );
                keys.push_back( strKeys.back() );
                accessMap[strKeys.back()] = ind++;
            }
            
            // size of keys array
            arrSize = strKeys.size();
            // result values
            values.reserve(arrSize);
            // result statuses
            statuses.reserve(arrSize);
            
            // filling values
            statuses = db->MultiGet(rocksdb::ReadOptions(), keys, &values);
        }

        /**
         *  I do not need a default constructor, but PHP-CPP it requires (why?)
         */
        MultiGetResult() {}

        /**
         *  C++ destructpr
         */
        virtual ~MultiGetResult() {}
        
        //forbidden __construct
        virtual void __construct(void) {}
        
        /**
         *  Method from the Php::Countable interface that 
         *  @return long
         */
        virtual long count() override 
        { 
            // IT NOT WORK. need debug PHP-CPP
            Php::out << "count()=" << arrSize << std::endl;
            return arrSize; 
        }

        /**
         *  Method from the Php::ArrayAccess interface that is
         *  called to check if a certain key exists in the map
         *  @param  key
         *  @return bool
         */
        virtual bool offsetExists(const Php::Value &key) override
        {
            return accessMap.find(key.stringValue()) != accessMap.end();
        }
        
        /**
         *  Set a member
         *  @param  key
         *  @param  value
         */
        virtual void offsetSet(const Php::Value &key, const Php::Value &value) override
        {
            // ???
            // XXX this will not work as expected, you need to fix.
            values[accessMap[key.stringValue()]] = value.stringValue();
        }
        
        /**
         *  Retrieve a member
         *  @param  key
         *  @return value
         */
        virtual Php::Value offsetGet(const Php::Value &key) override
        {
            return values[accessMap[key.stringValue()]];
        }
        
        /**
         *  Remove a member
         *  This is an expensive operation. Better not to use it
         *  @param key
         */
        virtual void offsetUnset(const Php::Value &key) override
        {
            std::string k = key.stringValue();
            unsigned int ind = accessMap[k];
            values.erase(values.begin()+ind);
            statuses.erase(statuses.begin()+ind);
            strKeys.erase(strKeys.begin()+ind);
            accessMap.erase(k);
            --arrSize;
        }
        
        /**
         *  Get the iterator
         *  @return Php::Iterator
         */
        virtual Php::Iterator *getIterator() override;
    };

    /**
     *  A sample iterator class that can be used to iterate
     *  over a map of strings
     */
    class MultiGetIterator : public Php::Iterator
    {
    private:
        // keys array
        const std::vector<std::string>& _strKeys;
        
        // result values
        const std::vector<std::string>& _values;
        
        // result statuses
        const std::vector<rocksdb::Status>& _statuses;
        
        // position in internal array
        unsigned int _ind = 0;

        const unsigned int size;

    public:
        /**
         *  Constructor
         *  @param  object      The object that is being iterated over
         *  @param  map         The internal C++ map that is being iterated over
         */
        MultiGetIterator(
                            MultiGetResult *object,
                            const std::vector<std::string>& strKeys,
                            const std::vector<std::string>& values,
                            const std::vector<rocksdb::Status>& statuses
                        ) :
                        Php::Iterator(object),
                        _strKeys(strKeys),
                        _values(values),
                        _statuses(statuses),
                        size(strKeys.size())
        {}
            
        /**
         *  Destructor
         */
        virtual ~MultiGetIterator() {}
        
        /**
         *  Is the iterator on a valid position
         *  @return bool
         */
        virtual bool valid() override
        {
            return (_ind >=0 && _ind < size);
        }
        
        /**
         *  The value at the current position
         *  @return Value
         */
        virtual Php::Value current() override
        {
            if(_statuses[_ind].ok())
                return _values[_ind];
            else
                return nullptr;
        }
        
        /**
         *  The key at the current position
         *  @return Value
         */
        virtual Php::Value key() override
        {
            return _strKeys[_ind];
        }
        
        /**
         *  Move to the next position
         */
        virtual void next() override
        {
            ++_ind;
        }
        
        /**
         *  Rewind the iterator to the front position
         */
        virtual void rewind() override
        {
            _ind = 0;
        }
    };

    /**
     *  construct a new map iterator
     */
    Php::Iterator* MultiGetResult::getIterator()
    {
        // the PHP-CPP library will delete it when ready
        return new MultiGetIterator(this, strKeys, values, statuses);
    }


}   // End of namespace
