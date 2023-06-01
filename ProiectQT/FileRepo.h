#pragma once
#include "repository.h"

class FileRepo : public Repository {
private:
	vector<Book> books;
	std::string fileName = "file";

public:
	FileRepo(std::string fileName) :fileName{ fileName } {};

	void readAllFromFile();

	void writeAllToFile();

	/// <summary>
	/// Adds the book to the list
	/// </summary>
	/// <param name="book"> Book </param>
	void add(const Book& book) override;

	/// <summary>
	/// Changes the book from the pos position in the list with newBook
	/// </summary>
	/// <param name="pos"> int </param>
	/// <param name="newBook"> Book </param>
	void modify(const int pos, const Book& newBook) override;

	/// <summary>
	/// Removes the book from the position pos from the list
	/// </summary>
	/// <param name="pos"> int </param>
	void remove(const int pos) override;

	/// <summary>
	/// Returns the number of books in the list
	/// </summary>
	/// <returns> int </returns>
	int booksNumber() override;

	/// <summary>
	/// Returns the book with the given title from the list
	/// </summary>
	/// <param name="pos"> int </param>
	/// <returns> Book </returns>
	const Book& getBook(const int pos) override;

	/// <summary>
	/// Returns the position of the given book
	/// </summary>
	/// <param name="book"> Book </param>
	/// <returns></returns>
	int getBookPos(const Book& book) override;

	/// <summary>
	/// Returns all the books from the list
	/// </summary>
	/// <returns> vector<Book> </returns>
	vector<Book> getAll() override;

	/// <summary>
	/// Returns the book with the given title. Raises exception if the book doesn't exist
	/// </summary>
	/// <param name="title"> string </param>
	/// <returns> Book </returns>
	/// <raises> RepositoryError, if the book doesn't exist </raises>
	const Book& searchByTitle(const std::string& title) override;
};

void testFileRepo();
