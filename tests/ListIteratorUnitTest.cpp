#include "pch.h"
#include "List.h"

#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

//
// Test List Iterator Operations (Reset, Advance, IsEnd, Value).
// List iterators are acquireed by calling Find or First on a List.
//

TEST_CLASS(ListIteratorInterfaceUnitTests)
{
public:
	BEGIN_TEST_CLASS_ATTRIBUTE()
		TEST_CLASS_ATTRIBUTE(L"Collections", L"List")
		TEST_CLASS_ATTRIBUTE(L"Iterators", L"List")
	END_TEST_CLASS_ATTRIBUTE()

		//
		// Populate the list used by the iterator tests.
		//

		ListIteratorInterfaceUnitTests()
	{
		m_list.Append("A");
		m_list.Append("B");
		m_list.Append("C");
		m_list.Append("D");
		m_list.Append("E");
	}

	//
	// Acquire an iterator using First on an empty collection.
	//
	// Result: a non-null iterator should be returned and IsEnd should be true.
	//

	TEST_METHOD(AcquireIteratorUsingFirstOnEmptyList)
	{
		List l;

		auto iterator = l.First();

		Assert::IsNotNull(iterator, L"List iterator must not be null.");
		Assert::IsTrue(iterator->IsEnd(), L"List iterator must not be at end.");
	}

	//
	// Acquire an iterator using First on an empty collection and Clone it.
	//
	// Result: a non-null iterator should be returned and IsEnd should be true
	// for both the initial iterator and the clone.
	//

	TEST_METHOD(CloneIteratorFromFirstOnEmptyList)
	{
		List l;

		auto iterator = l.First();
		auto clone = dynamic_cast<ListIterator*>(iterator)->Clone();

		Assert::IsNotNull(iterator, L"List iterator must not be null.");
		Assert::IsTrue(iterator->IsEnd(), L"List iterator must not be at end.");

		Assert::IsNotNull(clone.get(), L"Cloned List iterator must not be null.");
		Assert::IsTrue(clone->IsEnd(), L"Cloned List iterator must not be at end.");
	}

	//
	// Acquire an iterator using the First method.
	//
	// Result: a non-null iterator should be returned and IsEnd should be false.
	//

	TEST_METHOD(AcquireIteratorUsingFirst)
	{
		auto iterator = m_list.First();

		Assert::IsNotNull(iterator, L"List iterator must not be null.");
		Assert::IsFalse(iterator->IsEnd(), L"List iterator must not be at end.");
	}

	//
	// Acquire an iterator using the First method and Clone it.
	//
	// Result: a non-null iterator should be returned and IsEnd should be false
	// for both the iterator and the clone.
	//

	TEST_METHOD(CloneIteratorFromFirst)
	{
		auto iterator = m_list.First();
		auto clone = dynamic_cast<ListIterator*>(iterator)->Clone();

		Assert::IsNotNull(iterator, L"List iterator must not be null.");
		Assert::IsFalse(iterator->IsEnd(), L"List iterator must not be at end.");

		Assert::IsNotNull(clone.get(), L"Cloned List iterator must not be null.");
		Assert::IsFalse(clone->IsEnd(), L"Cloned List iterator must not be at end.");
	}

	//
	// Acquire an iterator using Find on each element.
	//
	// Result: a non-null iterator should be returned where IsEnd is false.
	//

	TEST_METHOD(AcquireIteratorUsingFind)
	{
		auto iterator = m_list.Find("A");

		Assert::IsNotNull(iterator, L"List iterator must not be null.");
		Assert::IsFalse(iterator->IsEnd(), L"List iterator must not be at end.");

		iterator = m_list.Find("B");

		Assert::IsNotNull(iterator, L"List iterator must not be null.");
		Assert::IsFalse(iterator->IsEnd(), L"List iterator must not be at end.");

		iterator = m_list.Find("C");

		Assert::IsNotNull(iterator, L"List iterator must not be null.");
		Assert::IsFalse(iterator->IsEnd(), L"List iterator must not be at end.");

		iterator = m_list.Find("D");

		Assert::IsNotNull(iterator, L"List iterator must not be null.");
		Assert::IsFalse(iterator->IsEnd(), L"List iterator must not be at end.");

		iterator = m_list.Find("E");

		Assert::IsNotNull(iterator, L"List iterator must not be null.");
		Assert::IsFalse(iterator->IsEnd(), L"List iterator must not be at end.");
	}

	// Acquire an iterator using Find on each element and Clone them.
	//
	// Result: a non-null iterator should be returned where IsEnd is false
	// for each of the iterators and the clones.
	//

	TEST_METHOD(CloneIteratorUsingFind)
	{
		auto iterator = m_list.Find("A");
		auto clone = dynamic_cast<ListIterator*>(iterator)->Clone();

		Assert::IsNotNull(iterator, L"List iterator must not be null.");
		Assert::IsFalse(iterator->IsEnd(), L"List iterator must not be at end.");

		Assert::IsNotNull(clone.get(), L"Cloned List iterator must not be null.");
		Assert::IsFalse(clone->IsEnd(), L"Cloned List iterator must not be at end.");

		iterator = m_list.Find("B");
		clone = dynamic_cast<ListIterator*>(iterator)->Clone();

		Assert::IsNotNull(iterator, L"List iterator must not be null.");
		Assert::IsFalse(iterator->IsEnd(), L"List iterator must not be at end.");

		Assert::IsNotNull(clone.get(), L"Cloned List iterator must not be null.");
		Assert::IsFalse(clone->IsEnd(), L"Cloned List iterator must not be at end.");

		iterator = m_list.Find("C");
		clone = dynamic_cast<ListIterator*>(iterator)->Clone();

		Assert::IsNotNull(iterator, L"List iterator must not be null.");
		Assert::IsFalse(iterator->IsEnd(), L"List iterator must not be at end.");

		Assert::IsNotNull(clone.get(), L"Cloned List iterator must not be null.");
		Assert::IsFalse(clone->IsEnd(), L"Cloned List iterator must not be at end.");

		iterator = m_list.Find("D");
		clone = dynamic_cast<ListIterator*>(iterator)->Clone();

		Assert::IsNotNull(iterator, L"List iterator must not be null.");
		Assert::IsFalse(iterator->IsEnd(), L"List iterator must not be at end.");

		Assert::IsNotNull(clone.get(), L"Cloned List iterator must not be null.");
		Assert::IsFalse(clone->IsEnd(), L"Cloned List iterator must not be at end.");

		iterator = m_list.Find("E");
		clone = dynamic_cast<ListIterator*>(iterator)->Clone();

		Assert::IsNotNull(iterator, L"List iterator must not be null.");
		Assert::IsFalse(iterator->IsEnd(), L"List iterator must not be at end.");

		Assert::IsNotNull(clone.get(), L"Cloned List iterator must not be null.");
		Assert::IsFalse(clone->IsEnd(), L"Cloned List iterator must not be at end.");
	}

	//
	// Acquire an iterator on an element not in the list.
	//
	// Result: a non-null iterator should be returned where IsEnd is true.
	//

	TEST_METHOD(AcquireIteratorForNonexistantElement)
	{
		auto iterator = m_list.Find("Z");

		Assert::IsNotNull(iterator, L"List iterator must not be null.");
		Assert::IsTrue(iterator->IsEnd(), L"List iterator must be at end.");
	}

	//
	// Acquire an iterator on an element not in the list.
	//
	// Result: a non-null iterator should be returned where IsEnd is true.
	//

	TEST_METHOD(CloneIteratorForNonexistantElement)
	{
		auto iterator = m_list.Find("Z");
		auto clone = dynamic_cast<ListIterator*>(iterator)->Clone();

		Assert::IsNotNull(iterator, L"List iterator must not be null.");
		Assert::IsTrue(iterator->IsEnd(), L"List iterator must be at end.");

		Assert::IsNotNull(clone.get(), L"Cloned List iterator must not be null.");
		Assert::IsTrue(clone->IsEnd(), L"Cloned List iterator must be at end.");
	}

	//
	// Advance Count() times on a list.
	//
	// Result: Advance() should return true for Count() - 1 calls then
	// it should return False and IsEnd should be true.
	//

	TEST_METHOD(WalkIteratorUsingAdvance)
	{
		auto iterator = m_list.First();

		WalkIteratorOverList(m_list, iterator);
	}

	//
	// Advance Count() times on a list.
	//
	// Result: Advance() should return true for Count() - 1 calls then
	// it should return False and IsEnd should be true.
	//

	TEST_METHOD(CloneWalkIteratorUsingAdvance)
	{
		auto iterator = m_list.First();
		auto clone = dynamic_cast<ListIterator*>(iterator)->Clone();

		WalkIteratorOverList(m_list, iterator);

		//
		// Now Walk over the clone.
		//

		WalkIteratorOverList(m_list, clone.get());
	}

	//
	// Reset the iterator after reaching the end and traverse through the
	// collection again.
	//
	// Result: reset should permit multiple traverals through the list.
	//

	TEST_METHOD(UseResetOnIterator)
	{
		auto iterator = m_list.First();
		WalkIteratorOverList(m_list, iterator);

		iterator->Reset();

		Assert::IsFalse(iterator->IsEnd(), L"List iterator after Reset must not be at end.");
		WalkIteratorOverList(m_list, iterator);
	}

	//
	// Reset the iterator after reaching the end and traverse through the
	// collection again.
	//
	// Result: reset should permit multiple traverals through the list.
	//

	TEST_METHOD(CloneUseResetOnIterator)
	{
		auto iterator = m_list.First();
		auto clone = dynamic_cast<ListIterator*>(iterator)->Clone();

		WalkIteratorOverList(m_list, iterator);

		iterator->Reset();

		Assert::IsFalse(iterator->IsEnd(), L"List iterator after Reset must not be at end.");
		WalkIteratorOverList(m_list, iterator);

		//
		// Do the same thing with the clone. The state of the clone should not be
		// affected by the state of the original iterator.
		//

		WalkIteratorOverList(m_list, clone.get());

		clone->Reset();

		Assert::IsFalse(clone->IsEnd(), L"Cloned List iterator after Reset must not be at end.");
		WalkIteratorOverList(m_list, clone.get());

	}

	//
	// Retrieve the value under an iterator.
	//
	// Result: the value method should return each element in the list.
	//

	TEST_METHOD(RetrieveValueUnderIterator)
	{
		auto iterator = m_list.First();
		std::string const* value = nullptr;

		Assert::IsTrue(iterator->Value(&value), L"Could not retrieve Value from list iterator.");
		Assert::IsNotNull(value, L"Value returned must not be null.");
		Assert::AreEqual(*value, std::string("A"), L"Item returned does not match expected value.");

		Assert::IsTrue(iterator->Advance(), L"Advance of list iterator should not have failed.");
		Assert::IsTrue(iterator->Value(&value), L"Value returned must not be null.");
		Assert::IsNotNull(value, L"Value returned must not be null.");
		Assert::AreEqual(*value, std::string("B"), L"Item returned does not match expected value.");

		Assert::IsTrue(iterator->Advance(), L"Advance of list iterator should not have failed.");
		Assert::IsTrue(iterator->Value(&value), L"Value returned must not be null.");
		Assert::IsNotNull(value, L"Value returned must not be null.");
		Assert::AreEqual(*value, std::string("C"), L"Item returned does not match expected value.");

		Assert::IsTrue(iterator->Advance(), L"Advance of list iterator should not have failed.");
		Assert::IsTrue(iterator->Value(&value), L"Value returned must not be null.");
		Assert::IsNotNull(value, L"Value returned must not be null.");
		Assert::AreEqual(*value, std::string("D"), L"Item returned does not match expected value.");

		Assert::IsTrue(iterator->Advance(), L"Advance of list iterator should not have failed.");
		Assert::IsTrue(iterator->Value(&value), L"Value returned must not be null.");
		Assert::IsNotNull(value, L"Value returned must not be null.");
		Assert::AreEqual(*value, std::string("E"), L"Item returned does not match expected value.");
	}

	//
	// Retrieve the value under an iterator.
	//
	// Result: the value method should return each element in the list.
	//

	TEST_METHOD(CloneRetrieveValueUnderIterator)
	{
		auto iterator = m_list.First();
		auto clone = dynamic_cast<ListIterator*>(iterator)->Clone();
		std::string const* value = nullptr;

		Assert::IsTrue(iterator->Value(&value), L"Could not retrieve Value from list iterator.");
		Assert::IsNotNull(value, L"Value returned must not be null.");
		Assert::AreEqual(*value, std::string("A"), L"Item returned does not match expected value.");

		Assert::IsTrue(iterator->Advance(), L"Advance of list iterator should not have failed.");
		Assert::IsTrue(iterator->Value(&value), L"Value returned must not be null.");
		Assert::IsNotNull(value, L"Value returned must not be null.");
		Assert::AreEqual(*value, std::string("B"), L"Item returned does not match expected value.");

		Assert::IsTrue(iterator->Advance(), L"Advance of list iterator should not have failed.");
		Assert::IsTrue(iterator->Value(&value), L"Value returned must not be null.");
		Assert::IsNotNull(value, L"Value returned must not be null.");
		Assert::AreEqual(*value, std::string("C"), L"Item returned does not match expected value.");

		Assert::IsTrue(iterator->Advance(), L"Advance of list iterator should not have failed.");
		Assert::IsTrue(iterator->Value(&value), L"Value returned must not be null.");
		Assert::IsNotNull(value, L"Value returned must not be null.");
		Assert::AreEqual(*value, std::string("D"), L"Item returned does not match expected value.");

		Assert::IsTrue(iterator->Advance(), L"Advance of list iterator should not have failed.");
		Assert::IsTrue(iterator->Value(&value), L"Value returned must not be null.");
		Assert::IsNotNull(value, L"Value returned must not be null.");
		Assert::AreEqual(*value, std::string("E"), L"Item returned does not match expected value.");

		//
		// Do the same thing for the clone.
		//

		Assert::IsTrue(clone->Value(&value), L"Clone Could not retrieve Value from list iterator.");
		Assert::IsNotNull(value, L"Clone Value returned must not be null.");
		Assert::AreEqual(*value, std::string("A"), L"Clone Item returned does not match expected value.");

		Assert::IsTrue(clone->Advance(), L"Clone Advance of list iterator should not have failed.");
		Assert::IsTrue(clone->Value(&value), L"Clone Value returned must not be null.");
		Assert::IsNotNull(value, L"Clone Value returned must not be null.");
		Assert::AreEqual(*value, std::string("B"), L"Clone Item returned does not match expected value.");

		Assert::IsTrue(clone->Advance(), L"Clone Advance of list iterator should not have failed.");
		Assert::IsTrue(clone->Value(&value), L"Clone Value returned must not be null.");
		Assert::IsNotNull(value, L"Clone Value returned must not be null.");
		Assert::AreEqual(*value, std::string("C"), L"Clone Item returned does not match expected value.");

		Assert::IsTrue(clone->Advance(), L"Clone Advance of list iterator should not have failed.");
		Assert::IsTrue(clone->Value(&value), L"Clone Value returned must not be null.");
		Assert::IsNotNull(value, L"Clone Value returned must not be null.");
		Assert::AreEqual(*value, std::string("D"), L"Clone Item returned does not match expected value.");

		Assert::IsTrue(clone->Advance(), L"Clone Advance of list iterator should not have failed.");
		Assert::IsTrue(clone->Value(&value), L"Clone Value returned must not be null.");
		Assert::IsNotNull(value, L"Clone Value returned must not be null.");
		Assert::AreEqual(*value, std::string("E"), L"Clone Item returned does not match expected value.");
	}

private:
	//
	// Acquire an iterator and walk through each element.
	//

	void WalkIteratorOverList(const List& l, ValueIterator<std::list<std::string>>* iterator) const
	{
		Assert::IsNotNull(iterator, L"Iterator should not be null.");
		Assert::IsFalse(iterator->IsEnd(), L"Iterator should not be at end.");

		for (size_t i = 1; i < l.Count(); ++i)
		{
			Assert::IsTrue(iterator->Advance(), L"Could not advance iterator.");
		}

		Assert::IsTrue(iterator->Advance(), L"Could not advance iterator.");
		Assert::IsTrue(iterator->IsEnd(), L"Expected IsEnd to return true.");
	}

	List m_list;
};
