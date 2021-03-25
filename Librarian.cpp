#include <iostream>
#include <fstream>
#include <string>
#include "Librarian.h"
#include <locale>
using namespace std;

Librarian::Librarian(){
	
}

void Librarian::getLogin() {
	string user, pass, type="librarian";
	int numBooks = 0;
	cout << "Welcome back, Librarian" << endl;
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

void Librarian::searchUser() {
	Librarian librarian;
	cout << "\n";
	cout << "**********************************************************" << endl;
	cout << "-                       Search User                         -" << endl;
	cout << "**********************************************************" << endl;
	ifstream fin("Reader.txt");
	if (fin.fail()) {
		cerr << "Reader could not be opened" << endl;
		exit(0);
	}
	string username, password, type, searchTerm ;
	int i = 0;
	cout << "Enter username: ";
	cin >> searchTerm;
	while (!fin.eof()) {
		fin >> type >> username>>password;
		if (searchTerm == username) {
			cout<<"Username: " << username << "\n" <<"Password: " << password << endl;
			i += 1;
		}
	}
	fin.close();
	if (i = 0) {
		ifstream librarianIn;
		librarianIn.open("Librarian.txt");
		if (librarianIn.fail()) {
			cerr << "Librarian.txt could not be opened" << endl;
			exit(0);
		}
		while (!librarianIn.eof()) {
			fin >> username >> password;
			if (searchTerm == username) {
				cout << "Username: " << username << "\n" << "Password: " << password << endl;
			}
			else {
				cout << "User could not be found" << endl;
			}
		}
		librarianIn.close();
	}
	librarian.getLogin();
}

void Librarian::addUser() {
	Librarian librarian;
	cout << "\n";
	cout << "**********************************************************" << endl;
	cout << "-                        Add User                        -" << endl;
	cout << "**********************************************************" << endl;

	string username, password, newUsername, newPassword, type, newType;
	int numBooks = 0;
	cout << "Enter user type: ";
	cin >> newType;
	locale loc;
	for (string::size_type i = 0; i<newType.length(); ++i) {
		newType[i] = toupper(newType[i], loc);
	}
	cout << "Enter new username: ";
	cin >> newUsername;
	cout << "Enter new password: ";
	cin >> newPassword;

	fstream fout("Reader.txt", ios::app);
	if (newType == "TEACHER") {
		fout << newType << " " << newUsername << " " << newPassword << " " << numBooks << " " << "10";
		fout << " " << endl;
	}
	else {
		fout << newType << " " << newUsername << " " << newPassword << " " << numBooks << " " <<"5";
		fout << " " << endl;
	}

	cout << "User added" << endl;

	librarian.getLogin();
}

void Librarian::deleteUser() {
	Librarian librarian;
	cout << "\n";
	cout << "**********************************************************" << endl;
	cout << "-                     Delete User                        -" << endl;
	cout << "**********************************************************" << endl;
	ifstream fin("Reader.txt");
	
	if (fin.fail()) {
		cerr << "File could not be opened" << endl;
		exit(0);
	}
	string user, username, password, numBooks, type, maxBooks;
	cout << "Enter username to delete" << endl;
	cin >> user;
	while (!fin.eof()) {
		fin >> type >> username>>password>>numBooks>>maxBooks ;
		if (!(user == username)) {
			ofstream fout("Reader.txt");
			fout << type << username<<password<< numBooks<<maxBooks;
			fout.close();
		}
		else {
			ofstream fout("Reader.txt");
			fout << " " << endl;
			cout << username << " has been eliminated" << endl;
		}
	}
	fin.close();
	librarian.getLogin();
}

void Librarian::addBooks() {
	Librarian librarian;
	cout << "\n";
	cout << "**********************************************************" << endl;
	cout << "-                       Add Books                        -" << endl;
	cout << "**********************************************************" << endl;
	ifstream fin("Book.txt");
	
	if (fin.fail()) {
		cerr << "File could not be opened" << endl;
		exit(1);
	}
	string newISBN, newTitle, newAuthor, newCategory, ISBN, title, author, category, borrower;
	int copies, newCopy, n=0;
	cout << "Enter new book title" << endl;
	cin >> newTitle;
	locale loc;
	for (string::size_type i = 0; i<newTitle.length(); ++i) {
		newTitle[i] = toupper(newTitle[i], loc);
	}
	cout << "\nEnter new book author" << endl;
	cin >> newAuthor;
	for (string::size_type i = 0; i<newAuthor.length(); ++i) {
		newAuthor[i] = toupper(newAuthor[i], loc);
	}
	cout << "\nEnter new book category" << endl;
	cin >> newCategory;
	for (string::size_type i = 0; i<newCategory.length(); ++i) {
		newCategory[i] = toupper(newCategory[i], loc);
	}
	cout << "\nEnter new book ISBN" << endl;
	cin >> newISBN;
	
	cout << "\nHow many copies of this book?" << endl;
	cin >> newCopy;
	
	while (!fin.eof()) {
		fin >> title >> author >> category >> ISBN >> copies;
		if (newTitle == title) {
			cout << "Book already exists" << endl;
			copies =copies+newCopy;
			n = 1;
			ofstream copyOut;
			copyOut.open("Copy.txt", ios::app);
			if (copyOut.fail()) {
				cerr << "Copy.txt could not be opened" << endl;
				exit(1);
			}
			copyOut <<copies << " " << title << " " << author << " " << category << " " << ISBN << " " << borrower;
			copyOut << " " << endl;
			copyOut.close();
			ofstream fout("Book.txt", ios::app);
			fout<< title << " " << author << " " << category << " " << ISBN << " " << copies;
			fout << " " << endl;
			fout.close();
		}
		/*else {
			ofstream fout("Book.txt", ios::app);
			fout <<"\n"<< title << " " << author << " " << category << " " << ISBN << " " << copies;
			fout.close();
		}*/
	}
	if (n==0){ 
		int i;
		cout << "New book" << endl;
		ofstream fout("Book.txt", ios::app);
		fout <<newTitle << " " << newAuthor << " " << newCategory << " " << newISBN << " " << newCopy;
		fout << " " << endl;
		ifstream copyIn;
		copyIn.open("Copy.txt");
		for (i = 0; i < newCopy; i++){
			ofstream copyOut;
			copyOut.open("Copy.txt", ios::app);
			copyOut << i+1 << " " << newTitle << " " << newAuthor << " " << newCategory << " " << newISBN;
			copyOut << " " << endl;
			copyOut.close();
			//copyOut << endl;
		}
		copyIn.close();
		
	}

	cout << "Book(s) Added" << endl;
	fin.close();
	librarian.getLogin();
}

void Librarian::deleteBooks() {
	Librarian librarian;
	cout << "\n";
	cout << "**********************************************************" << endl;
	cout << "-                    Delete Books                        -" << endl;
	cout << "**********************************************************" << endl;
	ifstream fin("Book.txt");
	ofstream fout("Book.txt");
	if (fin.fail()) {
		cerr << "Could not open file" << endl;
		exit(0);
	}
	string ISBN, title, author, category, term;
	int copy, n;
	cout << "Enter book to delete" << endl;
	cin >> term;
	while (!fin.eof()) {
		fin >> title >> author >> category >> ISBN >>copy;
		if (title == term) {
			cout << "Would you like to delete this book?" << endl;
			cout << "Title -- " << title<<endl;
			cout << "Author -- " <<author<< endl;
			cout << "Category -- " <<category<< endl;
			cout << "ISBN -- " <<ISBN<< endl;
			cout << "1 -- YES" << endl;
			cout << "2 -- NO" << endl;
			cin >> n;
			if (n==1) {
				cout << "Book Deleted" << endl;
			}
			else {
				fout << title << " " << author << " " << category << " " << ISBN << " " << copy;
			}
		}
		else {
			fout << title << " " << author << " " << category << " " << ISBN << " " << copy;
		}
	}
	fin.close();
	fout.close();
    librarian.getLogin();
}