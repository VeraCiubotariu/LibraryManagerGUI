#include "FileRepo.h"
#include <assert.h>
#include "errors.h"
#include <iostream>
#include <fstream>
using std::endl;


void FileRepo::readAllFromFile() {
	std::ifstream fin(fileName);
	books.clear();

//	while (!fin.eof()) {
//		std::string title, author, genre;
//		int year;
//		fin >> title;
//
//		if (fin.eof()) {
//			break;
//		}
//
//		fin >> author >> genre >> year;
//		auto book = Book(title, author, genre, year);
//		books.push_back(book);
//	}

	while (!fin.eof()) {
		std::string title, author, genre, space;
		int year;
		std::getline(fin, title);

		if (fin.eof()) {
			break;
		}

		std::getline(fin, author);
		std::getline(fin, genre);
		fin >> year;
		std::getline(fin, space);
		auto book = Book(title, author, genre, year);
		books.push_back(book);
	}

	fin.close();
}

void FileRepo::writeAllToFile() {
	std::ofstream fout(fileName);
	for (auto book : books) {
		fout << book.getTitle() << endl;
		fout << book.getAuthor() << endl;
		fout << book.getGenre() << endl;
		fout << book.getYear() << endl;
	}

	fout.close();
}

void FileRepo::add(const Book& book) {
	readAllFromFile();
	this->books.push_back(book);
	writeAllToFile();
}

void FileRepo::modify(const int pos, const Book& newBook) {
	readAllFromFile();
	books[pos].setTitle(newBook.getTitle());
	books[pos].setAuthor(newBook.getAuthor());
	books[pos].setGenre(newBook.getGenre());
	books[pos].setYear(newBook.getYear());
	writeAllToFile();
}

void FileRepo::remove(const int pos) {
	readAllFromFile();
	modify(pos, books[books.size() - 1]);
	books.pop_back();
	writeAllToFile();
}

int FileRepo::booksNumber() {
	readAllFromFile();
	return this->books.size();
}

const Book& FileRepo::getBook(const int pos) {
	readAllFromFile();
	return this->books[pos];
}

int FileRepo::getBookPos(const Book& book) {
	readAllFromFile();
	for (int i = 0; i < books.size(); i++) {
		if (books[i].getTitle() == book.getTitle() && books[i].getAuthor() == books[i].getAuthor()) {
			return i;
		}
	}

	throw(RepositoryError("Carte inexistenta!\n"));
}

vector<Book> FileRepo::getAll() {
	readAllFromFile();
	return this->books;
}

const Book& FileRepo::searchByTitle(const std::string& title) {
	readAllFromFile();
	auto iterator = std::find_if(books.begin(), books.end(), [=](const Book& book) {
		if (book.getTitle() == title) {
			return 1;
		}
		return 0;
		});

	if (iterator == books.end()) {
		throw RepositoryError("Carte inexistenta!\n");
	}

	else {
		return books[iterator - books.begin()];
	}
}

void testFileRepo() {
	std::ofstream fout("teste_file_repo.txt");
	fout << "";
	fout.close();

	auto books = FileRepo("teste_file_repo.txt");
	assert(books.booksNumber() == 0);
	
	Book a = Book("Title", "Author", "Genre", 2005);
	Book another = Book("Mamma", "Mia", "Horror", 2022);

	books.add(a);
	assert(books.booksNumber() == 1);
	assert(books.getBook(0) == a);

	Book b = Book("Other", "Cool", "Horror", 1987);
	books.add(b);
	
	assert(books.booksNumber() == 2);
	assert(books.getBook(1) == b);
	assert(books.searchByTitle("Title") == a);

	assert(books.getBookPos(a) == 0);
	try {
		books.getBookPos(another);
	}
	catch (RepositoryError& error) {
		assert(error.getMessage() == "Carte inexistenta!\n");
	}

	vector<Book> copy = books.getAll();
	assert(copy[0] == a);
	assert(copy[1] == b);
	assert(copy.size() == 2);

	Book c = Book("No longer human", "Osamu Dazai", "Psychological", 1978);
	books.modify(0, c);
	assert(books.getBook(0) == c);

	books.remove(0);
	assert(books.booksNumber() == 1);
	assert(books.getBook(0) == b);

	books.remove(0);
	assert(books.booksNumber() == 0);

	try {
		books.searchByTitle("Title");
		assert(false);
	}
	catch (RepositoryError error) {
		assert(true);
	}
}

