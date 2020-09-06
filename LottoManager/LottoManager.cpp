#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <map>
#include <iostream>
#include <fstream>
#include <vector>

#include "LottoManager.h"
#include "StatisticsManager.h"

using namespace std;

int NumOfWinLotto;
LOTTO LottoWinningNumber[10000];
map<ull, bool> MapLottoWinningNumber;

int NumOfSuckLotto;
LOTTO MySuckNumber[10000];
map<ull, bool> MapMySuckNumber;

LOTTO AllLottoNumber[NUM_OF_ALLCASE + 10];

int NumOfHotNumber;
int HotNumber[50];
int underHotNumber = -100;
int upperHotNumber = 100;

int NumOfColdNumber;
int ColdNumber[50];
int underColdNumber = -100;
int upperColdNumber = 100;

int NumOfOneNumber;
int OneNumber[50];
int underOneNumber = -100;
int upperOneNumber = 100;

int underAC = -100;
int upperAC = 100;

int underColor = -100;
int upperColor = 100;

int underNext = -100;
int upperNext = 100;

int mustNumber[50];
int mustSize;

int mustColor[10];
int mustColorSize;

int underPrimeNumber = -100;
int upperPrimeNumber = 100;
int underEvenNumber = -100;
int upperEvenNumber = 100;

int underRank2 = -100;
int upperRank2 = 100;

int underRank3 = -100;
int upperRank3 = 100;

int underRank4 = -100;
int upperRank4 = 100;

int SHUFFLE;
extern HotColdOne hotColdOne[2000];

extern int NumOfHotNumber;
extern int HotNumber[50];

extern int NumOfColdNumber;
extern int ColdNumber[50];


extern int NumOfOneNumber;
extern int OneNumber[50];

int SET_JUMP = -1;
int SET_CON2 = -1;
int SET_CON22 = -1;
int SET_CON3 = -1;

extern int colorBoard[47];


void setMustNumber(int* number, int size)
{
	mustSize = size;
	for (int i = 0; i < size;i++)
		mustNumber[number[i]] = 1;
}

bool isMustNumber(LOTTO& Lotto)
{
	int cnt = 0;
	for (int i = 0; i < 6;i++)
		if (mustNumber[Lotto.number[i]]) cnt++;

	if (cnt == mustSize) return true;
	return false;
}

int wrongNumber[50];
int wrongSize;
void setWrongNumber(int* number, int size)
{
	wrongSize = size;
	for (int i = 0; i < size;i++) wrongNumber[number[i]] = 1;
	printf(">> wrong number\n");
	
	int cnt = 0;
	for (int i = 1; i <= 45; i++)
		if (wrongNumber[i]) printf("%d ", i), cnt++;
	putchar('\n');
	printf(">> num of w : %d\n", cnt);
}

bool isWrongNumber(LOTTO& Lotto)
{
	int cnt = 0;
	for (int i = 0; i < 6;i++)
		if (wrongNumber[Lotto.number[i]]) return true;

	return false;
}

void setPrimeNumber(int under, int upper)
{
	underPrimeNumber = under;
	upperPrimeNumber = upper;
}

void setMustEvenNumber(int under, int upper)
{
	underEvenNumber = under;
	upperEvenNumber = upper;
}

void setPastRank2(int under, int upper)
{
	underRank2 = under;
	upperRank2 = upper;
}

void setPastRank3(int under, int upper)
{
	underRank3 = under;
	upperRank3 = upper;
}

void setPastRank4(int under, int upper)
{
	underRank4 = under;
	upperRank4 = upper;
}

void setHotNumber(int under, int upper)
{
	underHotNumber = under;
	upperHotNumber = upper;
}

void setColdNumber(int under, int upper)
{
	underColdNumber = under;
	upperColdNumber = upper;
}

void setOneNumber(int under, int upper)
{
	underOneNumber = under;
	upperOneNumber = upper;
}

void setACNumber(int under, int upper)
{
	underAC = under;
	upperAC = upper;
}

void setColor(int under, int upper)
{
	underColor = under;
	upperColor = upper;
}

void setNextNumber(int under, int upper)
{
	underNext = under;
	upperNext = upper;
}

void showLottoNumber(int index)
{
	printf("%4d] ", index + 1);
	for (int k = 0; k < 7;k++)
		printf("%2d ", LottoWinningNumber[index].number[k]);
	putchar('\n');
}

void showLottoNumber(LOTTO& Lotto)
{
	for (int k = 0; k < 7;k++)
		printf("%2d ", Lotto.number[k]);
	putchar('\n');
}

bool isLottoWinningNumber(LOTTO& Lotto)
{
	return MapLottoWinningNumber.count(Lotto.key);
}

bool isMySuckNumber(LOTTO& Lotto)
{
	return MapMySuckNumber.count(Lotto.key);
}

ull makeKey(LOTTO& Lotto)
{
	return Lotto.number[0] * 10000000000ull + Lotto.number[1] * 100000000ull + Lotto.number[2] * 1000000ull 
		+ Lotto.number[3] * 10000ull + Lotto.number[4] * 100ull + Lotto.number[5];
}

ull makeBitNumber(LOTTO& Lotto)
{
	return (1ull << Lotto.number[0]) | (1ull << Lotto.number[1]) | (1ull << Lotto.number[2]) | (1ull << Lotto.number[3]) | (1ull << Lotto.number[4]) | (1ull << Lotto.number[5]);
}

int makeSum(LOTTO& Lotto)
{
	return Lotto.number[0] + Lotto.number[1] + Lotto.number[2] + Lotto.number[3] + Lotto.number[4] + Lotto.number[5];
}

int countOddNumber(LOTTO& Lotto)
{
	return (Lotto.number[0] & 1) + (Lotto.number[1] & 1) + (Lotto.number[2] & 1) + (Lotto.number[3] & 1) + (Lotto.number[4] & 1) + (Lotto.number[5] & 1);
}

int countPrimeNumber(LOTTO& Lotto)
{
	int i;
	int ret = 0;
	
	for (i = 0; i < 6;i++) ret += isPrime(Lotto.number[i]);
	return ret;
}

void makeStatisticsInfo(LOTTO& Lotto)
{
	Lotto.key = makeKey(Lotto);
	Lotto.bitNumber = makeBitNumber(Lotto);
	Lotto.sum = makeSum(Lotto);
	Lotto.numOfOddNum = countOddNumber(Lotto);
	Lotto.numOfPrimeNum = countPrimeNumber(Lotto);
}

void outputPickNumber(int cnt)
{
	ofstream fout;
	fout.open("PickNumbers.txt");

	fout << "# of My PickNumber : ";
	fout << cnt << endl;
	
	vector<int>& vhot = hotColdOne[NumOfWinLotto + 1].hotNum;
	vector<int>& vcold = hotColdOne[NumOfWinLotto + 1].coldNum;
	vector<int>& vone = hotColdOne[NumOfWinLotto + 1].oneNum;

	for (int i = 0; i < vhot.size(); i++) printf("%d ", vhot[i]); putchar('\n');
	for (int i = 1; i <= 45; i++) if (HotNumber[i]) printf("%d ", i); putchar('\n');
	for (int i = 0; i < vcold.size(); i++) printf("%d ", vcold[i]); putchar('\n');
	for (int i = 1; i <= 45; i++) if (ColdNumber[i]) printf("%d ", i); putchar('\n');
	for (int i = 0; i < vone.size(); i++) printf("%d ", vone[i]); putchar('\n');
	for (int i = 1; i <= 45; i++) if (OneNumber[i]) printf("%d ", i); putchar('\n');

	for (int i = 0; i < cnt;i++)
	{
		LOTTO& lotto = AllLottoNumber[i];

		int hot, cold, one;
		hot = cold = one = 0;
		int chkhot[50] = { 0 };
		int chkcold[50] = { 0 };
		int chkone[50] = { 0 };

		for (int i = 0; i < vhot.size(); i++) chkhot[vhot[i]]++;
		for (int i = 0; i < vcold.size(); i++) chkcold[vcold[i]]++;
		for (int i = 0; i < vone.size(); i++) chkone[vone[i]]++;

		char buf[10];
		sprintf(buf, "%4d] ", i + 1);
		fout << buf;
		for (int k = 0; k < 6;k++)
		{
			bool hotflag = chkhot[lotto.number[k]] && (k != 6);
			bool coldflag = chkcold[lotto.number[k]] && (k != 6);
			bool oneflag = chkone[lotto.number[k]] && (k != 6);

			if (hotflag) ++hot, fout << "[";
			if (coldflag) ++cold;
			if (oneflag) ++one, fout << "(";


			fout << lotto.number[k];
			if (hotflag) fout << "]";
			if (oneflag) fout << ")";

			fout << " ";
		}
		fout << endl;

		//makePastLottoResult(lotto);

		fout << "      [ ";
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

		sprintf(evenoddprime, "[ %d / %d / %d ] ", lotto.hot, lotto.cold, lotto.one);

		fout << evenoddprime;

		lotto.numOfOddNum = odd;
		lotto.numOfPrimeNum = prime;
		lotto.numOfHot = hot;
		lotto.numOfCold = cold;
		lotto.numOfOne = one;

		sprintf(evenoddprime, "[%3d] ", makeSum(lotto));
		fout << evenoddprime;

		sprintf(evenoddprime, "[Clr: %d] ", lotto.countOfColor);
		fout << evenoddprime;

		lotto.AC = makeAC(lotto);
		sprintf(evenoddprime, "[AC: %2d] ", lotto.AC);
		fout << evenoddprime;


		fout << endl;
		fout << endl;
	}
	
	fout << endl;
	for (int i = 0; i < cnt;i++)
	{
		LOTTO& lotto = AllLottoNumber[i];

		char buf[10];
		sprintf(buf, "%4d] ", i + 1);
		fout << buf;

		for (int k = 0; k < 6;k++)
		{
			fout << lotto.number[k];
			fout << " ";
		}
		fout << endl;
	}
	

	fout.close();
}

void makeHotColdOne(LOTTO& Lotto)
{
	int hot, cold, one;

	hot = cold = one = 0;
	
	for (int k = 0; k < 6;k++)
	{
		if (HotNumber[Lotto.number[k]]) hot++;
		if (ColdNumber[Lotto.number[k]]) cold++;
		if (OneNumber[Lotto.number[k]]) one++;
	}


	Lotto.hot = hot;
	Lotto.cold = cold;
	Lotto.one = one;
}

int countNext(LOTTO& end, LOTTO& lotto)
{
	int cnt = 0;
	int check[46] = { 0 };

	for (int k = 0; k < 6;k++) check[end.number[k]] = 1;
	for (int k = 0; k < 6;k++) cnt += check[lotto.number[k]];
	
	return cnt;
}

int checkJumpNumber(LOTTO& lotto)
{
	for (int k = 0; k < 5;k++)
		if (lotto.number[k + 1] - lotto.number[k] == 2) return true;

	return false;
}

void set_Jump_Cons2_Cons22_Cons3(int jump, int cons, int cons22, int cons3)
{
	SET_JUMP = jump;
	SET_CON2 = cons;
	SET_CON22 = cons22;
	SET_CON3 = cons3;
}

void setMustColor(int* color, int size)
{
	mustColorSize = size;
	for (int i = 0; i < size;i++)
		mustColor[color[i]] = 1;
}


int isMustColor(LOTTO& lotto)
{
	int checkBoard[10] = { 0 };

	int cnt = 0;
	for (int k = 0; k < 6;k++) checkBoard[colorBoard[lotto.number[k]]] = 1;
	for (int k = 1; k <= 5;k++) cnt += checkBoard[k] && mustColor[k];

	if (cnt == mustColorSize) return true;
	return false;
}

bool Filter(LOTTO& Lotto)
{
	for(int i = 1; i<=45;i++)
		if (wrongNumber[i] && mustNumber[i]) 
		{
			printf("wrong and must number is same");
			exit(1);
		}

	for (int i = 1; i <= 45;i++)
		if ((HotNumber[i] + ColdNumber[i] + OneNumber[i]) != 1)
		{
			printf("hot cold one is error, check [%d]\n", i);
			exit(1);
		}



	if (isWrongNumber(Lotto)) return true;
	if (isMustNumber(Lotto) == false) return true;

	int cntPrime = countPrimeNumber(Lotto);
	if (!(underPrimeNumber <= cntPrime && cntPrime <= upperPrimeNumber)) return true;

	int cntEven = 6 - countOddNumber(Lotto);
	if (!(underEvenNumber <= cntEven && cntEven <= upperEvenNumber)) return true;
	if (checkConsecutive6(Lotto)) return true;  
	if (checkConsecutive5(Lotto)) return true;
	if (checkConsecutive4(Lotto)) return true;

	if (SET_CON3 == NO_CARE);
	else if (SET_CON3 == NEED && checkConsecutive3(Lotto) == false) return true;
	else if (SET_CON3 == DELETE && checkConsecutive3(Lotto) == true) return true;

	if (SET_JUMP == NO_CARE);
	else if (SET_JUMP == NEED && checkJumpNumber(Lotto) == false) return true;
	else if (SET_JUMP == DELETE && checkJumpNumber(Lotto) == true) return true;

	if (SET_CON2 == NO_CARE);
	else if (SET_CON2 == NEED && checkConsecutive2(Lotto) == false) return true;
	else if (SET_CON2 == DELETE && checkConsecutive2(Lotto) == true) return true;

	if (SET_CON22 == NO_CARE);
	else if (SET_CON22 == NEED && checkConsecutive2_2(Lotto) == false) return true;
	else if (SET_CON22 == DELETE && checkConsecutive2_2(Lotto) == true) return true;

	


	if (isMustColor(Lotto) == false) return true;

	if (isLottoWinningNumber(Lotto)) return true;
	if (isMySuckNumber(Lotto)) return true;



	if (checkDiff(Lotto, 2)) return true;
	if (checkDiff(Lotto, 3)) return true;
	if (checkDiff(Lotto, 4)) return true;
	if (checkDiff(Lotto, 5)) return true;
	if (checkDiff(Lotto, 6)) return true;
	if (checkDiff(Lotto, 7)) return true;
	if (checkDiff(Lotto, 8)) return true;

	makePastLottoResult(Lotto);
	if (!(underRank2 <= Lotto.countOfPastRanks[2] && Lotto.countOfPastRanks[2] <= upperRank2)) return true;
	if (!(underRank3 <= Lotto.countOfPastRanks[3] && Lotto.countOfPastRanks[3] <= upperRank3)) return true;
	if (!(underRank4 <= Lotto.countOfPastRanks[4] && Lotto.countOfPastRanks[4] <= upperRank4)) return true;

	makeHotColdOne(Lotto);

	if (!(underHotNumber <= Lotto.hot && Lotto.hot <= upperHotNumber))     return true;
	if (!(underColdNumber <= Lotto.cold && Lotto.cold <= upperColdNumber)) return true;
	if (!(underOneNumber <= Lotto.one && Lotto.one <= upperOneNumber))     return true;

	countColor(Lotto);
	if (!(underColor <= Lotto.countOfColor && Lotto.countOfColor <= upperColor)) return true;

	Lotto.AC = makeAC(Lotto);
	if (!(underAC <= Lotto.AC && Lotto.AC <= upperAC))     return true;

	LOTTO& endLotto = LottoWinningNumber[NumOfWinLotto];
	int cntNext = countNext(endLotto, Lotto);
	if (!(underNext <= cntNext && cntNext <= upperNext)) return true;

	return false;
}

void shuffle(int cnt)
{
	for (int i = 0; i < cnt;i++)
	{
		int a = random() % cnt;
		int b = random() % cnt;

		LOTTO tmp = AllLottoNumber[a];
		AllLottoNumber[a] = AllLottoNumber[b];
		AllLottoNumber[b] = tmp;
	}
}

void getAllNumber()
{
	int a, b, c, d, e, f;

	int cnt = 0;
	int testCnt = 0;
	for (a = 1; a <= 40;a++)
		for (b = a + 1; b <= 41;b++)
			for (c = b + 1; c <= 42;c++)
				for (d = c + 1; d <= 43;d++)
					for (e = d + 1; e <= 44;e++)
						for (f = e + 1; f <= 45;f++)
						{
							
							AllLottoNumber[cnt].number[0] = a;
							AllLottoNumber[cnt].number[1] = b;
							AllLottoNumber[cnt].number[2] = c;
							AllLottoNumber[cnt].number[3] = d;
							AllLottoNumber[cnt].number[4] = e;
							AllLottoNumber[cnt].number[5] = f;
							AllLottoNumber[cnt].key = makeKey(AllLottoNumber[cnt]);
							testCnt++;
							//printf("%d\n", testCnt);
							if (Filter(AllLottoNumber[cnt]))
							{
								memset(&AllLottoNumber[cnt], 0x00, sizeof(LOTTO));
								continue;
							}

							cnt++;
						}

	if (testCnt != NUM_OF_ALLCASE) 
	{
		printf("testCnt is not allcase\n");
		exit(1);
	}

	printf("hello! %d / %d\n", cnt, testCnt);
	if(SHUFFLE) shuffle(cnt);
	outputPickNumber(cnt);
	//for (int i = 0; i < cnt;i++) showLottoNumber(AllLottoNumber[i]);
	//printf("%d %d %d\n", cnt, NUM_OF_ALLCASE, testCnt);
}


void deleteNumber()
{
	//총 개수에서 몇개가 빠지는지 세기 [삭제 수 / 전체 수에서 삭제 수]
	//delete flag로 관리 후 마지막에 한꺼번에 삭제.

	//연속된 2 ~ 6자리 수 삭제
	//등차수열 삭제 차수 2 ~ 8 삭제
	//짝수가 6개인 경우
	//짝수가 5개인 경우
	//짝수가 4개인 경우
	//짝수가 3개인 경우
	//짝수가 2개인 경우
	//짝수가 1개인 경우
	//짝수가 0개인 경우
	//이미 로또 번호인 경우
	//SuckNumber 삭제
	//모두 소수인 경우 삭제

	//
	
}

bool checkConsecutive6(LOTTO& Lotto)
{
	if (Lotto.number[5] - Lotto.number[0] == 5) return true;
	return false;
}

bool checkConsecutive5(LOTTO& Lotto)
{
	if (Lotto.number[4] - Lotto.number[0] == 4
		|| Lotto.number[5] - Lotto.number[1] == 4) return true;
	return false;
}

bool checkConsecutive4(LOTTO& Lotto)
{
	if (Lotto.number[3] - Lotto.number[0] == 3
		|| Lotto.number[4] - Lotto.number[1] == 3
		|| Lotto.number[5] - Lotto.number[2] == 3) return true;
	return false;
}

bool checkConsecutive3(LOTTO& Lotto)
{
	if (Lotto.number[2] - Lotto.number[0] == 2
		|| Lotto.number[3] - Lotto.number[1] == 2
		|| Lotto.number[4] - Lotto.number[2] == 2
		|| Lotto.number[5] - Lotto.number[3] == 2) return true;
	return false;
}

bool checkConsecutive2(LOTTO& Lotto)
{
	if (Lotto.number[1] - Lotto.number[0] == 1
		|| Lotto.number[2] - Lotto.number[1] == 1
		|| Lotto.number[3] - Lotto.number[2] == 1
		|| Lotto.number[4] - Lotto.number[3] == 1
		|| Lotto.number[5] - Lotto.number[4] == 1) return true;
	return false;
}

bool checkConsecutive2_2(LOTTO& Lotto)
{
	if(
		((Lotto.number[3] - Lotto.number[2] + Lotto.number[1] - Lotto.number[0]) == 2)
		|| ((Lotto.number[4] - Lotto.number[3] + Lotto.number[1] - Lotto.number[0]) == 2)
		|| ((Lotto.number[5] - Lotto.number[4] + Lotto.number[1] - Lotto.number[0]) == 2)
		|| ((Lotto.number[4] - Lotto.number[3] + Lotto.number[2] - Lotto.number[1]) == 2)
		|| ((Lotto.number[5] - Lotto.number[4] + Lotto.number[2] - Lotto.number[1]) == 2)
		|| ((Lotto.number[5] - Lotto.number[4] + Lotto.number[3] - Lotto.number[2]) == 2)
		) return true;


	return false;
}


bool checkDiff(LOTTO& Lotto, int diff)
{
	for (int i = 1; i < 6;i++)
		if (Lotto.number[i] - Lotto.number[i - 1] != diff) return false;

	return true;
}

bool checkDifferentialSequence(LOTTO& Lotto)
{
	for (int diff = 2; diff <= 8;diff++)
	{
		if (checkDiff(Lotto, diff)) return true;
	}

	return false;
}



//void printMap()
//{
//	map<ull, bool>::iterator iter;
//	for (iter = m.begin(); iter != m.end(); ++iter)
//		cout << "(" << (*iter).first << "," << (*iter).second << ")" << " ";
//	cout << endl;
//}

