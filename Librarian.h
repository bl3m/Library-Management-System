#pragma once
#include "User.h"
class Librarian :
	public User
{

public:
	Librarian();
	~Librarian();
	Librarian(string& user_, string& pass_, string type_);
	void getLogin();
	void searchUser();
	void addUser();
	void deleteUser();
	void addBooks();
	void deleteBooks();
};

