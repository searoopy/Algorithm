#include <iostream>


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


//배열을 힙으로 만드는 함수
//array:정렬 중인 배열.
//length:배열 항목수.
//index 현재 처리중인 인덱스
void Heapify(int* array, int length, int index)
{

	//todo:구현

	//힙구성을 완료할 떄까지 반복.
	while (true)
	{
		//최대힙(MaxHeap).
		int largest = index;

		//자손 인덱스 구하기.
		//왼쪽 자손:2n+1,
		int leftChild = 2 * index + 1;
		//오른쪽 자손 :2n+1,
		int rightChild = 2 * index + 2;


		//더 큰값 크기( +자손 인덱스 존재 여부 확인)
		if (leftChild < length
			&& array[leftChild] > array[largest])
		{
			largest = leftChild;
		}

		//더 큰값 크기( +자손 인덱스 존재 여부 확인)
		if (rightChild < length
			&& array[rightChild] > array[largest])
		{
			largest = rightChild;
		}

		//현재 노드가 가장 크면 종료.
		//힙 구조가 유지된 것이기 때문.
		if (largest == index)
		{
			break;
		}


		//현재 노드와 자손노드 (가장 큰 값을 가지는) 교환
		std::swap<int>(array[largest], array[index]);


		//largest 를 index로 업데이트.
		index = largest;

	}
}


//glq wjdfuf gkatn.
void HeapSort(int* array, int length)
{
	//힙 구조로 변환.
	for (int i = (length / 2 )- 1; i >= 0; --i)
	{
		Heapify(array, length, i);
	}


	//힙 정렬.
	for (int i = length - 1; i > 0; --i)
	{
		//루트 노드와 마지막 노드를 교환
		//std::swap<int>(array[0], array[i]);

		//힙 구조를 유지하기 위해 루트 노드부터 다시 힙으로 만들기.
	///	Heapify(array, i, 0);
	}
}

//힙 정렬 함수
int main()
{
	int array[] = {2,24,5,1,6,4,4,4,62,123,634,231,1,11};


	int len = _countof(array);

	PrintArray(array, len);

	HeapSort(array, len);

	PrintArray(array, len);
}