#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include "Librarian.h"
#include <locale>
using namespace std;

Librarian::Librarian(){}

Librarian::Librarian(string& user_, string& pass_) :User{ user_, pass_ } {}

void Librarian::getLogin() {
	string user, pass, type="librarian";
	int numBooks = 0;
	while (1) {
		cout << "Welcome back, "<<getUser() << endl;
		cout << "Please choose:" << endl;
		cout << "         1 -- Search Books" << endl;
		cout << "         2 -- Add Books" << endl;
		cout << "         3 -- Delete Books" << endl;
		cout << "         4 -- Search Users" << endl;
		cout << "         5 -- Add Users" << endl;
		cout << "         6 -- Delete Users" << endl;
		cout << "         7 -- My Information" << endl;
		cout << "         8 -- Change Password" << endl;
		cout << "         0 -- Log Out" << endl;
		cout << "Selection: ";
		int n;
		cin >> n;
		switch (n) {
		case 1:
			searchBooks(type, numBooks);
			break;
		case 2:
			addBooks();
			break;
		case 3:
			deleteBooks();
			break;
		case 4:
			searchUser();
			break;
		case 5:
			addUser();
			break;
		case 6:
			deleteUser();
			break;
		case 7:
			lmyInfo(type, numBooks);
			break;
		case 8:
			changePassword(type, numBooks);
			break;
		case 0:
			logout(user, pass);
			break;
		}
	}
}

void Librarian::searchUser() {
	cout << "\n";
	cout << "**********************************************************" << endl;
	cout << "-                       Search User                         -" << endl;
	cout << "**********************************************************" << endl;
	ifstream readerIn("Reader.txt");
	ifstream librarianIn("Librarian.txt");
	if (readerIn.fail()) {
		cerr << "Reader.txt could not be opened" << endl;
		exit(0);
	}
	string userEntry, searchTerm;
	vector<string> reader;
	int type=0, user=1, pass=2, numBooks=3, maxBooks=4;
	cout << "Enter username: ";
	cin.ignore();
	getline(cin, searchTerm);
	bool found;
	while (!readerIn.eof()) {
		reader.clear();
		getline(readerIn, userEntry);
		if (userEntry == "") {
			break;
		}
		stringstream ss(userEntry);
		while (ss.good()) {
			string s;
			getline(ss, s, ',');
			reader.push_back(s);
		}
		if (searchTerm == reader[user]) {
			cout<<"Username: " << reader[user] << "\nType: "<<reader[type]<<"\nNumber of books borrowed: " << reader[numBooks]<< endl;
			found = true;
		}
	}
	readerIn.close();
	if (!found) {
		ifstream librarianIn;
		librarianIn.open("Librarian.txt");
		if (librarianIn.fail()) {
			cerr << "Librarian.txt could not be opened" << endl;
			exit(0);
		}
		while (!librarianIn.eof()) {
			reader.clear();
			getline(librarianIn, userEntry);
			stringstream ss(userEntry);
			while (ss.good()) {
				string s;
				getline(ss, s, ',');
				reader.push_back(s);
			}
			if (searchTerm == reader[user]) {
				cout << "Username: " << reader[user] << "\n Type: LIBRARIAN"<< "Password: " << reader[pass] << endl;
				found = true;
			}
		}
		if (!found) {
			cout << "User could not be found" << endl;
		}
		librarianIn.close();
	}
}

void Librarian::addUser() {
	cout << "\n";
	cout << "**********************************************************" << endl;
	cout << "-                        Add User                        -" << endl;
	cout << "**********************************************************" << endl;

	string newUsername, newPassword, newType, userEntry;
	int type=0, username=1, password=2, numBooks=3, maxBooks=4;
	vector<string>reader;
	cout << "Enter user type (teacher or student): ";
	cin.ignore();
	getline(cin, newType);
	locale loc;
	for (string::size_type i = 0; i<newType.length(); ++i) {
		newType[i] = toupper(newType[i], loc);
	}
	cout << "Enter new username: ";
	getline(cin, newUsername);
	cout << "Enter new password: ";
	getline(cin, newPassword);

	ifstream readerIn("Reader.txt");
	ofstream readerOut("Reader.txt", ios::app);
	bool exists = false;
	while (!readerIn.eof()) {
		reader.clear();
		getline(readerIn, userEntry);
		if (userEntry == "") {
			break;
		}
		stringstream ss(userEntry);
		while (ss.good()) {
			string sub;
			getline(ss, sub, ',');
			reader.push_back(sub);
		}
		if (newUsername == reader[username]) {
			cout << "User already exists" << endl;
			exists = true;
		}
	}
	readerIn.close();
	if (!exists) {
		if (newType == "TEACHER") {
			readerOut << newType << "," << newUsername << "," << newPassword << "," << "0"<< "," << "10"<<"\n";
			cout << "User added" << endl;
		}
		else if(newType=="STUDENT") {
			readerOut << newType << "," << newUsername << "," << newPassword << "," << "0"<< "," << "5" << "\n";
			cout << "User added" << endl;
		}
		else {
			cout << "Invalid type, user cannot be added" << endl;
		}
	}
	readerOut.close();
}

void Librarian::deleteUser() {
	cout << "\n";
	cout << "**********************************************************" << endl;
	cout << "-                     Delete User                        -" << endl;
	cout << "**********************************************************" << endl;
	ifstream readerIn("Reader.txt");
	ofstream temp("temp.txt", ios_base::app);
	
	if (readerIn.fail()) {
		cerr << "File could not be opened" << endl;
		exit(0);
	}
	string userEntry, userDel;
	int type = 0, user = 1, pass = 2, numBooks=3, maxBooks=4;
	vector<string> reader;
	cout << "Enter username to delete: ";
	cin.ignore();
	getline(cin, userDel);
	while (!readerIn.eof()) {
		getline(readerIn, userEntry);
		reader.clear();
		if (userEntry == "") {
			break;
		}
		stringstream ss(userEntry);
		while (ss.good()) {
			string sub;
			getline(ss, sub, ',');
			reader.push_back(sub);
		}
		if (reader[user] == userDel) {
			cout << reader[user] << " has been destroyed" << endl;
		}
		else {
			temp << userEntry << endl;
		}
	}
	temp.close();
	readerIn.close();
	remove("Reader.txt");
	rename("temp.txt", "Reader.txt");
}

void Librarian::addBooks() {
	cout << "\n";
	cout << "**********************************************************" << endl;
	cout << "-                       Add Books                        -" << endl;
	cout << "**********************************************************" << endl;
	ifstream bookIn("Book.txt");
	ofstream temp("temp.txt", ios_base::app), copyOut("Copy.txt", ios_base::app);
	
	if (bookIn.fail()) {
		cerr << "File could not be opened" << endl;
		exit(1);
	}
	if (copyOut.fail()) {
		cerr << "Copy.txt could not be opened" << endl;
		exit(1);
	}
	string newISBN, newTitle, newAuthor, newCategory, bookEntry;
	vector<string> bookAttr;
	int title=0, author=1, category=2, ISBN=3, copies=4, borrower=5, newCopy;
	bool exists = false;
	cout << "\nEnter new book title: ";
	cin.ignore();
	getline(cin , newTitle);
	locale loc;
	for (string::size_type i = 0; i<newTitle.length(); ++i) {
		newTitle[i] = toupper(newTitle[i], loc);
	}
	cout << "Enter new book author: ";
	getline(cin,newAuthor);
	for (string::size_type i = 0; i<newAuthor.length(); ++i) {
		newAuthor[i] = toupper(newAuthor[i], loc);
	}
	cout << "Enter new book category: ";
	getline(cin , newCategory);
	for (string::size_type i = 0; i<newCategory.length(); ++i) {
		newCategory[i] = toupper(newCategory[i], loc);
	}
	cout << "Enter new book ISBN: ";
	getline(cin, newISBN);
	
	cout << "How many copies of this book? ";
	cin >> newCopy;
	//check if textfile is null, if it is add new book, if not the check every book listed, 
	//if book already exists add new copy, if not then add line at end of file
	while (!bookIn.eof()) {
		getline(bookIn, bookEntry);
		if (bookEntry == "") {
			break;
		}
		stringstream ss(bookEntry);
		bookAttr.clear();
		while (ss.good()) {
			string sub;
			getline(ss, sub, ',');
			bookAttr.push_back(sub);
		}
		//matching ISBN?
		if (newTitle == bookAttr[title]) {
			cout << "Book already exists" << endl;
			exists = true;
			temp << bookAttr[title] << "," << bookAttr[author] << "," << bookAttr[category] << "," << bookAttr[ISBN] << "," << newCopy+stoi(bookAttr[copies]) << "\n";
			for (int i = stoi(bookAttr[copies]) + 1; i <= newCopy + stoi(bookAttr[copies]); i++){
				copyOut << i << "," << bookAttr[title] << "," << bookAttr[author] << "," << bookAttr[category] << "," << bookAttr[ISBN] << "\n";
			}
			copyOut.close();
		}
		else {
			temp << bookAttr[title] << "," << bookAttr[author] << "," << bookAttr[category] << "," << bookAttr[ISBN] << "," << bookAttr[copies] << "\n";
		}
	}
	bookIn.close();
	temp.close();
	if (!exists){ 
		int i;
		cout << "New book" << endl;
		ofstream bookOut;
		bookOut.open("Book.txt", ios_base::app);
		bookOut << newTitle << "," << newAuthor << "," << newCategory << "," << newISBN << "," << newCopy << "\n";
		for (i = 0; i < newCopy; i++){
			copyOut << i + 1 << "," << newTitle << "," << newAuthor << "," << newCategory << "," << newISBN << "\n";
		}
		remove("temp.txt");
		bookOut.close();
	}
	else {
		remove("Book.txt");
		rename("temp.txt", "Book.txt");
	}
	copyOut.close();
	cout << "Book Added" << endl;
}

void Librarian::deleteBooks() {
	Librarian librarian;
	cout << "\n";
	cout << "**********************************************************" << endl;
	cout << "-                    Delete Books                        -" << endl;
	cout << "**********************************************************" << endl;
	ifstream bookIn("Book.txt");
	ofstream bookTemp("temp.txt", ios_base::app), copyTemp("temp2.txt", ios_base::app);
	ifstream copyIn("Copy.txt");

	if (bookIn.fail()) {
		cerr << "Book.txt not be open" << endl;
		exit(1);
	}
	if (bookTemp.fail()) {
		cerr << "temp.txt could not be opened" << endl;
		exit(1);
	}
	if (copyTemp.fail()) {
		cerr << "temp2.txt could not be opened" << endl;
		exit(1);
	}
	if (copyIn.fail()) {
		cerr << "Copy.txt could not be opened" << endl;
		exit(1);
	}

	string term, entry, copyEntry;
	int title = 0, author = 1, category = 2, ISBN = 3, copies=4; //book vector indices
	int copyNum = 0, title_ = 1, author_ = 2, category_ = 3, ISBN_ = 4;//copy vector indices
	vector<string> bookAttr, copyAttr;
	string s;
	cout << "Enter book title to delete: ";
	cin.ignore();
	getline(cin, term);
	//to upper search term
	locale loc;
	for (string::size_type i = 0; i < term.length(); ++i) {
		term[i] = toupper(term[i], loc);
	}
	while (!bookIn.eof()) {
		bookAttr.clear();
		getline(bookIn, entry);
		if (entry == "") {
			break;
		}
		stringstream ss(entry);
		while (ss.good()) {
			string sub;
			getline(ss, sub, ',');
			bookAttr.push_back(sub);
		}
		//give librarian option to delete all or some copies of book
		if (bookAttr[title] == term) {
			cout << "Title -- " << bookAttr[title]<<endl;
			cout << "Author -- " <<bookAttr[author]<< endl;
			cout << "Category -- " <<bookAttr[category]<< endl;
			cout << "ISBN -- " <<bookAttr[ISBN]<< endl;
			cout << "Would you like to delete all copies of this book? Y/N" << endl;
			cin >> s;
			if (s=="y"||s=="Y") {
				cout << "Book Deleted" << endl;
				s = bookAttr[copies];
			}
			else {
				cout << "How many copies would you like to delete? : ";
				cin >> s;
			}
			if (stoi(bookAttr[copies]) < stoi(s)) {
				cout << "Only " << bookAttr[copies] << " available to delete" << endl;
				s = bookAttr[copies];
			}
			else if (stoi(bookAttr[copies]) == stoi(s)) {
				//do not translate
			}
			else {
				bookTemp << bookAttr[title] << "," << bookAttr[author] << "," << bookAttr[category] << "," << bookAttr[ISBN] << "," << stoi(bookAttr[copies])-stoi(s) << "\n";
			}
			while (!copyIn.eof()) {
				copyAttr.clear();
				getline(copyIn, copyEntry);
				if (copyEntry == "") {
					break;
				}
				stringstream copyStream(copyEntry);
				while (copyStream.good()){
					string sub;
					getline(copyStream, sub, ',');
					copyAttr.push_back(sub);
				}
				if (copyAttr[title_] == bookAttr[title]) {
					if (stoi(copyAttr[copyNum]) > stoi(bookAttr[copies]) - stoi(s)) {
						//do not transfer book to temp file
					}
					else {
						copyTemp << copyEntry << endl;
					}
				}
				else {
					copyTemp << copyEntry<<endl;
				}
			}
		}
		else {
			bookTemp << entry << endl;
		}
	}
	copyIn.close();
	bookIn.close();
	bookTemp.close();
	copyTemp.close();
	remove("Book.txt");
	remove("Copy.txt");
	rename("temp2.txt", "Copy.txt");
	rename("temp.txt", "Book.txt");
}