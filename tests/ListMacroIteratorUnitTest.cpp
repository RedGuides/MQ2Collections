#include "pch.h"
#include "List.h"

#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

//
// Test List Iterator Operations (Reset, Advance, IsEnd, Value).
// List iterators are acquireed by calling Find or First on a List.
//

TEST_CLASS(ListMacroIteratorUnitTests)
{
public:
	BEGIN_TEST_CLASS_ATTRIBUTE()
		TEST_CLASS_ATTRIBUTE(L"Collections", L"List")
		TEST_CLASS_ATTRIBUTE(L"MQ2Interface", L"List")
		TEST_CLASS_ATTRIBUTE(L"Iterators", L"List")
	END_TEST_CLASS_ATTRIBUTE()

	//
	// Populate the list used by the iterator tests.
	//

	ListMacroIteratorUnitTests()
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
		MQVarPtr source;
		MQVarPtr itersource;
		MQTypeVar dest = {};
		MQTypeVar iterdest = {};

		auto pl = std::make_unique<List>();

		// Set the source pointer to the new instance.
		source.Ptr = pl.get();

		// Acquire an iterator using the First method.
		bool bResult = List::GetMemberInvoker(source, "First", nullptr, dest);
		Assert::IsTrue(bResult, L"First invocation failed.");
		Assert::IsNotNull(dest.Ptr, L"First should not return null.");

		// Set the iterator source pointer to the returned instance.
		itersource.Ptr = dest.Ptr;

		// Find out if we are at the end of the iterator.
		bResult = ListIterator::GetMemberInvoker(itersource, "IsEnd", nullptr, iterdest);
		Assert::IsTrue(bResult, L"IsEnd invocation failed.");
		Assert::IsTrue(iterdest.Get<bool>(), L"IsEnd should return true.");

		// Free the ListIterator that was returned.
		ListIterator* li = static_cast<ListIterator*>(itersource.Ptr);
		li->FreeVariable(itersource);
	}

	//
	// Acquire an iterator using First on an empty collection and Clone it.
	//
	// Result: a non-null iterator should be returned and IsEnd should be true
	// for both the initial iterator and the clone.
	//

	TEST_METHOD(CloneIteratorFromFirstOnEmptyList)
	{
		MQVarPtr source;
		MQVarPtr itersource;
		MQVarPtr clonesource;
		MQTypeVar dest = {};
		MQTypeVar iterdest = {};
		MQTypeVar clonedest = {};
		bool bResult;

		auto pl = std::make_unique<List>();

		// Set the source pointer to the new instance.
		source.Ptr = pl.get();

		// Acquire an iterator using the First method.
		bResult = List::GetMemberInvoker(source, "First", nullptr, dest);
		Assert::IsTrue(bResult, L"First invocation failed.");
		Assert::IsNotNull(dest.Ptr, L"First should not return null.");

		// Set the iterator source pointer to the returned instance.
		itersource.Ptr = dest.Ptr;

		// Clone the iterator.
		bResult = ListIterator::GetMemberInvoker(itersource, "Clone", nullptr, clonedest);
		Assert::IsTrue(bResult, L"Clone invocation failed.");
		Assert::IsNotNull(clonedest.Ptr, L"Clone should not return null.");

		clonesource.Ptr = clonedest.Ptr;

		// Find out if we are at the end of the iterator.
		bResult = ListIterator::GetMemberInvoker(itersource, "IsEnd", nullptr, iterdest);
		Assert::IsTrue(bResult, L"IsEnd invocation failed.");
		Assert::IsTrue(iterdest.Get<bool>(), L"IsEnd should return true.");

		// Find out if we are at the end of the cloned iterator.
		bResult = ListIterator::GetMemberInvoker(clonesource, "IsEnd", nullptr, iterdest);
		Assert::IsTrue(bResult, L"Cloned IsEnd invocation failed.");
		Assert::IsTrue(iterdest.Get<bool>(), L"Cloned IsEnd should return true.");

		// Free the ListIterator and clone that were returned.
		ListIterator* li = static_cast<ListIterator*>(itersource.Ptr);
		li->FreeVariable(itersource);

		li = static_cast<ListIterator*>(clonesource.Ptr);
		li->FreeVariable(clonesource);
	}

	//
	// Acquire an iterator using the First method.
	//
	// Result: a non-null iterator should be returned and IsEnd should be false.
	//

	TEST_METHOD(AcquireIteratorUsingFirst)
	{
		MQVarPtr source;
		MQVarPtr itersource;
		MQTypeVar dest = {};
		MQTypeVar iterdest = {};
		bool bResult;

		// Set our source pointer to be the populated list.
		source.Ptr = &m_list;

		// Acquire an iterator using the First method.
		bResult = List::GetMemberInvoker(source, "First", nullptr, dest);
		Assert::IsTrue(bResult, L"First invocation failed.");
		Assert::IsNotNull(dest.Ptr, L"First should not return null.");

		// Set the iterator source pointer to the returned instance.
		itersource.Ptr = dest.Ptr;

		// Find out if we are at the end of the iterator.
		bResult = ListIterator::GetMemberInvoker(itersource, "IsEnd", nullptr, iterdest);
		Assert::IsTrue(bResult, L"IsEnd invocation failed.");
		Assert::IsFalse(iterdest.Get<bool>(), L"IsEnd should return False.");

		// Free the ListIterator that was returned.
		ListIterator* li = static_cast<ListIterator*>(itersource.Ptr);
		li->FreeVariable(itersource);
	}

	//
	// Acquire an iterator using the First method and Clone it.
	//
	// Result: a non-null iterator should be returned and IsEnd should be false
	// for both the iterator and the clone.
	//

	TEST_METHOD(CloneIteratorFromFirst)
	{
		MQVarPtr source;
		MQVarPtr itersource;
		MQVarPtr clonesource;
		MQTypeVar dest = {};
		MQTypeVar iterdest = {};
		MQTypeVar clonedest = {};
		bool bResult;

		// Set our source pointer to be the populated list.
		source.Ptr = &m_list;

		// Acquire an iterator using the First method.
		bResult = List::GetMemberInvoker(source, "First", nullptr, dest);
		Assert::IsTrue(bResult, L"First invocation failed.");
		Assert::IsNotNull(dest.Ptr, L"First should not return null.");

		// Set the iterator source pointer to the returned instance.
		itersource.Ptr = dest.Ptr;

		// Clone the iterator.
		bResult = ListIterator::GetMemberInvoker(itersource, "Clone", nullptr, clonedest);
		Assert::IsTrue(bResult, L"Clone invocation failed.");
		Assert::IsNotNull(clonedest.Ptr, L"Clone should not return null.");

		clonesource.Ptr = clonedest.Ptr;

		// Find out if we are at the end of the iterator.
		bResult = ListIterator::GetMemberInvoker(itersource, "IsEnd", nullptr, iterdest);
		Assert::IsTrue(bResult, L"IsEnd invocation failed.");
		Assert::IsFalse(iterdest.Get<bool>(), L"IsEnd should return False.");

		// Find out if we are at the end of the cloned iterator.
		bResult = ListIterator::GetMemberInvoker(clonesource, "IsEnd", nullptr, iterdest);
		Assert::IsTrue(bResult, L"Clone IsEnd invocation failed.");
		Assert::IsFalse(iterdest.Get<bool>(), L"Clone IsEnd should return False.");

		// Free the ListIterators that were returned.
		ListIterator* li = static_cast<ListIterator*>(itersource.Ptr);
		li->FreeVariable(itersource);

		li = static_cast<ListIterator*>(clonesource.Ptr);
		li->FreeVariable(clonesource);
	}

	//
	// Acquire an iterator using Find on each element.
	//
	// Result: a non-null iterator should be returned where IsEnd is false.
	//

	TEST_METHOD(AcquireIteratorUsingFind)
	{
		MQVarPtr source;
		MQVarPtr itersource;
		MQTypeVar iterdest = {};
		std::vector<std::string> elements =
		{
			"A",
			"B",
			"C",
			"D",
			"E"
		};

		// Set our source pointer to be the populated list.
		source.Ptr = &m_list;

		// Acquire an iterator using Find on each of the items in the list.
		for (const std::string& item : elements)
		{
			MQTypeVar dest = {};

			// Acquire an iterator using the Find method.
			bool bResult = List::GetMemberInvoker(source, "Find", item.c_str(), dest);
			Assert::IsTrue(bResult, L"Find invocation failed.");
			Assert::IsNotNull(dest.Ptr, L"Find should not return null.");

			// Set the iterator source pointer to the returned instance.
			itersource.Ptr = dest.Ptr;

			// Find out if we are at the end of the iterator.
			bResult = ListIterator::GetMemberInvoker(itersource, "IsEnd", nullptr, iterdest);
			Assert::IsTrue(bResult, L"IsEnd invocation failed.");
			Assert::IsFalse(iterdest.Get<bool>(), L"IsEnd should return False.");

			// Free the ListIterator that was returned.
			ListIterator* li = static_cast<ListIterator*>(itersource.Ptr);

			li->FreeVariable(itersource);
		}
	}

	//
	// Acquire an iterator using Find on each element and Clone them.
	//
	// Result: a non-null iterator should be returned where IsEnd is false
	// for each of the iterators and the clones.
	//

	TEST_METHOD(CloneIteratorUsingFind)
	{
		MQVarPtr source;
		MQVarPtr itersource;
		MQVarPtr clonesource;
		MQTypeVar dest = {};
		MQTypeVar iterdest = {};
		MQTypeVar clonedest = {};

		std::vector<std::string> elements =
		{
			"A",
			"B",
			"C",
			"D",
			"E"
		};

		// Set our source pointer to be the populated list.
		source.Ptr = &m_list;

		// Acquire an iterator using Find on each of the items in the list.
		for (const std::string& item : elements)
		{
			// Acquire an iterator using the Find method.
			bool bResult = List::GetMemberInvoker(source, "Find", item.c_str(), dest);
			Assert::IsTrue(bResult, L"Find invocation failed.");
			Assert::IsNotNull(dest.Ptr, L"Find should not return null.");

			// Set the iterator source pointer to the returned instance.
			itersource.Ptr = dest.Ptr;

			// Clone the iterator.
			bResult = ListIterator::GetMemberInvoker(itersource, "Clone", nullptr, clonedest);
			Assert::IsTrue(bResult, L"Clone invocation failed.");
			Assert::IsNotNull(clonedest.Ptr, L"Clone should not return null.");

			clonesource.Ptr = clonedest.Ptr;

			// Find out if we are at the end of the iterator.
			bResult = ListIterator::GetMemberInvoker(itersource, "IsEnd", nullptr, iterdest);
			Assert::IsTrue(bResult, L"IsEnd invocation failed.");
			Assert::IsFalse(iterdest.Get<bool>(), L"IsEnd should return False.");

			// Find out if we are at the end of the cloned iterator.
			bResult = ListIterator::GetMemberInvoker(clonesource, "IsEnd", nullptr, iterdest);
			Assert::IsTrue(bResult, L"Clone IsEnd invocation failed.");
			Assert::IsFalse(iterdest.Get<bool>(), L"Clone IsEnd should return False.");

			// Free the ListIterators that were returned.
			ListIterator* li = static_cast<ListIterator*>(itersource.Ptr);
			li->FreeVariable(itersource);

			li = static_cast<ListIterator*>(clonesource.Ptr);
			li->FreeVariable(clonesource);
		}
	}

	//
	// Acquire an iterator on an element not in the list.
	//
	// Result: a non-null iterator should be returned where IsEnd is true.
	//

	TEST_METHOD(AcquireIteratorForNonexistantElement)
	{
		MQVarPtr source;
		MQVarPtr itersource;
		MQTypeVar dest = {};
		MQTypeVar iterdest = {};

		// Set our source pointer to be the populated list.
		source.Ptr = &m_list;

		// Acquire an iterator using the Find method.
		bool bResult = List::GetMemberInvoker(source, "Find", "Z", dest);
		Assert::IsTrue(bResult, L"Find invocation failed.");
		Assert::IsNotNull(dest.Ptr, L"Find should not return null.");

		// Set the iterator source pointer to the returned instance.
		itersource.Ptr = dest.Ptr;

		// Find out if we are at the end of the iterator.
		bResult = ListIterator::GetMemberInvoker(itersource, "IsEnd", nullptr, iterdest);
		Assert::IsTrue(bResult, L"IsEnd invocation failed.");
		Assert::IsTrue(iterdest.Get<bool>(), L"IsEnd should return True.");

		// Free the ListIterator that was returned.
		ListIterator* li = static_cast<ListIterator*>(itersource.Ptr);

		li->FreeVariable(itersource);
	}

	//
	// Acquire an iterator on an element not in the list.
	//
	// Result: a non-null iterator should be returned where IsEnd is true.
	//

	TEST_METHOD(CloneIteratorForNonexistantElement)
	{
		MQVarPtr source;
		MQVarPtr itersource;
		MQVarPtr clonesource;
		MQTypeVar dest = {};
		MQTypeVar iterdest = {};
		MQTypeVar clonedest = {};

		// Set our source pointer to be the populated list.
		source.Ptr = &m_list;

		// Acquire an iterator using the Find method.
		bool bResult = List::GetMemberInvoker(source, "Find", "Z", dest);
		Assert::IsTrue(bResult, L"Find invocation failed.");
		Assert::IsNotNull(dest.Ptr, L"Find should not return null.");

		// Set the iterator source pointer to the returned instance.
		itersource.Ptr = dest.Ptr;

		// Clone the iterator.
		bResult = ListIterator::GetMemberInvoker(itersource, "Clone", nullptr, clonedest);
		Assert::IsTrue(bResult, L"Clone invocation failed.");
		Assert::IsNotNull(clonedest.Ptr, L"Clone should not return null.");

		clonesource.Ptr = clonedest.Ptr;

		// Find out if we are at the end of the iterator.
		bResult = ListIterator::GetMemberInvoker(itersource, "IsEnd", nullptr, iterdest);
		Assert::IsTrue(bResult, L"IsEnd invocation failed.");
		Assert::IsTrue(iterdest.Get<bool>(), L"IsEnd should return True.");

		// Find out if we are at the end of the cloned iterator.
		bResult = ListIterator::GetMemberInvoker(clonesource, "IsEnd", nullptr, iterdest);
		Assert::IsTrue(bResult, L"Clone IsEnd invocation failed.");
		Assert::IsTrue(iterdest.Get<bool>(), L"Clone IsEnd should return True.");

		// Free the ListIterators that were returned.
		ListIterator* li = static_cast<ListIterator*>(itersource.Ptr);
		li->FreeVariable(itersource);

		li = static_cast<ListIterator*>(clonesource.Ptr);
		li->FreeVariable(clonesource);
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
		WalkIteratorOverList(m_list, static_cast<ListIterator*>(iterator));
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

		WalkIteratorOverList(m_list, static_cast<ListIterator*>(iterator));
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
		MQVarPtr itersource;
		MQTypeVar iterdest = {};
		auto iterator = m_list.First();

		WalkIteratorOverList(m_list, static_cast<ListIterator*>(iterator));

		itersource.Ptr = iterator;

		// Reset the iterator using the GetMember interface.
		bool bResult = ListIterator::GetMemberInvoker(itersource, "Reset", nullptr, iterdest);
		Assert::IsTrue(bResult, L"Reset invocation failed.");
		Assert::IsTrue(iterdest.Get<bool>(), L"Reset should return True.");

		bResult = ListIterator::GetMemberInvoker(itersource, "IsEnd", nullptr, iterdest);
		Assert::IsTrue(bResult, L"IsEnd invocation failed.");
		Assert::IsFalse(iterdest.Get<bool>(), L"IsEnd should return False.");

		// And walk over the list again.
		WalkIteratorOverList(m_list, static_cast<ListIterator*>(iterator));
	}

	//
	// Reset the iterator after reaching the end and traverse through the
	// collection again.
	//
	// Result: reset should permit multiple traverals through the list.
	//

	TEST_METHOD(CloneUseResetOnIterator)
	{
		MQVarPtr itersource;
		MQVarPtr clonesource;
		MQTypeVar iterdest = {};
		auto iterator = m_list.First();
		auto clone = dynamic_cast<ListIterator*>(iterator)->Clone();

		WalkIteratorOverList(m_list, static_cast<ListIterator*>(iterator));

		itersource.Ptr = iterator;

		// Reset the iterator using the GetMember interface.
		bool bResult = ListIterator::GetMemberInvoker(itersource, "Reset", nullptr, iterdest);
		Assert::IsTrue(bResult, L"Reset invocation failed.");
		Assert::IsTrue(iterdest.Get<bool>(), L"Reset should return True.");

		bResult = ListIterator::GetMemberInvoker(itersource, "IsEnd", nullptr, iterdest);
		Assert::IsTrue(bResult, L"IsEnd invocation failed.");
		Assert::IsFalse(iterdest.Get<bool>(), L"IsEnd should return False.");

		// And walk over the list again.
		WalkIteratorOverList(m_list, static_cast<ListIterator*>(iterator));

		// Do the same for the clone.
		WalkIteratorOverList(m_list, clone.get());

		clonesource.Ptr = clone.get();

		// Reset the iterator using the GetMember interface.
		bResult = ListIterator::GetMemberInvoker(clonesource, "Reset", nullptr, iterdest);
		Assert::IsTrue(bResult, L"Clone Reset invocation failed.");
		Assert::IsTrue(iterdest.Get<bool>(), L"Clone Reset should return True.");

		bResult = ListIterator::GetMemberInvoker(clonesource, "IsEnd", nullptr, iterdest);
		Assert::IsTrue(bResult, L"Clone IsEnd invocation failed.");
		Assert::IsFalse(iterdest.Get<bool>(), L"Clone IsEnd should return False.");

		// And walk over the list via the clone again.
		WalkIteratorOverList(m_list, clone.get());
	}

	//
	// Retrieve the value under an iterator.
	//
	// Result: the value method should return each element in the list.
	//

	TEST_METHOD(RetrieveValueUnderIterator)
	{
		MQVarPtr itersource;
		MQTypeVar iterdest = {};
		auto iterator = m_list.First();

		std::vector<std::string> elements =
		{
			"A",
			"B",
			"C",
			"D",
			"E"
		};

		// Set the iterator as the source interface.
		itersource.Ptr = iterator;

		// Retrieve each element under the iterator and ensure that we can fetch it
		// and that it matches the expected value.
		for (const std::string& item : elements)
		{
			bool bResult = ListIterator::GetMemberInvoker(itersource, "Value", nullptr, iterdest);
			Assert::IsTrue(bResult, L"Value invocation failed.");
			Assert::IsTrue(iterdest.Get<bool>(), L"Value should return True.");

			Assert::AreEqual(item.c_str(), static_cast<const char*>(iterdest.Ptr), false, L"Expected value not found.");

			bResult = ListIterator::GetMemberInvoker(itersource, "IsEnd", nullptr, iterdest);
			Assert::IsTrue(bResult, L"IsEnd invocation failed.");
			Assert::IsFalse(iterdest.Get<bool>(), L"IsEnd should return False.");

			bResult = ListIterator::GetMemberInvoker(itersource, "Advance", nullptr, iterdest);
			Assert::IsTrue(bResult, L"Advance invocation failed.");
			Assert::IsTrue(iterdest.Get<bool>(), L"Advance should return True.");
		}

		// IsEnd should be true after processing the entire list.
		bool bResult = ListIterator::GetMemberInvoker(itersource, "IsEnd", nullptr, iterdest);
		Assert::IsTrue(bResult, L"IsEnd invocation failed.");
		Assert::IsTrue(iterdest.Get<bool>(), L"IsEnd should return True.");
	}

	//
	// Retrieve the value under an iterator.
	//
	// Result: the value method should return each element in the list.
	//

	TEST_METHOD(CloneRetrieveValueUnderIterator)
	{
		MQVarPtr clonesource;
		MQVarPtr itersource;
		MQTypeVar iterdest = {};
		auto iterator = m_list.First();
		auto clone = static_cast<ListIterator*>(iterator)->Clone();

		std::vector<std::string> elements =
		{
			"A",
			"B",
			"C",
			"D",
			"E"
		};

		// Set the iterator as the source interface.
		itersource.Ptr = iterator;

		// Retrieve each element under the iterator and ensure that we can fetch it
		// and that it matches the expected value.
		for (const std::string& item : elements)
		{
			bool bResult = ListIterator::GetMemberInvoker(itersource, "Value", nullptr, iterdest);
			Assert::IsTrue(bResult, L"Value invocation failed.");
			Assert::IsTrue(iterdest.Get<bool>(), L"Value should return True.");

			Assert::AreEqual(item.c_str(), static_cast<const char*>(iterdest.Ptr), false, L"Expected value not found.");

			bResult = ListIterator::GetMemberInvoker(itersource, "IsEnd", nullptr, iterdest);
			Assert::IsTrue(bResult, L"IsEnd invocation failed.");
			Assert::IsFalse(iterdest.Get<bool>(), L"IsEnd should return False.");

			bResult = ListIterator::GetMemberInvoker(itersource, "Advance", nullptr, iterdest);
			Assert::IsTrue(bResult, L"Advance invocation failed.");
			Assert::IsTrue(iterdest.Get<bool>(), L"Advance should return True.");
		}

		// IsEnd should be true after processing the entire list.
		bool bResult = ListIterator::GetMemberInvoker(itersource, "IsEnd", nullptr, iterdest);
		Assert::IsTrue(bResult, L"IsEnd invocation failed.");
		Assert::IsTrue(iterdest.Get<bool>(), L"IsEnd should return True.");

		// Repeat the process for the clone.
		clonesource.Ptr = clone.get();

		// Retrieve each element under the iterator and ensure that we can fetch it
		// and that it matches the expected value.
		for (const std::string& item : elements)
		{
			bResult = ListIterator::GetMemberInvoker(clonesource, "Value", nullptr, iterdest);
			Assert::IsTrue(bResult, L"Clone Value invocation failed.");
			Assert::IsTrue(iterdest.Get<bool>(), L"Clone Value should return True.");

			Assert::AreEqual(item.c_str(), static_cast<const char*>(iterdest.Ptr), false, L"Expected clone value not found.");

			bResult = ListIterator::GetMemberInvoker(clonesource, "IsEnd", nullptr, iterdest);
			Assert::IsTrue(bResult, L"Clone IsEnd invocation failed.");
			Assert::IsFalse(iterdest.Get<bool>(), L"Clone IsEnd should return False.");

			bResult = ListIterator::GetMemberInvoker(clonesource, "Advance", nullptr, iterdest);
			Assert::IsTrue(bResult, L"Clone Advance invocation failed.");
			Assert::IsTrue(iterdest.Get<bool>(), L"Clone Advance should return True.");
		}

		// IsEnd should be true after processing the entire list.
		bResult = ListIterator::GetMemberInvoker(clonesource, "IsEnd", nullptr, iterdest);
		Assert::IsTrue(bResult, L"Clone IsEnd invocation failed.");
		Assert::IsTrue(iterdest.Get<bool>(), L"Clone IsEnd should return True.");
	}

private:
	// Acquire an iterator and walk through each element using the GetMember
	// interface.
	void WalkIteratorOverList(const List& l, ListIterator* it) const
	{
		MQVarPtr source;
		MQTypeVar dest = {};

		Assert::IsNotNull(it, L"Iterator should not be null.");

		// Set our source pointer to be the populated list.
		source.Ptr = it;

		// Verify the iterator is not AtEnd.
		bool bResult = ListIterator::GetMemberInvoker(source, "IsEnd", nullptr, dest);
		Assert::IsTrue(bResult, L"IsEnd invocation failed.");
		Assert::IsFalse(dest.Get<bool>(), L"IsEnd should return True.");

		for (size_t i = 1; i < l.Count(); ++i)
		{
			bResult = ListIterator::GetMemberInvoker(source, "Advance", nullptr, dest);
			Assert::IsTrue(bResult, L"Advance invocation failed.");
			Assert::IsTrue(dest.Get<bool>(), L"Advance should return True.");
		}

		bResult = ListIterator::GetMemberInvoker(source, "Advance", nullptr, dest);
		Assert::IsTrue(bResult, L"Advance invocation failed.");
		Assert::IsTrue(dest.Get<bool>(), L"Advance should return True.");

		bResult = ListIterator::GetMemberInvoker(source, "IsEnd", nullptr, dest);
		Assert::IsTrue(bResult, L"IsEnd invocation failed.");
		Assert::IsTrue(dest.Get<bool>(), L"IsEnd should return True.");
	}

	List m_list;
};
