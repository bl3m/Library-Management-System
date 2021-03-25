#pragma once
#include "User.h"
#include <string>
class Reader :
	public User
{

public:
	Reader();
	int maxCopies;
	int penalty;
	string type;
	void getLogin(string type, int numBooks);
	void borrowBooks(int maxCopies, int numBooks, string type);
	void returnBooks(int maxCopies, int numBooks, string type);
	void reserveBooks(int maxCopies);
	void cancelReservation(int maxCopies);
	
};

