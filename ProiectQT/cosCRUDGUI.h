#pragma once
#include <qwidget.h>
#include <qtablewidget.h>
#include <qpushbutton.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <qspinbox.h>

#include "serviceBasket.h"

class CosCRUDGUI :public QWidget, public Observer {
	Q_OBJECT
	QTableWidget* basketTable;
	vector<Book> booksVector;
	ServiceBasket& servBasket;

	QLabel* basketBooksNumberLabel;
	QPushButton* addInBasketButton;
	QPushButton* viewBasketButton;
	QPushButton* clearBasketButton;
	QPushButton* generateBasketButton;
	QSpinBox* generatedNumberSBox;
	QLineEdit* fileNameEdit;
	QPushButton* exportCVSButton;
	QPushButton* exportHTMLButton;

	void setupUI(QWidget* widget);
	void populateTable(vector<Book> books);
	void connect();
	void update() override;

public:
	CosCRUDGUI(ServiceBasket& serv) :servBasket{ serv } {
		this->servBasket.addObserver(this);
		this->setupUI(this);
	};
};