#include "pch.h"
#include "Set.h"

#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

//
// Test Set Iterator operations (Reset, Advance, IsEnd and Value).
// Set iterators are acquired by calling Find or First on a Set.
//

TEST_CLASS(SetIteratorUnitTests)
{
public:
	BEGIN_TEST_CLASS_ATTRIBUTE()
		TEST_CLASS_ATTRIBUTE(L"Collections", L"Set")
		TEST_CLASS_ATTRIBUTE(L"Iterators", L"Set")
	END_TEST_CLASS_ATTRIBUTE()

	//
	// Populate the set used by the iterator tests.
	//

	SetIteratorUnitTests()
	{
		m_set.Add("A");
		m_set.Add("B");
		m_set.Add("C");
	}

	//
	// Test that we can acquire an iterator on the set.
	//
	// Result: A non-null iterator should be returned.
	//

	TEST_METHOD(AcqurieIteratorFromFirst)
	{
		auto iterator = m_set.First();

		Assert::IsNotNull(iterator, L"Iterator should not be null.");
	}

	//
	// Test that we can acquire a new iterator on each of the elements
	// by using Find.
	//
	// Result: Non-null iterators should be returned where IsEnd is false.
	//

	TEST_METHOD(AcquireIteratorFromFind)
	{
		auto iterator = m_set.Find("A");

		Assert::IsNotNull(iterator, L"Iterator should not be null.");
		Assert::IsFalse(iterator->IsEnd(), L"Iterator should not be at end.");

		iterator = m_set.Find("B");

		Assert::IsNotNull(iterator, L"Iterator should not be null.");
		Assert::IsFalse(iterator->IsEnd(), L"Iterator should not be at end.");

		iterator = m_set.Find("C");

		Assert::IsNotNull(iterator, L"Iterator should not be null.");
		Assert::IsFalse(iterator->IsEnd(), L"Iterator should not be at end.");
	}

	//
	// Test Find on an element not in the set.
	//
	// Result: An iterator should be returned where IsEnd is true.
	//

	TEST_METHOD(AcquireIteratorForNonexistantElement)
	{
		auto iterator = m_set.Find("D");

		Assert::IsNotNull(iterator, L"Iterator should not be null.");
		Assert::IsTrue(iterator->IsEnd(), L"Iterator should be at end.");
	}

	//
	// Test that returning a new iterator is not at the end.
	//
	// Result: IsEnd should be false.
	//

	TEST_METHOD(AcquireIteratorIsNotAtEnd)
	{
		auto iterator = m_set.First();

		Assert::IsNotNull(iterator, L"Iterator should not be null.");
		Assert::IsFalse(iterator->IsEnd(), L"Iterator should not be at end.");
	}

	//
	// Test that advancing Count() times reaches the end.
	//
	// Result: Advance() should return true for Count() - 1 calls then
	// it should return False and IsEnd should be true.
	//

	TEST_METHOD(AcquireIteratorAdvance)
	{
		auto iterator = m_set.First();
		WalkIteratorOverSet(m_set, iterator);
	}

	//
	// Test the Reseting the iterator after reaching the end lets us
	// traverse through the collection again.
	//
	// Result: Reset should permit multiple traverals through the set.
	//

	TEST_METHOD(IteratorReset)
	{
		auto iterator = m_set.First();
		WalkIteratorOverSet(m_set, iterator);

		iterator->Reset();

		Assert::IsFalse(iterator->IsEnd(), L"Iterator should not be at end.");
		WalkIteratorOverSet(m_set, iterator);
	}

	//
	// Test the Value method on an iterator.
	//
	// Result: The value method should return each element in the set.
	//

	TEST_METHOD(ValueUnderIterator)
	{
		auto iterator = m_set.First();
		std::string const* value = nullptr;

		Assert::IsTrue(iterator->Value(&value), L"Iterator Value should not fail.");
		Assert::IsNotNull(value, L"Iterator Value should not be null.");
		Assert::AreEqual(*value, std::string("A"), L"Iterator Value should be 'A'.");

		Assert::IsTrue(iterator->Advance(), L"Iterator Advance should not fail.");
		Assert::IsTrue(iterator->Value(&value), L"Iterator Value should not fail.");
		Assert::IsNotNull(value, L"Iterator Value should not be null.");
		Assert::AreEqual(*value, std::string("B"), L"Iterator Value should be 'B'.");

		Assert::IsTrue(iterator->Advance(), L"Iterator Advance should not fail.");
		Assert::IsTrue(iterator->Value(&value), L"Iterator Value should not fail.");
		Assert::IsNotNull(value, L"Iterator Value should not be null.");
		Assert::AreEqual(*value, std::string("C"), L"Iterator Value should be 'C'.");
	}

private:
	// Acquire an iterator and walk through each element.
	void WalkIteratorOverSet(const Set& s, ValueIterator<std::set<std::string>>* iterator) const
	{
		Assert::IsNotNull(iterator, L"Iterator should not be null.");
		Assert::IsFalse(iterator->IsEnd(), L"Iterator should not be at end.");

		for (size_t i = 1; i < s.Count(); ++i)
		{
			Assert::IsTrue(iterator->Advance(), L"Iterator Advance should not fail.");
		}

		Assert::IsTrue(iterator->Advance(), L"Iterator Advance should not fail.");
		Assert::IsTrue(iterator->IsEnd(), L"Iterator Advance should be at end.");
	}

	Set m_set;
};
