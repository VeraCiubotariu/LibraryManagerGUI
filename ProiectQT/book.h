#pragma once
#include <string>

class Book {
private:
	std::string title;
	std::string author;
	std::string genre;
	int year;

public:
	/// <summary>
	/// The constructor of the class
	/// </summary>
	/// <param name="title"> string </param>
	/// <param name="author"> string </param>
	/// <param name="genre"> string </param>
	/// <param name="year"> int </param>
	Book(const std::string& title, const std::string& author, const std::string& genre, const int year);

	/// <summary>
	/// The default constructor of the class
	/// </summary>
	Book();

	/// <summary>
	/// Copy constructor
	/// </summary>
	/// <param name="book"></param>
	Book(const Book& book);

	/// <summary>
	/// Verifies if the given book is equal to this book
	/// </summary>
	/// <param name="book"> Book </param>
	/// <returns> True, if the books are equal 
	///           False, otherwise </returns>
	bool operator == (const Book& book) const;

	/// <summary>
	/// Converts the Book object to a string with the format "Titlu: title\nAutor: author\nGen: genre\nAn: year\n\n"
	/// </summary>
	/// <returns> string </returns>
	std::string toString() const;

	/// <summary>
	/// Returns the title of the book
	/// </summary>
	/// <returns> string </returns>
	const std::string getTitle() const;

	/// <summary>
	/// Returns the author of the book
	/// </summary>
	/// <returns> string </returns>
	const std::string getAuthor() const;

	/// <summary>
	/// Returns the genre of the book
	/// </summary>
	/// <returns> string </returns>
	const std::string getGenre() const;

	/// <summary>
	/// Returns the year of release of the book
	/// </summary>
	/// <returns></returns>
	int getYear() const;

	/// <summary>
	/// Changes the title of the book to newTitle
	/// </summary>
	/// <param name="newTitle"> string </param>
	void setTitle(const std::string& newTitle);

	/// <summary>
	/// Changes the author of the book to newAuthor
	/// </summary>
	/// <param name="newAuthor"> string </param>
	void setAuthor(const std::string& newAuthor);

	/// <summary>
	/// Changes the genre of the book to newGenre
	/// </summary>
	/// <param name="newGenre"> string </param>
	void setGenre(const std::string& newGenre);

	/// <summary>
	/// Changes the year of release of the book to newYear
	/// </summary>
	/// <param name="newYear"> int </param>
	void setYear(const int newYear);
};

void testBook();