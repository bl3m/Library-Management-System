#include "Reader.h"
#include <sstream>
#include <queue>
#include <locale>
#include <iostream>
#include <fstream>

using std::cin;
using std::cout;

Reader::Reader():maxBooks(5), numBooks(0){}

Reader::~Reader(){}

Reader::Reader(string& user_, string& pass_, string& type_, int numBooks_, int maxBooks_) :User{ user_, pass_, type_},
numBooks(numBooks_), maxBooks(maxBooks_) {}

void Reader::getLogin() {
	while (1) {
		cout << "Welcome back, " << this->username << endl;
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
		cout << "Selection: ";
		cin >> n;
		switch (n) {
		case 1:
			searchBooks(this->type, this->numBooks);
			break;
		case 2:
			borrowBooks();
			break;
		case 3:
			returnBooks();
			break;
		case 4:
			reserveBooks();
			break;
		case 5:
			cancelReservation();
			break;
		case 6:
			myInfo(this->type, this->numBooks);
			break;
		case 7:
			changePassword(this->type, this->numBooks);
			break;
		case 0:
			logout(this->username, this->password);
			break;
		}
	}
}

void Reader::borrowBooks(){
	//1). Enter book you want to borrow
	//2). Check if max copies for reader exceeded
	//3). If not, check if copy available
	//4). If copy available, borrow book
		//a).Set due date for book, record borrower name, store in Copy text file
		//b).Increment numBooks for Reader
		//c).
	//5). If copy not available, prompt user to reserve a copy

	string copyEntry, userEntry, bookTitle;
	vector<string> copyAttr, userAttr;
	int id = 0, title = 1, author=2, category=3, ISBN=4, borrower=5, type=0, user=1, pass=2, numBooks=3, maxBooks=4 ;
	cout << "What book do you want to borrow: ";
	cin.ignore();
	getline(cin , bookTitle);
	for (string::size_type i = 0; i<bookTitle.length(); ++i) {
		bookTitle[i] = toupper(bookTitle[i]);
	}
	int i = numBooks;
	ifstream copyIn("Copy.txt");
	ofstream temp("temp.txt"), temp2("temp2.txt");
	if (copyIn.fail()) {cerr << "Could not open Copy.txt" << endl; return;}
	if (temp.fail()) {cerr << "Could not open temp.txt"<<endl; return;}
	if (temp2.fail()) { cerr << "Could not open temp2.txt" << endl; return; }
	bool borrowed=false;
	while (!copyIn.eof()) {
		copyAttr.clear();
		getline(copyIn, copyEntry);
		if (copyEntry == "") {
			break;
		}
		stringstream ss(copyEntry);
		while (ss.good()) {
			string s;
			getline(ss, s, ',');
			copyAttr.push_back(s);
		}
		if (copyAttr[title] == bookTitle && copyAttr[borrower]==""&&!borrowed) {
			cout << "Book available" << endl;
			temp << copyAttr[id] << "," << copyAttr[title] << "," << copyAttr[author] << "," << copyAttr[category] << "," << copyAttr[ISBN] << "," << this->username << endl;
			cout << "\nBook has been checked out" << endl;
			borrowed = true;
			this->numBooks++;
			ifstream readerIn("Reader.txt");
			if (readerIn.fail()) { cerr << "Reader.txt could not be opened"; return; }
			while (!readerIn.eof()) {
				userAttr.clear();
				getline(readerIn, userEntry);
				if (userEntry == "") {
					break;
				}
				stringstream ss(userEntry);
				while (ss.good()) {
					string s;
					getline(ss, s, ',');
					userAttr.push_back(s);
				}
				if (this->username == userAttr[user]) {
					temp2 << userAttr[type] << "," << userAttr[user] << "," << userAttr[pass] << "," << this->numBooks << "," << userAttr[maxBooks] << endl;
				}
				else {
					temp2 << userEntry << endl;
				}
			}
			readerIn.close();
			temp2.close();
			remove("Reader.txt");
			rename("temp2.txt", "Reader.txt");
		}
		else if (copyAttr[title]==bookTitle&&copyAttr[borrower]!="") {
			cout << "Book has already been taken out" << endl;
		}
		else{
			temp << copyEntry << endl;
		}
	}
	copyIn.close();
	temp.close();
	remove("Copy.txt");
	rename("temp.txt", "Copy.txt");
}

void Reader::returnBooks() {
	//1). Enter name of book to be returned
	//2). Remove borrower name from Copy textfile
	//3). decrement numbooks for Reader
	//4). notify user on login if book overdue/reservation available??? 
	//Teacher teacher;
	//Student student;
	string copyEntry, readerEntry, bookTitle;
	vector<string> copyAttr, readerAttr;
	int id = 0, title = 1, author = 2, category = 3, ISBN = 4, borrower = 5, type = 0, user = 1, pass = 2, numBooks = 3, maxBooks = 4;
	cout << "What book do you want to return: " << endl;
	cin >> bookTitle;
	for (string::size_type i = 0; i<bookTitle.length(); ++i) {
		bookTitle[i] = toupper(bookTitle[i]);
	}
	ifstream copyIn("Copy.txt");
	ofstream temp("temp.txt"), temp2("temp2.txt");
	if (copyIn.fail()) { cerr << "Copy.txt could not be opened" << endl; return; }
	if (temp.fail()) { cerr << "temp.txt could not be opened" << endl; return; }
	while (!copyIn.eof()) {
		copyAttr.clear();
		getline(copyIn, copyEntry);
		if (copyEntry == "") {
			break;
		}
		std::stringstream ss(copyEntry);
		while (ss.good()) {
			string s;
			getline(ss, s, ',');
			copyAttr.push_back(s);
		}
		if (copyAttr[title] == bookTitle && copyAttr[borrower] == this->username) {
			cout << "Book available to be returned" << endl;
			temp << copyAttr[id] << "," << copyAttr[title] << "," << copyAttr[author] << "," << copyAttr[category] << "," <<copyAttr[ISBN]<<","<<endl ;
			cout << "\nBook returned" << endl;
			this->numBooks--;
			ifstream readerIn;
			readerIn.open("Reader.txt");
			numBooks = numBooks - 1;
			while (!readerIn.eof()) {
				readerAttr.clear();
				getline(readerIn, readerEntry);
				if (readerEntry == "") { break; }
				stringstream rss(readerEntry);
				while (rss.good()) {
					string s;
					getline(rss, s, ',');
					readerAttr.push_back(s);
				}
				if (readerAttr[user] == this->username) {
					temp2 << this->type << "," << this->username << "," << this->password << "," << this->numBooks << "," << this->maxBooks<<endl;
				}
				else {
					temp2 << readerEntry << endl;
				}
			}
			readerIn.close();
		}
		else {
			temp << copyEntry << endl;
		}
	}
}

void Reader::reserveBooks() {
	//1). ask for book to reserve
	//2). if copy available then prompt reader to borrow(extra function parameter to see if tried to borrow first or direct reserve?)
	//3).if not, add username to copy for reservation list
}

void Reader::cancelReservation() {
	//1).Remove name from copy reservation list
}
