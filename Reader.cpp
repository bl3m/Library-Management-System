#include "Reader.h"
#include "Student.h"
#include "Teacher.h"
#include <string>
#include <queue>
#include <locale>
#include <iostream>
#include <fstream>
using namespace std;

Reader::Reader(){}

Reader::Reader(string& user_, string& pass_, string& type_, int numBooks_, int maxBooks_) :User{ user_, pass_ },
type(type_), numBooks(numBooks_), maxBooks(maxBooks_) {}

void Reader::getLogin(string type) {
	cout << "Welcome back, "<<getUser()<< endl;
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
	cout << "Selection: " << endl;
	cin >> n;
	switch (n) {
	case 1:
		searchBooks(type, numBooks);
		break;
	case 2:
		borrowBooks(maxBooks, numBooks, type);
		break;
	case 3:
		returnBooks(maxBooks, numBooks, type);
		break;
	case 4:
		reserveBooks(maxBooks);
		break;
	case 5:
		cancelReservation(maxBooks);
		break;
	case 6:
		smyInfo(type, numBooks);
		break;
	case 7:
		changePassword(type, numBooks);
		break;
	case 0:
		logout(username, password);
		break;
	}
}

void Reader::borrowBooks(int maxCopies, int numBooks, string type){
	Teacher teacher;
	Student student;
	string title, author, category, ISBN, borrower, bookTitle, name, type1;
	int currBooks, ID;
	cout << "What book do you want to borrow: " << endl;
	cin >> bookTitle;
	cout << "Enter your username" << endl;
	cin >> name;
	locale loc;
	for (string::size_type i = 0; i<bookTitle.length(); ++i) {
		bookTitle[i] = toupper(bookTitle[i], loc);
	}
	string user, pass;
	int numBooks1, maxCopies1;
	numBooks1 = numBooks;
	maxCopies1 = maxCopies;
	ifstream readerIn;
	readerIn.open("Reader.txt");
	while (!readerIn.eof()) {
		readerIn >> type1 >> user >> pass >> numBooks1 >> maxCopies1;
		if (numBooks1 >= maxCopies1) {
			cout << "Maximum number of copies has been exceeded " << endl;
			if (type == "teacher") {
				teacher.getLogin(numBooks1);
			}
			if (type == "student") {
				student.getLogin(numBooks1);
			}
		}
	}
	ifstream copyIn;
	copyIn.open("Copy.txt");
	while (!copyIn.eof()) {
		copyIn >> ID >> title >> author >> category >> ISBN >> borrower;
		if (bookTitle == title && borrower=="") {
			cout << "Book available" << endl;
			ofstream copyOut;
			copyOut.open("Copy.txt");
			copyOut << ID << " " << title << " " << author << " " << category << " " << ISBN << " " << name;
			cout << "\nBook has been checked out" << endl;
			ifstream readerIn;
			readerIn.open("Reader.txt");
			numBooks = numBooks + 1;
			while (!readerIn.eof()) {
				readerIn >> type1 >> user >> pass >> currBooks >> maxCopies1;
				if (name == user) {
					ofstream readerOut;
					readerOut.open("Reader.txt");
					readerOut << type1 << " " << user << " " << pass << " " << numBooks << " " << maxCopies1;
					readerOut.close();
				}
				else {
					ofstream readerOut;
					readerOut.open("Reader.txt");
					readerOut << type1 << " " << user << " " << pass << " " << currBooks << " " << maxCopies1;
					readerOut.close();
				}
			}
			copyOut.close();
			readerIn.close();
		}
		else {
			cout << "Book has already been taken out/ wrong book" << endl;
			ofstream copyOut;
			copyOut.open("Copy.txt");
			copyOut << ID << " " << title << " " << author << " " << category << " " << ISBN << " " << borrower;
			copyOut.close();
		}
	}
	cout << "End of process" << endl;
	copyIn.close();
	if (type == "teacher") {
		teacher.getLogin(numBooks1);
	}
	if (type == "student") {
		student.getLogin(numBooks1);
	}
}

void Reader::returnBooks(int maxCopies, int numBooks, string type) {
	Teacher teacher;
	Student student;
	string title, author, category, ISBN, borrower, bookTitle, name, type1;
	int currBooks, ID;
	cout << "What book do you want to return: " << endl;
	cin >> bookTitle;
	cout << "Enter your username" << endl;
	cin >> name;
	locale loc;
	for (string::size_type i = 0; i<bookTitle.length(); ++i) {
		bookTitle[i] = toupper(bookTitle[i], loc);
	}
	string user, pass;
	int numBooks1, maxCopies1;
	numBooks1 = numBooks;
	maxCopies1 = maxCopies;
	ifstream copyIn;
	copyIn.open("Copy.txt");
	cout << "Reading data file" << endl;
	while (!copyIn.eof()) {
		copyIn >> ID >> title >> author >> category >> ISBN >> borrower;
		if (bookTitle == title && borrower == name) {
			cout << "Book available to be returned" << endl;
			ofstream copyOut;
			copyOut.open("Copy.txt");
			copyOut << ID << " " << title << " " << author << " " << category << " " << ISBN ;
			cout << "\nBook returned" << endl;
			ifstream readerIn;
			readerIn.open("Reader.txt");
			numBooks = numBooks - 1;
			while (!readerIn.eof()) {
				readerIn >> type1 >> user >> pass >> currBooks >> maxCopies1;
				if (name == user) {
					ofstream readerOut;
					readerOut.open("Reader.txt");
					readerOut << type1 << " " << user << " " << pass << " " << numBooks << " " << maxCopies1;
					readerOut.close();
				}
				else {
					ofstream readerOut;
					readerOut.open("Reader.txt");
					readerOut << type1 << " " << user << " " << pass << " " << currBooks << " " << maxCopies1;
					readerOut.close();
				}
			}
			copyOut.close();
			readerIn.close();
		}
		else {
			ofstream copyOut;
			copyOut.open("Copy.txt");
			copyOut << ID << " " << title << " " << author << " " << category << " " << ISBN << " " << borrower;
			copyOut.close();
		}
	}
	cout << "\nEnd of process" << endl;
	copyIn.close();
	if (type == "teacher") {
		teacher.getLogin(numBooks1);
	}
	if (type == "student") {
		student.getLogin(numBooks1);
	}
}

void Reader::reserveBooks(int maxCopies) {

}

void Reader::cancelReservation(int maxCopies) {

}
