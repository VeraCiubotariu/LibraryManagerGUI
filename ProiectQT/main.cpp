#include <QtWidgets/QApplication>
#include <qlabel.h>

#include "bookUI.h"
#include "ProiectQT.h"
#include "cosCRUDGUI.h"

void runTests() {
	testValidator();

	testBook();
	testInMemoryRepo();
	testFileRepo();

	testAdd();
	testModify();
	testRemove();
	testSearch();
	testFilters();
	testSort();
	testGenreMap();
	testExportBooks();
	testUndo();

	//teste basket
	testAddClearBasket();
	testGenerateBasket();
	testExportBasket();
}

int main(int argc, char* argv[]) {
	runTests();

	auto repo = new InMemoryRepo();
//	auto repo = new FileRepo("app.txt");

	auto repoBasket = RepoBasket();
	auto val = Validator();
	TList undos;
	auto service = Service(undos, repo, val);
	auto serviceBasket = ServiceBasket(repoBasket, repo);
	
	service.addService("No longer human", "Osamu Dazai", "Psychological", 1948);
	service.addService("Berserk", "Kentaro Miura", "Fantasy", 1989);
	service.addService("Hellsing", "Kouta Hirano", "Fantasy", 1994);
	service.addService("Chainsaw Man", "Tatsuki Fujimoto", "Fantasy", 2018);
	service.addService("Monster", "Naoki Urasawa", "Psychological", 1994);

	QApplication a(argc, argv);
	QApplication::setFont(QFont("Serif", 10));
	BookUI ui{ service, serviceBasket };
	ui.show();

	return QApplication::exec();
}

