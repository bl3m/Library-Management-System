#include "Book.h"
#include <string>
#include <ctime>
#include <cmath>


using namespace std;
class Copy :
	public Book
{
private:
	int ID;
	string borrower;
public:
	string reader;
	int initialTime = 30;
	//clock_t start = clock();
	void reserve();
	void startTimer();
	int timeLeft(clock_t start);
	bool timeExpired(clock_t start, Copy copy);
	Copy();
};

