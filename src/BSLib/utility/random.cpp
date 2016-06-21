#include <time.h>
#include <stdlib.h>
#include <BSLib/utility/random.h>

namespace BSLib
{

namespace Utility
{

BSLib::uint32 g_randomSeed = (BSLib::uint32)time(NULL);

void CRandom::setRandomSeed(BSLib::uint32 randomSeed)
{
	g_randomSeed = randomSeed;
	srand(g_randomSeed);
}

int CRandom::randomBetween(int minNum, int maxNum)
{
	if (minNum == maxNum) {
		return minNum;
	}
	if (minNum > maxNum) {
		return maxNum + (int)(((double)minNum - (double)maxNum + 1.0) * ((double)rand()) / ((double)(RAND_MAX + 1.0)));
	}
	return minNum + (int)(((double)maxNum - (double)minNum + 1.0) * ((double)rand()) / ((double)(RAND_MAX + 1.0)));
}


bool CRandom::selectByOdds(BSLib::uint32 upNum, BSLib::uint32 downNum)
{
	if (upNum < 1 || downNum < 1) {
		return false;
	}
	if (upNum >= downNum) {
		return true;
	}
	BSLib::uint32 randData = (BSLib::uint32)randomBetween(0, downNum);
	return randData < upNum;
}

}//Utility

}//BSLib

