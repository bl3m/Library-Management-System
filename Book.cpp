#include "Book.h"
#include "Copy.h"
#include <string>
#include <fstream>
#include <iostream>

Book::Book() {

}
Book::Book(string ISBN_, string title_, string author_, string category_, int copies_){
	ISBN = ISBN_;
	title = title_;
	author = author_;
	category = category_;
	copies = copies_;
}

string Book::getISBN() {
	return ISBN;
}
string Book::getTitle() {
	return title;
}
string Book::getAuthor() {
	return author;
}
string Book::getCategory() {
	return category;
}
int Book::getNumCopies() {
	return copies;
}
void Book::setNumCopies(int copies_) {
	copies = copies_;
}


