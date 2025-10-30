#include "pch.h"
#include "List.h"
#include "StringExtensions.h"

#include <algorithm>
#include <memory>

const std::vector<MQTypeMember> ListIteratorMembers =
{
	{ static_cast<int>(ListIterator::ListIteratorMembers::Reset), "Reset" },
	{ static_cast<int>(ListIterator::ListIteratorMembers::Advance), "Advance" },
	{ static_cast<int>(ListIterator::ListIteratorMembers::IsEnd), "IsEnd" },
	{ static_cast<int>(ListIterator::ListIteratorMembers::Value), "Value" },
	{ static_cast<int>(ListIterator::ListIteratorMembers::Clone), "Clone" },
};

const std::vector<MQTypeMember> ListMembers =
{
	{ static_cast<int>(List::ListMembers::Count), "Count" },
	{ static_cast<int>(List::ListMembers::Clear), "Clear" },
	{ static_cast<int>(List::ListMembers::Contains), "Contains" },
	{ static_cast<int>(List::ListMembers::Splice), "Splice" },
	{ static_cast<int>(List::ListMembers::Index), "Index" },
	{ static_cast<int>(List::ListMembers::Item), "Item" },
	{ static_cast<int>(List::ListMembers::Insert), "Insert" },
	{ static_cast<int>(List::ListMembers::Sort), "Sort" },
	{ static_cast<int>(List::ListMembers::Reverse), "Reverse" },
	{ static_cast<int>(List::ListMembers::Append), "Append" },
	{ static_cast<int>(List::ListMembers::Remove), "Remove" },
	{ static_cast<int>(List::ListMembers::Erase), "Erase" },
	{ static_cast<int>(List::ListMembers::Replace), "Replace" },
	{ static_cast<int>(List::ListMembers::First), "First" },
	{ static_cast<int>(List::ListMembers::Find), "Find" },
	{ static_cast<int>(List::ListMembers::Head), "Head" },
	{ static_cast<int>(List::ListMembers::Tail), "Tail" },
	{ static_cast<int>(List::ListMembers::CountOf), "CountOf" },
	{ static_cast<int>(List::ListMembers::Delimiter), "Delimiter" },
};

ListIterator::ListIterator(const std::list<std::string>& refCollection)
	: ValueIterator(refCollection)
	, ReferenceType(::ListIteratorMembers)
{
}

ListIterator::ListIterator(
	const std::list<std::string>& refCollection,
	const std::string& refKey)
	: ValueIterator(refCollection)
	, ReferenceType(::ListIteratorMembers)
{
	// Position the iterator to the item or to the end of the list.
	Find(refKey);
}

ListIterator::ListIterator(const ListIterator& original)
	: ValueIterator(original)
	, ReferenceType(::ListIteratorMembers)
{
}

ListIterator::~ListIterator()
{
}

const char* ListIterator::GetTypeName()
{
	return "listiterator";
}

bool ListIterator::CanDelete() const
{
	return Cloned();
}

std::unique_ptr<ListIterator> ListIterator::Clone() const
{
	return std::make_unique<ListIterator>(*this);
}

bool ListIterator::Value(const std::string** const item) const
{
	// Return false if we are after the end of the list.
	if (IsEnd())
	{
		return false;
	}

	*item = &(*m_iterator);
	return true;
}

// When a member function is called on the type, this method is called.
// It returns true if the method succeeded and false otherwise.
bool ListIterator::GetMember(MQVarPtr VarPtr, const char* Member, char* Index, MQTypeVar& Dest)
{
	MQTypeVar typeVar;
	const std::string* pItem;

	// Default return value is FALSE.

	Dest.Set(false);
	Dest.Type = mq::datatypes::pBoolType;

	// Map the member name to the id.
	auto pMember = ListIterator::FindMember(Member);
	if (pMember == nullptr)
	{
		return false;
	}

	ListIterator* pThis = static_cast<ListIterator*>(VarPtr.Ptr);
	if (pThis == nullptr)
	{
		return false;
	}

	switch (static_cast<ListIteratorMembers>(pMember->ID))
	{
	case ListIteratorMembers::Reset:
		// Reset the iterator to the start of the list. Return the result as TRUE.
		pThis->Reset();
		Dest.Set(true);
		return true;

	case ListIteratorMembers::Advance:
		// Advance the iterator. Return TRUE if the iterator could be
		// advanced and FALSE otherwise.
		Dest.Set(pThis->Advance());
		return true;

	case ListIteratorMembers::IsEnd:
		// Return TRUE if we are at the Last element in the list and FALSE otherwise.
		Dest.Set(pThis->IsEnd());
		return true;

	case ListIteratorMembers::Value:
		// Return the current element under the iterator or FALSE if there isn't one.
		if (pThis->Value(&pItem))
		{
			Dest.Ptr = (void*)pThis->m_Buffer.SetBuffer(pItem->c_str(), pItem->size() + 1);
			Dest.Type = mq::datatypes::pStringType;
		}
		return true;

	case ListIteratorMembers::Clone:
		Dest.Ptr = (void*)pThis->Clone().release();
		Dest.Type = GetTypeInstance();
		return true;
	}

	return false;
}

// Used by the testing framework to call GetMember through the
// source variable.
bool ListIterator::GetMemberInvoker(MQVarPtr VarPtr, const char* Member, char* Index, MQTypeVar& Dest)
{
	ListIterator* pThis = static_cast<ListIterator*>(VarPtr.Ptr);
	if (pThis == nullptr)
	{
		return false;
	}

	return pThis->GetMember(VarPtr, Member, Index, Dest);
}

// Convert the iterator to a string. Output the current item or FALSE if there
// isn't one.
bool ListIterator::ToString(MQVarPtr VarPtr, char* Destination)
{
	ListIterator* pThis = static_cast<ListIterator*>(VarPtr.Ptr);
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

bool ListIterator::FromString(MQVarPtr& VarPtr, const char* Source)
{
	return false;
}

bool ListIterator::Find(const std::string& refKey)
{
	m_iterator = std::find(m_refCollection.cbegin(), m_refCollection.cend(), refKey);

	// Key was not in the collection.
	return m_iterator != m_refCollection.end();
}

//
// List Constructor.
//

List::List()
	: ObjectType(::ListMembers)
	, m_delimiter(",")
{
}

List::List(const std::list<std::string>& source)
	: ObjectType(::ListMembers)
	, m_delimiter(",")
{
	m_container = source;
}

List::~List()
{
}

const char* List::GetTypeName()
{
	return "list";
}

bool List::Contains(const std::string& item) const
{
	return std::find(m_container.cbegin(), m_container.cend(), item) != m_container.end();
}

int List::Index(const std::string& item) const
{
	// Compare each element in the list until key is found or until we reach the
	// end of the list.

	int nPosition = 0;
	auto it = m_container.cbegin();
	while (it != m_container.cend())
	{
		if (*it == item)
		{
			// Key found.
			return nPosition;
		}

		++it;
		++nPosition;
	}

	// Key not found.
	return -1;
}

bool List::Item(const size_t index, const std::string** const item) const
{
	// Find the item at position index.
	auto it = FindIteratorForPosition(index);
	if (it != m_container.cend())
	{
		// Return a reference to the item.
		*item = &(*it);
		return true;
	}

	// The index was not found in the list.
	return false;
}

void List::Sort()
{
	m_container.sort();
}

void List::Reverse()
{
	m_container.reverse();
}

void List::Append(const std::string& item)
{
	m_container.push_back(item);
}

size_t List::Remove(const std::string& item)
{
	// Count how many times item occurs in the list.
	auto itemCount = std::count(m_container.cbegin(), m_container.cend(), item);

	// Remove the item if there are any in the list. This test saves an
	// additional pass over the list for the removal.
	if (itemCount != 0)
	{
		m_container.remove(item);
	}

	return itemCount;
}

bool List::Erase(const size_t index)
{
	// If index is after the end of the list, don't erase anything.
	auto it = FindIteratorForPosition(index);
	if (it == m_container.cend())
	{
		return false;
	}

	// Otherwise, remove the element.
	m_container.erase(it);
	return true;
}

size_t List::Replace(const std::string& item, const std::string& newItem)
{
	// Count the items so we can return the replacement count.
	size_t replacedElements = CountOf(item);

	if (replacedElements != 0)
	{
		// Replacement is done in-place.
		std::replace(m_container.begin(), m_container.end(), item, newItem);
	}

	return replacedElements;
}

ValueIterator<std::list<std::string>>* List::Find(const std::string& refKey)
{
	m_findIter = std::make_unique<ListIterator>(m_container, refKey);

	return m_findIter.get();
}

bool List::Head(std::unique_ptr<const std::string>* item)
{
	// Only return the head if there are entries in the list.

	if (!IsEmpty())
	{
		// Copy the head of the list to a new std::string and return
		// that string to the caller. Then remove the head and
		// return true.
		//
		// The caller is responsible for deleting the string.

		*item = std::make_unique<const std::string>(m_container.front());
		m_container.pop_front();

		return true;
	}

	return false;
}

bool List::Tail(std::unique_ptr<const std::string>* item)
{
	// Only return the tail if there are entries in the list.
	if (!IsEmpty())
	{
		// Copy the tail of the list to a new std::string and return
		// that string to the caller. Then remove the tail and
		// return true.
		//
		// The caller is responsible for deleting the string.
		*item = std::make_unique<const std::string>(m_container.back());
		m_container.pop_back();

		return true;
	}

	return false;
}

size_t List::CountOf(const std::string& item) const
{
	return std::count(m_container.cbegin(), m_container.cend(), item);
}

std::unique_ptr<List> List::Splice(size_t startIndex) const
{
	// Return an empty list if startIndex is past the end of the list or length
	// is zero.
	if (startIndex >= Count())
	{
		return std::make_unique<List>();
	}

	// Return a splice from the range.
	std::list<std::string> newList(FindIteratorForPosition(startIndex), m_container.cend());

	return std::make_unique<List>(newList);
}

// Create a splice from a starting index for length entries. If startIndex is past
// the end of the list, an empty list is returned. If length is zero, an empty list
// is retruend. If there are less than length entries in the list, then at most
// Count() - startIndex entries will be returned.
std::unique_ptr<List> List::Splice(size_t startIndex, size_t length) const
{
	// Return an empty list if startIndex is past the end of the list or length is zero.
	if (startIndex >= Count() || length == 0)
	{
		return std::make_unique<List>();
	}

	// Return a splice from the range.
	std::list<std::string> newList(
		FindIteratorForPosition(startIndex),
		FindIteratorForPosition(startIndex + length));

	return std::make_unique<List>(newList);
}

bool List::GetMember(MQVarPtr VarPtr, const char* Member, char* Index, MQTypeVar& Dest)
{
	std::unique_ptr<const std::string> pItem;
	size_t replacedItems;

	Dest.Set(false);
	Dest.Type = mq::datatypes::pBoolType;

	auto pMember = List::FindMember(Member);
	if (pMember == nullptr)
	{
		return false;
	}

	List* pThis = static_cast<List*>(VarPtr.Ptr);
	if (pThis == nullptr)
	{
		return false;
	}

	switch (static_cast<ListMembers>(pMember->ID))
	{
	case ListMembers::Count:
		Dest.Int = static_cast<int>(pThis->Count());
		Dest.Type = mq::datatypes::pIntType;
		return true;

	case ListMembers::Clear:
		pThis->Clear();
		Dest.Set(true);
		return true;

	case ListMembers::Contains:
		// Does the list contain a value?
		if (Index[0])
		{
			Dest.Set(pThis->Contains(Index));
		}

		return true;

	case ListMembers::Splice:
		Dest.Ptr = static_cast<void*>(pThis->CreateSplice(Index).release());
		Dest.Type = GetTypeInstance();
		return true;

	case ListMembers::Index:
		if (Index[0])
		{
			// -1 is returned if the index was not found.
			Dest.Int = pThis->Index(Index);
			Dest.Type = mq::datatypes::pIntType;
		}
		return true;

	case ListMembers::Item:
		// Return the index'th item from the list.
		if (Index[0])
		{
			// Item fails if Index does not correspond to an item.
			std::string const* pItem;
			if (pThis->Item(Index, &pItem))
			{
				Dest.Ptr = (void*)pThis->m_buffer.SetBuffer(pItem->c_str(), pItem->size() + 1);
				Dest.Type = mq::datatypes::pStringType;
			}
		}

		return true;

	case ListMembers::Insert:
		// Insert the items into the index'th position in the list.
		if (Index[0])
		{
			Dest.Set(pThis->Insert(Index));
		}

		return true;

	case ListMembers::Sort:
		pThis->Sort();
		Dest.Set(true);
		return true;

	case ListMembers::Reverse:
		pThis->Reverse();
		Dest.Set(true);
		return true;

	case ListMembers::Append:
		if (Index[0])
		{
			pThis->AppendItems(Index);
			Dest.Set(true);
		}
		return true;

	case ListMembers::Remove:
		// Remove an item from the list. Return how many items were removed.
		if (Index[0])
		{
			Dest.Set(pThis->Remove(Index));
			Dest.Type = mq::datatypes::pIntType;
		}
		return true;

	case ListMembers::Erase:
		if (Index[0])
		{
			Dest.Set(pThis->Erase(Index));
		}
		return true;

	case ListMembers::Replace:
		if (Index[0])
		{
			if (pThis->Replace(Index, &replacedItems))
			{
				Dest.Int = static_cast<int>(replacedItems);
				Dest.Type = mq::datatypes::pIntType;
			}
		}
		return true;

	case ListMembers::First:
		Dest.Ptr = static_cast<void*>(pThis->First());
		Dest.Type = ListIterator::GetTypeInstance();
		return true;

	case ListMembers::Find:
		if (Index[0])
		{
			Dest.Ptr = static_cast<void*>(pThis->Find(Index));
			Dest.Type = ListIterator::GetTypeInstance();
		}
		return true;

	case ListMembers::Head:
		if (pThis->Head(&pItem))
		{
			Dest.Ptr = (void*)pThis->m_buffer.SetBuffer(pItem->c_str(), pItem->size() + 1);
			Dest.Type = mq::datatypes::pStringType;
		}
		return true;

	case ListMembers::Tail:
		if (pThis->Tail(&pItem))
		{
			Dest.Ptr = (void*)pThis->m_buffer.SetBuffer(pItem->c_str(), pItem->size() + 1);
			Dest.Type = mq::datatypes::pStringType;
		}
		return true;

	case ListMembers::CountOf:
		if (Index[0])
		{
			Dest.Int = static_cast<int>(pThis->CountOf(Index));
			Dest.Type = mq::datatypes::pIntType;
		}
		return true;

	case ListMembers::Delimiter:
		if (Index[0])
		{
			std::string old_delimiter = pThis->Delimiter(Index);
			Dest.Ptr = (void*)pThis->m_buffer.SetBuffer(old_delimiter.c_str(), old_delimiter.size() + 1);
			Dest.Type = mq::datatypes::pStringType;
		}
		return true;

	default: break;
	}

	return false;
}

bool List::GetMemberInvoker(MQVarPtr VarPtr, const char* Member, const char* Index, MQTypeVar& Dest)
{
	List* pThis = static_cast<List*>(VarPtr.Ptr);
	if (pThis == nullptr)
	{
		return false;
	}

	return pThis->GetMember(VarPtr, Member, const_cast<char*>(Index), Dest);
}

bool List::ToString(MQVarPtr VarPtr, char* Destination)
{
	List* pThis = static_cast<List*>(VarPtr.Ptr);
	if (Destination == nullptr)
	{
		return false;
	}

	sprintf_s(Destination, MAX_STRING, "%zu", pThis->Count());
	return true;
}

bool List::FromString(MQVarPtr& VarPtr, const char* Source)
{
	List* pDest = static_cast<List*>(VarPtr.Ptr);

	if (pDest != nullptr && Source[0])
	{
		pDest->Append(Source);
	}

	return true;
}

std::unique_ptr<ValueIterator<std::list<std::string>>> List::GetNewIterator(
	const std::list<std::string>& refCollection) const
{
	return std::make_unique<ListIterator>(refCollection);
}

std::list<std::string>::const_iterator List::FindIteratorForPosition(size_t position) const
{
	// If position is past the end of the list, return an iterator
	// to the end of the list.
	if (position >= Count())
	{
		return m_container.cend();
	}

	auto it = m_container.cbegin();
	while (position != 0)
	{
		--position;
		++it;
	}

	return it;
}

// Retrieve the index'th value from the list. Return true if index
// is in the bounds of the list and false otherwise. Index can
// be negative, in which case it is an offset from the end of the
// list.
bool List::Item(const std::string& index, const std::string** const item) const
{
	size_t lIndex;

	// Convert the string to an index value. Fail if we can not convert it.
	if (!IndexValueFromString(index, &lIndex))
	{
		return false;
	}

	// Get the item from the position.
	return Item(lIndex, item);
}

bool List::Insert(const std::string& args)
{
	size_t lIndex;

	// args must be of the form Integer , Sequence.
	// Find the , and then parse out the integer sequence.
	auto comma_pos = args.find_first_of(',');
	if ((comma_pos == std::string::npos) || (comma_pos == 0))
	{
		// No comma or no comma is at the start of the string.
		return false;
	}

	// Acquire the index value.
	if (!IndexValueFromString(args.substr(0, comma_pos), &lIndex))
	{
		return false;
	}

	if ((comma_pos + 1) == args.size())
	{
		// There aren't any strings to insert. This is a call of the form
		// Integer , Sequence where Sequence is empty, which inserts
		// nothing.
		return true;
	}

	// Split the string into extents. Each extent represents an argument

	auto arguments = std::make_unique<StringExtensions>(args.substr(comma_pos + 1));
	auto coll = arguments->Split(StringExtensions::string_type(m_delimiter));

	return Insert(lIndex, *coll);
}

void List::AppendItems(const std::string& args)
{
	// Split the string into extents. Each extent represents an argument
	// to insert. An empty collection will append no strings.
	auto arguments = std::make_unique<StringExtensions>(args);
	auto coll = arguments->Split(StringExtensions::string_type(m_delimiter));

	std::for_each(coll->cbegin(),
		coll->cend(),
		[this](const std::string& item)
		{
			Append(item);
		}
	);
}

bool List::Erase(const std::string& index)
{
	// Acquire the index value.
	size_t lIndex;
	if (!IndexValueFromString(index, &lIndex))
	{
		return false;
	}

	// And erase the item.
	return Erase(lIndex);
}

bool List::Replace(const std::string& args, size_t* count)
{
	// Split the strings and ensure there are two arguments.
	auto arguments = std::make_unique<StringExtensions>(args);
	auto container = arguments->Split(StringExtensions::string_type(","));

	if (container->size() != 2)
	{
		return false;
	}

	// Replace the first string with the second.
	size_t replaceCount = Replace(container->at(0), container->at(1));

	if (count)
	{
		*count = replaceCount;
	}

	return true;
}

std::unique_ptr<List> List::CreateSplice(const std::string& args) const
{
	auto start_it = m_container.cbegin();
	auto end_it = m_container.cend();

	// Split the strings and find out how many arguments there are, removing empty
	// strings from the output.
	auto arguments = std::make_unique<StringExtensions>(args);

	// Trim the string. If it is not empty, parse it into items.
	auto trimmed_string = arguments->Trim();
	if (!trimmed_string->Contents().empty())
	{
		auto coll = trimmed_string->Split(StringExtensions::string_type(","));

		// Update the iterators if there are arguments.
		size_t startIndex = Count();            // Default start is the end.
		size_t endIndex = Count();              // Default end is the end.

		// There is at least a starting index.
		if (coll->size() > 0)
		{
			// Select from index to end if index is valid. Otherwise use the end as the
			// starting element.
			if (IndexValueFromString((*coll)[0], &startIndex))
			{
				start_it = FindIteratorForPosition(startIndex);
			}
			else
			{
				start_it = m_container.cend();
			}
		}

		// Two arguments means there is a start and length. Pick up the length.
		if (coll->size() == 2)
		{
			size_t length;

			//
			// Select the length and add it to the start if it is valid.
			//

			if (IndexValueFromString((*coll)[1], &length))
			{
				end_it = FindIteratorForPosition(startIndex + length);
			}
		}
	}

	std::list<std::string> splice(start_it, end_it);
	return std::make_unique<List>(splice);
}

bool List::IndexValueFromString(const std::string& stringIndex, size_t* longIndex) const
{
	size_t lIndex;

	// Select all elements of the list from startIndex to the end of
	// the list. If startIndex is negative, use it as an offset from
	// the end of the list.
	if (!::FromString(stringIndex, &lIndex))
	{
		// Can't convert the index.
		return false;
	}

	// Compute lIndex as an offset from the start of the list.
	// If the list is empty, then treat any index as the start
	// of the list.
	if (IsEmpty())
	{
		lIndex = 0;
	}
	else
	{
		// Fail if the index is past the end of the list. If it is equal to the
		// end, treat this as an append.
		if (lIndex > Count())
		{
			return false;
		}
	}

	// Return the computed index.
	if (longIndex)
	{
		*longIndex = lIndex;
	}

	return true;
}

const std::string& List::Delimiter(const std::string& new_delimiter)
{
	std::string& old_delimiter(m_delimiter);

	m_delimiter = new_delimiter;

	return old_delimiter;
}
