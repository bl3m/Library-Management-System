#pragma once
#include <string>
using namespace std;
class Book
{
private:
	string ISBN;
	string title;
	string author;
	string category;
	int copies;
public:
	Book();
	Book(string ISBN_, string title_, string author_, string category_, int copies_);
	string getISBN();
	string getTitle();
	string getAuthor();
	string getCategory();
	int getNumCopies();
	void setNumCopies(int copies_);
};

