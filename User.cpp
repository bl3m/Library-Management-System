#include <iostream>
#include <sstream>
#include <fstream>
#include <conio.h>
#include <vector>
#include <locale>
#include "User.h"
#include "Librarian.h"
#include "Reader.h"

using std::cin;
using std::cout;
User::User(){}

User::~User(){}

User::User(string& username_, string& password_, string& type_):username(username_), password(password_), type(type_){}

void User::login() {
	User admin;
	while (1) {
		cout << "\n";
		cout << "**********************************************************" << endl;
		cout << "-                        LOGIN                           -" << endl;
		cout << "**********************************************************" << endl;
		ifstream librarianIn("Librarian.txt");
		if (librarianIn.fail()) {
			cerr << "File could not be opened" << endl; //error
			return;
		}
		string userEntry, user, pass;
		vector<string> userInfo;
		int lUser = 0, lPass = 1, rType = 0, rUser = 1, rPass = 2, rNumBooks=3;
		cout << "Username: ";
		getline(cin, user);
		pass = getPass("Password: ", true); // password masking
		//check textfile to verify existing user
		bool found = false;
		string foundType, foundUser, foundPass;
		int foundNumBooks;
		while (!librarianIn.eof()) {
			userInfo.clear();
			getline(librarianIn, userEntry);
			if (userEntry == "") {
				break;
			}
			//input username and password from textfile
			stringstream ss(userEntry);
			while (ss.good()) {
				string s;
				getline(ss, s, ',');
				userInfo.push_back(s);
			}
			if (userInfo[lUser] == user && userInfo[lPass] == pass) {
				foundUser = user;
				foundPass = pass;
				foundType = "LIBRARIAN";
				found = true;
				break;
				//Librarian librarian(user,pass, "LIBRARIAN");
				//librarian.getLogin(); //librarian home screen
			}
		}
		librarianIn.close();
		
		//if not found, then check reader text file
		if (!found) {
			ifstream readerIn;
			readerIn.open("Reader.txt");
			if (readerIn.fail()) {
				cerr << "Reader.txt could not be opened" << endl;
			}
			while (!readerIn.eof()) {
				userInfo.clear();
				getline(readerIn, userEntry);
				if (userEntry == "") {
					break;
				}
				stringstream ss(userEntry);
				while (ss.good()) {
					string s;
					getline(ss, s, ',');
					userInfo.push_back(s);
				}
				if (user == userInfo[rUser] && pass == userInfo[rPass]) {
					foundUser = user;
					foundPass = pass;
					foundNumBooks = stoi(userInfo[rNumBooks]);
					if (userInfo[rType] == "TEACHER") {
						foundType = "TEACHER";
					}
					else{
						foundType = "STUDENT";
					}
					found = true;
					break;
				}
			}
			readerIn.close();
		}
		if (found) {
			cout << endl;
			if (foundType == "LIBRARIAN") {
				Librarian librarian(foundUser, foundPass, "LIBRARIAN");
				librarian.getLogin(); //librarian home screen
			}
			else if (foundType == "TEACHER") {
				Reader reader(foundUser, foundPass, foundType, foundNumBooks, 10);
				reader.getLogin();
			}
			else if (foundType == "STUDENT") {
				Reader reader(foundUser, foundPass, foundType, foundNumBooks, 5);
				reader.getLogin();
			}
		}
		else{
			cout << "\nWrong username/password" << endl;
		}
	}
}

string User::getPass(const char *prompt, bool show_asterisk){
	const char BACKSPACE = 8;
	const char RETURN = 13;

	string passwordMask;
	unsigned char ch = 0;

	cout << prompt;

	while ((ch = _getch()) != RETURN)
	{
		if (ch == BACKSPACE)
		{
			if (passwordMask.length() != 0)
			{
				if (show_asterisk)
					cout << "\b \b";
				passwordMask.resize(passwordMask.length() - 1);
			}
		}
		else if (ch == 0 || ch == 224) // handle escape sequences
		{
			_getch(); // ignore non printable chars
			continue;
		}
		else
		{
			passwordMask += ch;
			if (show_asterisk)
				cout << '*';
		}
	}
	return passwordMask;
}

void User::changePassword(string& type, int& numBooks){
	cout << "\n";
	cout << "**********************************************************" << endl;
	cout << "-                     Change Password                    -" << endl;
	cout << "**********************************************************" << endl;
	
	ifstream librarianIn("Librarian.txt");
	ifstream readerIn("Reader.txt");
	ofstream temp("temp.txt", ios_base::app);
	if (librarianIn.fail()) {
		cerr << "Librarian.txt could not be opened" << endl;
		return;
	}
	if (readerIn.fail()) {
		cerr << "Reader.txt could not be opened" << endl;
		return;
	}
	if (temp.fail()) {
		cerr << "temp.txt could not be opened" << endl;
		return;
	}
	string userEntry, newPass,  enteredPass, type1;
	int lUser = 0, lPass = 1, rUser=1, rPass=2;
	vector<string> userAttr;
	cout << "Verify your current password: ";
	cin.ignore();
	enteredPass= getPass("", true);
	bool found = false;
		
	while (!librarianIn.eof()) {
		userAttr.clear();
		getline(librarianIn, userEntry);
		if (userEntry == "") {
			break;
		}
		stringstream ss(userEntry);
		while (ss.good()) {
			string s;
			getline(ss, s, ',');
			userAttr.push_back(s);
		}
		if (this->username==userAttr[lUser]&&enteredPass == userAttr[lPass]) {
			found = true;
			cout << "\nEnter new password: ";
			newPass= getPass("", true); //enter new password
			temp << userAttr[lUser] << "," << newPass << endl;
			cout << "\nPassword Changed" << endl << endl;
		}
		else {
			temp << userEntry << endl;
		}
	}
	librarianIn.close();
	temp.close();
	remove("Librarian.txt");
	rename("temp.txt", "Librarian.txt");
	//rename Librarian.txt
	if (!found) {
		ofstream temp2("temp2.txt", ios_base::app);
		if (temp2.fail()) {
			cerr << "temp2.txt could not be opened" << endl;
			return;
		}
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
			if (this->username == userAttr[rUser] && enteredPass == userAttr[rPass]) {
				found = true;
				cout << "\nEnter new password: ";
				newPass = getPass("", true); //enter new password
				temp2 << userAttr[0] << "," << userAttr[rUser] << "," << newPass <<","<< userAttr[3] << "," << userAttr[4] << endl;
				cout << "\nPassword Changed" << endl << endl;
			}
			else {
				temp2 << userEntry << endl;
			}
		}
		//rename Reader.txt
		readerIn.close();
		temp2.close();
		remove("Reader.txt");
		rename("temp2.txt", "Reader.txt");
	}
	if (!found) {
		cout << "Password could not be verified" << endl;
	}
}

void User::searchBooks(string& type, int& numBooks) {
	bool found = false;
	cout << "\n";
	cout << "**********************************************************" << endl;
	cout << "-                       Search Books                     -" << endl;
	cout << "**********************************************************" << endl;
	ifstream fin("Book.txt");
	if (fin.fail()) {
		cerr << "could not open input file Book.txt\n";
		return;
	}
	string searchTerm, bookEntry;
	int title = 0, author = 1, category = 2, ISBN = 3, copies = 4;
	vector<string> bookAttr;
	cout << "Enter a search term: ";
	cin.ignore();
	getline(cin, searchTerm);
	locale loc;
	for (string::size_type i = 0; i<searchTerm.length(); ++i){
		searchTerm[i]=toupper(searchTerm[i], loc);
	}
	//use substrings, search for term within title?
	while (!fin.eof()) {
		getline(fin, bookEntry);
		if (bookEntry == "") {
			break;
		}
		stringstream ss(bookEntry);
		while (ss.good()) {
			string sub;
			getline(ss, sub, ',');
			bookAttr.push_back(sub);
		}
		if (searchTerm == bookAttr[title] || searchTerm == bookAttr[author] || searchTerm == bookAttr[category] || searchTerm == bookAttr[ISBN]) {
			cout << "TITLE -- " << bookAttr[title] <<endl;
			cout << "AUTHOR -- " << bookAttr[author] <<endl;
			cout << "CATEGORY -- " << bookAttr[category] <<endl;
			cout << "ISBN -- " << bookAttr[ISBN]<<endl;
			if (stoi(bookAttr[copies]) > 1) {
				cout << bookAttr[copies] << " copies available" << endl;
			}
			else {
				cout << bookAttr[copies] << " copy available" << endl << endl;
			}
			found = true;
			break;
		}
	} 
	if (!found) {
		cout << "Book could not be found" << endl;
	}
	fin.close();
}

void User::myInfo(string& type, int& numBooks) {
	Librarian librarian;
	cout << "\n";
	cout << "**********************************************************" << endl;
	cout << "-                    Your Information                    -" << endl;
	cout << "**********************************************************" << endl;
	if (type == "LIBRARIAN") {
		cout << "Your username is " << this->username << endl;
	}
	else {
		cout << "Your username is " << this->username << endl;
		cout << "You have " << numBooks << " book borrowed" << endl;
	}
}

void User::logout(string& user, string& pass) {
	cout << "Goodbye" << endl;
	cin.ignore();
	login();
}