//
// Map - map (associative store) from a key to a value for MQ
//

#pragma once

#include "BufferManager.h"
#include "Collections.h"
#include "Types.h"

#include <string>
#include <map>

//
// An iterator on a map
//

class MapIterator
	: public KeyValueIterator<std::map<std::string, std::string>, std::string, std::string>
	, public ReferenceType<MapIterator, std::map<std::string, std::string>>
{
public:
	enum class MapIteratorMembers
	{
		Reset = 1,
		Advance,
		IsEnd,
		Value,
		Key,
		Clone
	};

	explicit MapIterator(const std::map<std::string, std::string>& refCollection);

	explicit MapIterator(
		const std::map<std::string, std::string>& refCollection,
		const std::string& refKey);

	explicit MapIterator(const MapIterator& original);

	virtual ~MapIterator() override;

	const MapIterator& operator=(const MapIterator&) = delete;

	// Return the name of this type - mapiterator.
	static const char* GetTypeName();

	// Cloned iterators can be deleted.
	virtual bool CanDelete() const override;

	// Return the value in the map under the current iterator.
	virtual bool Value(const std::string** item) const override;

	// Return the key in the map under the current iterator.
	virtual bool Key(const std::string** key) const override;

	// Clone this iterator, creating a new one.
	std::unique_ptr<MapIterator> Clone() const;

	// When a member function is called on the type, this method is called.
	// It returns true if the method succeeded and false otherwise.
	virtual bool GetMember(MQVarPtr VarPtr, const char* Member, char* Index, MQTypeVar& Dest) override;

	// Convert the map to a string -- output the current item.
	virtual bool ToString(MQVarPtr VarPtr, char* Destination) override;

protected:
	// Return an iterator on the map for a particular key. Return false if the key is not found.
	bool Find(const std::string& refKey);

private:
	// Internal character buffer for an iterated item to return.
	BufferManager<char> m_Buffer;
};


using MapStorageType = std::map<std::string, std::string>;

// A map is a collection that associates a key with a value. There is
// only one of each key in the map.
class Map 
	: public Collection<MapStorageType, std::string, std::string, KeyValueIterator<MapStorageType, std::string, std::string>>
	, public ObjectType<Map>
{
public:
	enum class MapMembers
	{
		Count = 1,
		Clear,
		Contains,
		Add,
		Remove,
		First,
		Find
	};

	Map();
	virtual ~Map() override;

	Map(const Map&) = delete;
	const Map& operator=(const Map&) = delete;

	// Return the name of this type - map.
	static const char* GetTypeName();

	// Return true if a key is in the collection.
	bool Contains(const std::string& key) const;

	// Add a new element to the map. If he key already exists, the
	// value is overwritten.
	void Add(const std::string& key, const std::string& item);

	// Remove an element from the map. Return false if the item was not in the map.
	bool Remove(const std::string& item);

	// Return an iterator to a requested key or to the end of the map.
	KeyValueIterator<MapStorageType, std::string, std::string>* Find(const std::string& refKey);

	// When a member function is called on the type, this method is called.
	// It returns true if the method succeeded and false otherwise.
	virtual bool GetMember(MQVarPtr VarPtr, const char* Member, char* Index, MQTypeVar& Dest) override;

	// Convert the map to a string -- output the count of items.
	virtual bool ToString(MQVarPtr VarPtr, char* Destination) override;

protected:
	// Return an iterator on the map.
	virtual std::unique_ptr<KeyValueIterator<MapStorageType, std::string, std::string>> GetNewIterator(const MapStorageType& refCollection) const override;

private:
	// Add a key and value to the map, returning true if they were
	// added and false otherwise.
	static bool AddKeyAndValue(Map* pThis, char* Arguments);

	// Iterator returned by Find operations.
	std::unique_ptr<MapIterator> m_findIter;
};
