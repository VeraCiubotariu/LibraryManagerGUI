#include "service.h"
#include <assert.h>
#include <iostream>
#include <fstream>
#include <string.h>
#include "errors.h"
#include <algorithm>

Service::~Service() {
	while (!undoList.empty()) {
		UndoAction* ptr = undoList.top();
		delete ptr;
		undoList.pop();
	}
}

int Service::searchPos(const std::string& title, const std::string& author) const {
	vector<Book> books = repo->getAll();

//	for (int i = 0; i < books.size(); i++) {
//		if (books[i].getTitle() == title && books[i].getAuthor() == author) {
//			return i;
//		}

	auto iterator =  std::find_if(books.begin(), books.end(), [=](const Book& book) {
		if (book.getTitle() == title && book.getAuthor() == author) {
			return 1;
		}
		return 0;
		});

    if (iterator == books.end()) {
	    throw(ServiceError("Carte inexistenta!\n"));
    }

	else {
		return iterator - books.begin();
	}
}

void Service::addService(const std::string& title, const std::string& author, const std::string& genre, const int year) {
	Book book = Book(title, author, genre, year);
	val.validateBook(book);
	bool existent = false;

	try {
		searchByTitleAuthor(title, author);
		existent = true;
	}
	catch (ServiceError error) {
		repo->add(book);
		undoList.push(new UndoAdd{ repo, book });
	}

	if (existent) {
		throw(ServiceError("Carte deja in lista!\n"));
	}

}

const vector<Book> Service::getAllService() const {
	return this->repo->getAll();
}

void Service::modifyService(const std::string& oldTitle, const std::string& oldAuthor, const std::string& newTitle, const std::string& newAuthor, const std::string& newGenre, const int newYear) {
	Book newBook = Book(newTitle, newAuthor, newGenre, newYear);
	Book oldBook = searchByTitleAuthor(oldTitle, oldAuthor);
	val.validateBook(newBook);

	bool exists = false;
	try {
		searchByTitleAuthor(newTitle, newAuthor);
		if (newTitle != oldTitle && newAuthor != oldAuthor) {
			exists = true;
		}
	}
	catch (StandardError& error) {
	}

	if (exists) {
		throw ServiceError("Carte existenta!\n");
	}

	repo->modify(searchPos(oldTitle, oldAuthor), newBook);
	undoList.push(new UndoModify{ repo, newBook, oldBook });
}

void Service::removeService(const std::string& title, const std::string& author) {
	auto book = searchByTitleAuthor(title, author);

	repo->remove(searchPos(title, author));
	undoList.push(new UndoRemove{ repo, book });
}

const Book& Service::searchByTitleAuthor(const std::string& title, const std::string& author) const {
	return repo->getBook(searchPos(title, author));
}

vector<Book> Service::standardFilter(std::function<bool(const Book&)> filterCond) {
	auto books = repo->getAll();
	vector<Book> res;

//	for (int i = 0; i < books.size(); i++) {
//		if (filterCond(books[i])) {
//			res.push_back(books[i]);
//		}
//	}

	auto iterator = std::copy_if(books.begin(), books.end(), std::back_inserter(res), filterCond);
	//res.resize(iterator - res.begin());

	return res;
}

vector<Book> Service::yearFilter(const int year) {
	return standardFilter([=](const Book& book) {
		return book.getYear() == year;
		});
}

vector<Book> Service::titleFilter(const std::string& title){
	return standardFilter([=](const Book& book) {
		return book.getTitle() == title;
		});
}

vector<Book> Service::standardSort(bool(*lessThan)(const Book& b1, const Book& b2)) {
	auto books = repo->getAll();

//	for (int i = 0; i < books.size() - 1; i++) {
//		for (int j = i + 1; j < books.size(); j++) {
//			if (lessThan(books[j], books[i])) {
//				auto aux = books[i];
//				books[i] = books[j];
//				books[j] = aux;
//			}
//		}
//	}

	std::sort(books.begin(), books.end(), lessThan);

	return books;
}

vector<Book> Service::titleSort() {
	return standardSort([](const Book& b1, const Book& b2) {
		return b1.getTitle() < b2.getTitle(); 
		});
}

vector<Book> Service::authorSort() {
	return standardSort([](const Book& b1, const Book& b2) {
		return b1.getAuthor() < b2.getAuthor();
		});
}

vector<Book> Service::yearGenreSort() {
	return standardSort([](const Book& b1, const Book& b2) {
		if (b1.getYear() == b2.getYear()) {
			return b1.getGenre() < b2.getGenre();
		}

		return b1.getYear() < b2.getYear();
		});
}

map<std::string, vector<Book>> Service::genreMap() {
	map<std::string, vector<Book>> res;
	auto books = repo->getAll();
	vector<Book> emptyVector;

	for (auto book : books) {
		auto key = book.getGenre();
		res[key].push_back(book);
	}

	return res;
}

void Service::exportBooks(std::string fileName, const int fileType) {
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

	auto books = repo->getAll();
	for (auto book : books) {
		fout << book.toString() << "\n";
	}

	fout.close();
}

void Service::undoService() {
	if (undoList.empty()) {
		throw ServiceError("Nu mai exista operatii!\n");
	}

	UndoAction* undo = undoList.top();
	undo->doUndo();
	delete undo;
	undoList.pop();
}

void testAdd() {
	TList undoList;
	Repository* repo = new InMemoryRepo();
	Validator val = Validator();
	Service serv = Service(undoList, repo, val);

	assert(repo->booksNumber() == 0);

	serv.addService("My life", "Nobody", "Confession", 2001);
	assert(repo->booksNumber() == 1);
	assert(repo->getBook(0).getTitle() == "My life");

	serv.addService("No longer human", "Osamu Dazai", "Psychological", 1989);
	assert(repo->booksNumber() == 2);
	assert(repo->getBook(1).getYear() == 1989);

	assert(serv.getAllService().size() == 2);

	try {
		serv.addService("", "", "", -90);
		assert(false);
	}
	catch (ValidationError error) {
		assert(true);
	}

	try {
		serv.addService("No longer human", "Osamu Dazai", "Psychological", 1999);
		assert(false);
	}
	catch (ServiceError error) {
		assert(true);
	} 

	delete repo;
}

void testModify() {
	TList undoList;
	Repository* repo = new InMemoryRepo();
	Validator val = Validator();
	Service serv = Service(undoList, repo, val);

	serv.addService("My life", "Nobody", "Confession", 2001);
	serv.addService("No longer human", "Osamu Dazai", "Psychological", 1989);

	serv.modifyService("No longer human", "Osamu Dazai", "a", "b", "c", 1000);
	assert(repo->getBook(1) == Book("a", "b", "c", 1000));

	try {
		serv.modifyService("a", "b", "", "", "", 2033);
		assert(false);
	}
	catch (ValidationError& error) {
		assert(true);
	}

	try {
		serv.modifyService("No longer human", "Osamu Dazai", "a", "b", "c", 1000);
		assert(false);
	}
	catch (ServiceError& error) {
		assert(true);
	}

	try {
		serv.modifyService("My life", "Nobody", "a", "b", "c", 1000);
		assert(false);
	}
	catch (ServiceError& error) {
		assert(true);
	}

	delete repo;
}

void testRemove() {
	TList undoList;
	Repository* repo = new InMemoryRepo();
	Validator val = Validator();
	Service serv = Service(undoList, repo, val);

	serv.addService("My life", "Nobody", "Confession", 2001);
	serv.addService("No longer human", "Osamu Dazai", "Psychological", 1989);

	serv.removeService("My life", "Nobody");
	assert(serv.getAllService().size() == 1);
	assert(repo->getBook(0).getTitle() == "No longer human");

	serv.removeService("No longer human", "Osamu Dazai");
	assert(serv.getAllService().size() == 0);

	try {
		serv.removeService("My life", "Nobody");
		assert(false);
	}
	catch (ServiceError& error) {
		assert(error.getMessage() == "Carte inexistenta!\n");
		assert(true);
	}

	delete repo;
}

void testSearch() {
	TList undoList;
	Repository* repo = new InMemoryRepo();
	Validator val = Validator();
	Service serv = Service(undoList, repo, val);

	serv.addService("My life", "Nobody", "Confession", 2001);
	serv.addService("No longer human", "Osamu Dazai", "Psychological", 1989);

	assert(serv.searchByTitleAuthor("My life", "Nobody") == Book("My life", "Nobody", "Confession", 2001));
	assert(serv.searchByTitleAuthor("No longer human", "Osamu Dazai") == Book("No longer human", "Osamu Dazai", "Psychological", 1989));

	try {
		serv.searchByTitleAuthor("Cool Book", "Not so Cool Author");
		assert(false);
	}
	catch (ServiceError error) {
		assert(true);
	}

	delete repo;
}

void testFilters() {
	TList undoList;
	Repository* repo = new InMemoryRepo();
	Validator val = Validator();
	Service serv = Service(undoList, repo, val);

	serv.addService("My life", "Nobody", "Confession", 2001);
	serv.addService("No longer human", "Osamu Dazai", "Psychological", 1989);
	serv.addService("Mr. Bottle", "Mamma Mia", "Comedy", 2001);
	serv.addService("My life", "Marge Simpson", "Thriller", 2001);
	serv.addService("My life", "Mary Poppins", "Fantasy", 1999);

	auto filteredList = serv.yearFilter(2001);
	assert(filteredList.size() == 3);
	assert(filteredList[0].getAuthor() == "Nobody");
	assert(filteredList[2].getAuthor() == "Marge Simpson");

	filteredList = serv.yearFilter(1989);
	assert(filteredList.size() == 1);

	filteredList = serv.yearFilter(2020);
	assert(filteredList.size() == 0); 

	filteredList = serv.titleFilter("My life");
	assert(filteredList.size() == 3);
	assert(filteredList[2].getAuthor() == "Mary Poppins");

	filteredList = serv.titleFilter("No way");
	assert(filteredList.size() == 0);

	delete repo;
}

void testSort() {
	TList undoList;
	Repository* repo = new InMemoryRepo();
	Validator val = Validator();
	Service serv = Service(undoList, repo, val);

	serv.addService("Wanna go home", "Nobody", "Confession", 2001);
	serv.addService("No longer human", "Osamu Dazai", "Psychological", 1989);
	serv.addService("Mr. Bottle", "Mamma Mia", "Comedy", 2001);
	serv.addService("No more donuts", "Marge Simpson", "Thriller", 2001);
	serv.addService("My wife", "Mary Poppins", "Fantasy", 1999);

	auto sortedList = serv.titleSort();
	assert(sortedList.size() == 5);
	assert(sortedList[0].getTitle() == "Mr. Bottle");
	assert(sortedList[1].getTitle() == "My wife");
	assert(sortedList[4].getTitle() == "Wanna go home");

	sortedList = serv.authorSort();
	assert(sortedList[0].getAuthor() == "Mamma Mia");
	assert(sortedList[4].getAuthor() == "Osamu Dazai");

	sortedList = serv.yearGenreSort();
	assert(sortedList[0].getGenre() == "Psychological");
	assert(sortedList[1].getGenre() == "Fantasy");
	assert(sortedList[3].getGenre() == "Confession");

	delete repo;
}

void testGenreMap() {
	TList undoList;
	Repository* repo = new InMemoryRepo();
	Validator val = Validator();
	Service serv = Service(undoList, repo, val);

	serv.addService("Wanna go home", "Nobody", "Comedy", 2001);
	serv.addService("No longer human", "Osamu Dazai", "Psychological", 1989);
	serv.addService("Mr. Bottle", "Mamma Mia", "Comedy", 2001);
	serv.addService("No more donuts", "Marge Simpson", "Thriller", 2001);
	serv.addService("My wife", "Mary Poppins", "Comedy", 1999);
	serv.addService("Great book", "Cool dude", "Psychological", 2021);

	auto map = serv.genreMap();
	assert(map["Comedy"].size() == 3);
	assert(map["Psychological"].size() == 2);
	assert(map["Thriller"].size() == 1);

	delete repo;
}

void testExportBooks() {
	TList undoList;
	Repository* repo = new InMemoryRepo();
	Validator val = Validator();
	Service serv = Service(undoList, repo, val);

	serv.addService("Wanna go home", "Nobody", "Confession", 2001);
	serv.addService("No longer human", "Osamu Dazai", "Psychological", 1989);

	serv.exportBooks("test", 0);
	std::ifstream fin("test.cvs");
	std::string word;

	fin >> word >> word;
	assert(word == "Wanna");

	fin.close();

	serv.exportBooks("test", 1);
	std::ifstream fin2("test.html");

	fin2 >> word >> word;
	assert(word == "Wanna");

	fin2.close();

	try {
		serv.exportBooks("test", 421);
		assert(false);
	}
	catch (ServiceError error) {
		assert(true);
	}

	delete repo;
}

void testUndo() {
	TList undoList;
	Repository* repo = new InMemoryRepo();
	Validator val = Validator();
	Service serv = Service(undoList, repo, val);

	Book a = Book("Wanna go home", "Nobody", "Comedy", 2001);

	serv.addService("Wanna go home", "Nobody", "Comedy", 2001);
	
	serv.addService("No longer human", "Osamu Dazai", "Psychological", 1989);
	serv.undoService();
	assert(repo->booksNumber() == 1);

	serv.modifyService("Wanna go home", "Nobody", "Well done, boy", "Mark Fisher", "Drama", 1989);
	serv.undoService();
	assert(repo->getBook(0) == a);

	serv.removeService("Wanna go home", "Nobody");
	serv.undoService();
	assert(repo->booksNumber() == 1);
	assert(repo->getBook(0) == a);

	serv.undoService();
	assert(repo->booksNumber() == 0);

	try {
		serv.undoService();
		assert(false);
	}
	catch (ServiceError& error) {
		assert(error.getMessage() == "Nu mai exista operatii!\n");
	}

	delete repo;
}