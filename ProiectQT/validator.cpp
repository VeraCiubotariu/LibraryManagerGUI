#include "validator.h"
#include "book.h"
#include "errors.h"
#include <assert.h>

void Validator::validateBook(const Book& book) {
	if (book.getTitle() == "") {
		throw(ValidationError("Titlu invalid!\n"));
	}

	else if (book.getAuthor() == "") {
		throw(ValidationError("Autor invalid!\n"));
	}

	else if (book.getGenre() == "") {
		throw(ValidationError("Gen invalid!\n"));
	}

	else if (book.getYear() < 0) {
		throw(ValidationError("An invalid!\n"));
	}
}

void testValidator() {
	Book a = Book("No longer human", "Osamu Dazai", "Psychological", 1987);
	Validator val = Validator();

	val.validateBook(a);

	Book b = Book("No longer human", "Osamu Dazai", "Psychological", -89);
	try {
		val.validateBook(b);
		assert(false);
	}
	catch (ValidationError error) {
		assert(true);
	}

	Book c = Book("No longer human", "Osamu Dazai", "", 1989);
	try {
		val.validateBook(c);
		assert(false);
	}
	catch (ValidationError error) {
		assert(true);
	}

	Book d = Book("No longer human", "", "Psychological", 1989);
	try {
		val.validateBook(d);
		assert(false);
	}
	catch (ValidationError error) {
		assert(true);
	}

	Book e = Book("", "Osamu Dazai", "Psychological", 1989);
	try {
		val.validateBook(e);
		assert(false);
	}
	catch (ValidationError error) {
		assert(true);
	}
}