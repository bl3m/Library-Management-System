#include "Student.h"
#include <string>
#include <iostream>

using namespace std;

Student::Student(){

}

void Student::getLogin(int numBooks){
	string user, pass;
	string type = "student";
	int maxCopies = 5;
	cout << "Welcome back, Student" << endl;
	cout << "Please choose:" << endl;
	cout << "         1 -- Search Books" << endl;
	cout << "         2 -- Borrow Books" << endl;
	cout << "         3 -- Return Books" << endl;
	cout << "         4 -- Reserve Books" << endl;
	cout << "         5 -- Cancel Reservation" << endl;
	cout << "         6 -- My Information" << endl;
	cout << "         7 -- Change Password" << endl;
	cout << "         0 -- Log Out" << endl;
	int n;
	cin >> n;
	switch (n) {
	case 1:
		searchBooks(type, numBooks);
		break;
	case 2:
		borrowBooks(maxCopies, numBooks, type);
		break;
	case 3:
		returnBooks(maxCopies, numBooks, type);
		break;
	case 4:
		//reserveBooks();
		break;
	case 5:
		//cancelReservation();
		break;
	case 6:
		smyInfo(type, numBooks);
		break;
	case 7:
		changePassword(type, numBooks);
		break;
	case 0:
		logout(user, pass);
		break;
	}
}
 
void maxCopies() {

}