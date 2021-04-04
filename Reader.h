#pragma once
#include "User.h"
#include <string>
class Reader :
	public User
{
protected:
	string type;
	int numBooks,maxBooks;
public:
	Reader();
	Reader(string& user_, string& pass_, string& type_, int numBooks_, int maxBooks_);
	int penalty;
	void getLogin(string type);
	void borrowBooks(int maxCopies, int numBooks, string type);
	void returnBooks(int maxCopies, int numBooks, string type);
	void reserveBooks(int maxCopies);
	void cancelReservation(int maxCopies);
	
};

