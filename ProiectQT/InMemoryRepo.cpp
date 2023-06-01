#include "InMemoryRepo.h"
#include <assert.h>
#include "errors.h"

void InMemoryRepo::add(const Book& book) {
	this->books.push_back(book);
}

void InMemoryRepo::modify(const int pos, const Book& newBook) {
	books[pos].setTitle(newBook.getTitle());
	books[pos].setAuthor(newBook.getAuthor());
	books[pos].setGenre(newBook.getGenre());
	books[pos].setYear(newBook.getYear());
}

void InMemoryRepo::remove(const int pos) {
	modify(pos, books[books.size() - 1]);
	books.pop_back();
}

int InMemoryRepo::booksNumber() {
	return this->books.size();
}

const Book& InMemoryRepo::getBook(const int pos) {
	return this->books[pos];
}

int InMemoryRepo::getBookPos(const Book& book) {
	for (int i = 0; i < books.size(); i++) {
		if (books[i].getTitle() == book.getTitle() && books[i].getAuthor() == books[i].getAuthor()) {
			return i;
		}
	}

	throw(RepositoryError("Carte inexistenta!\n"));
}

vector<Book> InMemoryRepo::getAll() {
	return this->books;
}

const Book& InMemoryRepo::searchByTitle(const std::string& title) {
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

void testInMemoryRepo() {
	auto books = InMemoryRepo();
	assert(books.booksNumber() == 0);
	Book a = Book("Title", "Author", "Genre", 2005);
	Book another = Book("Mamma", "Mia", "Horror", 2022);

	books.add(a);
	assert(books.booksNumber() == 1);
	assert(books.getBook(0) == a);

	Book b = Book("Other", "Cool dude", "Horror", 1987);
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

