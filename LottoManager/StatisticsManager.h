#ifndef __STATISTICS_MANAGER__
#define __STATISTICS_MANAGER__

#include "define.h"
#include "LottoManager.h"

unsigned int random(void);

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

#endif

