#pragma once


#include "Bounds.h"
#include <vector>



//메모리 삭제 ㅅ헬퍼 함수.
template<typename T>
void SafeDelete(T*& pointer)
{
	if (pointer)
	{
		delete pointer;
		pointer = nullptr;
	}
}

//영역 구분을 위한 열거형
enum class NodeIndex
{
	//완전히 포함되는 4가지.
	TopLeft = 0,
	TopRight = 1,
	BottomLeft = 2,
	BottomRight = 3,

	//경계선에 걸침.
	Stradding,
	//영역을 벗어난 경우.
	OutOfArea
};;


//쿼드 트리를 구성하는 노드 클래스.
//
class Node
{
public:
	Node(const Bounds& bounds, int depth = 0);
	~Node();


	void Insert(Node* node);

	//질의
	//bounds: 영역 테스트 요청값.
	//possibleNodes: 전달된 영역을 관리할 가능성이 있는 노드 목록.
	void Query(const Bounds& bounds, std::vector<Node*>& result);


	void Clear();

	//getter
	inline const Bounds& GetBounds() const { return bounds; }

	inline const std::vector<Node*>& Points() const { return points; }

	//자식노드
	inline Node* TopLeft() const { return topLeft; }
	inline Node* TopRight() const { return topRight; }
	inline Node* BottomLeft() const { return bottomLeft; }
	inline Node* BottomRight() const { return bottomRight; }
	
	
private:
	//4분할 함수
	bool Subdivide();

	//영역이 분할됐는지 여부 확인 함수.
	bool IsDivided();

	//전달된 영역과 겹치는 영역을 반환하는함수.
	NodeIndex TestRegion(const Bounds& bounds);

	//전달한 영역이 포함되거나 거치는 영역을 모두 구할때 사용하는 함수.
	std::vector<NodeIndex> GetQuads(const Bounds& bounds);

	void ClearChildren();


private:
	//현재 노드의 깊이.
	int depth = 0;

	//노드의 영역(bounds).
	Bounds bounds;

	//현재 영역에 포함된 노드(목록)
	std::vector<Node*> points;


	std::vector<Node*> possibleNodes;

	//자식 노드(4개)
	Node* topLeft = nullptr;
	Node* topRight = nullptr;
	Node* bottomLeft = nullptr;
	Node* bottomRight = nullptr;

};