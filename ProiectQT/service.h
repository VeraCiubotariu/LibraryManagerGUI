#pragma once
#include "InMemoryRepo.h"
#include "FileRepo.h"
#include "validator.h"
#include <functional>
#include <map>
#include <stack>
#include "undo.h"
using std::map;
typedef std::stack<UndoAction*> TList;

class Service {
private:
	TList& undoList;
	Repository* repo;
	Validator& val;

public:
	/// <summary>
	/// The constructor of the class
	/// </summary>
	/// <param name="books"> Repository </param>
	/// <param name="val"> Validator </param>
	Service(TList& undoList, Repository* books, Validator& val) noexcept : repo{ books }, val{ val }, undoList{ undoList }{
	};

	/// <summary>
	/// The destructor of the class
	/// </summary>
	~Service();

	/// <summary>
	/// Returns the list of books
	/// </summary>
	/// <returns> vector<Book> </returns>
	const vector<Book> getAllService() const;

	/// <summary>
	/// Searches the book with the given title and author and returns its position in the list
	/// </summary>
	/// <param name="title"> string </param>
	/// <param name="author"> string </param>
	/// <returns> int </returns>
	/// <raises> ServiceError, if the book doesn't exist </raises>
	int searchPos(const std::string& title, const std::string& author) const;

	/// <summary>
	/// Adds the book with the given properties to the list
	/// </summary>
	/// <param name="title"> string </param>
	/// <param name="author"> string </param>
	/// <param name="genre"> string </param>
	/// <param name="year"> int </param>
	/// <raises> ValidationError, if the book isn't valid
	///          ServiceError, if the book already exists </raises>
	void addService(const std::string& title, const std::string& author, const std::string& genre, const int year);

	/// <summary>
	/// Modifies the properties of the given book with the new ones
	/// </summary>
	/// <param name="oldTitle"> string </param>
	/// <param name="oldAuthor"> string </param>
	/// <param name="newTitle"> string </param>
	/// <param name="newAuthor"> string </param>
	/// <param name="newGenre"> string </param>
	/// <param name="newYear"> int </param>
	/// <raises> ValidationError, if the new book isn't valid
	///          ServiceError, if the book doesn't exist </raises>
	void modifyService(const std::string& oldTitle, const std::string& oldAuthor, const std::string& newTitle, const std::string& newAuthor, const std::string& newGenre, const int newYear);

	/// <summary>
	/// Removes the books with the given title from the list
	/// </summary>
	/// <param name="title"> string </param>
	/// <param name="author"> string </param>
	/// <raises> ServiceError, if the book doesn't exist </raises>
	void removeService(const std::string& title, const std::string& author);

	/// <summary>
	/// Searches the book with the given title and author in the list and returns it
	/// </summary>
	/// <param name="title"> string </param>
	/// <param name="author"> string </param>
	/// <returns> Book </returns>
	/// <raises> ServiceError, if the book doesn't exist </raises>
	const Book& searchByTitleAuthor(const std::string& title, const std::string& author) const;

	/// <summary>
	/// Filters the list of books by the given parameter
	/// </summary>
	/// <param name="filterCond"> function </param>
	/// <returns> vector<Book> </returns>
	vector<Book> standardFilter(std::function <bool(const Book&)> filterCond);

	/// <summary>
	/// Filters the list of books by the given year
	/// </summary>
	/// <param name="year"> T </param>
	/// <returns> vector<Book> </returns>
	vector<Book> yearFilter(const int year);

	/// <summary>
	/// Filters the list of books by the given title
	/// </summary>
	/// <param name="title"> string </param>
	/// <returns> vector<Book> </returns>
	vector<Book> titleFilter(const std::string& title);

	/// <summary>
	/// Sorts the list of books, depending on the compare function (lessThan)
	/// </summary>
	/// <param name="lessThan"> function </param>
	/// <returns> vector<Book> </returns>
	vector<Book> standardSort(bool(*lessThan)(const Book& b1, const Book& b2));

	/// <summary>
	/// Sorts the list of books by their titles
	/// </summary>
	/// <returns> vector<Book> </returns>
	vector<Book> titleSort();

	/// <summary>
	/// Sorts the list of books by their author
	/// </summary>
	/// <returns> vector<Book> </returns>
	vector<Book> authorSort();

	/// <summary>
	/// Sorts the list of books by their year of release and, if equal, by their genre
	/// </summary>
	/// <returns></returns>
	vector<Book> yearGenreSort();

	map<std::string, vector<Book>> genreMap();

	/// <summary>
	/// Exports all the books into fileName.cvs if fileType = 0, 
	///                    or into fileName.html if fileType = 1
	/// </summary>
	/// <param name="fileName"> string </param>
	/// <param name="fileType"> int </param>
	/// <raises> ServiceError, if fileType != 0 or fileType != 1 </raises>
	void exportBooks(std::string fileName, const int fileType);

	/// <summary>
	/// Undos the last operation
	/// </summary>
	/// <raises> ServiceError, if the undoList is empty </raises>
	void undoService();
};

void testAdd();
void testModify();
void testRemove();
void testSearch();
void testFilters();
void testSort();
void testGenreMap();
void testExportBooks();
void testUndo();