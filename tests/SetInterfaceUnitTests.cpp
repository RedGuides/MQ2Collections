#include "pch.h"
#include "Set.h"

#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

//
// Test Set Operations (Creation, Count, Clear, Contains, Add and Remove)
//

TEST_CLASS(SetInterfaceUnitTests)
{
public:
	BEGIN_TEST_CLASS_ATTRIBUTE()
		TEST_CLASS_ATTRIBUTE(L"Collections", L"Set")
	END_TEST_CLASS_ATTRIBUTE()

	//
	// Test the Set constructor.
	//
	// Result: a new zero element set should be constructed.
	//

	TEST_METHOD(Constructor)
	{
		Set s;

		Assert::AreEqual(static_cast<size_t>(0), s.Count(), L"Expected set to be empty.");
	}

	//
	// Add a string to a set.
	//
	// Result: the set should contain one element.
	//

	TEST_METHOD(MakeSetOfOneElement)
	{
		Set s;

		s.Add("A");

		Assert::AreEqual(static_cast<size_t>(1), s.Count(), L"Expected set to contain element.");
	}

	//
	// Add three strings to a set.
	// 
	// Result: the set should contain three elements.
	//

	TEST_METHOD(MakeSetOfThreeElements)
	{
		Set s;

		InsertElements(&s);

		Assert::AreEqual(static_cast<size_t>(3), s.Count(), L"Expected set to contain three elements.");
	}

	//
	// Add an element to a set and test if it is there.
	//
	// Result: the set should contain the element.
	//

	TEST_METHOD(ContainsOneElement)
	{
		Set s;

		s.Add("A");

		Assert::IsTrue(s.Contains("A"), L"Expected set to contain 'A'.");
	}

	//
	// Add three elements to a set and test that it contains all three
	// elements.
	//
	// Result: the set should contain all three elements.
	//

	TEST_METHOD(ContainsThreeElements)
	{
		Set s;

		InsertElements(&s);

		Assert::IsTrue(s.Contains("A"), L"Expected set to contain 'A'.");
		Assert::IsTrue(s.Contains("B"), L"Expected set to contain 'B'.");
		Assert::IsTrue(s.Contains("C"), L"Expected set to contain 'C'.");
	}

	//
	// Add an element to a set and test if another element is there.
	//
	// Result: the set should not contain the element.
	//

	TEST_METHOD(DoesNotContainsAnElement)
	{
		Set s;

		s.Add("A");

		Assert::IsFalse(s.Contains("B"), L"Set should not contain 'Z'.");
	}

	//
	// Create a set and clear it.
	//
	// Result: the set should contain zero elements.
	//

	TEST_METHOD(ClearedEmptySetContainsNoElements)
	{
		Set s;

		s.Clear();

		Assert::AreEqual(static_cast<size_t>(0), s.Count(), L"Set should have a size of zero.");
	}

	//
	// Create a new set. Add three elements and clear it.
	//
	// Result: the set should contain zero elements.
	//

	TEST_METHOD(ClearedSetContainsNoElements)
	{
		Set s;

		InsertElements(&s);
		s.Clear();

		Assert::AreEqual(static_cast<size_t>(0), s.Count(), L"Set should have a size of zero.");
	}

	//
	// Create a new set and add an element. Then remove it.
	//
	// Result: the set should permit the removal and contain no elements.
	//

	TEST_METHOD(RemovalOfOneElementLeavesAnEmptySet)
	{
		Set s;

		s.Add("A");

		Assert::IsTrue(s.Remove("A"), L"Remove of 'A' failed.");
		Assert::AreEqual(static_cast<size_t>(0), s.Count(), L"Set should have a size of zero.");
	}

	//
	// Create a new set and add three elements. Then remove them.
	//
	// Result: The removals should succeed and the set should be empty.
	//

	TEST_METHOD(RemovalOfAllElementsLeavesAnEmptySet)
	{
		Set s;

		InsertElements(&s);

		Assert::IsTrue(s.Remove("A"), L"Remove of 'A' failed.");
		Assert::IsTrue(s.Remove("B"), L"Remove of 'B' failed.");
		Assert::IsTrue(s.Remove("C"), L"Remove of 'C' failed.");
		Assert::AreEqual(static_cast<size_t>(0), s.Count(), L"Set should have a size of zero.");
	}

	//
	// Create a new set and add an element. Then remove another element.
	//
	// Result: The remove should fail and the first element should be in
	// the set.
	//

	TEST_METHOD(RemovalOfNonExistantElementFails)
	{
		Set s;

		s.Add("A");

		Assert::IsFalse(s.Remove("B"), L"Remove of 'B' should not have succeeded.");
		Assert::AreEqual(static_cast<size_t>(1), s.Count(), L"Set should have a size of one.");
	}

	//
	// Create a set and insert a duplicate element.
	//
	// Result: The cardinality of the set should be 1.
	//

	TEST_METHOD(AddDuplicate)
	{
		Set s;

		s.Add("A");
		s.Add("A");

		Assert::AreEqual(static_cast<size_t>(1), s.Count(), L"Set should have a size of one.");
	}

	//
	// Create a set and add an empty string elements.
	//
	// Result: The cardinality of the set should be 0.
	//

	TEST_METHOD(AddItemsZero)
	{
		Set s;

		s.AddItems("");

		Assert::AreEqual(static_cast<size_t>(1), s.Count(), L"Set should have a size of one.");
	}

	//
	// Create a set and add one string elements.
	//
	// Result: The cardinality of the set should be 1.
	//

	TEST_METHOD(AddItemsOne)
	{
		Set s;

		s.AddItems("A");

		Assert::AreEqual(static_cast<size_t>(1), s.Count(), L"Set should have a size of one.");
	}

	//
	// Create a set and add two string elements.
	//
	// Result: The cardinality of the set should be 2.
	//

	TEST_METHOD(AddItemsTwo)
	{
		Set s;

		s.AddItems("A,B");

		Assert::AreEqual(static_cast<size_t>(2), s.Count(), L"Set should have a size of two.");
	}

	//
	// Create a set and add duplicate items.
	//
	// Result: The cardinality of the set should be 1.
	//

	TEST_METHOD(AddItemsDuplicate)
	{
		Set s;

		s.AddItems("A,A");

		Assert::AreEqual(static_cast<size_t>(1), s.Count(), L"Set should have a size of one.");
	}

private:
	//
	// Insert three elements into a set.
	//

	void InsertElements(Set* s)
	{
		Assert::IsNotNull(s);

		s->Add("A");
		s->Add("B");
		s->Add("C");
	}
};
