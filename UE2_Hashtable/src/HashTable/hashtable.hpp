#ifndef hashtable_hpp
#define hashtable_hpp

#include <cassert>
#include <vector>
#include <list>
#include <iostream>
#include <iterator>
#include <iomanip>

using namespace std;

template<typename V, typename H, typename C>
class hashtable;

template<typename V, typename H, typename C>
std::ostream & operator << (std::ostream & os, const hashtable<V, H, C> &ht);

template<typename V, typename H, typename C>
class hashtable {
	friend std::ostream & operator << <V, H, C>(std::ostream & os, const hashtable<V, H, C> &ht);

public:
	typedef V value_type;
	typedef H hash_function_type;
	typedef C key_equal_function_type;
	typedef unsigned int size_t;
	typedef value_type const * const_pointer;
	typedef value_type const & const_reference;
	typedef ptrdiff_t     difference_type;
	typedef const_pointer      pointer;
	typedef const_reference    reference;
	typedef size_t        size_type;

	hashtable(size_t n_buckets = 10,
		hash_function_type hasher = hash<V>(),
		key_equal_function_type equals = equal_to<V>(),
		double max_load_factor = 0.8,
		double min_load_factor = 0.2)
		: _capacity(n_buckets), _hasher(hasher), _equals(equals), _maxLoadFactor(max_load_factor), _minLoadFactor(min_load_factor)
	{
		_currentSize = 0;
		rehash(_capacity);
	}

	virtual ~hashtable() {}
	
	void insert(const V &value);
	void erase(const V &value);
	bool contains(const V &value) const;
	void rehash(size_t new_n_buckets);
	double load_factor() const;
	size_t size() const;
	size_t capacity();
	bool empty() const;
	bool operator == (const hashtable &other) const;

	typedef iterator <bidirectional_iterator_tag,
		value_type,
		difference_type,
		const_pointer,
		const_reference> iterator_base;

	class const_iterator : public iterator_base {
	public:
		typedef typename iterator_base::difference_type   difference_type;
		typedef typename iterator_base::iterator_category iterator_category;
		typedef typename iterator_base::pointer           pointer;
		typedef typename iterator_base::reference         reference;
		typedef typename iterator_base::value_type        value_type;

		bool operator == (const_iterator const & rhs) const;
		bool operator != (const_iterator const & rhs) const;

		reference operator *  () const;
		pointer   operator -> () const;

		const_iterator & operator ++ ();
		const_iterator & operator -- ();

		const_iterator operator ++ (int);
		const_iterator operator -- (int);

	};

	typedef const_iterator iterator;

	const_iterator begin() const;
	const_iterator end() const;

	iterator cbegin();
	iterator cend();
	const_iterator cbegin() const;
	const_iterator cend() const;
	
private : 
	vector<list<V>> _table;
	size_t _capacity;
	size_t _currentSize;
	double _minLoadFactor;
	double _maxLoadFactor;
	hash_function_type _hasher;
	key_equal_function_type _equals;
	size_t getHashedValue(const V& value);
};

template<typename V, typename H, typename C>
ostream & operator << (ostream & os, const hashtable<V, H, C> &ht){
	for (auto list : ht._table){
		for (auto element : list){
			os << element << endl;
		}
	}
	return os;
}

template <typename V, typename H, typename C>
bool hashtable<V, H, C>::contains(const V &value) const {
	list<value_type>& whichList = _table[getHashedValue(value)];
	return find(whichList.begin(), whichList.end(), value) != whichList.end();
}

template <typename V, typename H, typename C>
double hashtable<V, H, C>::load_factor() const {
	return _currentSize / _capacity;
}

template <typename V, typename H, typename C>
size_t hashtable<V, H, C>::size() const{
	return _currentSize;
}

template <typename V, typename H, typename C>
size_t hashtable<V, H, C>::capacity(){
	return _capacity;
}

template <typename V, typename H, typename C>
bool hashtable<V, H, C>::empty() const{
	return _table.empty();
}

template <typename V, typename H, typename C>
void hashtable<V, H, C>::insert(const V &value){
	if (!contains(value)){
		list<value_type>& whichList = _table[getHashedValue(value)];
		whichList.push_back(value);
		if (++_currentSize > _maxLoadFactor * _capacity)
			rehash(static_cast<size_t>(_currentSize * 2));
	}
	else{
		// Element is already available in hashtable so there is no need to add it
	}
}

template <typename V, typename H, typename C>
void hashtable<V, H, C>::erase(const V &value){
	if (contains(value)){
		list<value_type>& whichList = _table[getHashedValue(value)];
		auto elemet = find(whichList.begin(), whichList.end(), value);
		whichList.remove(value);
		if (--_currentSize > _minLoadFactor * _capacity){
			rehash(static_cast<size_t>(_currentSize * 0.5))
		}
	}
	else{
		// Element is not existent in hashtable so there is no need to remove it
	}
}

template <typename V, typename H, typename C>
void hashtable<V, H, C>::rehash(size_t new_n_buckets){
	vector<list<V>> old = _table;
	_table.resize(new_n_buckets);
	_currentSize = 0;
	for (size_t i = 0; i < _table.size(); i++) {
		_table[i].clear();
	}

	for (auto elements : old) {
		for (auto element : elements) {
			insert(element);
		}
	}
}

template <typename V, typename H, typename C>
size_t hashtable<V, H, C>::getHashedValue(const V& value){
	size_t hashValue = _hasher(value) / _capacity;
	if (hashValue < 0){
		hashValue += _table.size();
	}
	return hashValue;
}

#endif // hashtable_hpp