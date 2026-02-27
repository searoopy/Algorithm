#pragma once

#include "Node.h"
#include <vector>

template<typename T>
void SafeDelete(T*& t)
{
	if (t)
	{
		delete t;
		t = nullptr;
	}
}

class AStar 
{
public:


	//방향 처리를 위한 구조체
	struct Direction
	{
		int x = 0;
		int y = 0;

		//이동 비용.
		float cost = 0.0f;
	};



	AStar();
	~AStar();
	
	//객체 지향 이론에서 -> 메시지(message) ->공개 멤버 함수....(인터페이스)
	//경로 검색 (탐색) 함수.,

	//startnode:시작지점
	//goalnode: 목표 지점.
	//grid 탐색할 맵(2차원 배열)
	std::vector<Node*> FindPath(Node* statNode, Node* goalNode,
		std::vector<std::vector<int>>& grid);


	//맵 그리드 출력 함수.
	void DisplayGridWithPath(
		std::vector<std::vector<int>>& grid,
		const std::vector<Node*>& path
	);


private:
	//객체 지향 이론에서 -> 매소드(method) -> 비공개 멤버 함수.


	//탐색을 완료한 후에 최적 경로 반환하는 함수.
	//부모링크를 따라가면서 역추적..
	std::vector<Node*> ConstructPath(Node* goalNode);


	//휴리스틱 계산 함수
	float CalculateHeuristic(Node* currentNode, Node* goalNode);

	//탐색하려는 위치가 그리고 범위안에 있는지 확인
	//유효성 검증
	bool IsInRange(int x, int y, const std::vector<std::vector<int>>& grid);


	//이미 방문했는지 확인하는 함수
	bool HasVisited(int x, int y, float gCost);


	//탐색하려는 노드가 목표노드인지 확인하는 함수
	bool IsDestination(const Node* const node);


	//그리그 출력함수
	void DisplayGrid(std::vector< std::vector<int>>& grid);


private:




	//열린 리스트.

	std::vector<Node*> openList;



	//닫힌 리스트
	std::vector<Node*> closedList;



	//시작 노드
	Node* startNode = nullptr;



	// 목표 노드.
	Node* goalNode = nullptr;



};