#pragma once
#include "book.h"

class Validator {
public:
	/// <summary>
	/// Checks if the given book is valid
	/// </summary>
	/// <param name="book"></param>
	/// <raises> ValidationError, if the book isn't valid </raises>
	void validateBook(const Book& book);
};

void testValidator();