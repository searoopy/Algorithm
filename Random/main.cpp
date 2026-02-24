#include <iostream>
#include <time.h>

int RandomRange(int min, int max)
{
	//범위의 차이
	int diff = (max - min) + 1;


	//나눗셈을 이용해서 원하는 범위의 랜덤 반환.
	return ((diff * rand()) / (RAND_MAX + 1)) + min;
}

//부동 소수형
float RandomPercent()
{
	// 0~1사이의 부동 소수형 값 반환.
	return rand() / static_cast<float>(RAND_MAX);
}

//범위를 지정해 사용하는 랜덤 함수(부동소수형)
float RandomRange(float min, float max)
{
	float diff = (max - min);

	return (RandomPercent() * diff) + min;
}

int main()
{

	//종자값 (seed) 설정.
	srand( static_cast<unsigned int>(time(nullptr))  );
	//srand( time(nullptr) );

	std::cout << "random: " << RandomRange(1,100) << "\n";
	std::cout << "random: " << RandomRange(1,100) << "\n";
	std::cout << "random: " << RandomRange(1,100) << "\n";
	std::cout << "random: " << RandomRange(1.0f, 10.0f) << "\n";


	std::cin.get();
}