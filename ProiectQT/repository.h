#pragma once
#include <vector>
using std::vector;
#include "book.h"

class Repository {
public:
	virtual ~Repository() {};

	/// <summary>
	/// Adds the book to the list
	/// </summary>
	/// <param name="book"> Book </param>
	virtual void add(const Book& book) = 0;

	/// <summary>
	/// Changes the book from the pos position in the list with newBook
	/// </summary>
	/// <param name="pos"> int </param>
	/// <param name="newBook"> Book </param>
	virtual void modify(const int pos, const Book& newBook) = 0;

	/// <summary>
	/// Removes the book from the position pos from the list
	/// </summary>
	/// <param name="pos"> int </param>
	virtual void remove(const int pos) = 0;

	/// <summary>
	/// Returns the number of books in the list
	/// </summary>
	/// <returns> int </returns>
	virtual int booksNumber() = 0;

	/// <summary>
	/// Returns the book with the given title from the list
	/// </summary>
	/// <param name="pos"> int </param>
	/// <returns> Book </returns>
	virtual const Book& getBook(const int pos) = 0;

	/// <summary>
	/// Returns the position of the given book
	/// </summary>
	/// <param name="book"> Book </param>
	/// <returns></returns>
	virtual int getBookPos(const Book& book) = 0;

	/// <summary>
	/// Returns all the books from the list
	/// </summary>
	/// <returns> vector<Book> </returns>
	virtual vector<Book> getAll() = 0;

	/// <summary>
	/// Returns the book with the given title. Raises exception if the book doesn't exist
	/// </summary>
	/// <param name="title"> string </param>
	/// <returns> Book </returns>
	/// <raises> RepositoryError, if the book doesn't exist </raises>
	virtual const Book& searchByTitle(const std::string& title) = 0;
};