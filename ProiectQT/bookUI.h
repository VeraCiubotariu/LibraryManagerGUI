#pragma once
#include <qwidget.h>
#include <qlistwidget.h>
#include <qlineedit.h>
#include <qpushbutton.h>
#include <qcombobox.h>
#include <qboxlayout.h>
#include <qlabel.h>
#include <qtablewidget.h>
#include <qspinbox.h>

#include "service.h"
#include "serviceBasket.h"
#include "cosCRUDGUI.h"
#include "cosReadOnlyGUI.h"

class BookUI : public QWidget, public Observer {
	Q_OBJECT
	vector<QPushButton*> buttons;

	QHBoxLayout* mainHBoxLayout;
	QVBoxLayout* buttonsVLayout;
	QListWidget* booksList;
	
	QLineEdit* titleEdit;
	QLineEdit* authorEdit;
	QLineEdit* genreEdit;
	QLineEdit* yearEdit;

	QPushButton* addButton;
	QPushButton* modifyButton;
	QPushButton* removeButton;
	QPushButton* undoButton;

	QPushButton* sortButton;
	QComboBox* sortCBox;

	QLineEdit* filterEdit;
	QComboBox* filterCBox;

	QLabel* basketBooksNumberLabel;
	QPushButton* addInBasketButton;
	QPushButton* viewBasketButton;
	QPushButton* viewPaintBasketButton;

	vector<Book> booksVector;
	Service& serv;
	ServiceBasket& servBasket;

	QTableWidget* basketTable;
	vector<CosCRUDGUI*> cosCRUDWindows;
	vector<CosReadOnlyGUI*> cosRONLYWindows;

	void setupUI(QWidget* widget);

	void populateList(vector<Book> elems);

	int selectedIndex();

	void connect();

	void createGenreButtons();

	void update() override;

signals:
	void listChanged();

public:
	BookUI(Service& serv, ServiceBasket& servBasket) : serv{ serv }, servBasket { servBasket }{
		this->servBasket.addObserver(this);
		setupUI(this);
	}

	~BookUI();
};