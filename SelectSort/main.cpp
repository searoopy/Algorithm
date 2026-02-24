#include <iostream>


void SelectionSort(int* array, int len)
{

	for (int i = 0; i < len; ++i)

	{

		int minidx = i;


		//현재 위치에서 끝까지 반복.
		//회차가 거듭될수록 오른쪽으로 위치를 옴겨가며 정렬.
		for (int j = i + 1; j < len; ++j)
		{
			if (array[minidx] > array[j])
			{
				minidx = j;
			}
		}

		//회차전에 저장했던 인덱스가 바뀌었는지 확인
		if (minidx != i)
		{
			std::swap<int>(array[i], array[minidx]);
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
	int array[] = { 5,23,123,5,1,3,5,6,745,3,321,123123,11 };


	int len = sizeof(array) / sizeof(array[0]);
	PrintArray(array,len);


	SelectionSort(array,len);


	PrintArray(array, len);


}