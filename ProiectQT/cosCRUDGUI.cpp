#include <qboxlayout.h>
#include <qmessagebox.h>

#include "cosCRUDGUI.h"

void CosCRUDGUI::setupUI(QWidget* widget){
	this->resize(1000, 400);
	this->setWindowTitle("CosCRUDGUI");

	auto basketMainHLayout = new QHBoxLayout(this);
	this->basketTable = new QTableWidget;
	this->basketTable->setColumnCount(4);

	this->basketTable->setHorizontalHeaderLabels(QStringList() << "Titlu" << "Autor" << "Gen" << "An");
	basketMainHLayout->addWidget(this->basketTable);

	auto basketButtonsVLayout = new QVBoxLayout;

	this->clearBasketButton = new QPushButton("Sterge cos");
	basketButtonsVLayout->addWidget(this->clearBasketButton);

	auto generateBasketHLayout = new QHBoxLayout;
	this->generateBasketButton = new QPushButton("Genereaza cos");
	this->generatedNumberSBox = new QSpinBox();

	generateBasketHLayout->addWidget(this->generateBasketButton);
	generateBasketHLayout->addWidget(this->generatedNumberSBox);
	basketButtonsVLayout->addLayout(generateBasketHLayout);

	auto exportBasketHLayout = new QHBoxLayout;
	auto exportBasketLabel = new QLabel("Exporta cos: ");
	this->fileNameEdit = new QLineEdit("numele_fisierului");
	this->exportCVSButton = new QPushButton("CVS");
	this->exportHTMLButton = new QPushButton("HTML");

	exportBasketHLayout->addWidget(exportBasketLabel);
	exportBasketHLayout->addWidget(this->fileNameEdit);
	exportBasketHLayout->addWidget(this->exportCVSButton);
	exportBasketHLayout->addWidget(this->exportHTMLButton);
	basketButtonsVLayout->addLayout(exportBasketHLayout);

	basketMainHLayout->addLayout(basketButtonsVLayout);

	this->populateTable(servBasket.getAll());
	this->connect();
}

void CosCRUDGUI::populateTable(vector<Book> books) {
	auto size = this->basketTable->rowCount();

	for (int i = size - 1; i >= 0; i--) {
		this->basketTable->removeRow(i);
	}

	int i = 0;
	for (auto& book : books) {
		auto title = new QTableWidgetItem(QString::fromStdString(book.getTitle()));
		auto author = new QTableWidgetItem(QString::fromStdString(book.getAuthor()));
		auto genre = new QTableWidgetItem(QString::fromStdString(book.getGenre()));
		auto year = new QTableWidgetItem(QString::fromStdString(std::to_string(book.getYear())));

		this->basketTable->insertRow(i);

		this->basketTable->setItem(i, 0, title);
		this->basketTable->setItem(i, 1, author);
		this->basketTable->setItem(i, 2, genre);
		this->basketTable->setItem(i, 3, year);

		i++;
	}
}

void CosCRUDGUI::connect() {
	QObject::connect(this->clearBasketButton, &QPushButton::clicked,
		[this]() {
			this->servBasket.clearBasket();
		});

	QObject::connect(this->generateBasketButton, &QPushButton::clicked,
		[this]() {
			int booksNumber = this->generatedNumberSBox->value();
			this->servBasket.generateBasket(booksNumber);
		});

	QObject::connect(this->exportCVSButton, &QPushButton::clicked,
		[this]() {
			auto fileName = this->fileNameEdit->text().toStdString();
			if (fileName == "") {
				QMessageBox::warning(this, "Eroare", "Numele fisierului invalid");
				return;
			}

			this->servBasket.exportBasket(fileName, 0);
		});

	QObject::connect(this->exportHTMLButton, &QPushButton::clicked,
		[this]() {
			auto fileName = this->fileNameEdit->text().toStdString();
			if (fileName == "") {
				QMessageBox::warning(this, "Eroare", "Numele fisierului invalid");
				return;
			}

			this->servBasket.exportBasket(fileName, 1);
		});
}

void CosCRUDGUI::update(){
	this->populateTable(this->servBasket.getAll());
}