//
// Collections.h
//
// Define the base interfaces for collection classes.
//

#pragma once

#include <memory>

//
// Define a base class for an iterator on a collection.
//
// An iterator has the following methods and properties:
//
// Reset  - Position the iterator to the beginning of the collection.
// End    - Position the iterator to the end of the collection.
// Next   - Advance the iterator to the next element.
// IsEnd  - Is the iterator at the end of the collection?
//

template<class ContainerType>
class IteratorBase
{
public:
	// Make an empty iterator.
	explicit IteratorBase(const ContainerType& collection)
		: m_refCollection(collection)
	{
		Reset();
	}

	// Copy the iterator. The copy is cloned and can/must be deleted.
	explicit IteratorBase(const IteratorBase& original)
		: m_iterator(original.m_iterator)
		, m_refCollection(original.m_refCollection)
		, m_cloned(true)
	{
	}

	virtual ~IteratorBase()
	{
	}

	// Reset the iterator to the start of the collection.
	void Reset()
	{
		m_iterator = m_refCollection.begin();
	}

	// Advance the iterator.  Return true if the iterator could be advanced
	// and false otherwise.
	bool Advance()
	{
		if (m_iterator != m_refCollection.end())
		{
			++m_iterator;
			return true;
		}

		return false;
	}

	// Return true if the iterator is at the end of the collection.
	bool IsEnd() const
	{
		return m_refCollection.end() == m_iterator;
	}

protected:
	// Was this iterator cloned?
	bool Cloned() const
	{
		return m_cloned;
	}

	// Iterator on m_refCollection.
	typename ContainerType::const_iterator m_iterator;

	// Reference to the underlying collection.
	const ContainerType& m_refCollection;

	// Was this iterator cloned?
	const bool m_cloned = false;
};


//
// Define an iterator on a collection that only returns values.  For
// example, an iterator on a set.
//
// A value iterator has methods of the IteratorBase class plus:
//
// Value  - Return the value under the current iterator
//

template<class ContainerType, typename ValueType = ContainerType::value_type>
class ValueIterator : public IteratorBase<ContainerType>
{
public:
	explicit ValueIterator(const ContainerType& collection)
		: IteratorBase<ContainerType>(collection)
	{
	}

	explicit ValueIterator(const ValueIterator& iter)
		: IteratorBase<ContainerType>(iter)
	{
	}

	virtual ~ValueIterator() override
	{
	}

	// Return the value under the current iterator through the item parameter.
	// True is returned if item is valid and false if it is not.  Item is
	// not valid if the iterator points after the end of the collection.
	virtual bool Value(const ValueType** item) const = 0;
};


//
// Define an iterator on a collection that returns keys and values.  For
// example, an iterator on a map.
//
// A value iterator has methods of the ValueIterator class plus:
//
// Key    - Return the key under the current iterator
//
//

template<class ContainerType, typename KeyType, typename ValueType>
class KeyValueIterator : public ValueIterator<ContainerType, ValueType>
{
public:
	explicit KeyValueIterator(const ContainerType& collection)
		: ValueIterator<ContainerType, ValueType>(collection)
	{
	}

	explicit KeyValueIterator(const KeyValueIterator& iter)
		: ValueIterator<ContainerType, ValueType>(iter)
	{
	}

	virtual ~KeyValueIterator() override
	{
	}

	// Return the key under the current iterator through the key parameter.
	// True is returned if key is valid and false if it is not.  Key is
	// not valid if the iterator points after the end of the collection,
	// or if the collection in question doesn't have keys, such as an
	// array or list.
	virtual bool Key(const KeyType** key) const = 0;
};


//
// A Collection defines the following methods and properties:
//
// Count  - Return the number of elements in the collection
// Clear  - Delete all elements in the collection
// First  - Return an Iterator referencing the first element.
//
template<
	typename ContainerType,
	typename ValueType = ContainerType::value_type,
	typename KeyType = ValueType,
	typename IteratorType = IteratorBase<ContainerType>>
class Collection
{
public:
	Collection()
	{
	}

	virtual ~Collection()
	{
		Clear();
	}

	// Return the count of elements in the collection.
	virtual size_t Count() const
	{
		return static_cast<size_t>(m_container.size());
	}

	// Return if the container is empty
	virtual bool IsEmpty() const
	{
		return m_container.empty();
	}

	// Clear (delete all elements) in the collection.
	void Clear()
	{
		m_container.clear();
	}

	// Return a pointer to an iterator to the first element in the
	// collection or an iterator for which IsEnd is true.
	IteratorType* First()
	{
		m_iter = GetNewIterator(m_container);

		return m_iter.get();
	}

protected:
	// Derived class must implement a method that creates a new Iterator
	// appropriate to that class.
	virtual std::unique_ptr<IteratorType> GetNewIterator(const ContainerType& refCollection) const = 0;

	// Container maintained by the collection.
	ContainerType m_container;

	// Iterator on the collection returned by First.
	std::unique_ptr<IteratorType> m_iter;
};
