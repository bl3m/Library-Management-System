#include <iostream>
#include <string>
#include <ctime>
#include <fstream>
#include "User.h"

#include "Book.h"
using namespace std;

int main() {
	cout << "----------------------------------------------------------" << endl;
	cout << "-                Welcome to My Library                   -" << endl;
	cout << "----------------------------------------------------------" << endl;
	cout << "Welcome to the Library" << endl<<endl;
	User admin;
	string user, pass;
	admin.login(user, pass); //call login screen
	getchar();
	getchar();
	return 0;
}
