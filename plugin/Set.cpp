#include "pch.h"
#include "Set.h"
#include "StringExtensions.h"

const std::vector<MQTypeMember> SetIteratorMembers =
{
	{ static_cast<int>(SetIterator::SetIteratorMembers::Reset), "Reset" },
	{ static_cast<int>(SetIterator::SetIteratorMembers::Advance), "Advance" },
	{ static_cast<int>(SetIterator::SetIteratorMembers::IsEnd), "IsEnd" },
	{ static_cast<int>(SetIterator::SetIteratorMembers::Value), "Value" },
	{ static_cast<int>(SetIterator::SetIteratorMembers::Clone), "Clone" },
};

const std::vector<MQTypeMember> SetMembers =
{
	{ static_cast<int>(Set::SetMembers::Count), "Count" },
	{ static_cast<int>(Set::SetMembers::Clear), "Clear" },
	{ static_cast<int>(Set::SetMembers::Contains), "Contains" },
	{ static_cast<int>(Set::SetMembers::Add), "Add" },
	{ static_cast<int>(Set::SetMembers::Remove), "Remove" },
	{ static_cast<int>(Set::SetMembers::First), "First" },
	{ static_cast<int>(Set::SetMembers::Find), "Find" },
};


//
// SetIterator methods
//

SetIterator::SetIterator(const std::set<std::string>& refCollection)
	: ValueIterator(refCollection)
	, ReferenceType(::SetIteratorMembers)
{
}

SetIterator::SetIterator(
	const std::set<std::string>& refCollection,
	const std::string& refKey)
	: ValueIterator(refCollection)
	, ReferenceType(::SetIteratorMembers)
{
	Find(refKey);
}

SetIterator::SetIterator(const SetIterator& original)
	: ValueIterator(original)
	, ReferenceType(::SetIteratorMembers)
{
}

SetIterator::~SetIterator()
{
}

const char* SetIterator::GetTypeName()
{
	return "setiterator";
}

// Cloned iterators can be deleted.
bool SetIterator::CanDelete() const
{
	return Cloned();
}

std::unique_ptr<SetIterator> SetIterator::Clone() const
{
	return std::make_unique<SetIterator>(*this);
}

bool SetIterator::Value(const std::string** const item) const
{
	// Return false if we are after the end of the set.
	if (IsEnd())
	{
		return false;
	}

	*item = &(*m_iterator);
	return true;
}

bool SetIterator::GetMember(MQVarPtr VarPtr, const char* Member, char* Index, MQTypeVar& Dest)
{
	Dest.Set(false);
	Dest.Type = mq::datatypes::pBoolType;

	auto pMember = SetIterator::FindMember(Member);
	if (pMember == nullptr)
	{
		return false;
	}

	SetIterator* pThis = static_cast<SetIterator*>(VarPtr.Ptr);
	if (pThis == nullptr)
	{
		return false;
	}

	switch (static_cast<SetIteratorMembers>(pMember->ID))
	{
	case SetIteratorMembers::Reset:
		pThis->Reset();
		Dest.Set(true);
		return true;

	case SetIteratorMembers::Advance:
		Dest.Set(pThis->Advance());
		return true;

	case SetIteratorMembers::IsEnd:
		Dest.Set(pThis->IsEnd());
		return true;

	case SetIteratorMembers::Value: {
		const std::string* pItem;
		if (pThis->Value(&pItem))
		{
			Dest.Ptr = (void*)pThis->m_Buffer.SetBuffer(pItem->c_str(), pItem->size() + 1);
			Dest.Type = mq::datatypes::pStringType;
		}
		return true;
	}

	case SetIteratorMembers::Clone:
		Dest.Ptr = (void*)pThis->Clone().release();
		Dest.Type = SetIterator::GetTypeInstance();
		return true;

	default: break;
	}

	return false;
}

bool SetIterator::ToString(MQVarPtr VarPtr, PCHAR Destination)
{
	SetIterator* pThis = static_cast<SetIterator*>(VarPtr.Ptr);
	if (Destination == nullptr)
	{
		return false;
	}

	errno_t rc;
	const std::string* item;
	if (!pThis->Value(&item))
	{
		rc = strcpy_s(Destination, BUFFER_SIZE, "FALSE");
	}
	else
	{
		rc = strcpy_s(Destination, BUFFER_SIZE, item->c_str());
	}

	return rc == 0;
}

bool SetIterator::Find(const std::string& refKey)
{
	m_iterator = m_refCollection.find(refKey);

	return m_iterator != m_refCollection.end();
}


//
// Set implementation.
//

Set::Set()
	: ObjectType(::SetMembers)
{
}

Set::~Set()
{
}

const char* Set::GetTypeName()
{
	return "set";
}

bool Set::Contains(const std::string& key) const
{
	return m_container.find(key) != m_container.end();
}

void Set::Add(const std::string& item)
{
	m_container.insert(item);
}

bool Set::Remove(const std::string& item)
{
	if (!Contains(item))
	{
		return false;
	}

	m_container.erase(item);
	return true;
}

void Set::AddItems(const std::string& items)
{
	// Split the string into extents. Each extent represents an argument
	// to insert. An empty collection will append no strings.
	auto arguments = std::make_unique<StringExtensions>(items);
	auto coll = arguments->Split(StringExtensions::string_type(","));

	std::for_each(coll->cbegin(), coll->cend(),
		[this](const std::string& item)
	{
		Add(item);
	});
}

ValueIterator<std::set<std::string>>* Set::Find(const std::string& refKey)
{
	m_findIter = std::make_unique<SetIterator>(m_container, refKey);

	return m_findIter.get();
}

bool Set::GetMember(MQVarPtr VarPtr, const char* Member, char* Index, MQTypeVar& Dest)
{
	Dest.Set(false);
	Dest.Type = mq::datatypes::pBoolType;

	auto pMember = Set::FindMember(Member);
	if (pMember == nullptr)
	{
		return false;
	}

	Set* pThis = static_cast<Set*>(VarPtr.Ptr);
	if (pThis == nullptr)
	{
		return false;
	}

	switch (static_cast<SetMembers>(pMember->ID))
	{
	case SetMembers::Count:
		Dest.Int = static_cast<int>(pThis->Count());
		Dest.Type = mq::datatypes::pIntType;
		return true;

	case SetMembers::Clear:
		pThis->Clear();
		Dest.Set(true);
		return true;

	case SetMembers::Contains:
		if (Index[0])
		{
			Dest.Set(pThis->Contains(Index));
		}
		return true;

	case SetMembers::Add:
		if (Index[0])
		{
			if (std::string_view(Index).find_first_not_of(" \t\n\r\f") != std::string::npos)
			{
				pThis->AddItems(Index);
				Dest.Set(true);
			}
		}
		return true;

	case SetMembers::Remove:
		if (Index[0])
		{
			Dest.Set(pThis->Remove(Index));
		}
		return true;

	case SetMembers::First:
		Dest.Ptr = (void*)pThis->First();
		Dest.Type = SetIterator::GetTypeInstance();
		return true;

	case SetMembers::Find:
		if (Index[0])
		{
			Dest.Ptr = (void*)pThis->Find(Index);
			Dest.Type = SetIterator::GetTypeInstance();
		}
		return true;

	default: break;
	}

	return false;
}

bool Set::ToString(MQVarPtr VarPtr, PCHAR Destination)
{
	Set* pThis = static_cast<Set*>(VarPtr.Ptr);

	if (Destination == nullptr)
	{
		return false;
	}

	sprintf_s(Destination, MAX_STRING, "%zu", pThis->Count());
	return true;
}

bool Set::FromString(MQVarPtr& VarPtr, const char* Source)
{
	Set* pDest = static_cast<Set*>(VarPtr.Ptr);

	if (pDest != nullptr && Source[0])
	{
		pDest->Add(Source);
	}

	return true;
}

//
// Return an iterator on the set.
//

std::unique_ptr<ValueIterator<std::set<std::string>>> Set::GetNewIterator(
	const std::set<std::string>& refCollection) const
{
	return std::make_unique<SetIterator>(refCollection);
}

