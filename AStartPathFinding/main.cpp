
#include "Navigation/AStar.h"
#include "Navigation/Node.h"

#include <vector>
#include <Windows.h>
#include <iostream>




void FindStartAndGoalPositions(const std::vector<std::vector<int>>& grid, Node*& startNode, Node*& goalNode);


int main()
{


	std::vector<std::vector<int>> grid =
	{
		{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
		{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1 },
		{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 3, 1 },
		{ 1, 0, 0, 0, 1, 1, 1, 0, 0, 1, 1, 1, 0, 0, 0, 1 },
		{ 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1 },
		{ 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1 },
		{ 1, 0, 0, 0, 1, 1, 1, 0, 0, 1, 1, 1, 0, 0, 1, 1 },
		{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1 },
		{ 1, 2, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1 },
		{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	};

	CONSOLE_CURSOR_INFO info = {};
	info.dwSize = 1; //커서 크기 설정(1~100)
	info.bVisible = FALSE; //커서 숨김
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
	


	//시작 위치 및 목표 위치.
	Node* startNode = nullptr;
	Node* goalNode = nullptr;
	


	FindStartAndGoalPositions(grid, startNode, goalNode);


	//못찾은 경우.
	if (!startNode || !goalNode)
	{
		SafeDelete(startNode);
		SafeDelete(goalNode);


		//콘솔복구(넘어감)
		///...
		return 0;
	}


	//길찾기
	AStar aStar;


	//경로 탐색.
	auto path = aStar.FindPath(startNode, goalNode, grid);


	//성공한 경우.
	if (!path.empty())
	{
		std::cout << "\n경로 탐색 성공\n";
		aStar.DisplayGridWithPath(grid, path);
	}
	//실패한 경우
	else
	{
		std::cout << "\n경로 탐색 실패\n";
	}


	//목표 노드 메모리 해제
	SafeDelete(goalNode);



	std::cin.get();

}

void FindStartAndGoalPositions(const std::vector<std::vector<int>>& grid, Node*& startNode, Node*& goalNode)
{
	
	for (size_t y = 0; y < grid.size(); ++y)
	{

		//다 찾았으면 종료.
		if( startNode && goalNode)
		{
			break;
		}	




		for (size_t x = 0; x < grid[y].size(); ++x)
		{
			//다 찾았으면 종료.
			if (startNode && goalNode)
			{
				break;
			}


			if (grid[y][x] == 2) //시작 위치
			{
				startNode = new Node(static_cast<int>(x), static_cast<int>(y));
				continue ;
			}
			else if (grid[y][x] == 3) //목표 위치
			{
				goalNode = new Node(static_cast<int>(x), static_cast<int>(y));
				continue ;
			}
		}
	}
	

}
