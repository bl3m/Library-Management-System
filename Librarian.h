#pragma once
#include "User.h"
class Librarian :
	public User
{
private:
	User login;
public:
	Librarian();
	void getLogin();
	void searchUser();
	void addUser();
	void deleteUser();
	void addBooks();
	void deleteBooks();
};

