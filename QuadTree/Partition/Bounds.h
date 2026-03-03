#pragma once



class Bounds
{
public:

	Bounds(int x, int y, int width =1 , int height=1)
		: x(x), y(y), width(width), height(height)
	{
	}	


	//Getter
	int X() const { return x; }
	int Y() const { return y; }
	int Width() const { return width; }
	int Height() const { return height; }

	int MaxX() const { return x + width; }
	int MaxY() const { return y + height; }


	//겹칩 판정 함수
	bool Intersects(const Bounds& other) const;
	



private:
	//왼쪽 상단 지점을 기준으로위치 표기.
	int x = 0;
	int y = 0;

	//너비/높이
	int width = 1;
	int height = 1;

};