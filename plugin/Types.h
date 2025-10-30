//
// Provide classes and interfaces for interfacing with the MQ type system.
//

#pragma once

#include "mq/Plugin.h"

#include <string>
#include <map>

// Map from type names onto their ObjectTypes.
class TypeMap
{
public:
	// Add a new type name and type instance to the type map. If the
	// type name already exists, return false. Otherwise, return true.
	static bool AddType(const char* typeName, MQ2Type* typeInstance);

	// Return true if a name is in the map and false otherwise.
	static bool HasName(const char* typeName);

	// Return the type instance for a type name or null if it was never
	// registered.
	static MQ2Type* GetTypeInstanceForTypeName(const char* typeName);

	// Remove the typename and delete the type instance. Return true if
	// the type name was found and removed and false otherwise.
	static bool RemoveType(const char* typeName);
};

// BaseType is an interface derived from MQ2Type which provides default
// functionality based on the MQ2Type interface.
template <typename ObjectClass>
class BaseType : public MQ2Type
{
public:
	// Buffer pointed to by naked PCHAR is at least this long.
	const int BUFFER_SIZE = MAX_STRING;

	// Initialize our methods and properties in MQ.
	explicit BaseType(const std::vector<MQTypeMember>& aMembers)
		: MQ2Type(ObjectClass::GetTypeName())
	{
		for (const MQTypeMember& member : aMembers)
		{
			AddMember(member.ID, member.Name);
		}
	}

	virtual ~BaseType() override
	{
	}

	// By default, this type can be deleted.
	virtual bool CanDelete() const
	{
		return true;
	}

	// This method is executed when the /vardata statement is executed on
	// the type. Delete the destination instance and set the source
	// instance to it.
	virtual bool FromData(MQVarPtr& VarPtr, const MQTypeVar& Source) override
	{
		if (Source.Type != TypeMap::GetTypeInstanceForTypeName(ObjectClass::GetTypeName()))
		{
			return false;
		}

		ObjectClass* pDest = static_cast<ObjectClass*>(VarPtr.Ptr);

		// Delete the destination object if it is not the same as the
		// source object and set the destination to the source.
		if (pDest != Source.Ptr)
		{
			if (CanDelete())
			{
				delete pDest;
			}
		}

		VarPtr.Ptr = Source.Ptr;

		return true;
	}

	// Delete an instance of ObjectClass.
	virtual void FreeVariable(MQVarPtr& VarPtr) override
	{
		if (CanDelete())
		{
			delete static_cast<ObjectClass*>(VarPtr.Ptr);
		}

		VarPtr.Ptr = nullptr;
	}

	// The default implementation of GetMember returns false -- there
	// aren't any members on the type.
	virtual bool GetMember(MQVarPtr VarPtr, const char* Member, char* Index, MQTypeVar& Dest) override
	{
		return false;
	}

	// Register the type, using an instance as our unique type
	// descriptor.
	static void RegisterType(ObjectClass* instance)
	{
		// If we were already registered, do nothing.
		if (!TypeMap::HasName(ObjectClass::GetTypeName()))
		{
			// Associate the type with an instance -- this lets us compare the type information.
			TypeMap::AddType(ObjectClass::GetTypeName(), instance);
			AddTopLevelObject(ObjectClass::GetTypeName(), TypeDescriptor);
		}
	}

	// Unregister the type
	static void UnregisterType()
	{
		// If we were never registered, do nothing.
		if (TypeMap::HasName(ObjectClass::GetTypeName()))
		{
			// Remove the type name and unregister the class name and type name.
			RemoveTopLevelObject(ObjectClass::GetTypeName());
			TypeMap::RemoveType(ObjectClass::GetTypeName());
		}
	}

	static MQ2Type* GetTypeInstance()
	{
		return TypeMap::GetTypeInstanceForTypeName(ObjectClass::GetTypeName());
	}

	// Return the MQ Type.
	static bool TypeDescriptor(const char* szName, MQTypeVar& Dest)
	{
		Dest.DWord = 1;
		Dest.Type = GetTypeInstance();

		return true;
	}
};

// ReferenceType is a type with methods and properties. It can not be
// created by a /declare statement and is returned by a method on
// an ObjectType. A ReferenceType takes an argument to its constructor
// which is a reference to an ObjectClass.
template <typename ObjectClass, typename Reference>
class ReferenceType : public BaseType<ObjectClass>
{
public:
	explicit ReferenceType(const std::vector<MQTypeMember>& aMembers)
		: BaseType<ObjectClass>(aMembers)
	{
	}

	virtual ~ReferenceType() override
	{
	}

	// This type cannot be deleted.
	virtual bool CanDelete() const override
	{
		return false;
	}

	// Register the type - reference types have an instance bound to a
	// reference of Reference.
	static void RegisterType()
	{
		Reference* refClass = new Reference();
		BaseType<ObjectClass>::RegisterType(new ObjectClass(*refClass));
	}
};

// ObjectType is a type that has methods and properties and can be
// created by a /declare statement.
template <typename ObjectClass>
class ObjectType : public BaseType<ObjectClass>
{
public:
	ObjectType(const std::vector<MQTypeMember>& aMembers)
		: BaseType<ObjectClass>(aMembers)
	{
	}

	virtual ~ObjectType() override
	{
	}

	// Allocate a new instance of this ObjectType.
	virtual void InitVariable(MQVarPtr& VarPtr) override
	{
		VarPtr.Ptr = new ObjectClass();
	}

	// Register the type with no arguments.
	static void RegisterType()
	{
		BaseType<ObjectClass>::RegisterType(new ObjectClass());
	}
};
