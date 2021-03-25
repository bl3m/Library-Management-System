#include "Copy.h"
#include <iostream>
#include <ctime>
#include <cmath>

Copy::Copy()
{

}

void Copy:: reserve() {

}
void Copy::startTimer()
{
	clock_t start = clock();
	timeLeft(start);
}

int Copy::timeLeft(clock_t start)
{

	clock_t	cur = clock();
	int cur_date = initialTime + int(cur - start) / CLOCKS_PER_SEC;
	return cur_date;
}

bool Copy::timeExpired(clock_t start, Copy copy)
{
	if (copy.timeLeft(start) <= 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

