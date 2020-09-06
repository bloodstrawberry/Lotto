#ifndef __STATISTICS_MANAGER__
#define __STATISTICS_MANAGER__

#include "define.h"
#include "LottoManager.h"
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

struct pairKey
{
	int index[7];
	bool operator < (const pairKey& o) const
	{
		if (o.index[0] < index[0]) return true;
		if (o.index[0] == index[0])
		{
			if (o.index[1] < index[1]) return true;
			if (o.index[1] == index[1])
			{
				if (o.index[2] < index[2]) return true;
				if (o.index[2] == index[2])
				{
					if (o.index[3] < index[3]) return true;
					if (o.index[3] == index[3])
					{
						if (o.index[4] < index[4]) return true;
						if (o.index[4] == index[4])
						{
							if (o.index[5] < index[5]) return true;
							if (o.index[5] == index[5])
							{
								if (o.index[6] < index[6]) return true;
							}
						}
					}

				}

			}
				
		}
	


		return false;
	}
};

typedef struct _HOTCOLDONE
{
	vector<int> hotNum;
	vector<int> coldNum;
	vector<int> oneNum;
}HotColdOne;

unsigned int random(void);

int makeAC(LOTTO& lotto);

void makePastLottoResult(LOTTO& Lotto);
void showPastLottoResult(LOTTO Lotto, int offset);
void showAllPastLottoResult(int offset);
void showBinary_long(ull n);

void findConsecutiveNumbers(int lottoNum);
void findAllConsecutiveNumbers();
void showConsecutiveNumbers();

void findJumpNumbers(int lottoNum);
void findAllJumpNumbers();
void showJumpNumbers();

bool isPrime(int num);

void setStatistics(int under, int upper);
void setLatestStatistics(int latest);

void statistics();
void showHotColdOne(int result);

void latestAnalysis(bool bonus);


void countColor(LOTTO& Lotto);

#endif

