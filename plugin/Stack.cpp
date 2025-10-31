
#include "pch.h"
#include "Stack.h"

//
// Initialize the member name map. Last entry must contain a null string
// pointer.
//

const std::vector<MQTypeMember> StackMembers =
{
	{ static_cast<int>(Stack::StackMembers::Count), "Count" },
	{ static_cast<int>(Stack::StackMembers::Push), "Push" },
	{ static_cast<int>(Stack::StackMembers::Pop), "Pop" },
	{ static_cast<int>(Stack::StackMembers::IsEmpty), "IsEmpty" },
	{ static_cast<int>(Stack::StackMembers::Peek), "Peek" },
};

Stack::Stack() : ObjectType(::StackMembers)
{
}

Stack::~Stack()
{
}

bool Stack::GetMember(MQVarPtr VarPtr, const char* Member, char* Index, MQTypeVar& Dest)
{
	Dest.Set(false);
	Dest.Type = mq::datatypes::pBoolType;

	auto pMember = Stack::FindMember(Member);
	if (pMember == nullptr)
	{
		return false;
	}

	Stack* pThis = static_cast<Stack*>(VarPtr.Ptr);
	if (pThis == nullptr)
	{
		return false;
	}


	switch (static_cast<StackMembers>(pMember->ID))
	{
	case StackMembers::Count:
		Dest.Int = (int)pThis->Count();
		Dest.Type = mq::datatypes::pIntType;
		return true;

	case StackMembers::Push:
		if (Index[0])
		{
			if (std::string_view(Index).find_first_not_of(" \t\n\r\f") != std::string::npos)
			{
				pThis->Push(Index);
				Dest.Set(true);
			}
		}
		return true;

	case StackMembers::Pop: {
		// Return the top of the stack, if it isn't empty. If the stack is
		// empty, return FALSE.
		std::unique_ptr<std::string> pValue;
		if (pThis->Pop(&pValue))
		{
			Dest.Ptr = (void*)pThis->m_Buffer.SetBuffer(pValue->c_str(), pValue->size() + 1);
			Dest.Type = mq::datatypes::pStringType;
		}
		return true;
	}

	case StackMembers::IsEmpty:
		Dest.Set(pThis->IsEmpty());
		return true;

	case StackMembers::Peek: {
		// Return the top of the stack, if the stack is not empty. Don't
		// remove the entry from the stack. If the stack is empty, return FALSE.
		std::unique_ptr<std::string> pValue;
		if (pThis->Peek(&pValue))
		{
			Dest.Ptr = (void*)pThis->m_Buffer.SetBuffer(pValue->c_str(), pValue->size() + 1);
			Dest.Type = mq::datatypes::pStringType;
		}
		return true;
	}

	default: break;
	}

	return false;
}

bool Stack::ToString(MQVarPtr VarPtr, char* Destination)
{
	Stack* pThis = static_cast<Stack*>(VarPtr.Ptr);
	if (Destination == nullptr)
	{
		return false;
	}

	sprintf_s(Destination, MAX_STRING, "%zu", pThis->Count());
	return true;
}

bool Stack::FromString(MQVarPtr& VarPtr, const char* Source)
{
	Stack* pDest = static_cast<Stack*>(VarPtr.Ptr);
	if (pDest != nullptr && Source[0])
	{
		pDest->Push(Source);
	}

	return false;
}
