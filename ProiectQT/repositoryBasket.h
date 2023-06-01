#pragma once
#include "InMemoryRepo.h"

class RepoBasket :public InMemoryRepo {
public:
	/// <summary>
	/// Deletes all the books from the basket
	/// </summary>
	void clear() {
		books.clear();
	}
}; 