#include <iostream>
#include <string>
#include <fstream>
#include <conio.h>
#include <locale>
#include "User.h"
#include "Librarian.h"
#include "Reader.h"
#include "Student.h"
#include "Teacher.h"

using namespace std;
User::User(){

}

void User::login(string user, string pass) {
	User admin;
	Librarian librarian; //access librarian class
	Reader reader; //access reader class
	cout << "\n";
	cout << "**********************************************************" << endl;
	cout << "-                        LOGIN                           -" << endl;
	cout << "**********************************************************" << endl;
	string type, username, password; //initialize username, type, and password
	int numBooks;
	ifstream fin("Librarian.txt");
	if (fin.fail()) {
		cerr << "File could not be opened" << endl; //error
		exit(0);
	}
	//enter username
	cout << "Username: ";
	cin >> user;	
	pass = getPass("Password: ", true); // Show asterisks
	int n = 0; //indicator for librarian or reader account
	//check textfile to verify existing user
	while (!fin.eof()) {
		fin >> username >> password;
		//input username and password from textfile
		if (user == username && pass == password) {
			cout << endl;
			librarian.getLogin(); //librarian home screen
		}
		else {
			n += 1;
		}
	}
	fin.close();
	//if n=1, then check reader text file
	if (n >= 1) {
		ifstream readerIn;
		readerIn.open("Reader.txt");
		if (readerIn.fail()) {
			cerr << "Reader.txt could not be opened" << endl;
		}
		while (!readerIn.eof()) {
			readerIn >> type >> username >> password>> numBooks;
			if (user == username&& pass == password) {
				cout << endl;
				reader.getLogin(type, numBooks);
			}
		}
		readerIn.close();
	}
	cout << "\nWrong username/password" << endl;
	admin.login(user, pass);
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
	cout << "\n";
	cout << "**********************************************************" << endl;
	cout << "-                       Search Books                     -" << endl;
	cout << "**********************************************************" << endl;
	ifstream fin("Book.txt");
	if (fin.fail()) {
		cerr << "could not open input file Book.txt\n";
		exit(0);
	}
	string title, ISBN, author, category, searchTerm;
	int copies;
	int n=0;
	cout << "Enter search term with no spaces" << endl;
	cin >> searchTerm;
	//cin.ignore();
	//getline(cin, searchTerm);
	//searchTerm.erase(remove(searchTerm.begin(), searchTerm.end(), ' '), searchTerm.end()); //lets user use spaces
	//transform(searchTerm.begin(), searchTerm.end(), searchTerm.begin(), ::toupper); //lets user user upper/lowercase
	/*int length = searchTerm.length();
	for (int i = 0; i < length; i++) {
		if (searchTerm[i] == ' ') {
			searchTerm.erase(i, 1);
		}
	}*/
	locale loc;
	for (string::size_type i = 0; i<searchTerm.length(); ++i){
		searchTerm[i]=toupper(searchTerm[i], loc);
	}
	

	while (!fin.eof()) {
		fin >> title >> author >> category >> ISBN>>copies;
		if (searchTerm == title | searchTerm == author | searchTerm == category | searchTerm == ISBN) {
			cout << "TITLE -- " << title << endl;
			cout << "AUTHOR -- " << author << endl;
			cout << "CATEGORY -- " << category << endl;
			cout << "ISBN -- " << ISBN << endl;
			if (copies > 1) {
				cout << copies << " copies available" << endl;
			}
			else {
				cout << copies << " copies available" << endl << endl;
			}
			n += 1;
		}
	} 
	if (n == 0) {
		cout << "Book could not be found" << endl;
	}
	fin.close();
	if (type == "librarian") {
		librarian.getLogin();
	}
	else if (type == "teacher") {
		teacher.getLogin(numBooks);
	}
	else {
		student.getLogin(numBooks);
	}
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

void User::logout(string user, string pass) {
	cout << "Goodbye" << endl;
	login(user, pass);
}