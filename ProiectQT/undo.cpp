#include "undo.h"

void UndoAdd::doUndo() {
	int pos = repo->getBookPos(book);
	repo->remove(pos);
}

void UndoRemove::doUndo() {
	repo->add(book);
}

void UndoModify::doUndo() {
	int pos = repo->getBookPos(oldBook);
	repo->modify(pos, newBook);
}