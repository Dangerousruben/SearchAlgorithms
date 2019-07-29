#pragma once
#include <algorithm>

#include <assert.h>
#include <exception>

struct ElementNotFound : public std::exception
{
	const char* what() const throw()
	{
		return "Did not find element in array";
	}
};

template<typename Type, int Size>
struct CustomArray
{
	void Initialize(Type a_Value);

	void Initialize(Type a_CopyArray[Size]);

	int GetSize();

	void BubbleSort(bool(*Predicate)(int, int));

	int LinearSearch(Type a_Value);

	int BinarySearch(Type a_Value);

	int JumpSearch(Type a_Value);

	int InterpolationSearch(Type a_Value);

	int ExponentialSearch(Type a_Value);

	Type& operator[](int index)
	{
		assert(index >= 0 && index < Size);
		return Array[index];
	}

private:
	Type Array[Size];

	int BinarySearch(Type a_Value, int a_Left, int a_Right);
};

template<typename Type, int Size>
inline void CustomArray<Type, Size>::Initialize(Type a_Value)
{
	for (int i = 0; i < Size; i++)
	{
		Array[i] = a_Value;
	}
}

template<typename Type, int Size>
inline void CustomArray<Type, Size>::Initialize(Type a_CopyArray[Size])
{
	for (int i = 0; i < Size; i++)
	{
		Array[i] = a_CopyArray;
	}
}

template<typename Type, int Size>
inline void CustomArray<Type, Size>::BubbleSort(bool(*Predicate)(int, int))
{
	for (int i = 0; i < Size - 1; i++)
	{
		for (int j = 0; j < Size - 1; j++)
		{
			if (Predicate(Array[j + 1], Array[j]))
			{
				Type tempValue = Array[j];
				Array[j] = Array[j + 1];
				Array[j + 1] = tempValue;
			}
		}
	}
}


template<typename Type, int Size>
inline int CustomArray<Type, Size>::GetSize()
{
	return Size;
}

//Linear search loops through the array and compares each entry to the deisred value
//Complexity O(n)
template<typename Type, int Size>
inline int CustomArray<Type, Size>::LinearSearch(Type a_Value)
{
	for (int i = 0; i < Size; i++)
	{
		if (Array[i] == a_Value)
		{
			return i;
		}
	}
	throw ElementNotFound();
	return -1;
}


//Binary search only works with sorted array
//It compares the middle element to the desired value and if does not equal the desired value it 
//repeats on either the left or right half
//Complexity O(Log n)
template<typename Type, int Size>
inline int CustomArray<Type, Size>::BinarySearch(Type a_Value)
{
	return BinarySearch(a_Value, 0, Size - 1);
}

template<typename Type, int Size>
inline int CustomArray<Type, Size>::BinarySearch(Type a_Value, int a_Left, int a_Right)
{
	if (a_Right >= a_Left)
	{
		int mid = a_Left + ((a_Right - a_Left) / 2);

		if (Array[mid] == a_Value)
		{
			return mid;
		}
		else if (Array[mid] < a_Value)
		{
			return BinarySearch(a_Value, mid + 1, a_Right);
		}
		else
		{
			return BinarySearch(a_Value, a_Left, mid - 1);
		}
	}

	throw ElementNotFound();
	return -1;
}

//Jump search only works with sorted array
//It jumps to elements in steps and compares them to the desired value
//If desired value is in between the current element and the previous element, a linear search is done on that block
//The best step amount is √ArraySize
//Complexity O(√n)
template<typename Type, int Size>
inline int CustomArray<Type, Size>::JumpSearch(Type a_Value)
{
	int step = (int)sqrt(Size);

	int previousStep = 0;
	while (Array[(std::min(step, Size) - 1)] < a_Value)
	{
		previousStep = step;
		if (previousStep >= Size)
		{
			throw ElementNotFound();
			return -1;
		}
		step += (int)sqrt(Size);
	}
	while (Array[previousStep] < a_Value)
	{
		previousStep++;

		if (previousStep == std::min(step, Size))
		{
			throw ElementNotFound();
			return -1;
		}
	}

	if (Array[previousStep] == a_Value)
	{
		return previousStep;
	}

	throw ElementNotFound();
	return -1;
}

//Interpolation search only works with sorted array
//A linear function (y = ax + c) is constructed and then interpolated to approximate the desired values location
//If the aproximated index is smaller than the desired value is above our approximation
//If the aproximated index is Higher than the desired value is below our approximation
//Complexity best case: O(log log n), worst case: O(n)
template<typename Type, int Size>
inline int CustomArray<Type, Size>::InterpolationSearch(Type a_Value)
{
	int startIndex = 0;
	int endIndex = Size - 1;

	while (startIndex <= endIndex && a_Value >= Array[startIndex] && a_Value <= Array[endIndex])
	{
		//Interpolation:
		// y = ax + c
		// y - y1 = a(x - x1)
		// y = a(x - x1) + y1
		// y = ((y2 - y1)/(x2 - x1)) * (x - x1) + y1
		int position = ((endIndex - startIndex) / (Array[endIndex] - Array[startIndex])) * 
			(a_Value - Array[startIndex]) + startIndex;

		if (a_Value == Array[position])
		{
			return position;
		}
		else if (a_Value > Array[position])
		{
			startIndex = position + 1;
		}
		else
		{
			endIndex = position - 1;
		}
	}
	throw ElementNotFound();
	return -1;
}

//Exponential search only works on sorted arrays
//It tries to find a range where the object can be found by repeatedly doubling the index
//After it found a range it does a binary search
//Works better on arrays of infinte length or when the desired value is close to the start
//Complexity O(Log n)
template<typename Type, int Size>
inline int CustomArray<Type, Size>::ExponentialSearch(Type a_Value)
{
	if (Array[0] == a_Value)
	{
		return 0;
	}

	int i = 1;
	while (i < Size && Array[std::min(i, Size)] <= a_Value)
	{
		i *= 2;
	}
	return BinarySearch(a_Value, i/2, std::min(i, Size));
}