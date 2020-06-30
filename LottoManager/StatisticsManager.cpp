//당첨된 번호 분석용 cpp
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <map>
#include <iostream>
#include <fstream>
#include <vector>
#include <time.h>

#include "StatisticsManager.h"

using namespace std;
//statistic
extern int NumOfWinLotto;
extern LOTTO LottoWinningNumber[];

int START_NUMBER;
int END_NUMBER;

int CONSECUTIVE_NUMBERS[7][50];
int JUMP_NUMBERS[7][50];

extern int NumOfHotNumber;
extern int HotNumber[50];
extern int NumOfColdNumber;
extern int ColdNumber[50];
extern int NumOfOneNumber;
extern int OneNumber[50];


LOTTO endLotto;
int endNumber[50];
HotColdOne hotColdOne[2000];

int primeNumber[] = { 0,
						0,1,1,0,1,0,1,0,0,0,
						1,0,1,0,0,0,1,0,1,0,
						0,0,1,0,0,0,0,0,1,0,
						1,0,0,0,0,0,1,0,0,0,
						1,0,1,0,0,0,1,0,0,0, };

unsigned long long seed = 5; // seed can be changed
unsigned int random(void)
{
	return ((unsigned int)((seed = seed * 25214903917ULL + 11ULL) >> 16));
}

MYTIME getTime(int result)
{
	struct tm *t;
	time_t BASEDAY = 1038620800 + 604800 * result;
	MYTIME ret;

	t = localtime(&BASEDAY);

	ret.year = t->tm_year + 1900;
	ret.month = t->tm_mon + 1;
	ret.day = t->tm_mday;

	return ret;
}

int myabs(int a, int b)
{
	return (a < b) ? b - a : a - b;
}

int makeAC(LOTTO& lotto)
{
	int table[46] = { 0 };
	for (int k1 = 0; k1 < 5;k1++)
		for (int k2 = k1 + 1; k2 < 6;k2++)
			table[myabs(lotto.number[k1], lotto.number[k2])] = 1;

	int cnt = 0;
	for (int i = 1; i <= 44;i++) cnt += table[i];

	return cnt - 5;
}

void makePastLottoResult(LOTTO& Lotto)
{
	int RANK[] = { 6, 6, 6, 5, 4, 3, 1 };

	for (int i = 1; i <= NumOfWinLotto;i++)
	{
		int cnt, bonus, rank;
		int table[50] = { 0 };

		cnt = bonus = 0;

		for (int k = 0; k < 6;k++) table[LottoWinningNumber[i].number[k]] = 1;
		for (int k = 0; k < 6;k++) cnt += table[Lotto.number[k]];

		for (int k = 0; k < 6;k++)
		{
			if (Lotto.number[k] == LottoWinningNumber[i].bonus)
			{
				bonus = 1;
				break;
			}
		}

		rank = RANK[cnt];
		if (rank == 3 && bonus == 1) rank = 2;
		Lotto.countOfPastRanks[rank]++;
	}
}


void showPastLottoResult(LOTTO Lotto, int offset)
{
	int RANK[] = { 6, 6, 6, 5, 4, 3, 1 };

	for (int i = 1; i <= NumOfWinLotto;i++)
	{
		int cnt, bonus, rank;
		int table[50] = { 0 };

		cnt = bonus = 0;

		for (int k = 0; k < 6;k++) table[LottoWinningNumber[i].number[k]] = 1;
		for (int k = 0; k < 6;k++) cnt += table[Lotto.number[k]];

		for (int k = 0; k < 6;k++)
		{
			if (Lotto.number[k] == LottoWinningNumber[i].bonus)
			{
				bonus = 1;
				break;
			}
		}

		rank = RANK[cnt];
		if (rank == 3 && bonus == 1) rank = 2;

		if (rank <= offset)
		{
			printf("round %4d]   ", i);
			showLottoNumber(LottoWinningNumber[i]);
			printf("rank  %4d]   ", rank);
			for (int k = 0; k < 6;k++)
			{
				if (table[Lotto.number[k]]) printf("[%d] ", Lotto.number[k]);
				else printf("%d ", Lotto.number[k]);
			}
			printf("\n=================================\n");
		}

	}

}

void showAllPastLottoResult(int offset)
{
	int i;
	for (i = 1; i <= NumOfWinLotto;i++)
		showPastLottoResult(LottoWinningNumber[i], offset);
}

void showBinary_long(ull n)
{
	ull mask = 1ull << 63;
	for (int i = 0; i < 64;i++)
	{
		printf("%d ", (n & mask) == mask);
		mask >>= 1;
	}
	putchar('\n');
}

void findConsecutiveNumbers(int lottoNum)
{
	int i;
	LOTTO& Lotto = LottoWinningNumber[lottoNum];

	for (i = 0; i < 5;i++)
	{
		if (Lotto.number[i + 1] - Lotto.number[i] == 1)
		{
			//printf("%d] %d %d\n", lottoNum + 1, Lotto.number[i], Lotto.number[i + 1]);
			CONSECUTIVE_NUMBERS[2][Lotto.number[i]]++;
		}
	}
}

void findAllConsecutiveNumbers()
{
	// 2연속 번호만 check.
	int lottoNum;
	for (lottoNum = START_NUMBER; lottoNum <= END_NUMBER;lottoNum++)
	{
		findConsecutiveNumbers(lottoNum);
	}
}

void showConsecutiveNumbers()
{
	ofstream fout;
	fout.open("ShowConsecutiveNumber.txt");

	printf("\n================ show consecutivenumbers ==============\n");

	int index[50] = { 0 };
	int value[50] = { 0 };

	for (int i = 0; i < 50;i++) index[i] = i;
	for (int i = 0; i < 50;i++) value[i] = CONSECUTIVE_NUMBERS[2][i];

	for (int i = 0; i < 49;i++)
	{
		for (int k = i + 1; k < 50;k++)
		{
			if (value[i] > value[k]) continue;

			int tmp = value[i];
			value[i] = value[k];
			value[k] = tmp;

			tmp = index[i];
			index[i] = index[k];
			index[k] = tmp;
		}
	}

	for (int i = 0; i < 45;i++)
	{
		//if (index[i] <= 45) printf("%d, %d] : %d\n", index[i], index[i] + 1, value[i]);
		if (index[i] <= 45)
		{
			char buff[10];
			sprintf(buff, "%2d, ", index[i]);
			fout << buff;
			sprintf(buff, "%2d] : %2d ", index[i] + 1, value[i]);
			fout << buff;
			if (endNumber[index[i]] && endNumber[index[i] + 1]) fout << " [+]";
			fout << endl;
		}
	}
		
	fout.close();
}

void findJumpNumbers(int lottoNum)
{
	int i;
	LOTTO& Lotto = LottoWinningNumber[lottoNum];

	for (i = 0; i < 5;i++)
	{
		if (Lotto.number[i + 1] - Lotto.number[i] == 2)
		{
			//printf("%d] %d %d\n", lottoNum + 1, Lotto.number[i], Lotto.number[i + 1]);
			JUMP_NUMBERS[2][Lotto.number[i]]++;
		}
	}
}

void findAllJumpNumbers()
{
	int lottoNum;
	for (lottoNum = START_NUMBER; lottoNum <= END_NUMBER;lottoNum++)
	{
		findJumpNumbers(lottoNum);
	}
}

void showJumpNumbers()
{
	ofstream fout;
	fout.open("ShowJumpNumber.txt");

	//for (int i = 1; i <= 44;i++) 
	//if(consecutive_numbers[2][i]) printf("%d, %d] : %d\n", i, i+1, consecutive_numbers[2][i]);
	
	printf("\n================ show jump number ==============\n");

	int index[50] = { 0 };
	int value[50] = { 0 };

	for (int i = 0; i < 50;i++) index[i] = i;
	for (int i = 0; i < 50;i++) value[i] = JUMP_NUMBERS[2][i];

	for (int i = 0; i < 49;i++)
	{
		for (int k = i + 1; k < 50;k++)
		{
			if (value[i] > value[k]) continue;

			int tmp = value[i];
			value[i] = value[k];
			value[k] = tmp;

			tmp = index[i];
			index[i] = index[k];
			index[k] = tmp;
		}
	}

	
	for (int i = 0; i < 45;i++)
	{
		//if (index[i] <= 45) printf("%d, %d] : %d\n", index[i], index[i] + 1, value[i]);
		if (index[i] <= 45)
		{
			char buff[10];

			sprintf(buff, "%2d, ", index[i]);
			fout << buff;
			sprintf(buff, "%2d] : %2d ", index[i] + 2, value[i]);
			fout << buff;

			if (endNumber[index[i]] && endNumber[index[i] + 2]) fout << " [+]";
			fout << endl;
		}
	}

	fout.close();
}

bool isPrime(int num)
{
	return primeNumber[num];
}

void setStatistics(int under, int upper)
{
	START_NUMBER = under;
	END_NUMBER = upper;

	if (END_NUMBER > NumOfWinLotto) END_NUMBER = NumOfWinLotto;
	endLotto = LottoWinningNumber[END_NUMBER];
	for (int i = 0; i < 6;i++) endNumber[endLotto.number[i]] = 1;
}

void showWinningNumbers()
{
	ofstream fout;
	fout.open("ShowWinningNumber.txt");

	for (int i = 1; i <= NumOfWinLotto;i++)
	{
		int cnt = 0;
		LOTTO& lotto = LottoWinningNumber[i];
		
		lotto.mtime = getTime(i);

		for (int k = 1; k <= 45;k++)
		{
			if (lotto.number[cnt] == k)
			{
				fout << "[";
				fout << lotto.number[cnt];
				fout << "]";
				cnt++;
			}
			else if (lotto.bonus == k)
			{
				fout << "<";
				fout << lotto.bonus;
				fout << ">";
			}
			else
			{
				fout << " ";
				fout << k;
				fout << " ";
			}
		}

		fout << endl;
	}

	fout << endl;
	for (int i = 1; i <= NumOfWinLotto;i++)
	{
		int cnt = 0;
		LOTTO& lotto = LottoWinningNumber[i];
		for (int k = 1; k <= 45;k++)
		{
			if (lotto.bonus == k) fout << "○";
			else if (lotto.number[cnt] == k)
			{
				fout << "■";
				cnt++;
			}
			else fout << "□";
			
		}

		fout << endl;
	}

	fout.close();
}

void findNextNumber(vector<int>& nextNumber, LOTTO& lotto, LOTTO& before)
{
	int check[50] = { 0 };
	for (int k = 0; k < 6;k++) check[before.number[k]] = 1;

	for (int k = 0; k < 6;k++)
		if (check[lotto.number[k]]) nextNumber.push_back(lotto.number[k]);
}

int dayCount[50];
int monthCount[50];
int ndayCount[50];
int nmonthCount[50];

int dayCountb[50];
int monthCountb[50];
int ndayCountb[50];
int nmonthCountb[50];


void checkDayMonth(LOTTO& lotto, char* buff, int result)
{
	int table[50] = { 0 };
	for (int k = 0; k < 6;k++)
		table[lotto.number[k]] = 1;

	int len = 0;
	
	if (table[lotto.mtime.month])
	{
		len += sprintf(buff, "[ M: %2d, ", lotto.mtime.month);
		if(START_NUMBER <= result && result <= END_NUMBER) monthCount[lotto.mtime.month]++;
	}
	else
	{
		len += sprintf(buff, "[ M:   , ");
		if (START_NUMBER <= result && result <= END_NUMBER) nmonthCount[lotto.mtime.month]++;
	}

	if (table[lotto.mtime.day])
	{
		len += sprintf(buff + len, "D: %2d, ", lotto.mtime.day);
		if (START_NUMBER <= result && result <= END_NUMBER) dayCount[lotto.mtime.day]++;
	}
	else
	{
		len += sprintf(buff + len, "D:   , ");
		if (START_NUMBER <= result && result <= END_NUMBER) ndayCount[lotto.mtime.day]++;
	}

	if (lotto.mtime.month == lotto.bonus)
	{
		len += sprintf(buff + len, "MB: %2d, ", lotto.bonus);
		if (START_NUMBER <= result && result <= END_NUMBER) monthCountb[lotto.mtime.month]++;
	}
	else
	{
		len += sprintf(buff + len, "MB:   , ");
		if (START_NUMBER <= result && result <= END_NUMBER) nmonthCountb[lotto.mtime.month]++;
	}

	if (lotto.mtime.day == lotto.bonus)
	{
		len += sprintf(buff + len, "DB: %2d ] ", lotto.bonus);
		if (START_NUMBER <= result && result <= END_NUMBER) dayCountb[lotto.mtime.day]++;
	}
	else
	{
		len += sprintf(buff + len, "MD:    ] ");
		if (START_NUMBER <= result && result <= END_NUMBER) ndayCountb[lotto.mtime.day]++;
	}
}

void showStatisticsWinningNumber()
{
	ofstream fout;
	fout.open("StatisticsWinningNumber.txt");
	char buff[100];
	for (int i = 1; i <= NumOfWinLotto;i++)
	{
		LOTTO& lotto = LottoWinningNumber[i];
		
		int hot, cold, one;
		vector<int>& vhot = hotColdOne[i].hotNum;
		vector<int>& vcold = hotColdOne[i].coldNum;
		vector<int>& vone = hotColdOne[i].oneNum;

		hot = cold = one = 0;
		int chkhot[50] = { 0 };
		int chkcold[50] = { 0 };
		int chkone[50] = { 0 };

		for (int i = 0; i < vhot.size(); i++) chkhot[vhot[i]]++;
		for (int i = 0; i < vcold.size(); i++) chkcold[vcold[i]]++;
		for (int i = 0; i < vone.size(); i++) chkone[vone[i]]++;


		char buf[100];
		sprintf(buf, "%4d] { %4d/%02d/%02d } ", i,lotto.mtime.year, lotto.mtime.month, lotto.mtime.day);
		fout << buf;
		for (int k = 0; k < 7;k++)
		{
			if (k == 6) fout << "<";
			bool hotflag = chkhot[lotto.number[k]] && (k != 6);
			bool coldflag = chkcold[lotto.number[k]] && (k != 6);
			bool oneflag = chkone[lotto.number[k]] && (k != 6);

			if (hotflag) ++hot, fout << "[";
			if (coldflag) ++cold, fout << " ";
			if (oneflag) ++one, fout << "(";

			sprintf(buff, "%2d", lotto.number[k]);
			fout << buff;
			if (hotflag) fout << "]";
			if (coldflag) fout << " ";
			if (oneflag) fout << ")";

			
			if (k == 6) fout << ">";
			fout << " ";
		}
		fout << endl;

		checkDayMonth(lotto, buf, i);
		fout << buf;

		makePastLottoResult(lotto);

		fout << "                         [ ";
		for (int k = 1; k <= 5;k++)
		{
			fout << lotto.countOfPastRanks[k];
			
			fout << " ";
		}
		fout << "] ";
		
		int odd = countOddNumber(lotto);
		int even = 6 - odd;
		int prime = countPrimeNumber(lotto);

		char evenoddprime[30];
		sprintf(evenoddprime, "[ %d vs %d / %d ] ", even, odd, prime);
		fout << evenoddprime;

		odd += (lotto.bonus & 1);
		even += (!(lotto.bonus & 1));
		prime += isPrime(lotto.bonus);
		sprintf(evenoddprime, "[ %d vs %d / %d ] ", even, odd, prime);
		fout << evenoddprime;

		sprintf(evenoddprime, "[ %d / %d / %d ] ", hot, cold, one);
		
		fout << evenoddprime;

		lotto.numOfOddNum	= odd;
		lotto.numOfPrimeNum = prime;
		lotto.numOfHot		= hot;
		lotto.numOfCold		= cold;
		lotto.numOfOne		= one;

		sprintf(evenoddprime, "[%3d] ", makeSum(lotto));
		fout << evenoddprime;

		lotto.AC = makeAC(lotto);
		sprintf(evenoddprime, "[AC: %2d] ", lotto.AC);
		fout << evenoddprime;

		vector<int> nextNumber;
		LOTTO& before = LottoWinningNumber[i - 1];
		findNextNumber(nextNumber, lotto, before);

		if (nextNumber.size() == 0) fout << "[ x ]";
		else
		{
			fout << "[ ";
			for (int k = 0; k < nextNumber.size();k++)
			{
				if(k == nextNumber.size() - 1) sprintf(buff, "%2d ", nextNumber[k]);
				else sprintf(buff, "%2d ", nextNumber[k]);
				fout << buff;
			}
			

			bool R_BFlag = false;
			for (int k = 0; k < 6;k++)
			{
				if (before.number[k] == lotto.bonus)
				{
					R_BFlag = true;
					break;
				}
			}

			bool B_RFlag = false;
			for (int k = 0; k < 6;k++)
			{
				if (lotto.number[k] == before.bonus)
				{
					B_RFlag = true;
					break;
				}
			}

			if (B_RFlag || R_BFlag || lotto.bonus == before.bonus) fout << "/ ";

			if (B_RFlag)
			{
				sprintf(buff, "B->R {%d} ", before.bonus);
				fout << buff;
			}

			if (R_BFlag)
			{
				sprintf(buff, "R->B <%d> ",lotto.bonus);
				fout << buff;
			}

			if (lotto.bonus == before.bonus)
			{
				sprintf(buff, "B->B -%d- ", lotto.bonus);
				fout << buff;
			}

			
			fout << "]";
		}


		fout << endl;
		fout << endl;
		
	}

	fout.close();
}

void showHotColdOne(int result)
{
	vector<int>& vhot = hotColdOne[result].hotNum;
	vector<int>& vcold = hotColdOne[result].coldNum;
	vector<int>& vone = hotColdOne[result].oneNum;

	printf("Hot : \n");
	for (int i = 0; i < vhot.size(); i++)
		printf("%d ", vhot[i]);
	putchar('\n');

	printf("Cold : \n");
	for (int i = 0; i < vcold.size(); i++)
		printf("%d ", vcold[i]);
	putchar('\n');

	printf("One : \n");
	for (int i = 0; i < vone.size(); i++)
		printf("%d ", vone[i]);
	putchar('\n');

}

int LIMIT = 10;
void findHotColdOne(int result)
{
	if (result <= LIMIT)
	{
		printf("LIMIT [%d], result [%d] is impossible\n", LIMIT, result);
		exit(1);
	}

	vector<int>& vhot = hotColdOne[result].hotNum;
	vector<int>& vcold = hotColdOne[result].coldNum;
	vector<int>& vone = hotColdOne[result].oneNum;

	int beforelimitx2 = result - LIMIT;
	int beforelimit = result - LIMIT / 2;
	int checkx2[50] = { 0 };
	int check[50] = { 0 };

	for (int i = beforelimitx2; i < beforelimitx2 + (LIMIT / 2); i++)
	{
		for (int k = 0; k < 6;k++)
			checkx2[LottoWinningNumber[i].number[k]]++;
	}

	for (int i = beforelimit; i < beforelimit + (LIMIT / 2);i++)
	{
		for (int k = 0; k < 6;k++)
			check[LottoWinningNumber[i].number[k]]++;
	}
	
	for (int i = 1; i <= 45;i++)
	{
		if ((checkx2[i] && check[i]) || (check[i] >= 2)) vhot.push_back(i);
		else if ((checkx2[i] + check[i]) == 0) vone.push_back(i);
		else vcold.push_back(i);
	}


}

map<pairKey, int> oneNum;
map<pairKey, int> latestOneNum;
map<pairKey, int> onlyBonus;
map<pairKey, int> latestOnlyBonus;
map<pairKey, int> withBonus;
map<pairKey, int> latestWithBonus;

map<pairKey, int> pair2;
map<pairKey, int> latestPair2;
map<pairKey, int> pair2b;
map<pairKey, int> latestPair2b;

map<pairKey, int> pair3;
map<pairKey, int> latestPair3;
map<pairKey, int> pair3b;
map<pairKey, int> latestPair3b;

map<pairKey, int> pair4;
map<pairKey, int> latestPair4;
map<pairKey, int> pair4b;
map<pairKey, int> latestPair4b;

map<pairKey, int> pair5;
map<pairKey, int> latestPair5;
map<pairKey, int> pair5b;
map<pairKey, int> latestPair5b;

map<pairKey, int> pair6b;
map<pairKey, int> latestPair6b;

bool cmp(const pair<pairKey, int>& a, const pair<pairKey, int>& b)
{
	return (a.second > b.second);
}

void pksort(pairKey& pk, int index)
{
	for(int i = 0; i<index -1; i++)
		for(int k = i+1; k<index;k++)
			if (pk.index[i] > pk.index[k])
			{
				int tmp = pk.index[i];
				pk.index[i] = pk.index[k];
				pk.index[k] = tmp;
			}
	
}

void showPair(const char* fileName, map<pairKey, int>& m, map<pairKey, int>& latest)
{
	ofstream fout;
	fout.open(fileName);

	vector<pair<pairKey, int>> vec(m.begin(), m.end());
	sort(vec.begin(), vec.end(), cmp);

	fout << fileName << endl;

	for (auto chk : vec)
	{
		char buf[50];
		for (int k = 0; k < 4;k++)
		{
			sprintf(buf, "%2d", chk.first.index[k]);
			fout << buf;
			if (chk.first.index[k + 1] == 0) break;
			fout << " ";
		}

		sprintf(buf, "] %d %d", chk.second, latest[chk.first]);
		fout << buf;
		if (latest[chk.first] == END_NUMBER) fout << " [+]" << endl;
		else fout << endl;
		
		//printf("%d %d %d] %d %d\n", chk.first.index[0], chk.first.index[1], chk.first.index[2], chk.second, latestPair5[chk.first]);
	}

	fout.close();
}

int sttPrime[8];
int sttPrimeb[8];
int sttEven[8];
int sttEvenb[8];

int sttPastRanks[6][2000];

int arrLotto[2000][46];
int arrLottob[2000][46];

int countJumpNumber(LOTTO& lotto, int jump)
{
	int cnt = 0;
	for (int k = 0; k < 5;k++)
		if ((lotto.number[k + 1] - lotto.number[k]) == jump) cnt++;
	return cnt;
}

void showAllStatistics()
{
	int total = END_NUMBER - START_NUMBER + 1;
	ofstream fout;
	fout.open("ShowAllStatistics.txt");
	endLotto = LottoWinningNumber[END_NUMBER];
	for (int i = START_NUMBER; i <= END_NUMBER; i++)
	{
		LOTTO& lotto = LottoWinningNumber[i];
		for (int k = 0; k < 6;k++)
		{	
			pairKey pk = { 0 };
			pk.index[0] = lotto.number[k];
			oneNum[pk]++;
			latestOneNum[pk] = i;
		}
		
		for (int k = 0; k < 7;k++)
		{
			pairKey pk = { 0 };
			pk.index[0] = lotto.number[k];
			withBonus[pk]++;
			latestWithBonus[pk] = i;
		}
			
		{
			pairKey pk = { 0 };
			pk.index[0] = lotto.bonus;
			onlyBonus[pk]++;
			latestOnlyBonus[pk] = i;
		}

		for (int k1 = 0; k1 < 5;k1++)
		{
			for (int k2 = k1 + 1; k2 < 6;k2++)
			{
				pairKey pk = { 0 };
				pk.index[0] = lotto.number[k1];
				pk.index[1] = lotto.number[k2];

				pair2[pk]++;
				latestPair2[pk] = i;
			}
		}

		for (int k1 = 0; k1 < 6;k1++)
		{
			for (int k2 = k1 + 1; k2 < 7;k2++)
			{
				pairKey pk = { 0 };
				pk.index[0] = lotto.number[k1];
				pk.index[1] = lotto.number[k2];

				pksort(pk, 2);

				pair2b[pk]++;
				latestPair2b[pk] = i;
			}
		}

		for (int k1 = 0; k1 < 4;k1++)
		{
			for (int k2 = k1 + 1; k2 < 5;k2++)
			{
				for (int k3 = k2 + 1; k3 < 6;k3++)
				{
					pairKey pk = { 0 };
					pk.index[0] = lotto.number[k1];
					pk.index[1] = lotto.number[k2];
					pk.index[2] = lotto.number[k3];

					pair3[pk]++;
					latestPair3[pk] = i;
				}
			}
		}

		for (int k1 = 0; k1 < 5;k1++)
		{
			for (int k2 = k1 + 1; k2 < 6;k2++)
			{
				for (int k3 = k2 + 1; k3 < 7;k3++)
				{
					pairKey pk = { 0 };
					pk.index[0] = lotto.number[k1];
					pk.index[1] = lotto.number[k2];
					pk.index[2] = lotto.number[k3];

					pksort(pk, 3);

					pair3b[pk]++;
					latestPair3b[pk] = i;
				}
			}
		}

		for (int k1 = 0; k1 < 3;k1++)
		{
			for (int k2 = k1 + 1; k2 < 4;k2++)
			{
				for (int k3 = k2 + 1; k3 < 5;k3++)
				{
					for (int k4 = k3 + 1; k4 < 6;k4++)
					{
						pairKey pk = { 0 };
						pk.index[0] = lotto.number[k1];
						pk.index[1] = lotto.number[k2];
						pk.index[2] = lotto.number[k3];
						pk.index[3] = lotto.number[k4];

						pair4[pk]++;
						latestPair4[pk] = i;
					}
				}
			}
		}

		for (int k1 = 0; k1 < 4;k1++)
		{
			for (int k2 = k1 + 1; k2 < 5;k2++)
			{
				for (int k3 = k2 + 1; k3 < 6;k3++)
				{
					for (int k4 = k3 + 1; k4 < 7;k4++)
					{
						pairKey pk = { 0 };
						pk.index[0] = lotto.number[k1];
						pk.index[1] = lotto.number[k2];
						pk.index[2] = lotto.number[k3];
						pk.index[3] = lotto.number[k4];

						pksort(pk, 4);
						pair4b[pk]++;
						latestPair4b[pk] = i;
					}
				}
			}
		}



		//for (int k1 = 0; k1 < 2;k1++)
		//{
		//	for (int k2 = k1 + 1; k2 < 3;k2++)
		//	{
		//		for (int k3 = k2 + 1; k3 < 4;k3++)
		//		{
		//			for (int k4 = k3 + 1; k4 < 5;k4++)
		//			{
		//				for (int k5 = k4 + 1; k5 < 6;k5++)
		//				{
		//					pairKey pk = { 0 };
		//					pk.index[0] = lotto.number[k1];
		//					pk.index[1] = lotto.number[k2];
		//					pk.index[2] = lotto.number[k3];
		//					pk.index[3] = lotto.number[k4];
		//					pk.index[4] = lotto.number[k5];
		//					pair5[pk]++;
		//					latestPair5[pk] = i;
		//				}
		//			}
		//		}
		//	}
		//}
	}
	
	printf("================ show Pair ==============\n");
	showPair("Pair1.txt", oneNum, latestOneNum);
	showPair("Pair1_bonus.txt", withBonus, latestWithBonus);
	showPair("Pair1_onlybonus.txt", onlyBonus, latestOnlyBonus);
	showPair("Pair2.txt", pair2, latestPair2);
	showPair("Pair2_bonus.txt", pair2b, latestPair2b);
	showPair("Pair3.txt", pair3, latestPair3);
	showPair("Pair3_bonus.txt", pair3b, latestPair3b);
	showPair("Pair4.txt", pair4, latestPair4);
	showPair("Pair4_bonus.txt", pair4b, latestPair4b);

	int sttAC[11] = { 0 };
	for (int i = START_NUMBER; i <= END_NUMBER; i++)
	{
		LOTTO& lotto = LottoWinningNumber[i];

		sttPrime[countPrimeNumber(lotto)]++;
		sttEven[6 - countOddNumber(lotto)]++;
		sttPrimeb[countPrimeNumber(lotto) + isPrime(lotto.bonus)]++;
		sttEvenb[6 - countOddNumber(lotto) + !(lotto.bonus & 1)]++;

		sttPastRanks[1][lotto.countOfPastRanks[1]]++;
		sttPastRanks[2][lotto.countOfPastRanks[2]]++;
		sttPastRanks[3][lotto.countOfPastRanks[3]]++;
		sttPastRanks[4][lotto.countOfPastRanks[4]]++;
		sttPastRanks[5][lotto.countOfPastRanks[5]]++;
		sttAC[lotto.AC]++;
	}

	char buff[500];
	printf("================ show All Statistics ==============\n");
	fout << "Prime Count\n";
	for (int i = 0; i <= 6;i++)
	{
		sprintf(buff, "%d] %d", i, sttPrime[i]);
		fout << buff;
		if (i == endLotto.numOfPrimeNum) fout << " [+]";
		fout << endl;
	}

	fout << "\nPrime Count with Bonus\n";
	for (int i = 0; i <= 6;i++)
	{
		sprintf(buff, "%d] %d", i, sttPrimeb[i]);
		fout << buff;
		if (i == endLotto.numOfPrimeNum + isPrime(endLotto.bonus)) fout << " [+]";
		fout << endl;
	}

	fout << "\nEven vs Odd Count\n";
	for (int i = 0; i <= 6;i++)
	{
		sprintf(buff, "%d vs %d ] %d", i, 6 - i, sttEven[i]);
		fout << buff;
		if (i == (6 - endLotto.numOfOddNum)) fout << " [+]";
		fout << endl;
	}

	fout << "\nEven vs Odd Count with Bonus\n";
	for (int i = 0; i <= 7;i++)
	{
		sprintf(buff, "%d vs %d ] %d", i, 7 - i, sttEvenb[i]);
		fout << buff;
		if (i == (7 - endLotto.numOfOddNum - (endLotto.bonus & 1))) fout << " [+]";
		fout << endl;
	}

	int chk;
	chk = 0; for (int i = 0; i < 7;i++) chk += sttPrime[i];
	if (chk != total) printf("chk Number is not Prime Number %d != %d\n", chk, total);
	chk = 0; for (int i = 0; i < 8;i++) chk += sttPrimeb[i];
	if (chk != total) printf("chk Number is not Prime Number with Bonus %d != %d\n", chk, total);
	chk = 0; for (int i = 0; i < 8;i++) chk += sttEven[i];
	if (chk != total) printf("chk Number is not Even vs Odd %d != %d\n", chk, total);
	chk = 0; for (int i = 0; i < 8;i++) chk += sttEvenb[i];
	if (chk != total) printf("chk Number is not Even vs Odd with Bonus %d != %d\n", chk, total);

	fout << "\n*** 해당 월/일이 나오는 경우 ***\n";
	fout << ">> 월이 나온 경우 \n";

	int sum = 0;
	for (int k = 1; k <= 12;k++)
	{
		sprintf(buff, "%3d ", k);
		fout << buff;
	}
	fout << "total"<< endl;
	for (int k = 1; k <= 12;k++)
	{
		sprintf(buff, "%3d ", monthCount[k]);
		fout << buff;
		sum += monthCount[k];
	}
	sprintf(buff, "%3d ", sum);
	fout << buff;
	fout << endl;
	int bsum = 0;
	for (int k = 1; k <= 12;k++)
	{
		sprintf(buff, "%3d ", monthCountb[k]);
		fout << buff;
		bsum += monthCountb[k];
	}
	sprintf(buff, "%3d ", bsum);
	fout << buff;
	fout << "bonus"<< endl;

	for (int k = 1; k <= 12;k++)
	{
		sprintf(buff, "%3d ", monthCount[k] + monthCountb[k]);
		fout << buff;
	}
	sprintf(buff, "%3d ", sum + bsum);
	fout << buff;
	fout << "total" << endl;
	fout << endl;

	sum = 0;
	for (int k = 1; k <= 12;k++)
	{
		sprintf(buff, "%3d ", nmonthCount[k]);
		fout << buff;
		sum += nmonthCount[k];
	}
	sprintf(buff, "%3d ", sum);
	fout << buff;
	fout << endl;
	bsum = 0;
	for (int k = 1; k <= 12;k++)
	{
		sprintf(buff, "%3d ", nmonthCountb[k]);
		fout << buff;
		bsum += nmonthCountb[k];
	}
	sprintf(buff, "%3d ", bsum);
	fout << buff;
	fout << "bonus" << endl;

	for (int k = 1; k <= 12;k++)
	{
		sprintf(buff, "%3d ", nmonthCount[k] + nmonthCountb[k]);
		fout << buff;
	}
	sprintf(buff, "%3d ", sum + bsum);
	fout << buff;
	fout << "total" << endl;
	fout << endl;
	fout << endl;

	fout << ">> 일이 나온 경우 \n";

	sum = 0;
	for (int k = 1; k <= 31;k++)
	{
		sprintf(buff, "%3d ", k);
		fout << buff;
	}
	fout << "total" << endl;
	for (int k = 1; k <= 31;k++)
	{
		sprintf(buff, "%3d ", dayCount[k]);
		fout << buff;
		sum += dayCount[k];
	}
	sprintf(buff, "%3d ", sum);
	fout << buff;
	fout << endl;
	bsum = 0;
	for (int k = 1; k <= 31;k++)
	{
		sprintf(buff, "%3d ", dayCountb[k]);
		fout << buff;
		bsum += dayCountb[k];
	}
	sprintf(buff, "%3d ", bsum);
	fout << buff;
	fout << "bonus" << endl;

	for (int k = 1; k <= 31;k++)
	{
		sprintf(buff, "%3d ", dayCount[k] + dayCountb[k]);
		fout << buff;
	}
	sprintf(buff, "%3d ", sum + bsum);
	fout << buff;
	fout << "total" << endl;
	fout << endl;

	sum = 0;
	for (int k = 1; k <= 31;k++)
	{
		sprintf(buff, "%3d ", ndayCount[k]);
		fout << buff;
		sum += ndayCount[k];
	}
	sprintf(buff, "%3d ", sum);
	fout << buff;
	fout << endl;
	bsum = 0;
	for (int k = 1; k <= 31;k++)
	{
		sprintf(buff, "%3d ", ndayCountb[k]);
		fout << buff;
		bsum += ndayCountb[k];
	}
	sprintf(buff, "%3d ", bsum);
	fout << buff;
	fout << "bonus" << endl;

	for (int k = 1; k <= 31;k++)
	{
		sprintf(buff, "%3d ", ndayCount[k] + ndayCountb[k]);
		fout << buff;
	}
	sprintf(buff, "%3d ", sum + bsum);
	fout << buff;
	fout << "total" << endl;

	fout << "\n*** Total AC ***\n";
	endLotto.AC = makeAC(endLotto);
	for (int k = 0; k <= 10;k++)
	{
		if (k == endLotto.AC) fout << " [+]";
		else fout << "    ";
	}
	fout << endl;
	for (int k = 0; k <= 10;k++)
	{
		sprintf(buff, "%3d ", k);
		fout << buff;
	}
	fout << endl;
	for (int k = 0; k <= 10;k++)
	{
		sprintf(buff, "%3d ", sttAC[k]);
		fout << buff;
	}
	fout << endl;


	fout << "\n*** Total Rank ***\n";
	sprintf(buff, ">> %d %d %d %d %d\n", endLotto.countOfPastRanks[1], endLotto.countOfPastRanks[2], endLotto.countOfPastRanks[3], endLotto.countOfPastRanks[4], endLotto.countOfPastRanks[5]);
	fout << buff;
	fout << "  ";
	for (int k = 1; k <= 40;k++)
	{
		sprintf(buff, "%3d ", k);
		fout << buff;
	}
	fout << endl;
	for (int i = 1; i <= 5;i++)
	{
		sprintf(buff, "%d ", i);
		fout << buff;
		for (int k = 1; k <= 40;k++)
		{
			if(sttPastRanks[i][k]) sprintf(buff, "%3d ", sttPastRanks[i][k]);
			else sprintf(buff, "    ", sttPastRanks[i][k]);
			fout << buff;
		}
		fout << endl;
	}

	if (sttPastRanks[1][1] != total) printf("chk Rank 1 is not num of win lotto %d %d\n", sttPastRanks[1][1], NumOfWinLotto);

	for (int i = START_NUMBER; i <= END_NUMBER; i++)
	{
		LOTTO& lotto = LottoWinningNumber[i];
		
		for (int k = 0; k < 6; k++) arrLotto[i][lotto.number[k]] = 1;
		for (int k = 0; k < 7; k++) arrLottob[i][lotto.number[k]] = 1;


	}

	//hot, cold, one
	int hotColdOneCount[7][7][7] = { 0 };
	for (int i = START_NUMBER; i <= END_NUMBER; i++)
	{
		if (i <= LIMIT)
		{
			printf("%d <= LIMIT\n", i);
			continue;
		}

		LOTTO& lotto = LottoWinningNumber[i];
		hotColdOneCount[lotto.numOfHot][lotto.numOfCold][lotto.numOfOne]++;			
	}

	fout << "\n *** Hot / Cold / One ***\n";
	
	for (int k1 = 0; k1 <= 6;k1++)
		for (int k2 = 0; k2 <= 6;k2++)
			for (int k3 = 0; k3 <= 6;k3++)
			{
				if ((k1 + k2 + k3) != 6 && hotColdOneCount[k1][k2][k3])
				{
					printf("hot cold one count %d %d %d is error, it is not 6 != %d\n", k1, k2, k3, hotColdOneCount[k1][k2][k3]);
					exit(1);
				}
				
				if ((k1 + k2 + k3) == 6 && hotColdOneCount[k1][k2][k3])
				{
					sprintf(buff, "%d %d %d] %d", k1, k2, k3, hotColdOneCount[k1][k2][k3]);
					fout << buff;

					if (endLotto.numOfHot == k1 && endLotto.numOfCold == k2 && endLotto.numOfOne == k3) fout << "  [+]";
					fout << endl;
				}
			}
	fout << endl;
	
	int consecutiveNumber[10] = { 0 };
	for (int i = START_NUMBER; i <= END_NUMBER; i++)
	{
		LOTTO& lotto = LottoWinningNumber[i];

		if (checkConsecutive6(lotto))
		{
			consecutiveNumber[6]++;continue;
		}

		if (checkConsecutive5(lotto))
		{
			consecutiveNumber[5]++;continue;
		}

		if (checkConsecutive4(lotto))
		{
			consecutiveNumber[4]++;continue;
		}

		if (checkConsecutive3(lotto))
		{
			consecutiveNumber[3]++;continue;
		}

		if (checkConsecutive2_2(lotto))
		{
			consecutiveNumber[7]++;continue;
		}

		if (checkConsecutive2(lotto))
		{
			consecutiveNumber[2]++;continue;
		}

		consecutiveNumber[1]++;
	}

	fout << "\n*** 연속번호 횟수 ***\n";
	for (int i = 1; i <= 6;i++)
	{
		int t = i;
		if (t == 1) t = 0;
		sprintf(buff, "%3d ", t);
		fout << buff;
	}
	fout << " 2_2" << endl;
	for (int i = 1; i <= 7;i++)
	{
		sprintf(buff, "%3d ", consecutiveNumber[i]);
		fout << buff;
	}
	fout << endl;

	int jumpNumber[45] = { 0 };
	int jumpNumberTotal[45] = { 0 };
	for (int i = START_NUMBER; i <= END_NUMBER; i++)
	{
		LOTTO& lotto = LottoWinningNumber[i];

		int flag = 0;
		for (int k = 2; k <= 40;k++)
		{
			int cnt = countJumpNumber(lotto, k);
			
			if(cnt) jumpNumber[k]++;
			jumpNumberTotal[k] += cnt;
			if (k == 2 && cnt) flag = 1;
		}

		if (flag == 0) jumpNumber[1]++;
	}

	fout << "\n*** jumpNumber 횟수, 0 : jump2가 없는 경우 ***\n";
	for (int i = 1; i <= 40;i++)
	{
		int t = i;
		if (t == 1) t = 0;
		sprintf(buff, "%3d ", t);
		fout << buff;
	}
	fout << endl;
	for (int i = 1; i <= 40;i++)
	{
		sprintf(buff, "%3d ", jumpNumber[i]);
		fout << buff;
	}
	fout << endl;

	for (int i = 1; i <= 40;i++)
	{
		sprintf(buff, "%3d ", jumpNumberTotal[i]);
		fout << buff;
	}
	fout << endl;
	//이월 된게 하나도 없는 경우
	//이월 된게 1개인 경우 -> show
	//이월 된게 2개인 경우 -> show pair 
	//이월 된게 3 ~ 5개인 경우
	fout << "\n *** Case : NextNumber 0 ~ 6 ***\n";
	int nextNumberCount[10] = { 0 };
	int nextNumber[50] = { 0 };
	int nextNumberPair[45][50] = { 0 };
	for (int i = START_NUMBER; i <= END_NUMBER - 1; i++)
	{
		LOTTO& lotto = LottoWinningNumber[i];
		LOTTO& next = LottoWinningNumber[i + 1];

		int cnt = 0;
		for (int k = 0; k < 6;k++)
		{
			cnt += arrLotto[i + 1][lotto.number[k]];
			nextNumber[lotto.number[k]] += arrLotto[i + 1][lotto.number[k]];
		}

		for (int k1 = 0; k1 < 5;k1++)
		{
			for (int k2 = k1 + 1;k2 < 6;k2++)
				nextNumberPair[lotto.number[k1]][lotto.number[k2]] += arrLotto[i + 1][lotto.number[k1]] && arrLotto[i + 1][lotto.number[k2]];
		}

		nextNumberCount[cnt]++;
	}

	fout << "\n N개 이월된 횟수 >>\n";
	for (int i = 0; i <= 6;i++)
	{
		sprintf(buff, "%3d ", i);
		fout << buff;
	}
	fout << endl;
	for (int i = 0; i <= 6;i++)
	{
		sprintf(buff, "%3d ", nextNumberCount[i]);
		fout << buff;
	}
	fout << endl;
	fout << "\n 번호별 이월된 횟수 >>\n";
	for (int i = 1; i <= 45;i++)
	{
		sprintf(buff, "%2d ", i);
		fout << buff;
	}
	fout << endl;
	for (int i = 1; i <= 45;i++)
	{
		sprintf(buff, "%2d ", nextNumber[i]);
		fout << buff;
	}
	fout << endl;

	fout << "\n 두 번호 이월된 횟수 >>\n";
	for (int k1 = 1; k1 <= 44; k1++)
	{
		for (int k2 = k1 + 1; k2 <= 45;k2++)
		{
			if (nextNumberPair[k1][k2] == 0) continue;
			sprintf(buff, "%2d %2d] ", k1, k2);
			fout << buff;
			sprintf(buff, "%2d\n", nextNumberPair[k1][k2]);
			fout << buff;
		}
	}


	//이월 된게 하나도 없는 경우 보너스
	//이월 된게 1개인 경우 보너스
	//이월 된게 2개인 경우 보너스
	//이월 된게 3 ~ 5개인 경우 보너스
	fout << "\n *** Case : NextNumber 0 ~ 6 with Bonus ***\n";
	int nextNumberCountb[10] = { 0 };
	int nextNumberb[50] = { 0 };
	int nextNumberPairb[45][50] = { 0 };
	for (int i = START_NUMBER; i <= END_NUMBER - 1; i++)
	{
		LOTTO& lotto = LottoWinningNumber[i];
		LOTTO& next = LottoWinningNumber[i + 1];

		int cnt = 0;
		for (int k = 0; k < 7;k++)
		{
			cnt += arrLottob[i + 1][lotto.number[k]];
			nextNumberb[lotto.number[k]] += arrLottob[i + 1][lotto.number[k]];
		}

		for (int k1 = 0; k1 < 5;k1++)
		{
			for (int k2 = k1 + 1;k2 < 6;k2++)
			{
				int t1 = lotto.number[k1];
				int t2 = lotto.number[k2];

				if (t1 > t2)
				{
					int tmp = t1;
					t1 = t2;
					t2 = tmp;
				}
				nextNumberPairb[t1][t2] += arrLottob[i + 1][t1] && arrLottob[i + 1][t2];
			}
		}

		nextNumberCountb[cnt]++;
	}

	fout << "\n N개 이월된 횟수 with bonus >>\n";
	for (int i = 0; i <= 6;i++)
	{
		sprintf(buff, "%3d ", i);
		fout << buff;
	}
	fout << endl;
	for (int i = 0; i <= 6;i++)
	{
		sprintf(buff, "%3d ", nextNumberCountb[i]);
		fout << buff;
	}
	fout << endl;
	fout << "\n 번호별 이월된 횟수 with bonus >>\n";
	for (int i = 1; i <= 45;i++)
	{
		sprintf(buff, "%2d ", i);
		fout << buff;
	}
	fout << endl;
	for (int i = 1; i <= 45;i++)
	{
		sprintf(buff, "%2d ", nextNumberb[i]);
		fout << buff;
	}
	fout << endl;

	fout << "\n 두 번호 이월된 횟수  with bonus >>\n";
	for (int k1 = 1; k1 <= 44; k1++)
	{
		for (int k2 = k1 + 1; k2 <= 45;k2++)
		{
			if (nextNumberPairb[k1][k2] == 0) continue;
			sprintf(buff, "%2d %2d] ", k1, k2);
			fout << buff;
			sprintf(buff, "%2d\n", nextNumberPairb[k1][k2]);
			fout << buff;
		}
	}


	//번호별 이월된 최대 횟수, 횟수별 경우의 수.

	//보너스 번호가 다음 번호에 나오는 경우
	fout << "\n *** Case : Bonus -> RealNumber ***\n";

	int bonusNextReal = 0;
	int bonusNextRealCount[46] = { 0 };
	int bonusNextRealCountx[46] = { 0 };
	int bonus[46] = { 0 };
	for (int i = START_NUMBER; i <= END_NUMBER - 1; i++)
	{
		LOTTO& lotto = LottoWinningNumber[i];
		LOTTO& next = LottoWinningNumber[i + 1];
		bonus[lotto.bonus]++;
		if (arrLotto[i+1][lotto.bonus])
		{
			bonusNextReal++;
			bonusNextRealCount[lotto.bonus]++;
			sprintf(buff, "[bonus -> real %2d] has appeared! %3d -> %3d\n", lotto.bonus, i, i + 1);
			fout << buff;
		}
		else
		{
			bonusNextRealCountx[lotto.bonus]++;
		}
	}

	sprintf(buff, "\nBonus Next Real : %d / %d\n", bonusNextReal, total);
	fout << buff;

	for (int i = 1; i <= 45;i++)
	{
		sprintf(buff, "%2d ", i);
		fout << buff;
	}
	fout << endl;
	for (int i = 1; i <= 45;i++)
	{
		sprintf(buff, "%2d ", bonusNextRealCount[i]);
		fout << buff;
	}
	fout << "bonus -> real" << endl;
	for (int i = 1; i <= 45;i++)
	{
		sprintf(buff, "%2d ", bonusNextRealCountx[i]);
		fout << buff;
	}
	fout << "bonus -> x" << endl;
	for (int i = 1; i <= 45;i++)
	{
		sprintf(buff, "%2d ", bonus[i]);
		fout << buff;
	}
	fout << "bonus total" << endl;


	//보너스 번호가 다음 보너스에 나오는 경우
	fout << "\n *** Case : Bonus -> Bonus ***\n";
	
	int bonusNextBonus = 0;
	int bonusNextBonusCount[46] = { 0 };
	for (int i = START_NUMBER; i <= END_NUMBER - 1; i++)
	{
		LOTTO& lotto = LottoWinningNumber[i];
		LOTTO& next = LottoWinningNumber[i + 1];

		if (lotto.bonus == next.bonus)
		{
			bonusNextBonus++;
			bonusNextBonusCount[lotto.bonus]++;
			sprintf(buff, "[bonus -> bonus %2d] has appeared! %3d -> %3d\n", lotto.bonus, i, i + 1);
			fout << buff;
		}
	}

	sprintf(buff, "\nBonus Next Bonus : %d / %d\n", bonusNextBonus, total);
	fout << buff;
	
	for (int i = 1; i <= 45;i++)
	{
		sprintf(buff, "%2d ", i);
		fout << buff;
	}
	fout << endl;
	for (int i = 1; i <= 45;i++)
	{
		sprintf(buff, "%2d ", bonusNextBonusCount[i]);
		fout << buff;
	}
	fout << endl;

	fout.close();

	//1이 나온다음에 나올 숫자들은?
}

void statistics()
{
	showWinningNumbers();

	//연속된 2자리 번호
	findAllConsecutiveNumbers();
	showConsecutiveNumbers();

	//1칸 점프 번호
	findAllJumpNumbers();
	showJumpNumbers();

	for (int i = LIMIT + 1; i <= NumOfWinLotto + 1;i++) findHotColdOne(i);

	showStatisticsWinningNumber();
	showAllStatistics();
}


//보너스 포함

//역대 프라임 넘버 나온 횟수 1 2 3 4 5 6 7
//역대 1~45 번호별 횟수
//역대 2개 ~ 5개 조합 횟수
//역대 홀 vs 짝 횟수
//