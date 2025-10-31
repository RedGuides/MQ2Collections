//
// Queue - Queue of strings for MQ
//

#pragma once

#include "BufferManager.h"
#include "Types.h"

#include <string>
#include <queue>

//
// A queue is a collection where an entry is inserted (pushed) onto the
// end and popped off the front.
//

class Queue : public ObjectType<Queue>
{
public:
	enum class QueueMembers
	{
		Count = 1,
		Push,
		Pop,
		IsEmpty,
		Peek
	};

	Queue();
	virtual ~Queue() override;

	Queue(const Queue&) = delete;
	const Queue& operator=(const Queue&) = delete;

	static const char* GetTypeName()
	{
		return "queue";
	}

	// Return the number of entries on the queue.
	size_t Count() const
	{
		return m_coll.size();
	}

	// Push an entry onto the queue.
	void Push(const std::string& item)
	{
		m_coll.push(item);
	}

	// If the queue isn't empty, return the first element and remove
	// it from the queue. The method returns true if the queue is
	// empty and false otherwise.
	bool Pop(std::unique_ptr<std::string>* item)
	{
		if (IsEmpty())
		{
			return false;
		}

		*item = std::make_unique<std::string>(m_coll.front());
		m_coll.pop();
		return true;
	}

	// If the queue is empty, return true. Otherwise, return false.
	bool IsEmpty() const
	{
		return m_coll.empty();
	}

	// If the queue isn't empty, return the front element. The method
	// returns true if the queue is empty and false otherwie.
	bool Peek(std::unique_ptr<std::string>* item) const
	{
		if (IsEmpty())
		{
			return false;
		}

		*item = std::make_unique<std::string>(m_coll.front());
		return true;
	}

	// When a member function is called on the type, this method is called.
	// It returns true if the method succeeded and false otherwise.
	virtual bool GetMember(MQVarPtr VarPtr, const char* Member, char* Index, MQTypeVar& Dest) override;

	// Convert the queue to a string -- output the count of items.
	virtual bool ToString(MQVarPtr VarPtr, char* Destination) override;

	// This method is executed when the /varset statement is executed. Treat
	// this as a queue push call.
	virtual bool FromString(MQVarPtr& VarPtr, const char* Source) override;

private:
	// Collection on which our queue is implemented.
	std::queue<std::string> m_coll;

	// Buffer containing the value of an item returned from the queue.
	BufferManager<char> m_Buffer;
};
