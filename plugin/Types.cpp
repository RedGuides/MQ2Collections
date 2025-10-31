
#include "pch.h"
#include "Types.h"

#include <map>

// Map from type names onto a single instance of the type that indicates
// whether a variable is of that type.
static std::map<std::string, std::unique_ptr<MQ2Type>> s_typeMap;


bool TypeMap::AddType(const char* typeName, MQ2Type* typeInstance)
{
	std::string sTypeName(typeName);
	if (s_typeMap.find(sTypeName) == s_typeMap.end())
	{
		s_typeMap[sTypeName] = std::unique_ptr<MQ2Type>(typeInstance);
		return true;
	}

	return false;
}

// Return true if a name is in the map and false otherwise.
bool TypeMap::HasName(const char* typeName)
{
	return s_typeMap.find(typeName) != s_typeMap.end();
}

MQ2Type* TypeMap::GetTypeInstanceForTypeName(const char* typeName)
{
	auto itTypes = s_typeMap.find(typeName);
	if (itTypes == s_typeMap.end())
	{
		return nullptr;
	}

	return itTypes->second.get();
}

bool TypeMap::RemoveType(const char* typeName)
{
	// See if the type name exists in the map.  If it does, remove
	// it and return true.
	auto it = s_typeMap.find(typeName);
	if (it != s_typeMap.end())
	{
		s_typeMap.erase(it);
		return true;
	}

	return false;
}
