#include <iostream>
void Merge(
	int* array,
	int* leftarray , int leftArrlen,
	int* rightarray, int rightArrlen
)
{

	int leftidx = 0;
	int rightidx = 0;
	int mergedidx = 0;



	//왼쪽/오른쪽 배열 요소를 비교해 더 작은 배열의 요소를
	//array에 복사
	while (leftidx < leftArrlen &&
		rightidx < rightArrlen)
	{
		if(leftarray[leftidx] <= rightarray[rightidx])
		{
			array[mergedidx] = leftarray[leftidx];
			++leftidx;

		}
		else
		{
			
			array[mergedidx] = rightarray[rightidx];
			++rightidx;

			
		}

		++mergedidx;

	}



	//위의 과정에서 왼쪽 배열의 남은 요소를 최종 배열에 복사.
	while (leftidx < leftArrlen)
	{
		array[mergedidx] = leftarray[leftidx];
		++leftidx;
		++mergedidx;
	}

	while (rightidx < rightArrlen)
	{
		//위의 과정에서 오른쪽 배열에 남은 요소를 최종 배열에 복사.
		array[mergedidx] = rightarray[rightidx];
		++rightidx;
		++mergedidx;
	}
}


//병합 정렬 함수 (재귀)
void MergeSort(int* array, int len)
{

	//종료 조건 (더이상 나눌수 없는 상태)
	if (len <= 1)
	{
		return;
	}


	//배열 나누기
	int mid = len / 2;


	//나눠서 저장할 배열 선언(공간 사용).
	int* leftArray = new int[mid];
	int* rightArray = new int[len - mid];


	//배열 복사.memcpy 함수로 메모리 통 복사.
	memcpy(leftArray, array, sizeof(int) * mid);
	memcpy(rightArray, array+mid, sizeof(int) * (len-mid));

	//왼쪽 배열 병합 정렬(재귀)
	MergeSort(leftArray, mid);


	//오른쪽 배열 병합 정렬 (재귀).
	MergeSort(rightArray, len-mid );



	//병합.
	Merge(array, leftArray, mid, rightArray, len - mid);





	//동적 메모리 해제.
	delete[] leftArray;
	delete[] rightArray;
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
	MergeSort(array, len);
	PrintArray(array, len);



}