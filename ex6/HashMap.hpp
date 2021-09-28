#ifndef HASHMAPEX6_HASHMAP_HPP
#define HASHMAPEX6_HASHMAP_HPP

/**
 * @file HashMap.hpp
 * @author  Avi Kogan <avi.kogan@mail.huji.ac.il>
 * @version 1.0
 * @date October 2020
 *
 * @brief implementation for template hashMap container.
 *
 */

// ------------------------------ includes ------------------------------

#include <list>
#include <map>
#include <algorithm>

// -------------------------- using definitions -------------------------

using std::pair;
using std::list;
using std::nothrow;

// --------------------- HashMap class declaration -----------------------

/**
 * @class HashMap
 * @brief The class represents a template HashMap container that get a template parameters for
 *        its key and value.
 */
template <typename KeyT, typename ValueT>
class HashMap
{

public:

    /**
     * @class ConstIterator
     * @brief The class implements the iterator of the template HashMap container.
     */
    class ConstIterator
    {

    public:

        /**
         * The iterator traits.
         */
        typedef pair<KeyT, ValueT> value_type;
        typedef const pair<KeyT, ValueT> &reference;
        typedef const pair<KeyT, ValueT> *pointer;
        typedef int difference_type;
        typedef std::forward_iterator_tag iterator_category;

        /**
         * Default Constructor.
         */
        ConstIterator() : _curBucket(nullptr), _endOfBuckets(nullptr) {}

        /**
         * Init the iterator to point to the first pair in the hash table.
         * @param startBuckets the address of the first index in the hashTable.
         * @param endBuckets the address of the index after the last index in the hashTable.
         */
        ConstIterator(list<pair<KeyT, ValueT>> *startBuckets, list<pair<KeyT, ValueT>>
                      *endBuckets) : _curBucket(startBuckets), _endOfBuckets(endBuckets)
        {
            while(_curBucket != _endOfBuckets)
            {
                if(!_curBucket->empty())
                {
                    _curDataIt = _curBucket->begin();
                    return;
                }
                _curBucket++;
            }
        }

        /**
         * @return the current pair the iterator points to.
         * @throw std::out_of_range if it's the end throws exception.
         */
        reference operator*() const noexcept(false)
        {
            if(_curBucket == _endOfBuckets)
            {
                throw std::out_of_range("The iterator reached the end.");
            }
            return *_curDataIt;
        }

        /**
         * @return pointer to the refernce returned from operator*().
         * @throw std::out_of_range if it's the end throws exception.
         */
        pointer operator->() noexcept(false)
        {
            return &(operator*());
        }

        /**
         * Move the iterator to the next pair in the table.
         * @return the iterator after the increment.
         * @throw std::out_of_range if it's the end throws exception.
         */
        ConstIterator& operator++()
        {
            if(_curBucket == _endOfBuckets)
            {
                throw std::out_of_range("The iterator reached the end.");
            }

            if(_curDataIt != _curBucket->end())
            {
                _curDataIt++;
                if(_curDataIt != _curBucket->end())
                {
                    return *this;
                }// else search in next bucket.
            }

            while(++_curBucket != _endOfBuckets)
            {
                if(!_curBucket->empty())
                {
                    _curDataIt = _curBucket->begin();
                    return *this;
                }
            }
            // no more elements.
            return *this;
        }

        /**
         * Move the iterator to the next pair in the table.
         * @return the iterator after the increment.
         * @throw std::out_of_range if it's the end throws exception.
         */
        ConstIterator operator++(int)
        {

            ConstIterator tmp = *this;
            ++(*this);
            return tmp;
        }

        /**
         * @param rhs the iterator compared to.
         * @return true if both lhs and rhs pointing to the same pair, otherwise false.
         */
        bool operator==(const ConstIterator& rhs) const
        {
            if(this->_curBucket == rhs._curBucket)
            {
                if(_curBucket == _endOfBuckets || _curDataIt == rhs._curDataIt)
                {
                    return true;
                }
            }
            return false;
        }

        /**
         * @param rhs the iterator compared to.
         * @return false if both lhs and rhs pointing to the same pair, otherwise true.
         */
        bool operator!=(const ConstIterator& rhs) const
        {
            return !(*this == rhs);
        }

    private:
        /**
         * The address to the current bucket that the iterator returning it's pairs.
         */
        list<pair<KeyT, ValueT>>* _curBucket;

        /**
         * The address of the index after the last bucket index.
         */
        list<pair<KeyT, ValueT>>* _endOfBuckets;

        /**
         * The iterator of the list in _curBucket, pointing to the current pair to return.
         */
        typename list<pair<KeyT, ValueT>>::const_iterator _curDataIt;
    };

    /**
     * typedef for the STL convention.
     */
    typedef ConstIterator iterator;

    /**
     * typedef for the STL convention.
     */
    typedef ConstIterator const_iterator;

    /**
     * Default constructor, create empty table with DEFAULT_CAPACITY capacity.
     */
    HashMap() : _hashTable(new list<pair<KeyT, ValueT>>[DEFAULT_CAPACITY]), _capacity
            (DEFAULT_CAPACITY), _size(EMPTY_SIZE){ }

    /**
     * Initialize table with the key and value in the order they appear in the given input
     * iterator, if there is more than one of some key, the last value will stay.
     * @tparam KeysInputIterator the type of the keys iterator.
     * @tparam ValuesInputIterator the type of the values iterator.
     * @param keysBegin the start of the keys to insert the table.
     * @param keysEnd the end of the keys to insert the table.
     * @param valuesBegin the start of the values to insert the table.
     * @param valuesEnd the end of the values to insert the table.
     * @throw std::exception if the the number of keys not equal to the number of values.
     */
    template <typename KeysInputIterator, typename ValuesInputIterator>
    HashMap(const KeysInputIterator keysBegin, const KeysInputIterator keysEnd,
            const ValuesInputIterator valuesBegin, const ValuesInputIterator valuesEnd)
    noexcept(false);

    /**
     * Copy constructor, deep copy for the table of rhs.
     * @param rhs the HashMap to copy from.
     */
    HashMap(const HashMap& rhs);

    /**
     * Class destructor, delete the table.
     */
    ~HashMap();

    /**
     * Deep copy for the table of rhs, deletes the prev table.
     * @param rhs the HashMap to copy from.
     * //todo add throw for bad_alloc
     */
    HashMap &operator=(const HashMap& rhs);

    /**
     * @param key the key to return the it's value.
     * @return copy of the value of the given key in the table, if it not exist return the
     *         default value of VaultT
     */
    ValueT operator[](const KeyT& key) const noexcept;

    /**
     * @param key the key to return the it's value.
     * @return refernce of the value of the given key in the table, if it not exist return the
     *         default value of VaultT
     */
    ValueT &operator[](const KeyT& key) noexcept;

    /**
     * @param rhs the HashMap to compare to.
     * @return true if both have the same capacity, size and the same pairs, otherwise false.
     */
    bool operator==(const HashMap& rhs) const noexcept;

    /**
     * @param rhs the HashMap to compare to.
     * @return false if both have the same capacity, size and the same pairs, otherwise true.
     */
    bool operator!=(const HashMap& rhs) const noexcept { return !(*this == rhs); }

    /**
     * @return the number of elements in the table.
     */
    size_t size() const noexcept {return _size; }

    /**
     * @return the capacity of the table.
     */
    size_t capacity() const noexcept { return _capacity; }

    /**
     * @return true if the table is empty, otherwise false.
     */
    bool empty() const noexcept { return _size == EMPTY_SIZE; }

    /**
     * @param keyToFind the key to check if its exist in the table.
     * @return true if the key exist, itherwise false.
     */
    bool contains_key(const KeyT& keyToFind) const noexcept;

    /**
     * Insert to the table the given key with the given vakue if the key dosen't exist before.
     * @param key the key to insert.
     * @param val the value to insert.
     * @return true if the insertion completed, false if the key was already in the table or the
     *         allocation for the new pair failed.
     */
    bool insert(const KeyT& key, const ValueT& val);

    /**
     * Erase the given key from the table.
     * @param key the key to erase.
     * @return true if the erased seccessfully, false if the key wasn't in the table or the
     *         allocation for the resized if needed failed.
     */
    bool erase(const KeyT& key);

    /**
     * @param key the key to return it's value.
     * @return the value of the key.
     * @throw std::out_of_range if the ley dosen't exist in the table.
     */
    const ValueT& at(const KeyT& key) const noexcept(false);

    /**
     * @param key the key to return it's value.
     * @return the value of the key.
     * @throw std::out_of_range if the ley dosen't exist in the table.
     */
    ValueT &at(const KeyT& key) noexcept(false);

    /**
     * @return the current load factor of the table.
     */
    double load_factor() const noexcept {return (double) _size / _capacity; }

    /**
     * @param key the key to check it's bucket.
     * @return the size of the bucket the ket contained in.
     * @throw std::exception() if the key dosen't exist in the table.
     */
    size_t bucket_size(const KeyT& key) const noexcept(false)
    {
        return contains_key(key) ?_hashTable[_hash(key)].size() : throw std::exception();
    }

    /**
    * @param key the key to return it's bucket number.
    * @return the bucket number that the given key contained in.
    * @throw std::exception() if the key dosen't exist in the table.
    */
    size_t bucket_index(const KeyT& key) const noexcept(false)
    {
        return contains_key(key) ? _hash(key) : throw std::exception();
    }

    /**
     * clear all the buckets in the table, no change in the capacity.
     */
    void clear() noexcept;

    /**
     * @return const iterator to the first element in the table.
     */
    const_iterator begin() noexcept { return { &_hashTable[0], &_hashTable[_capacity] }; }

    /**
     * @return const iterator to the first element in the table.
     */
    const_iterator begin() const noexcept { return { &_hashTable[0], &_hashTable[_capacity] }; }

    /**
     * @return const iterator to the first element in the table.
     */
    const_iterator cbegin() const noexcept { return { &_hashTable[0], &_hashTable[_capacity] }; }

    /**
     * @return const iterator to the index after the last index in the table.
     */
    iterator end() noexcept { return { &_hashTable[_capacity], &_hashTable[_capacity] }; }

    /**
     * @return const iterator to the index after the last index in the table.
     */
    const_iterator end() const noexcept
    {
        return { &_hashTable[_capacity], &_hashTable[_capacity]};
    }

    /**
     * @return const iterator to the index after the last index in the table.
     */
    const_iterator cend() const noexcept
    {
        return { &_hashTable[_capacity], &_hashTable[_capacity]};
    }

private:

    /**
     * Represent the lower load factor parameter to rehash the table to lower capacity.
     */
    static const double LOWER_LOAD_FACTOR;

    /**
     * Represent the upper load factor parameter to rehash the table to lower capacity.
     */
    static const double UPPER_LOAD_FACTOR;

    /**
     * Represent the number of elements in empty hashMap.
     */
    static const size_t EMPTY_SIZE ;

    /**
     * Represent the default capacity of hashMap.
     */
    static const size_t DEFAULT_CAPACITY ;

    /**
     * Represent the factor the capacity changed according to.
     */
    static const size_t CAPACITY_FACTOR ;

    /**
     * @param key the ket to hash
     * @return the hash value of the given key according to the current _capacity.
     */
    size_t _hash(const KeyT& key) const noexcept
    {
        return std::hash<KeyT>()(key) & (_capacity - 1);
    }

    /**
     * rehash the pairs from given table with it's size to the current _hashtable.
     * @param prevTable the table to rehash it's pairs to the _hashtable.
     * @param prevCapacity the capacity of 'prevTable'.
     */
    void _reHashPrevToCurrent(list<pair<KeyT, ValueT>> *prevTable, size_t prevCapacity);

    /**
     * Doesn't check for duplicates, check if adding the key require to enlarge the capacity, if
     * need - enlarge, than rehash the table to new one, at the end add the new pair to the needed
     * bucket as the first element in the bucket list.
     * @param key the key to add.
     * @param val the value to add.
     * @throw bad_alloc if the table enlarging failed.
     */
    void _addFirstToBucket(const KeyT& key, const ValueT& val);

    /**
     * Pointer to the table of the hashMap, containing list of pair<KeyT, ValueT>.
     */
    list<pair<KeyT, ValueT>> *_hashTable;

    /**
     * The current capacity of the table.
     */
    size_t _capacity;

    /**
     * The current number of elements in the table.
     */
    size_t _size;

    /**
     * Value to return if the allocation failed or value not exist in operator[].
     */
    ValueT _defReturnValue;
};


template<typename KeyT, typename ValueT>
const double HashMap<KeyT, ValueT>::LOWER_LOAD_FACTOR = 0.25;

template<typename KeyT, typename ValueT>
const double HashMap<KeyT, ValueT>::UPPER_LOAD_FACTOR = 0.75;

template<typename KeyT, typename ValueT>
const size_t HashMap<KeyT, ValueT>::EMPTY_SIZE = 0;

template<typename KeyT, typename ValueT>
const size_t HashMap<KeyT, ValueT>::DEFAULT_CAPACITY = 16;

template<typename KeyT, typename ValueT>
const size_t HashMap<KeyT, ValueT>::CAPACITY_FACTOR = 2;

template<typename KeyT, typename ValueT>
template<typename KeysInputIterator, typename ValuesInputIterator>
HashMap<KeyT, ValueT>::HashMap(const KeysInputIterator keysBegin,
                               const KeysInputIterator keysEnd,
                               const ValuesInputIterator valuesBegin,
                               const ValuesInputIterator valuesEnd) noexcept(false)

{
    if(std::distance(keysBegin, keysEnd) != std::distance(valuesBegin, valuesEnd))
    {
        throw std::exception(); // not the same length of the iterators
    }

    _hashTable = new list<pair<KeyT, ValueT>>[DEFAULT_CAPACITY];
    _capacity = DEFAULT_CAPACITY;
    _size = EMPTY_SIZE;
    auto curKeyIt = keysBegin;
    auto curValIt = valuesBegin;

    while(curKeyIt != keysEnd)
    {
        operator[](*curKeyIt) = *curValIt;
        curKeyIt++;
        curValIt++;
    }
}

template<typename KeyT, typename ValueT>
HashMap<KeyT, ValueT>::HashMap(const HashMap &rhs) : _hashTable(new list<pair<KeyT, ValueT>>[rhs
        ._capacity]), _capacity(rhs._capacity), _size(rhs._size)
{
    for(size_t i = 0; i < _capacity; ++i)
    {
        for(auto entry : rhs._hashTable[i])
        {
            _hashTable[i].push_front(pair<KeyT, ValueT>(entry.first, entry.second));
        }
    }
}

template<typename KeyT, typename ValueT>
HashMap<KeyT, ValueT>::~HashMap()
{
    delete[] _hashTable;
}

template<typename KeyT, typename ValueT>
HashMap<KeyT, ValueT> &HashMap<KeyT, ValueT>::operator=(const HashMap &rhs)
{
    if(this == &rhs)
    {
        return *this;
    }

    list<pair<KeyT, ValueT>>* prevTable = _hashTable;

    try
    {
        _hashTable = new list<pair<KeyT, ValueT>>[rhs.capacity()];
        _size = rhs.size();
        _capacity = rhs.capacity();
        delete[] prevTable;
    }
    catch (const std::bad_alloc& e)
    {
        // alloc failed, return to previous table.
        _hashTable = prevTable;
        return *this;
    }


    for(int i = 0; i < _capacity; ++i)
    {
        for(auto entry : rhs._hashTable[i])
        {
            _hashTable[i].push_back(entry);
        }
    }
    return *this;
}

template<typename KeyT, typename ValueT>
ValueT HashMap<KeyT, ValueT>::operator[](const KeyT &key) const noexcept
{
    size_t keysCell = _hash(key);
    for(const auto& entry : _hashTable[keysCell])
    {
        if(entry.first == key)
        {
            return entry.second;
        }
    }
    return _defReturnValue;
}

template<typename KeyT, typename ValueT>
ValueT &HashMap<KeyT, ValueT>::operator[](const KeyT &key) noexcept
{
    size_t keysCell = _hash(key);
    for(auto& entry : _hashTable[keysCell])
    {
        if(entry.first == key)
        {
            return entry.second;
        }
    }
    try{
        _addFirstToBucket(key, ValueT());
        return _hashTable[_hash(key)].begin()->second;
    }catch (const std::bad_alloc& e){
        //enlarge failed.
        return _defReturnValue;
    }

}

template<typename KeyT, typename ValueT>
bool HashMap<KeyT, ValueT>::operator==(const HashMap &rhs) const noexcept
{
    if(_size == rhs.size() && _capacity == rhs._capacity)
    {
        for(size_t i = 0; i < _capacity; ++i)
        {
            for(const auto& curPair : _hashTable[i])
            {
                if(find(rhs._hashTable[i].begin(), rhs._hashTable[i].end(), pair<KeyT, ValueT>
                   (curPair.first, curPair.second)) == rhs._hashTable[i].end())
                {
                    return false;
                }
            }
        }
        //no false during the for.
        return true;
    }
    return false;
}

template<typename KeyT, typename ValueT>
bool HashMap<KeyT, ValueT>::contains_key(const KeyT &keyToFind) const noexcept
{
    size_t keysCell = _hash(keyToFind);
    for(const auto& entry : _hashTable[keysCell])
    {
        if(entry.first == keyToFind)
        {
            return true;
        }
    }
    return false;
}

template<typename KeyT, typename ValueT>
bool HashMap<KeyT, ValueT>::insert(const KeyT &key, const ValueT &val)
{
    if(!contains_key(key))
    {
        try
        {
            _addFirstToBucket(key, val);
            return true;
        }
        catch (const std::bad_alloc& e)
        {
            //enlarge failed.
            return false;
        }
    }
    return false;
}

template<typename KeyT, typename ValueT>
bool HashMap<KeyT, ValueT>::erase(const KeyT &key)
{
    size_t bucketInd = _hash(key);
    for(auto it : _hashTable[bucketInd])
    {
        if(it.first == key)
        {
            _hashTable[bucketInd].remove(it);
            _size--;
            double newLoadFactor = (double)_size / _capacity;
            if(newLoadFactor < LOWER_LOAD_FACTOR)
            {
                list<pair<KeyT, ValueT>>* prevTable = _hashTable;
                size_t prevCapacity = _capacity;
                _capacity = _capacity / CAPACITY_FACTOR;
                try
                {
                    _hashTable = new list<pair<KeyT, ValueT>>[_capacity];
                } catch (const std::bad_alloc& e)
                {
                    //the allocation failed, return to the table before.
                    _capacity = _capacity * CAPACITY_FACTOR;
                    _size++;
                    _hashTable = prevTable;
                    return false;
                }
                _reHashPrevToCurrent(prevTable, prevCapacity);
            }
            return true;
        }
    }
    return false;
}

template<typename KeyT, typename ValueT>
const ValueT& HashMap<KeyT, ValueT>::at(const KeyT &key) const noexcept(false)
{
    size_t keysCell = _hash(key);
    for(const auto& entry : _hashTable[keysCell])
    {
        if(entry.first == key)
        {
            return entry.second;
        }
    }
    throw std::out_of_range("key not found");
}

template<typename KeyT, typename ValueT>
ValueT &HashMap<KeyT, ValueT>::at(const KeyT &key) noexcept(false)
{
    size_t keysCell = _hash(key);
    for(auto& entry : _hashTable[keysCell])
    {
        if(entry.first == key)
        {
            return entry.second;
        }
    }
    throw std::out_of_range("key not found");
}

template<typename KeyT, typename ValueT>
void HashMap<KeyT, ValueT>::clear() noexcept
{
    for(size_t i = 0; i < _capacity; ++i)
    {
        _hashTable[i].clear();
    }
    _size = EMPTY_SIZE;
}


// ---------------------- private methods implementations -------------------------

template<typename KeyT, typename ValueT>
void HashMap<KeyT, ValueT>::_addFirstToBucket(const KeyT &key, const ValueT &val)
{
    double newLoadFactor = (double)(_size + 1) / _capacity;
    if(newLoadFactor > UPPER_LOAD_FACTOR)
    {
        //enlarge
        size_t prevCapacity = _capacity;
        list<pair<KeyT, ValueT>>* prevTable = _hashTable;
        _capacity *= CAPACITY_FACTOR;
        try
        {
            _hashTable = new list<pair<KeyT, ValueT>>[_capacity];
            _reHashPrevToCurrent(prevTable, prevCapacity);
        } catch (const std::bad_alloc& e)
        {
            //enlarge failed
            _capacity /= CAPACITY_FACTOR;
            _hashTable = prevTable;
            throw e;
        }
    }

    _hashTable[_hash(key)].push_front(pair<KeyT, ValueT>(key, val));
    _size++;
}

template<typename KeyT, typename ValueT>
void HashMap<KeyT, ValueT>::_reHashPrevToCurrent(list<pair<KeyT, ValueT>> *prevTable,
                                                 size_t prevCapacity)
{
    for(size_t i = 0; i < prevCapacity; ++i)
    {
        for(auto entry : prevTable[i])
        {
            //rehash list entries to the current table, direct insert to avoid contains check.
            _hashTable[_hash(entry.first)].push_front(entry);
        }
    }
    delete[] prevTable; //free the table
}

#endif //HASHMAPEX6_HASHMAP_HPP
