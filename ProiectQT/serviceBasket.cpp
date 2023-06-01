#include "serviceBasket.h"
#include "errors.h"

#include <random>
#include <iostream>
#include <fstream>
#include <assert.h>


void ServiceBasket::addInBasket(const std::string& title) {
	Book book = repoBooks->searchByTitle(title);
	items.add(book);

	this->notify();
}

void ServiceBasket::clearBasket() {
	items.clear();

	this->notify();
}

int ServiceBasket::size() const {
	return items.booksNumber();
}

vector<Book> ServiceBasket::getAll() const {
	return items.getAll();
}

void ServiceBasket::generateBasket(const int number) {
	if (repoBooks->booksNumber() == 0) {
		throw(ServiceError("Nu exista carti in biblioteca!\n"));
	}

	if (number < 0) {
		throw(ServiceError("Numar invalid!\n"));
	}

	for (int i = 0; i < number; i++) {
		std::mt19937 mt{ std::random_device{}() };
		std::uniform_int_distribution<> dist(0, repoBooks->booksNumber() - 1);
		int randNr = dist(mt);

		items.add(repoBooks->getBook(randNr));
	}

	this->notify();
}

void ServiceBasket::exportBasket(std::string fileName, const int fileType) {
	if (fileType == 0) {
		fileName += ".cvs";
	}

	else if (fileType == 1) {
		fileName += ".html";
	}

	else {
		throw(ServiceError("Tip fisier invalid!\n"));
	}

	std::ofstream fout(fileName);

	auto books = items.getAll();
	for (auto book : books) {
		fout << book.toString() << "\n";
	}

	fout.close();
}

void testAddClearBasket() {
	auto basket = RepoBasket();
	assert(basket.booksNumber() == 0);

	Book a = Book("Wanna go home", "Nobody", "Confession", 2001);
	Book b = Book("No longer human", "Osamu Dazai", "Psychological", 1989);

	Repository* repo = new InMemoryRepo();
	repo->add(a);
	repo->add(b);

	auto serv = ServiceBasket(basket, repo);

	serv.addInBasket("Wanna go home");
	serv.addInBasket("No longer human");
	assert(serv.getAll().size() == 2);
	assert(basket.getBook(0) == a);
	assert(basket.getBook(1) == b);

	try {
		serv.addInBasket("Title");
		assert(false);
	}
	catch (RepositoryError error) {
		assert(true);
	}

	serv.clearBasket();
	assert(serv.size() == 0);

	delete repo;
}

void testGenerateBasket() {
	auto basket = RepoBasket();
	assert(basket.booksNumber() == 0);

	Book a = Book("Wanna go home", "Nobody", "Confession", 2001);
	Book b = Book("No longer human", "Osamu Dazai", "Psychological", 1989);
	Book c = Book("Mr. Bottle", "Mamma Mia", "Comedy", 2001);
	Book d = Book("No more donuts", "Marge Simpson", "Thriller", 2001);
	Book e = Book("My wife", "Mary Poppins", "Fantasy", 1999);

	auto repo = new InMemoryRepo();
	repo->add(a);
	repo->add(b);
	repo->add(c);
	repo->add(d);
	repo->add(e);

	auto serv = ServiceBasket(basket, repo);
	serv.generateBasket(9);
	assert(serv.size() == 9);

	serv.generateBasket(2);
	assert(serv.size() == 11);

	serv.clearBasket();
	serv.generateBasket(2);
	assert(serv.size() == 2);

	try {
		serv.generateBasket(-23);
		assert(false);
	}
	catch (ServiceError error) {
		assert(true);
	}

	for (int i = 0; i < 5; i++) {
		repo->remove(0);
	}

	try {
		serv.generateBasket(8);
		assert(false);
	}
	catch (ServiceError error) {
		assert(true);
	}

	delete repo;
}

void testExportBasket() {
	auto basket = RepoBasket();
	Book a = Book("Wanna go home", "Nobody", "Confession", 2001);
	Book b = Book("No longer human", "Osamu Dazai", "Psychological", 1989);

	auto repo = new InMemoryRepo();
	repo->add(a);
	repo->add(b);

	auto serv = ServiceBasket(basket, repo);

	serv.addInBasket("Wanna go home");
	serv.addInBasket("No longer human");

	serv.exportBasket("test", 0);
	std::ifstream fin("test.cvs");
	std::string word;

	fin >> word >> word;
	assert(word == "Wanna");

	fin.close();

	serv.exportBasket("test", 1);
	std::ifstream fin2("test.html");
	
	fin2 >> word >> word;
	assert(word == "Wanna");

	fin2.close();

	try {
		serv.exportBasket("test", 421);
		assert(false);
	}
	catch (ServiceError error) {
		assert(true);
	}

	delete repo;
} 