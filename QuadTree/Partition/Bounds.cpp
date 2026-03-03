#include "Bounds.h"

bool Bounds::Intersects(const Bounds& other) const
{

	
	//겹치는 경우는 다음과 같음.
	//1. this의 왼쪽이 other의 오른쪽보다 왼쪽에 있는 경우.
	//2. this의 오른쪽이 other의 왼쪽보다 오른쪽에 있는 경우.
	//3. this의 위쪽이 other의 아래쪽보다 위에 있는 경우.
	//4. this의 아래쪽이 other의 위쪽보다 아래에 있는 경우.
	return !(X() >= other.MaxX() || MaxX() <= other.X() ||
		Y() >= other.MaxY() || MaxY() <= other.Y());

}
