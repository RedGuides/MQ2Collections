#include "pch.h"
#include "Queue.h"

const std::vector<MQTypeMember> QueueMembers =
{
	{ static_cast<int>(Queue::QueueMembers::Count), "Count" },
	{ static_cast<int>(Queue::QueueMembers::Push), "Push" },
	{ static_cast<int>(Queue::QueueMembers::Pop), "Pop" },
	{ static_cast<int>(Queue::QueueMembers::IsEmpty), "IsEmpty" },
	{ static_cast<int>(Queue::QueueMembers::Peek), "Peek" },
};

Queue::Queue()
	: ObjectType(::QueueMembers)
{
}

Queue::~Queue()
{
}

bool Queue::GetMember(MQVarPtr VarPtr, const char* Member, char* Index, MQTypeVar& Dest)
{
	Dest.Set(false);
	Dest.Type = mq::datatypes::pBoolType;

	auto pMember = Queue::FindMember(Member);
	if (pMember == nullptr)
	{
		return false;
	}

	Queue* pThis = static_cast<Queue*>(VarPtr.Ptr);
	if (pThis == nullptr)
	{
		return false;
	}

	switch (static_cast<Queue::QueueMembers>(pMember->ID))
	{
	case QueueMembers::Count:
		Dest.Int = (int)pThis->Count();
		Dest.Type = mq::datatypes::pIntType;
		return true;

	case QueueMembers::Push:
		if (Index[0])
		{
			if (std::string_view(Index).find_first_not_of(" \t\n\r\f") != std::string::npos)
			{
				pThis->Push(Index);
				Dest.Set(true);
			}
		}
		return true;

	case QueueMembers::Pop: {
		// Return the front of the stack, if it isn't empty. If the queue is
		// empty, return FALSE.
		std::unique_ptr<std::string> pValue;
		if (pThis->Pop(&pValue))
		{
			Dest.Ptr = (void*)pThis->m_Buffer.SetBuffer(pValue->c_str(), pValue->size() + 1);
			Dest.Type = mq::datatypes::pStringType;
		}
		return true;
	}

	case QueueMembers::IsEmpty:
		Dest.Set(pThis->IsEmpty());
		return true;

	case QueueMembers::Peek: {
		// Return the top of the queue, if the queue is not empty. Don't
		// remove the entry from the queue. If the queue is empty, return FALSE.
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

bool Queue::ToString(MQVarPtr VarPtr, PCHAR Destination)
{
	Queue* pThis = static_cast<Queue*>(VarPtr.Ptr);
	if (Destination == nullptr)
	{
		return false;
	}

	sprintf_s(Destination, MAX_STRING, "%zu", pThis->Count());
	return true;
}

bool Queue::FromString(MQVarPtr& VarPtr, const char* Source)
{
	Queue* pDest = static_cast<Queue*>(VarPtr.Ptr);

	if (pDest != nullptr && Source[0])
	{
		pDest->Push(Source);
	}

	return false;
}
