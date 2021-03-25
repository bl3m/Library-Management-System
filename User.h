#include <string>
#pragma once
using namespace std;
class User{
private:
	string username;
	string password;
public:
	User();
	void changePassword(string type, int numBooks);
	void searchBooks(string type, int numBooks);
	void login(string user, string pass);
	void tmyInfo(string type, int numBooks);
	void lmyInfo(string type, int numBooks);
	void smyInfo(string type, int numBooks);
	void logout(string user, string pass);
	string getPass(const char *prompt, bool show_asterisk=true);
};
