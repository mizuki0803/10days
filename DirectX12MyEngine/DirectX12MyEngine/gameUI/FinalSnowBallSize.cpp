#include "FinalSnowBallSize.h"

float FinalSnowBallSize::finalSize = {};

void FinalSnowBallSize::DetermineFinalSize(float finalSize)
{
	//引数で渡された値を記録する
	FinalSnowBallSize::finalSize = finalSize;
}
