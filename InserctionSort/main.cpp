#include <iostream>

void InserctionSort(int* array, int len)
{

	if (len <= 1)
	{
		return;
	}


	//배열 순회.
	for (int i = 1; i < len; ++i)
	{
		//현재 삽입할 값
		int key = array[i];
		int j = i - 1;


		//key보다 큰 값은 ㅎ오른쪽으로 배치.
		while (j >= 0 && array[j] > key )
		{
			array[j + 1] = array[j];
			--j;
		}

		//적절한 위칭 key 삽입
		array[j + 1] = key;


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


	int len = _countof(array);


	PrintArray(array, len);
	InserctionSort(array, len);

	PrintArray(array, len);
}
