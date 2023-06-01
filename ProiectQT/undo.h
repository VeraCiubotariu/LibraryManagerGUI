#pragma once
#include "book.h"
#include "repository.h"

class UndoAction {
public:
	/// <summary>
	/// Undos the specific operation
	/// </summary>
	virtual void doUndo() = 0;

	/// <summary>
	/// The destructor of the class
	/// </summary>
	virtual ~UndoAction() {};
};

class UndoAdd : public UndoAction {
private:
	Repository* repo;
	Book book;
public:
	UndoAdd(Repository* repo, const Book& book) : repo{ repo }, book{ book }{}
	void doUndo() override;
};

class UndoRemove : public UndoAction {
private:
	Repository* repo;
	Book book;
public:
	UndoRemove(Repository* repo, const Book& book) : repo{ repo }, book{ book }{}
	void doUndo() override;
};

class UndoModify : public UndoAction {
private:
	Repository* repo;
	Book oldBook, newBook;
public:
	UndoModify(Repository* repo, const Book& oldBook, const Book& newBook) :repo{ repo }, oldBook{ oldBook }, newBook{ newBook }{}
	void doUndo() override;
};