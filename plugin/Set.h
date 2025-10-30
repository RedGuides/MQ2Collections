//
// Set - set of strings for MQ
//

#pragma once

#include "BufferManager.h"
#include "Collections.h"
#include "Types.h"

#include <string>
#include <set>

//
// An iterator on a set.
//

class SetIterator
	: public ValueIterator<std::set<std::string>>
	, public ReferenceType<SetIterator, std::set<std::string>>
{
public:
	enum class SetIteratorMembers
	{
		Reset = 1,
		Advance,
		IsEnd,
		Value,
		Clone
	};

	explicit SetIterator(const std::set<std::string>& refCollection);

	explicit SetIterator(
		const std::set<std::string>& refCollection,
		const std::string& refKey);

	explicit SetIterator(const SetIterator& original);

	virtual ~SetIterator() override;

	const SetIterator& operator=(const SetIterator&) = delete;

	static const char* GetTypeName();

	virtual bool CanDelete() const override;

	// Return the value in the set under the current iterator.
	virtual bool Value(const std::string** item) const override;

	// Clone this iterator, creating a new one.
	std::unique_ptr<SetIterator> Clone() const;

	// When a member function is called on the type, this method is called.
	// It returns true if the method succeeded and false otherwise.
	virtual bool GetMember(MQVarPtr VarPtr, const char* Member, char* Index, MQTypeVar& Dest) override;

	// Convert the set to a string -- output the current item.
	virtual bool ToString(MQVarPtr VarPtr, char* Destination) override;

protected:
	// Return an iterator on the set for a particular key. Return
	// false if the key is not found.
	bool Find(const std::string& refKey);

private:
	// Internal character buffer for an iterated item to return.
	BufferManager<char> m_Buffer;
};


//
// A set is a collection that contains only one of each element. Adding an
// existing element to the set produces a set with the same elements.
//

class Set : public Collection<
	std::set<std::string>,
	std::string,
	std::string,
	ValueIterator<std::set<std::string>>>,
	public ObjectType<Set>
{
public:
	enum class SetMembers
	{
		Count = 1,
		Clear,
		Contains,
		Add,
		Remove,
		First,
		Find
	};

	Set();
	virtual ~Set() override;

	Set(const Set&) = delete;
	const Set& operator=(const Set&) = delete;

	static const char* GetTypeName();

	// Return true if a key is in the collection.
	bool Contains(const std::string& key) const;

	// Add a new element to the set.
	void Add(const std::string& item);

	// Add a sequence of items to the set.
	void AddItems(const std::string& items);

	// Remove an element from the set. Return false if the item was not in the set.
	bool Remove(const std::string& item);

	// Return an iterator to a requested key or to the end of the set.
	ValueIterator<std::set<std::string>>* Find(const std::string& refKey);

	// When a member function is called on the type, this method is called.
	// It returns true if the method succeeded and false otherwise.
	virtual bool GetMember(MQVarPtr VarPtr, const char* Member, char* Index, MQTypeVar& Dest) override;

	// Convert the set to a string -- output the count of items.
	virtual bool ToString(MQVarPtr VarPtr, char* Destination) override;

	// This method is executed when the /varset statement is executed. Treat
	// this as a set Add call.
	virtual bool FromString(MQVarPtr& VarPtr, const char* Source) override;

protected:
	// Return an iterator on the set.
	virtual std::unique_ptr<ValueIterator<std::set<std::string>>> GetNewIterator(
		const std::set<std::string>& refCollection) const override;

private:
	// Iterator returned by Find operations.
	std::unique_ptr<SetIterator> m_findIter;
};
