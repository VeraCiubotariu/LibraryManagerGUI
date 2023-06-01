#include "book.h"
#include <string>
#include <assert.h>
#include <iostream>

Book::Book(const std::string& title, const std::string& author, const std::string& genre, const int year) {
	this->title = title;
	this->author = author;
	this->genre = genre;
	this->year = year;
}

Book::Book() {
	this->title = this->author = this->genre = " ";
	this->year = 0;
}

Book::Book(const Book& book) {
	title = book.title;
	author = book.author;
	genre = book.genre;
	year = book.year;

	//std::cout << "copying...\n";
}

bool Book::operator==(const Book& book) const {
	if (this->author == book.author && this->title == book.title && this->genre == book.genre && this->year == book.year) {
		return true;
	}
	return false;
}

std::string Book::toString() const {
	std::string res = "Titlu: " + title + "\nAutor: " + author + "\nGen: " + genre + "\nAn: " + std::to_string(year) + "\n\n";
	return res;
}

const std::string Book::getTitle() const {
	return this->title;
}

const std::string Book::getAuthor() const {
	return this->author;
}

const std::string Book::getGenre() const {
	return this->genre;
}

int Book::getYear() const {
	return this->year;
}

void Book::setTitle(const std::string& newTitle) {
	this->title = newTitle;
}

void Book::setAuthor(const std::string& newAuthor) {
	this->author = newAuthor;
}

void Book::setGenre(const std::string& newGenre) {
	this->genre = newGenre;
}

void Book::setYear(const int newYear) {
	this->year = newYear;
}

void testBook() {
	Book b = Book("Title", "Author", "Genre", 2005);
	assert(b.getTitle() == "Title");
	assert(b.getAuthor() == "Author");
	assert(b.getGenre() == "Genre");
	assert(b.getYear() == 2005);

	b.setTitle("New Title");
	assert(b.getTitle() == "New Title");

	b.setAuthor("New Author");
	assert(b.getAuthor() == "New Author");

	b.setGenre("New Genre");
	assert(b.getGenre() == "New Genre");

	b.setYear(1999);
	assert(b.getYear() == 1999);

	b = Book();
	assert(b.getAuthor() == " ");
	assert(b.getYear() == 0);

	Book a = Book();
	assert(a == b);
	assert(a.toString() == "Titlu:  \nAutor:  \nGen:  \nAn: 0\n\n");

	a.setAuthor("aer");
	assert(!(a == b));
}