#include <string>
#pragma once
using namespace std;
class User{
protected:
	string username;
	string password;
	string type;
public:
	User();
	~User();
	User(string& username_, string& password_, string& type_);
	void changePassword(string& type, int& numBooks);
	void searchBooks(string& type, int& numBooks);
	void login();
	void myInfo(string& type, int& numBooks);
	void logout(string& user, string& pass);
	string getPass(const char *prompt, bool show_asterisk=true);
};
