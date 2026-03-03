#include "QuadTree.h"

QuadTree::QuadTree(const Bounds& bounds)
{
	//루트 노드 생성
	root = new Node(bounds);
}

QuadTree::~QuadTree()
{
	SafeDelete(root);
}

//트리에 노드 추가 함수
void QuadTree::Insert(Node* node) 
{
	if (!node)
	{
		return;
	}

	root->Insert(node);
}

//질의 함수
std::vector<Node*> QuadTree::Query(Node* queryNode)
{
	if (!queryNode)
	{
		return {};
		//return  std::vector<Node*> ();
	}

	//겹칠 가능성 있는 영역 확인.
	std::vector<Node*> possibleNodes;
	root->Query(queryNode->GetBounds(), possibleNodes);

	//실제 겹치는 노드들만 확인
	std::vector<Node*> intersects;
	for (Node* const node : possibleNodes)
	{
		for (Node* const point : node->Points() )
		{
			if (point->GetBounds().Intersects(queryNode->GetBounds()))
			{
				intersects.emplace_back(point);
				continue;
			}
		}
	}

	return intersects;
}