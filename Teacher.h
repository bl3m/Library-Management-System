#pragma once
#include "Reader.h"
class Teacher :
	public Reader
{
private:
	User login;
public:
	Teacher();
	int maxCopies(int maxCopies);
	void getLogin(int numBooks); 
};

