#include "Partition/QuadTree.h"

#include <iostream>

//단순한 레벨 클래스.
class Level
{
public:
	Level() = default;
	~Level()
	{
		for (Node*& node : nodeList)
		{
			SafeDelete(node);
		}

		nodeList.clear();

	}


	void AddNewNode(Node* newNode)
	{
		nodeList.emplace_back(newNode);
	}


	//getter.
	const std::vector<Node*>& GetAllnodes() const { return nodeList;  }

private:

	//레벨에 배치된 노드(actor로생각해볼수 있음)
	std::vector<Node*> nodeList;
};

int main()
{
	//레벨 구성.
	Level level;
	level.AddNewNode(new Node(Bounds(60, 70)));
	level.AddNewNode(new Node(Bounds(50, 50)));
	level.AddNewNode(new Node(Bounds(150, 150)));
	level.AddNewNode(new Node(Bounds(50, 150)));
	level.AddNewNode(new Node(Bounds(150, 50)));


	//트리 구성.
	//(0,0)좌표를 왼쪽 상단 지점으로
	QuadTree tree(Bounds(0, 0, 200, 200));

	for (Node* node : level.GetAllnodes())
	{
		tree.Insert(node);
	}
	std::cout << "노드 삽입 완료\n";



	Node testNode(Bounds(10, 10));
	std::vector<Node*> intersects = tree.Query(&testNode);

	//검색 성공
	if (!intersects.empty())
	{
		std::cout << "겹치는 노드를 " << intersects.size() << " 개 찾았습니다\n";
	}
	//검색 실패.
	else
	{
		std::cout << " 겹치는 노드를 찾이 못했습니다\n";
	}
}