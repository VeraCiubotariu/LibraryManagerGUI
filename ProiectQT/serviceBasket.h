#pragma once
#include "repositoryBasket.h"
#include "observer.h"

class ServiceBasket: public Observable {
private:
	RepoBasket& items;
	Repository* repoBooks;

public:
	/// <summary>
	/// The constructor of the class
	/// </summary>
	/// <param name="items"> RepoBasket </param>
	/// <param name="repo"> Repository </param>
	ServiceBasket(RepoBasket& items, Repository* repo) noexcept : items{ items }, repoBooks{ repo }{};

	/// <summary>
	/// Adds the book with the given title in the basket. Raises exception otherwise
	/// </summary>
	/// <param name="title"> string </param>
	/// <raises> RepositoryError, if the book doesn't exist </raises> 
	void addInBasket(const std::string& title);

	/// <summary>
	/// Deletes all the elements in the basket
	/// </summary>
	void clearBasket();

	/// <summary>
	/// Generates a basket with the given number of random books
	/// </summary>
	/// <param name="number"> int </param>
	/// <raises> ServiceError, if there aren't any books in the library
	///                        or if the number < 0 </raises>
	void generateBasket(const int number);

	/// <summary>
	/// Returns the number of books in the basket
	/// </summary>
	/// <returns></returns>
	int size() const;

	/// <summary>
	/// Returns all the books from the basket
	/// </summary>
	/// <returns></returns>
	vector<Book> getAll() const;

	/// <summary>
	/// Exports the basket into fileName.cvs if fileType = 0, 
	///                 or into fileName.html if fileType = 1
	/// </summary>
	/// <param name="fileName"> string </param>
	/// <param name="fileType"> int </param>
	/// <raises> ServiceError, if fileType != 0 or fileType != 1 </raises>
	void exportBasket(std::string fileName, const int fileType);
};

void testAddClearBasket();
void testGenerateBasket();
void testExportBasket(); 