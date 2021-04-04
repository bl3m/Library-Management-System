#pragma once
#include "Reader.h"
class Student :
	public Reader
{
private:
	User login;
public:
	Student();
	Student(string user_, string pass_, int numBooks);
	void getLogin(int numBooks);
};

