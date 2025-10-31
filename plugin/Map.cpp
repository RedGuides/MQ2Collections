#include "pch.h"
#include "Map.h"
#include "StringExtensions.h"

const std::vector<MQTypeMember> MapIteratorMembers =
{
	{ static_cast<int>(MapIterator::MapIteratorMembers::Reset), "Reset" },
	{ static_cast<int>(MapIterator::MapIteratorMembers::Advance), "Advance" },
	{ static_cast<int>(MapIterator::MapIteratorMembers::IsEnd), "IsEnd" },
	{ static_cast<int>(MapIterator::MapIteratorMembers::Value), "Value" },
	{ static_cast<int>(MapIterator::MapIteratorMembers::Key), "Key" },
	{ static_cast<int>(MapIterator::MapIteratorMembers::Clone), "Clone" },
};

const std::vector<MQTypeMember> MapMembers =
{
	{ static_cast<int>(Map::MapMembers::Count), "Count" },
	{ static_cast<int>(Map::MapMembers::Clear), "Clear" },
	{ static_cast<int>(Map::MapMembers::Contains), "Contains" },
	{ static_cast<int>(Map::MapMembers::Add), "Add" },
	{ static_cast<int>(Map::MapMembers::Remove), "Remove" },
	{ static_cast<int>(Map::MapMembers::First), "First" },
	{ static_cast<int>(Map::MapMembers::Find), "Find" },
};

MapIterator::MapIterator(const std::map<std::string, std::string>& refCollection)
	: KeyValueIterator(refCollection)
	, ReferenceType(::MapIteratorMembers)
{
}


MapIterator::MapIterator(const std::map<std::string, std::string>& refCollection, const std::string& refKey)
	: KeyValueIterator(refCollection)
	, ReferenceType(::MapIteratorMembers)
{
	Find(refKey);
}


MapIterator::MapIterator(const MapIterator& original)
	: KeyValueIterator(original)
	, ReferenceType(::MapIteratorMembers)
{
}

MapIterator::~MapIterator()
{
}

const char* MapIterator::GetTypeName()
{
	return "mapiterator";
}

bool MapIterator::CanDelete() const
{
	return Cloned();
}

std::unique_ptr<MapIterator> MapIterator::Clone() const
{
	return std::make_unique<MapIterator>(*this);
}

bool MapIterator::Value(const std::string** const item) const
{
	// Return false if we are after the end of the set.
	if (IsEnd())
	{
		return false;
	}

	*item = &m_iterator->second;
	return true;
}

bool MapIterator::Key(const std::string** const key) const
{
	// Return false if we are after the end of the set.
	if (IsEnd())
	{
		return false;
	}

	*key = &m_iterator->first;
	return true;
}

bool MapIterator::GetMember(MQVarPtr VarPtr, const char* Member, char* Index, MQTypeVar& Dest)
{
	MQTypeVar typeVar;
	const std::string* pItem;

	// Default return value is FALSE.
	Dest.Set(false);
	Dest.Type = mq::datatypes::pBoolType;

	// Map the member name to the id.
	auto pMember = MapIterator::FindMember(Member);
	if (pMember == nullptr)
	{
		return false;
	}

	MapIterator* pThis = static_cast<MapIterator*>(VarPtr.Ptr);
	if (pThis == nullptr)
	{
		return false;
	}

	switch (static_cast<MapIteratorMembers>(pMember->ID))
	{
	case MapIteratorMembers::Reset:
		pThis->Reset();
		Dest.Set(true);
		return true;

	case MapIteratorMembers::Advance:
		Dest.Set(pThis->Advance());
		return true;

	case MapIteratorMembers::IsEnd:
		Dest.Set(pThis->IsEnd());
		return true;

	case MapIteratorMembers::Value:
		if (pThis->Value(&pItem))
		{
			Dest.Ptr = (void*)pThis->m_Buffer.SetBuffer(pItem->c_str(), pItem->size() + 1);
			Dest.Type = mq::datatypes::pStringType;
		}
		return true;

	case MapIteratorMembers::Key:
		if (pThis->Key(&pItem))
		{
			Dest.Ptr = (void*)pThis->m_Buffer.SetBuffer(pItem->c_str(), pItem->size() + 1);
			Dest.Type = mq::datatypes::pStringType;
		}
		return true;

	case MapIteratorMembers::Clone:
		Dest.Ptr = (void*)pThis->Clone().release();
		Dest.Type = MapIterator::GetTypeInstance();
		return true;

	default: break;
	}

	return false;
}

bool MapIterator::ToString(MQVarPtr VarPtr, PCHAR Destination)
{
	MapIterator* pThis = reinterpret_cast<MapIterator*>(VarPtr.Ptr);
	if (Destination == nullptr)
	{
		return false;
	}

	// Format the output buffers as (Key, Value).
	// If either the key or the value is missing, write in its place.
	if (strcpy_s(Destination, BUFFER_SIZE, "(") != 0)
	{
		return false;
	}

	const std::string* item;
	if (!pThis->Key(&item))
	{
		if (strcat_s(Destination, BUFFER_SIZE, "FALSE") != 0)
		{
			return false;
		}
	}
	else
	{
		if (strcat_s(Destination, BUFFER_SIZE, item->c_str()) != 0)
		{
			return false;
		}
	}

	if (strcat_s(Destination, BUFFER_SIZE, ", ") != 0)
	{
		return false;
	}

	if (!pThis->Value(&item))
	{
		if (strcat_s(Destination, BUFFER_SIZE, "FALSE") != 0)
		{
			return false;
		}
	}
	else
	{
		if (strcat_s(Destination, BUFFER_SIZE, item->c_str()) != 0)
		{
			return false;
		}
	}

	return strcat_s(Destination, BUFFER_SIZE, ")") == 0;
}

bool MapIterator::Find(const std::string& refKey)
{
	m_iterator = m_refCollection.find(refKey);

	return m_iterator != m_refCollection.end();
}


//
// Map implementation.
//

Map::Map() : ObjectType(::MapMembers)
{
}

Map::~Map()
{
}

const char* Map::GetTypeName()
{
	return "map";
}

bool Map::Contains(const std::string& key) const
{
	return m_container.find(key) != m_container.end();
}

void Map::Add(const std::string& key, const std::string& item)
{
	m_container[key] = item;
}

bool Map::Remove(const std::string& item)
{
	if (!Contains(item))
	{
		return false;
	}

	m_container.erase(item);
	return true;
}

KeyValueIterator<MapStorageType, std::string, std::string>* Map::Find(const std::string& refKey)
{
	m_findIter = std::make_unique<MapIterator>(m_container, refKey);

	return m_findIter.get();
}

bool Map::GetMember(MQVarPtr VarPtr, const char* Member, char* Index, MQTypeVar& Dest)
{
	Dest.Set(false);
	Dest.Type = mq::datatypes::pBoolType;

	auto pMember = Map::FindMember(Member);
	if (pMember == nullptr)
	{
		return false;
	}

	Map* pThis = static_cast<Map*>(VarPtr.Ptr);
	if (pThis == nullptr)
	{
		return false;
	}

	switch (static_cast<MapMembers>(pMember->ID))
	{
	case MapMembers::Count:
		Dest.Int = static_cast<int>(pThis->Count());
		Dest.Type = mq::datatypes::pIntType;
		return true;

	case MapMembers::Clear:
		pThis->Clear();
		Dest.Set(true);
		return true;

	case MapMembers::Contains:
		if (Index[0])
		{
			Dest.Set(pThis->Contains(Index));
		}
		return true;

	case MapMembers::Add:
		if (Index[0])
		{
			Dest.Set(AddKeyAndValue(pThis, Index));
		}
		return true;

	case MapMembers::Remove:
		if (Index[0])
		{
			Dest.Set(pThis->Remove(Index));
		}
		return true;

	case MapMembers::First:
		Dest.Ptr = (void*)pThis->First();
		Dest.Type = MapIterator::GetTypeInstance();
		return true;

	case MapMembers::Find:
		if (Index[0])
		{
			Dest.Ptr = (void*)pThis->Find(Index);
			Dest.Type = MapIterator::GetTypeInstance();
		}
		return true;

	default: break;
	}

	return false;
}

bool Map::ToString(MQVarPtr VarPtr, char* Destination)
{
	Map* pThis = static_cast<Map*>(VarPtr.Ptr);
	if (Destination == nullptr)
	{
		return false;
	}

	sprintf_s(Destination, MAX_STRING, "%zu", pThis->Count());
	return true;
}

std::unique_ptr<KeyValueIterator<MapStorageType, std::string, std::string>> Map::GetNewIterator(const MapStorageType& refCollection) const
{
	return std::make_unique<MapIterator>(refCollection);
}

bool Map::AddKeyAndValue(Map* pThis, char* Arguments)
{
	bool fResult = true;

	// Split the arguments and add the first one as the key and
	// the second as the value.
	auto argument = std::make_unique<StringExtensions>(Arguments);
	auto splits = argument->Split(StringExtensions::string_type(","));

	// There must be two and only two arguments.
	if (splits->size() != 2)
	{
		// Generate an error because we have the incorrect number of arguments.
		fResult = false;
	}
	else
	{
		// Trim the key and value.
		auto arg = std::make_unique<StringExtensions>((*splits)[0]);
		auto key = arg->Trim();

		arg = std::make_unique<StringExtensions>((*splits)[1]);
		auto value = arg->Trim();

		// Neither the key nor the value can be empty.
		if (key->Contents().empty() || value->Contents().empty())
		{
			fResult = false;
		}
		else
		{
			pThis->Add(key->Contents(), value->Contents());
		}
	}

	return fResult;
}
