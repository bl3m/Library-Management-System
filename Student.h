#pragma once
#include "Reader.h"
class Student :
	public Reader
{
private:
	User login;
public:
	Student();
	void getLogin(int numBooks);
};

