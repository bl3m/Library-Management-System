#pragma once
#include "User.h"
#include <string>
class Reader :
	public User
{
protected:
	int numBooks,maxBooks;
public:
	Reader();
	~Reader();
	Reader(string& user_, string& pass_, string& type_, int numBooks_, int maxBooks_);
	int penalty;
	void getLogin();
	void borrowBooks();
	void returnBooks();
	void reserveBooks();
	void cancelReservation();
	
};

