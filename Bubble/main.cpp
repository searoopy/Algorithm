#include <iostream>



using Comparer = bool (*)(int, int);

bool IsGreater(int left, int right)
{
	return left > right;
}


bool IsLess(int left, int right)
{
	return left < right;
}

//버블 정렬 함수.
void BubbleSort(int* array, int length , Comparer comparer )
{
	for (int i = 0; i < length - 1; ++i)
	{
		for (int j = 0; j < length -1 - i; ++j)
		{
			//if (array[j] > array[j + 1])
			if(comparer( array[j], array[j+1] ))
			{
				//교체
				std::swap<int>(array[j], array[j + 1]);
			}
		}
	}
}



void PrintArray(int* array, int length)
{
	for (int i = 0; i < length; ++i)
	{
		std::cout << array[i];


		//마지막 원소 전까지는 콤마 출력.
		if (i < length - 1)
		{
			std::cout << ", ";
		}
	}

	std::cout << "\n";
}


int main()
{

	int array[] = { 5,2,312,3123,124,23,1,2,123,5,23,5,23,234,7679,34,32 };



	int len = sizeof(array) / sizeof(array[0]);


	PrintArray(array, len);



	BubbleSort(array, len , IsLess);


	PrintArray(array, len);

	std::cin.get();
}