#include "Node.h"
#include "QuadTree.h"

Node::Node(const Bounds& bounds, int depth )
    : bounds(bounds), depth(depth)
{
}

Node::~Node()
{
    Clear();
}



void Node::Insert(Node* node)
{

    if (!node)
    {
        return;
    }


    //겹치는 영역 확인
	NodeIndex region = TestRegion(node->GetBounds());

    //두개 이상의 영역에 겹치는 경우에는 현재 노드에 추가
    if(region == NodeIndex::Stradding)
    {
        points.emplace_back(node);
        return;
	}
    //겹치치지 않는 경우
    //경우의수 1:1영역에만 포함되는 경우
    else if (region != NodeIndex::OutOfArea)
    {
        //subdivide 호출시 maxdepth에 도달하지 않으면 분할 진행
        if (Subdivide())
        {
            if (region == NodeIndex::TopLeft)
            {
                topLeft->Insert(node);
            }
            else if (region == NodeIndex::TopRight)
            {
                topRight->Insert(node);
            }
            else if (region == NodeIndex::BottomLeft)
            {
                bottomLeft->Insert(node);
            }
            else if (region == NodeIndex::BottomRight)
            {
                bottomRight->Insert(node);
			}
        }

		//분할 할수 없는경우 (최대 깊이에 도달한 경우) 현재 노드에 추가.
        else
        {
			points.emplace_back(node);
        }

    }

    return;
    //경우의 수 2: 영역 밖에 있는 경우(outofarea)
    //else
    //{
        //아무처리 안함.....노드추가 안함...
     // }


}


void Node::Query(const Bounds& bounds, std::vector<Node*>& possibleNodes)
{
    //현재 노드를 추가하고 이후 과정 진행.
    possibleNodes.emplace_back(this);

    //분할 여부 확인후 자손 검사.
    if( !IsDivided())
    {
        return;
	}
 

    // 전달 받은 영역과 겹치는 4분면 목록 확인.
    std::vector<NodeIndex> quads = GetQuads(bounds);

    // 검사 진행.
    for (const NodeIndex& index : quads)
    {
        if (index == NodeIndex::TopLeft)
        {
            topLeft->Query(bounds, possibleNodes);
        }
        else if (index == NodeIndex::TopRight)
        {
            topRight->Query(bounds, possibleNodes);
        }
        else if (index == NodeIndex::BottomLeft)
        {
            bottomLeft->Query(bounds, possibleNodes);
        }
        else if (index == NodeIndex::BottomRight)
        {
            bottomRight->Query(bounds, possibleNodes);
        }
    }
}

void Node::Clear()
{

    //points에 추가되는 노드는 외부(level)관리하는 노드이기 때문에
    //여기에서는메모리 관리 (제거) 하지 않음.
    //목록 정리
    points.clear();

    //분할된 경우 자손 정리.
    if( IsDivided())
    {
		topLeft->Clear();
		topRight->Clear();
		bottomLeft->Clear();
		bottomRight->Clear();

        ClearChildren();
	}
}

bool Node::Subdivide()
{
    if (depth == 5)
        return false;


    //분할 여부 파악
    //분할 전이면 영역 나누기
    if (!IsDivided())
    {
        
        //영역을 나누기 위한 변수.
		int x = bounds.X();
		int y = bounds.Y();
		int halfWidth = bounds.Width() / 2;
		int halfHeight = bounds.Height() / 2;


        //각 4분면의 자식 객체 생성.
		topLeft = new Node(Bounds(x,y, halfWidth, halfHeight) , depth + 1 );

		topRight = new Node(Bounds(x + halfWidth, y, halfWidth, halfHeight), depth + 1);

		bottomLeft = new Node(Bounds(x, y + halfHeight, halfWidth, halfHeight), depth + 1);

		bottomRight = new Node(Bounds(x + halfWidth, y + halfHeight, halfWidth, halfHeight), depth + 1);


    }

    return true;
}

bool Node::IsDivided()
{

    //분할이 됐다면 모든 자식노드가 null이 아니기 때문에
    //분할여부 파악할때는 한개만 확인해도 됨

	return topLeft != nullptr;
}

NodeIndex Node::TestRegion(const Bounds& bounds)
{
    //전달된 bounds와 겹치는 4분면 목록 확인.
	std::vector<NodeIndex> quads = GetQuads(bounds);

    //겹치는 곳이 없으면 outofarea반환.
    if( quads.empty())
    {
        return NodeIndex::OutOfArea;
	}


    //4개중 하나의 영역에만 겹치는 경우 해당 4분면 반환.
    if (quads.size() == 1)
    {
        return quads[0];
    }


    //여러 영역과 겹친경우.
    return NodeIndex::Stradding;
}

std::vector<NodeIndex> Node::GetQuads(const Bounds& bounds)
{
    //겹치는 영역 반환을 위한 변수
    std::vector<NodeIndex> quads;

    //영역 계산에 필요한 변수
	int x = this->bounds.X();
	int y = this->bounds.Y();
	int halfWidth = this->bounds.Width() / 2;
	int halfHeight = this->bounds.Height() / 2;
	int centerX = x + halfWidth;
	int centerY = y + halfHeight;

	bool left = bounds.X() < centerX && bounds.MaxX() >= x;
	bool right = bounds.MaxX() >= centerX && bounds.X() < this->bounds.MaxX();
	bool top = bounds.Y() < centerY && bounds.MaxY() >= y;
	bool bottom = bounds.Y() < this->bounds.MaxY() && bounds.MaxY() >= centerY;



    //영역 판정.
    if (top && left)
    {
        quads.emplace_back(NodeIndex::TopLeft);
    }
    if( top && right)
    {
        quads.emplace_back(NodeIndex::TopRight);
	}
    if (bottom && left)
    {
        quads.emplace_back(NodeIndex::BottomLeft);
	}
    if (bottom && right)
    {
        quads.emplace_back(NodeIndex::BottomRight);
    }



    return quads;
}

void Node::ClearChildren()
{
    //분할이 진행된 경우 자손노드삭제
    if (IsDivided())
    {
        SafeDelete(topLeft);
        SafeDelete(topRight);
        SafeDelete(bottomLeft);
		SafeDelete(bottomRight);

    }
}
