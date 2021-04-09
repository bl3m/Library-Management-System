#include <iostream>
#include "Teacher.h"
#include <fstream>


Teacher::Teacher(){
	
}

void Teacher::getLogin(int numBooks){
	string user, pass, type="teacher";
	int maxCopies = 10;
	cout << "Welcome back, Teacher" << endl;
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
		borrowBooks();
		break;
	case 3:
		returnBooks();
		break;
	case 4:
		//reserveBooks();
		break;
	case 5:
		//cancelReservation();
		break;
	case 6:
		myInfo(type, numBooks);
		break;
	case 7:
		changePassword(type, numBooks);
		break;
	case 0:
		logout(user, pass);
		break;
	}
}

int Teacher::maxCopies(int maxCopies) {
	//int maxCopies = 50;
	return maxCopies;
}