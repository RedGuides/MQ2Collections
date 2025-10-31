#include "pch.h"

#include "Map.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;


//
// Test Map Iterator operations (Reset, Advance, IsEnd, Value and Key).
// Map iterators are acquired by calling Find or First on a Set.
//

TEST_CLASS(MapIteratorUnitTests)
{
public:
	BEGIN_TEST_CLASS_ATTRIBUTE()
		TEST_CLASS_ATTRIBUTE(L"Collections", L"Map")
		TEST_CLASS_ATTRIBUTE(L"Iterators", L"Map")
	END_TEST_CLASS_ATTRIBUTE()

	//
	// Populate the map used by the iterator tests.
	//

	MapIteratorUnitTests()
	{
		m_map.Add("A", "Value1");
		m_map.Add("B", "Value2");
		m_map.Add("C", "Value3");
	}

	//
	// Test that we can acquire an iterator on the map.
	//
	// Result: A non-null iterator should be returned.
	//

	TEST_METHOD(AcquireIteratorFromFirst)
	{
		auto iterator = m_map.First();

		Assert::IsNotNull(iterator, L"Iterator must not be null.");
	}

	//
	// Test that we can acquire an iterator on the map and clone it.
	//
	// Result: A non-null iterator should be returned for the iterator
	// and the clone.
	//

	TEST_METHOD(CloneAcquireIteratorFromFirst)
	{
		auto iterator = m_map.First();
		auto clone = dynamic_cast<MapIterator*>(iterator)->Clone();

		Assert::IsNotNull(iterator, L"Iterator must not be null.");
		Assert::IsNotNull(clone.get(), L"Cloned iterator must not be null.");
	}

	//
	// Test that we can acquire a new iterator on each of the elements
	// by using Find.
	//
	// Result: Non-null iterators should be returned where IsEnd is false.
	//

	TEST_METHOD(AcquireIteratorFromFind)
	{
		auto iterator = m_map.Find("A");

		Assert::IsNotNull(iterator, L"Iterator must not be null.");
		Assert::IsFalse(iterator->IsEnd(), L"Iterator must not be at end.");

		iterator = m_map.Find("B");

		Assert::IsNotNull(iterator, L"Iterator must not be null.");
		Assert::IsFalse(iterator->IsEnd(), L"Iterator must not be at end.");

		iterator = m_map.Find("C");

		Assert::IsNotNull(iterator, L"Iterator must not be null.");
		Assert::IsFalse(iterator->IsEnd(), L"Iterator must not be at end.");
	}

	//
	// Test that we can acquire a new iterator on each of the elements
	// by using Find and clone it.
	//
	// Result: Non-null iterators should be returned where IsEnd is false for
	// the iterator and the clone.
	//

	TEST_METHOD(CloneAcquireIteratorFromFind)
	{
		auto iterator = m_map.Find("A");
		auto clone = dynamic_cast<MapIterator*>(iterator)->Clone();

		Assert::IsNotNull(iterator, L"Iterator must not be null.");
		Assert::IsFalse(iterator->IsEnd(), L"Iterator must not be at end.");

		Assert::IsNotNull(clone.get(), L"Cloned iterator must not be null.");
		Assert::IsFalse(clone->IsEnd(), L"Cloned iterator must not be at end.");

		iterator = m_map.Find("B");
		clone = dynamic_cast<MapIterator*>(iterator)->Clone();

		Assert::IsNotNull(iterator, L"Iterator must not be null.");
		Assert::IsFalse(iterator->IsEnd(), L"Iterator must not be at end.");

		Assert::IsNotNull(clone.get(), L"Cloned iterator must not be null.");
		Assert::IsFalse(clone->IsEnd(), L"Cloned iterator must not be at end.");

		iterator = m_map.Find("C");
		clone = dynamic_cast<MapIterator*>(iterator)->Clone();

		Assert::IsNotNull(iterator, L"Iterator must not be null.");
		Assert::IsFalse(iterator->IsEnd(), L"Iterator must not be at end.");

		Assert::IsNotNull(clone.get(), L"Cloned iterator must not be null.");
		Assert::IsFalse(clone->IsEnd(), L"Cloned iterator must not be at end.");
	}

	//
	// Test Find on an element not in the map.
	//
	// Result: An iterator should be returned where IsEnd is true.
	//

	TEST_METHOD(AcquireIteratorForNonexistantElement)
	{
		auto iterator = m_map.Find("D");

		Assert::IsNotNull(iterator, L"Iterator must not be null.");
		Assert::IsTrue(iterator->IsEnd(), L"Iterator must be at end.");
	}

	//
	// Test Find on an element not in the map. A cloned iterator
	// should also not be in the map.
	//
	// Result: An iterator should be returned where IsEnd is true and
	// for the clone, IsEnd should be true too.
	//

	TEST_METHOD(CloneAcquireIteratorForNonexistantElement)
	{
		auto iterator = m_map.Find("D");
		auto clone = dynamic_cast<MapIterator*>(iterator)->Clone();

		Assert::IsNotNull(iterator, L"Iterator must not be null.");
		Assert::IsTrue(iterator->IsEnd(), L"Iterator must be at end.");

		Assert::IsNotNull(clone.get(), L"Cloned iterator must not be null.");
		Assert::IsTrue(clone->IsEnd(), L"Cloned iterator must be at end.");
	}

	//
	// Test that returning a new iterator is not at the end.
	//
	// Result: IsEnd should be false.
	//

	TEST_METHOD(FirstIteratorIsNotAtEnd)
	{
		auto iterator = m_map.First();

		Assert::IsNotNull(iterator, L"Iterator must not be null.");
		Assert::IsFalse(iterator->IsEnd(), L"Iterator must not be at end.");
	}

	//
	// Test that returning a new iterator is not at the end.
	//
	// Result: IsEnd should be false.
	//

	TEST_METHOD(CloneFirstIteratorIsNotAtEnd)
	{
		auto iterator = m_map.First();
		auto clone = dynamic_cast<MapIterator*>(iterator)->Clone();

		Assert::IsNotNull(iterator, L"Iterator must not be null.");
		Assert::IsFalse(iterator->IsEnd(), L"Iterator must not be at end.");

		Assert::IsNotNull(clone.get(), L"Cloned iterator must not be null.");
		Assert::IsFalse(clone->IsEnd(), L"Cloned iterator must not be at end.");
	}

	//
	// Test that advancing Count() times reaches the end.
	//
	// Result: Advance() should return true for Count() - 1 calls then
	// it should return False and IsEnd should be true.
	//

	TEST_METHOD(IteratorAdvance)
	{
		auto iterator = m_map.First();
		WalkIteratorOverMap(m_map, iterator);
	}

	//
	// Test that advancing Count() times reaches the end. The same should
	// be true of the cloned iterator.
	//
	// Result: Advance() should return true for Count() - 1 calls then
	// it should return False and IsEnd should be true.
	//

	TEST_METHOD(CloneIteratorAdvance)
	{
		auto iterator = m_map.First();
		auto clone = dynamic_cast<MapIterator*>(iterator)->Clone();

		WalkIteratorOverMap(m_map, iterator);
		WalkIteratorOverMap(m_map, clone.get());
	}

	//
	// Test the Reseting the iterator after reaching the end lets us
	// traverse through the collection again.
	//
	// Result: Reset should permit multiple traverals through the map.
	//

	TEST_METHOD(IteratorReset)
	{
		auto iterator = m_map.First();
		WalkIteratorOverMap(m_map, iterator);

		iterator->Reset();

		Assert::IsFalse(iterator->IsEnd(), L"Iterator should not be at end.");
		WalkIteratorOverMap(m_map, iterator);
	}

	//
	// Test the Reseting the iterator after reaching the end lets us
	// traverse through the collection again. The same should also
	// be true of an iterator cloned from the initial iterator.
	//
	// Result: Reset should permit multiple traverals through the map
	// for the initial iterator and the clone.
	//

	TEST_METHOD(CloneIteratorReset)
	{
		auto iterator = m_map.First();
		auto clone = dynamic_cast<MapIterator*>(iterator)->Clone();

		WalkIteratorOverMap(m_map, iterator);
		WalkIteratorOverMap(m_map, clone.get());

		iterator->Reset();
		clone->Reset();

		Assert::IsFalse(iterator->IsEnd(), L"Iterator should not be at end.");
		WalkIteratorOverMap(m_map, iterator);

		Assert::IsFalse(clone->IsEnd(), L"Cloned iterator should not be at end.");
		WalkIteratorOverMap(m_map, clone.get());
	}

	//
	// Test the Value method on an iterator.
	//
	// Result: The value method should return each element in the map.
	//

	TEST_METHOD(ValueUnderIterator)
	{
		auto iterator = m_map.First();
		std::string const* value = nullptr;

		Assert::IsTrue(iterator->Value(&value), L"Iterator->Value returned false.");
		Assert::IsNotNull(value, L"Value returned is null.");
		Assert::AreEqual(std::string("Value1"), *value, L"Expected 'Value1' to be returned.");

		Assert::IsTrue(iterator->Advance(), L"Iterator->Advance returned false.");
		Assert::IsTrue(iterator->Value(&value), L"Iterator->Value returned false.");
		Assert::IsNotNull(value, L"Value returned is null.");
		Assert::AreEqual(std::string("Value2"), *value, L"Expected 'Value2' to be returned.");

		Assert::IsTrue(iterator->Advance(), L"Iterator->Advance returned false.");
		Assert::IsTrue(iterator->Value(&value), L"Iterator->Value returned false.");
		Assert::IsNotNull(value, L"Value returned is null.");
		Assert::AreEqual(std::string("Value3"), *value, L"Expected 'Value3' to be returned.");
	}

	//
	// Test the Value method on an iterator and its clone
	//
	// Result: The value method should return each element in the map.
	//

	TEST_METHOD(CloneValueUnderIterator)
	{
		auto iterator = m_map.First();
		auto clone = dynamic_cast<MapIterator*>(iterator)->Clone();
		std::string const* value = nullptr;

		Assert::IsTrue(iterator->Value(&value), L"Iterator->Value returned false.");
		Assert::IsNotNull(value, L"Value returned is null.");
		Assert::AreEqual(std::string("Value1"), *value, L"Expected 'Value1' to be returned.");

		Assert::IsTrue(iterator->Advance(), L"Iterator->Advance returned false.");
		Assert::IsTrue(iterator->Value(&value), L"Iterator->Value returned false.");
		Assert::IsNotNull(value, L"Value returned is null.");
		Assert::AreEqual(std::string("Value2"), *value, L"Expected 'Value2' to be returned.");

		Assert::IsTrue(iterator->Advance(), L"Iterator->Advance returned false.");
		Assert::IsTrue(iterator->Value(&value), L"Iterator->Value returned false.");
		Assert::IsNotNull(value, L"Value returned is null.");
		Assert::AreEqual(std::string("Value3"), *value, L"Expected 'Value3' to be returned.");

		Assert::IsTrue(clone->Value(&value), L"Cloned iterator->Value returned false.");
		Assert::IsNotNull(value, L"Cloned Value returned is null.");
		Assert::AreEqual(std::string("Value1"), *value, L"Expected Cloned 'Value1' to be returned.");

		Assert::IsTrue(clone->Advance(), L"Cloned Iterator->Advance returned false.");
		Assert::IsTrue(clone->Value(&value), L"Cloned Iterator->Value returned false.");
		Assert::IsNotNull(value, L"Value returned is null.");
		Assert::AreEqual(std::string("Value2"), *value, L"Expected Cloned 'Value2' to be returned.");

		Assert::IsTrue(clone->Advance(), L"Cloned Iterator->Advance returned false.");
		Assert::IsTrue(clone->Value(&value), L"Cloned Iterator->Value returned false.");
		Assert::IsNotNull(value, L"Value returned is null.");
		Assert::AreEqual(std::string("Value3"), *value, L"Expected Cloned 'Value3' to be returned.");
	}

	//
	// Test the key method on an iterator.
	//
	// Result: The key method should return each element in the map.
	//

	TEST_METHOD(KeyUnderIterator)
	{
		auto iterator = m_map.First();
		auto clone = dynamic_cast<MapIterator*>(iterator)->Clone();
		std::string const* key = nullptr;

		Assert::IsTrue(iterator->Key(&key), L"Iterator->Key returned false.");
		Assert::IsNotNull(key, L"Key returned is null.");
		Assert::AreEqual(std::string("A"), *key, L"Expected 'A' to be returned.");

		Assert::IsTrue(iterator->Advance(), L"Iterator->Advance returned false.");
		Assert::IsTrue(iterator->Key(&key), L"Iterator->Key returned false.");
		Assert::IsNotNull(key, L"Key returned is null.");
		Assert::AreEqual(std::string("B"), *key, L"Expected 'B' to be returned.");

		Assert::IsTrue(iterator->Advance(), L"Iterator->Advance returned false.");
		Assert::IsTrue(iterator->Key(&key), L"Iterator->Key returned false.");
		Assert::IsNotNull(key, L"Key returned is null.");
		Assert::AreEqual(std::string("C"), *key, L"Expected 'C' to be returned.");

		Assert::IsTrue(clone->Key(&key), L"Cloned Iterator->Key returned false.");
		Assert::IsNotNull(key, L"Key returned is null.");
		Assert::AreEqual(std::string("A"), *key, L"Expected Cloned 'A' to be returned.");

		Assert::IsTrue(clone->Advance(), L"Cloned Iterator->Advance returned false.");
		Assert::IsTrue(clone->Key(&key), L"Cloned Iterator->Key returned false.");
		Assert::IsNotNull(key, L"Key returned is null.");
		Assert::AreEqual(std::string("B"), *key, L"Expected Cloned 'B' to be returned.");

		Assert::IsTrue(clone->Advance(), L"Cloned Iterator->Advance returned false.");
		Assert::IsTrue(clone->Key(&key), L"Cloned Iterator->Key returned false.");
		Assert::IsNotNull(key, L"Key returned is null.");
		Assert::AreEqual(std::string("C"), *key, L"Expected Cloned 'C' to be returned.");
	}

	//
	// Test the key method on an iterator and its clone.
	//
	// Result: The key method should return each element in the map.
	//

	TEST_METHOD(CloneKeyUnderIterator)
	{
		auto iterator = m_map.First();
		std::string const* key = nullptr;

		Assert::IsTrue(iterator->Key(&key), L"Iterator->Key returned false.");
		Assert::IsNotNull(key, L"Key returned is null.");
		Assert::AreEqual(std::string("A"), *key, L"Expected 'A' to be returned.");

		Assert::IsTrue(iterator->Advance(), L"Iterator->Advance returned false.");
		Assert::IsTrue(iterator->Key(&key), L"Iterator->Key returned false.");
		Assert::IsNotNull(key, L"Key returned is null.");
		Assert::AreEqual(std::string("B"), *key, L"Expected 'B' to be returned.");

		Assert::IsTrue(iterator->Advance(), L"Iterator->Advance returned false.");
		Assert::IsTrue(iterator->Key(&key), L"Iterator->Key returned false.");
		Assert::IsNotNull(key, L"Key returned is null.");
		Assert::AreEqual(std::string("C"), *key, L"Expected 'C' to be returned.");
	}


private:
	// Acquire an iterator and walk through each element.
	void WalkIteratorOverMap(const Map& m, KeyValueIterator<std::map<std::string, std::string>, std::string, std::string>* iterator) const
	{
		Assert::IsNotNull(iterator, L"Iterator must not be null.");
		Assert::IsFalse(iterator->IsEnd(), L"Iterator should not be at end.");

		for (size_t i = 1; i < m.Count(); ++i)
		{
			Assert::IsTrue(iterator->Advance(), L"Iterator->Advance returned false.");
		}

		Assert::IsTrue(iterator->Advance(), L"Iterator Advance returned false.");
		Assert::IsTrue(iterator->IsEnd(), L"Iterator should be at the end.");
	}

	Map m_map;
};
