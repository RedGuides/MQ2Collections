//
// Manage a sequence of items as a blob.
//

#pragma once

#include <vector>

//
// Manage a buffer of items of a homogeneous type.
//

template<typename T>
class BufferManager
{
public:
	BufferManager()
	{
	}

	BufferManager(const T* array, size_t elements)
	{
		CopyToBuffer(array, elements);
	}

	~BufferManager()
	{
	}

	// Set contents of the current buffer and return its pointer.
	const T* SetBuffer(const T* array, size_t elements)
	{
		CopyToBuffer(array, elements);
		return GetBufferPointer();
	}

	// Return the pointer to our buffer.
	const T* GetBufferPointer() const
	{
		return m_buffer.data();
	}

private:
	// Copy an array to our buffer.
	void CopyToBuffer(const T* array, size_t elements)
	{
		if (elements > 0)
		{
			// Allocate vector elements.
			m_buffer.resize(elements);

			// Copy the array to the buffer.
			std::uninitialized_copy(array, array + elements, m_buffer.data());
		}
	}

	// Pointer to a temporary buffer
	std::vector<T> m_buffer;
};
