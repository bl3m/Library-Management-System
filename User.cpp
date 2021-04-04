#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <conio.h>
#include <vector>
#include <locale>
#include "User.h"
#include "Librarian.h"
#include "Reader.h"
#include "Student.h"
#include "Teacher.h"

using namespace std;
User::User(){}

User::User(string& username_, string& password_):username(username_), password(password_) {}

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
			exit(0);
		}
		string userEntry, user, pass;
		vector<string> userInfo;
		int lUser = 0, lPass = 1, rType = 0, rUser = 1, rPass = 2, rNumBooks=3;
		cout << "Username: ";
		getline(cin, user);
		pass = getPass("Password: ", true); // password masking
		//check textfile to verify existing user
		bool found = true;
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
				cout << endl;
				Librarian librarian(user,pass);
				librarian.getLogin(); //librarian home screen
			}
			else {
				found = false;
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
					cout << endl;
					if (userInfo[rType] == "TEACHER") {
						Reader reader(user, pass, userInfo[rType], stoi(userInfo[rNumBooks]), 10);
						reader.getLogin("TEACHER");
					}
					else{
						Reader reader(user, pass, userInfo[rType], stoi(userInfo[rNumBooks]), 10);
						reader.getLogin("STUDENT");
					}
					break;
				}
			}
			readerIn.close();
		}
		if (!found) {
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

void User::changePassword(string type, int numBooks){
	Student student;
	Librarian librarian;
	Teacher teacher;
	cout << "\n";
	cout << "**********************************************************" << endl;
	cout << "-                     Change Password                    -" << endl;
	cout << "**********************************************************" << endl;
	ifstream fin("Librarian.txt");
	
	if (fin.fail()) {
		cerr << "Librarian.txt could not be opened" << endl;
		exit(0);
	}
	string user, pass, newPass,  enteredPass, type1;
	int n = 0;
	cout << "Enter your current password: ";
	cin >> enteredPass;
	/*locale loc;
	for (string::size_type i = 0; i<enteredPass.length(); ++i) {
		enteredPass[i] = toupper(enteredPass[i], loc);
	}*/
	cout << enteredPass << endl;
	while (!fin.eof()) {
		fin >> user >> pass;
		if (enteredPass == pass) {
			cout << "Enter new password: ";
			cin >> newPass; //enter new password
			pass = newPass; //set old password to new
			n += 1; 
			ofstream fout("Librarian.txt");
			fout << user <<" "<< newPass;
			fout.close();
			cout << "Password Changed" << endl << endl;
		}
		else {
			ofstream fout("Librarian.txt");
			fout << user<< " " << pass;
			fout.close();
		}
	}
	fin.close();
	if (n == 0) {
		ifstream readerIn;
		readerIn.open("Reader.txt");
		if (readerIn.fail()) {
			cerr << "Reader.txt could not be opened" << endl;
			exit(0);
		}
		while (!readerIn.eof()){
			readerIn >> type1 >> user >> pass;
			if (user == enteredPass) {
				cout << "Enter new 0password: ";
				cin >> newPass;
				locale loc;
				ofstream readerOut;
				readerOut.open("Reader.txt");
				readerOut << " " << type1 << " " << user << " " << newPass;
				readerOut << " " << endl;
				cout << "Password Changed" << endl;
				readerOut.close();
			}
			else {
				ofstream fout("Reader.txt");
				fout << type1 <<"  "<<user <<" "<< pass;
				fout << " " << endl;
				fout.close();
			}
		}
	}
	fin.close();
	if (type == "student") {
		student.getLogin(numBooks); //go to student login screen
	}
	else if(type=="librarian"){
		cout << n << endl;
		cout << user << endl;
		librarian.getLogin(); //go to librarian login screen
	}
	else {
		teacher.getLogin(numBooks); //go to teacher login screen
	}
}

void User::searchBooks(string type, int numBooks) {
	Librarian librarian;
	Student student;
	Teacher teacher;
	bool found = false;
	cout << "\n";
	cout << "**********************************************************" << endl;
	cout << "-                       Search Books                     -" << endl;
	cout << "**********************************************************" << endl;
	ifstream fin("Book.txt");
	if (fin.fail()) {
		cerr << "could not open input file Book.txt\n";
		exit(0);
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

void User::lmyInfo(string type, int numBooks) {
	Librarian librarian;
	cout << "\n";
	cout << "**********************************************************" << endl;
	cout << "-                    Your Information                    -" << endl;
	cout << "**********************************************************" << endl;
	string type1, user, pass, enterUser;
	cout << "Enter your username: ";
	cin >> enterUser;
	ifstream fin("Librarian.txt");
	while (!fin.eof()) {
		fin >> user >> pass;
		if (user == enterUser) {
			cout << "Your username is " << user << endl;
			cout << "Your password is " << pass << endl;
		}
	}
	fin.close();
	
	librarian.getLogin();
}

void User::smyInfo(string type, int numBooks) {
	Student student;
	cout << "\n";
	cout << "**********************************************************" << endl;
	cout << "-                    Your Information                    -" << endl;
	cout << "**********************************************************" << endl;
	string type1, user, pass, enterUser;
	int numberofCopies;
	cout << "Enter your username: ";
	cin >> enterUser;
	ifstream fin("Reader.txt");
	while (!fin.eof()) {
		fin >> type1 >> user >> pass >> numberofCopies;
		if (enterUser == user) {
			cout << "Your username is " << user << endl;
			cout << "Your password is " << pass << endl;
			cout << "You have " << numberofCopies << " books borrowed" << endl;
		}
	}
	fin.close();

	student.getLogin(numBooks);
	
}

void User::tmyInfo(string type, int numBooks) {
	Teacher teacher;
	cout << "\n";
	cout << "**********************************************************" << endl;
	cout << "-                    Your Information                    -" << endl;
	cout << "**********************************************************" << endl;
	string type1, user, pass, enterUser;
	int numberofCopies;
	cout << "Enter your username: ";
	cin >> enterUser;
	ifstream fin("Reader.txt");
	while (!fin.eof()) {
		fin >> type1 >> user >> pass >> numberofCopies;
		if (enterUser == user) {
			cout << "Your username is " << user << endl;
			cout << "Your password is " << pass << endl;
			cout << "You have " << numberofCopies << " books borrowed" << endl;
		}
	}
	fin.close();

	teacher.getLogin(numBooks);
}
/*void User::myInfo(string type, int numBooks) {
	Librarian librarian;
	cout << "\n";
	cout << "**********************************************************" << endl;
	cout << "-                    Your Information                    -" << endl;
	cout << "**********************************************************" << endl;
	Student student;
	Teacher teacher;
	string type1, user, pass, enterUser;
	int numberofCopies, n=0;
	cout << "Enter your username: ";
	cin >> enterUser;
	ifstream fin("Librarian.txt");
	while (!fin.eof()){
		fin >> user >> pass;
		if (user == enterUser) {
			cout << "Your username is " << user<<endl;
			cout << "Your password is " << pass << endl;
			n += 1;
		}
	}
	fin.close();
	if (n = 0) {
		ifstream fin("Reader.txt");
		while (!fin.eof()) {
			fin >> type1 >> user >> pass >> numberofCopies;
			if (enterUser == user) {
				cout << "Your username is " << user << endl;
				cout << "Your password is " << pass << endl;
				cout << "You have " << numberofCopies << " books borrowed" << endl;
			}
		}
		fin.close();
	}
	if (type == "librarian") {
		librarian.getLogin();
	}
	if (type == "teacher") {
		teacher.getLogin(numBooks);
	}
	if (type == "student") {
		student.getLogin(numBooks);
	}
}*/

string User::getUser() {
	return this->username;
}
void User::logout(string user, string pass) {
	cout << "Goodbye" << endl;
	cin.ignore();
	login();
}
