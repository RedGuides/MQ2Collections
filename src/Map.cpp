
//
// Implementation file for MapIterator and Map.
//


#include <MQ2Plugin.h>

#include "Map.h"
#include "StringExtensions.h"
#include "Conversions.h"

using namespace Collections::Containers;
using namespace Extensions::Strings;

//
// Initialize the member name map for the map iterator.  Last entry must
// contain a null string pointer.
//

const MQ2TYPEMEMBER MapIterator::MapIteratorMembers[] =
{
    { (DWORD) MapIteratorMembers::Reset, "Reset" },
    { (DWORD) MapIteratorMembers::Advance, "Advance" },
    { (DWORD) MapIteratorMembers::IsEnd, "IsEnd" },
    { (DWORD) MapIteratorMembers::Value, "Value" },
    { (DWORD) MapIteratorMembers::Key, "Key" },
    { 0, 0 }
};

//
// Initialize the member name map for the map.  Last entry must contain a null
// string pointer.
//

const MQ2TYPEMEMBER Map::MapMembers[] =
{
    { (DWORD) MapMembers::Count, "Count" },
    { (DWORD) MapMembers::Clear, "Clear" },
    { (DWORD) MapMembers::Contains, "Contains" },
    { (DWORD) MapMembers::Add, "Add" },
    { (DWORD) MapMembers::Remove, "Remove" },
    { (DWORD) MapMembers::First, "First" },
    { (DWORD) MapMembers::Find, "Find" },
    { 0, 0 }
};

//
// MapIterator methods.
//

//
// When a member function is called on the type, this method is called.
// It returns true if the method succeeded and false otherwise.
//

bool MapIterator::GetMember(MQ2VARPTR VarPtr, PCHAR Member, PCHAR Index, MQ2TYPEVAR &Dest)
{
    MapIterator *pThis;
    const std::string *pItem;

    DebugSpew("MapIterator::GetMember %s", Member);

    //
    // Default return value is FALSE.
    //

    Dest.Int = 0;
    Dest.Type = pBoolType;

    //
    // Map the member name to the id.
    //

    PMQ2TYPEMEMBER pMember = MapIterator::FindMember(Member);
    if (!pMember)
    {
        //
        // No such member.
        //

        return false;
    }

    //
    // Member ID is an MapIteratorMemberEnums enumeration.
    //

    pThis = reinterpret_cast<MapIterator *>(VarPtr.Ptr);
    if (!pThis)
    {
        DebugSpewAlways("MapIterator instance is NULL!");
        return false;
    }

    switch ((enum class MapIteratorMembers) pMember->ID)
    {
        case MapIteratorMembers::Reset:
            //
            // Reset the iterator to the start of the map.   Return the result as
            // TRUE.
            //

            pThis->Reset();

            Dest.Int = 1;
            break;

        case MapIteratorMembers::Advance:
            //
            // Advance the iterator.  Return TRUE if the iterator could be advanced
            // and FALSE otherwise.
            //

            Dest.Int = (int) pThis->Advance();
            break;

        case MapIteratorMembers::IsEnd:
            //
            // Return TRUE if we are at the Last element in the map and FALSE
            // otherwise.
            //

            Dest.Int = (int) pThis->IsEnd();
            break;

        case MapIteratorMembers::Value:
            //
            // Return the current value under the iterator or FALSE if there
            // isn't one.
            //

            if (pThis->Value(&pItem))
            {
                Dest.Ptr = (PVOID) pThis->m_Buffer.SetBuffer(
                    pItem->c_str(),
                    pItem->size() + 1
                );
                Dest.Type = pStringType;
            }
            break;

        case MapIteratorMembers::Key:
            //
            // Return the current key under the iterator or FALSE if there
            // isn't one.
            //

            if (pThis->Key(&pItem))
            {
                Dest.Ptr = (PVOID) pThis->m_Buffer.SetBuffer(
                    pItem->c_str(),
                    pItem->size() + 1
                );
                Dest.Type = pStringType;
            }
            break;

        default:

            //
            // Unknown member!
            //

            return false;
    }

    return true;
}

//
// Convert the iterator to a string.  Output the current key and Value or
// FALSE if there isn't one.
//

bool MapIterator::ToString(MQ2VARPTR VarPtr, PCHAR Destination)
{
    MapIterator *pThis;
    const std::string *item;

    pThis = reinterpret_cast<MapIterator *>(VarPtr.Ptr);
    if (Destination == 0)
    {
        return false;
    }

    //
    // Format the output buffers as (Key, Value).
    // If either the key or the value is missing, write in its place.
    //

    if (strcpy_s(Destination, BUFFER_SIZE, "(") != 0)
    {
        return false;
    }

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

//
// This method is executed when the /varset statement is executed.
// Return false because this operation is not supported.
//

bool MapIterator::FromString(MQ2VARPTR &VarPtr, PCHAR Source)
{
    return false;
}

//
// Return an iterator to a requested key or to the end of the set.
//

KeyValueIterator<std::map<std::string, std::string>, std::string, std::string> *
Map::Find(const std::string & refKey) const
{
    return new MapIterator(m_coll, refKey);
}

//
// When a member function is called on the type, this method is called.
// It returns true if the method succeeded and false otherwise.
//

bool Map::GetMember(MQ2VARPTR VarPtr, PCHAR Member, PCHAR Index, MQ2TYPEVAR &Dest)
{
    Map *pThis;
    MQ2TYPEVAR iteratorTypeVar;
    std::string value;

    DebugSpew("Map::GetMember %s", Member);

    //
    // Default return value is FALSE.
    //

    Dest.Int = 0;
    Dest.Type = pBoolType;

    //
    // Map the member name to the id.
    //

    PMQ2TYPEMEMBER pMember = Map::FindMember(Member);
    if (!pMember)
    {
        //
        // No such member.
        //

        return false;
    }

    //
    // Member ID is an SetMemberEnums enumeration.
    //

    pThis = reinterpret_cast<Map *>(VarPtr.Ptr);
    if (!pThis)
    {
        DebugSpewAlways("Map instance is NULL!");
        return false;
    }

    switch ((enum class MapMembers) pMember->ID)
    {
        case MapMembers::Count:
            //
            // Count of items in the map.
            //

            Dest.Int = (int) pThis->Count();
            Dest.Type = pIntType;
            return true;

        case MapMembers::Clear:
            //
            // Clear the map.  Return the result as TRUE.
            //

            pThis->Clear();

            Dest.Int = 1;
            break;

        case MapMembers::Contains:
            //
            // Does the map contain a key?
            //

            //
            // Check for a valid Index value.
            //

            if (*Index)
            {
                Dest.Int = (int) pThis->Contains(std::string(Index));
            }
            break;

        case MapMembers::Add:
            //
            // Add an item to the map.  Return TRUE if the item was added.
            //

            //
            // We can only add an item if Index is a string.
            //

            if (*Index)
            {
                Dest.Int = (int) AddKeyAndValue(pThis, Index);
            }
            break;

        case MapMembers::Remove:
            //
            // Remove an item from the set.  Return TRUE if it was removed and
            // FALSE otherwise.
            //

            //
            // Only attempt a remove if there is a string.
            //

            if (*Index)
            {
                Dest.Int = (int) pThis->Remove(std::string(Index));
            }
            break;

        case MapMembers::First:
            //
            // Return an iterator on the first element.
            //

            Dest.Ptr = (PVOID) pThis->First().release();

            //
            // Get the MapIterator type and return it.
            //

            MapIterator::TypeDescriptor(0, iteratorTypeVar);
            Dest.Type = iteratorTypeVar.Type;
            break;

        case MapMembers::Find:
            //
            // Return an iterator on a key.
            //

            //
            // It only makes sense to find a non-null key.
            //

            if (*Index)
            {
                Dest.Ptr = (PVOID) pThis->Find(std::string(Index));

                //
                // Get the MapIterator type and return it.
                //

                MapIterator::TypeDescriptor(0, iteratorTypeVar);
                Dest.Type = iteratorTypeVar.Type;
            }
            break;

        default:

            //
            // Unknown member!
            //

            return false;
    }

    return true;
}

//
// Convert the map to a string -- output the count of items.
//

bool Map::ToString(MQ2VARPTR VarPtr, PCHAR Destination)
{
    Map *pThis;

    pThis = reinterpret_cast<Map *>(VarPtr.Ptr);
    if (Destination == nullptr)
    {
        return false;
    }

    errno_t rc;
    rc = Conversions::ToString(pThis->Count(), Destination, BUFFER_SIZE);
    return rc == 0;
}

//
// This method is executed when the /varset statement is executed.  Ignore
// this call.
//

bool Map::FromString(MQ2VARPTR &VarPtr, PCHAR Source)
{
    return false;
}

//
// Add a key and value to the map, returning true if they were
// added and false otherwise.
//

bool Map::AddKeyAndValue(Map * pThis, PCHAR Arguments)
{
    StringExtensions<std::string, std::vector<std::string>> * argument;
    StringExtensions<std::string, std::vector<std::string>> * arg;
    StringExtensions<std::string, std::vector<std::string>> * key;
    StringExtensions<std::string, std::vector<std::string>> * value;
    std::vector<std::string> * splits;
    bool fResult;

    //
    // By default, we succeeded.
    //

    fResult = true;

    //
    // Split the arguments and add the first one as the key and
    // the second as the value.
    //

    argument = new StringExtensions<std::string, std::vector<std::string>>(
        std::string(Arguments)
        );
    splits = argument->Split(std::string(","));

    //
    // There must be two and only two arguments.
    //

    if (splits->size() != 2)
    {
        //
        // Generate an error because we have the incorrect number
        // of arguments.
        //

        fResult = false;
    }
    else
    {
        //
        // Trim the key and value.
        //

        arg = new StringExtensions<std::string, std::vector<std::string>>(
            (*splits)[0]
            );
        key = arg->Trim();

        //
        // Done with the string extension for the key.
        //

        delete arg;

        arg = new StringExtensions<std::string, std::vector<std::string>>(
            (*splits)[1]
            );
        value = arg->Trim();

        //
        // Done with the string extension for the value.
        //

        delete arg;

        //
        // Neither the key nor the value can be empty.
        //

        if ((key->Contents().length() == 0) || (value->Contents().length() == 0))
        {
            fResult = false;
        }
        else
        {
            pThis->Add(key->Contents(), value->Contents());
        }

        //
        // Done with the key and value.
        //

        delete key;
        delete value;
    }

    //
    // Done with the extension string and the splits.
    //

    delete argument;
    delete splits;

    return fResult;
}