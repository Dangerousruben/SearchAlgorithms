// SearchAlgorithms.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include "CustomArray.h"

namespace SetupCode
{
	template<typename Type, int Size>
	void SetupArray(CustomArray<Type, Size>& a_Array)
	{
		Type copyArray[Size] = { 10, 15, 1, 16, 0, 5, 20, 7, 12, 20 };
		for (int i = 0; i < Size; i++)
		{
			a_Array[i] = copyArray[i];
		}
	}
}

int main()
{
	CustomArray<int, 10> Array;
	SetupCode::SetupArray(Array);
	Array.BubbleSort([](int First, int Last) {return First < Last; });

	for (int i = 0; i < Array.GetSize(); i++)
	{
		std::cout << Array[i] << std::endl;
	}
	int valueToFind = 20;
	try
	{
		std::cout << "\nSearching array for value " << valueToFind << "\nFound at: " << Array.BinarySearch(valueToFind) << std::endl << std::endl;
	}
	catch (std::exception& except)
	{
		std::cout << "\nException caught: " << except.what() << std::endl << std::endl;
	}
}
