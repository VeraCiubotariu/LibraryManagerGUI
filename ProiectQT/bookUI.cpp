#include <qformlayout.h>
#include <qmessagebox.h>
#include <qdebug.h>
#include <qframe.h>

#include "bookUI.h"
#include "errors.h"

BookUI::~BookUI() {
	for (auto& el : this->cosCRUDWindows) {
		delete el;
	}
}

void BookUI::setupUI(QWidget* widget) {
	this->buttonsVLayout = new QVBoxLayout;
	widget->setWindowTitle("Aplicatia principala");
	widget->resize(1000, 400);
	this->mainHBoxLayout = new QHBoxLayout(widget);
	
	this->booksList = new QListWidget;
	mainHBoxLayout->addWidget(booksList);

	this->titleEdit = new QLineEdit;
	this->authorEdit = new QLineEdit;
	this->genreEdit = new QLineEdit;
	this->yearEdit = new QLineEdit;

	auto formLayout = new QFormLayout;
	formLayout->addRow("Titlu", this->titleEdit);
	formLayout->addRow("Autor", this->authorEdit);
	formLayout->addRow("Gen", this->genreEdit);
	formLayout->addRow("An", this->yearEdit);

	auto leftVBoxLayout = new QVBoxLayout;
	leftVBoxLayout->addLayout(formLayout);

	auto crudLayout = new QHBoxLayout;
	this->addButton = new QPushButton("Adauga");
	this->modifyButton = new QPushButton("Modifica");
	this->removeButton = new QPushButton("Sterge");
	this->undoButton = new QPushButton("Undo");

	crudLayout->addWidget(this->addButton);
	crudLayout->addWidget(this->modifyButton);
	crudLayout->addWidget(this->removeButton);
	crudLayout->addWidget(this->undoButton);
	leftVBoxLayout->addLayout(crudLayout);

	auto sortHBoxLayout = new QHBoxLayout;
	this->sortCBox = new QComboBox;

	this->sortCBox->addItem("dupa titlu");
	this->sortCBox->addItem("dupa autor");
	this->sortCBox->addItem("dupa an si gen");

	this->sortButton = new QPushButton("Sorteaza");
	
	sortHBoxLayout->addWidget(this->sortButton);
	sortHBoxLayout->addWidget(this->sortCBox);
	leftVBoxLayout->addLayout(sortHBoxLayout);

	auto filterHBoxLayout = new QHBoxLayout;
	auto filterLabel = new QLabel("Filtreaza");

	this->filterCBox = new QComboBox();
	this->filterCBox->addItem("dupa titlu");
	this->filterCBox->addItem("dupa an");

	this->filterEdit = new QLineEdit();

	filterHBoxLayout->addWidget(filterLabel);
	filterHBoxLayout->addWidget(this->filterCBox);
	filterHBoxLayout->addWidget(this->filterEdit);
	leftVBoxLayout->addLayout(filterHBoxLayout);

	leftVBoxLayout->addStretch();

	auto basketLabelHBoxLayout = new QHBoxLayout;
	auto basketLabel = new QLabel("Produse in cos: ");
	this->basketBooksNumberLabel = new QLabel("0");
	this->addInBasketButton = new QPushButton("Adauga in cos");
	this->viewBasketButton = new QPushButton("CosCRUDGUI");
	this->viewPaintBasketButton = new QPushButton("CosReadOnlyGUI");

	basketLabelHBoxLayout->addWidget(basketLabel);
	basketLabelHBoxLayout->addWidget(this->basketBooksNumberLabel);
	basketLabelHBoxLayout->addStretch();
	basketLabelHBoxLayout->addWidget(this->addInBasketButton);
	basketLabelHBoxLayout->addWidget(this->viewBasketButton);
	basketLabelHBoxLayout->addWidget(this->viewPaintBasketButton);

	leftVBoxLayout->addLayout(basketLabelHBoxLayout);

	mainHBoxLayout->addLayout(leftVBoxLayout);

	auto line = new QFrame();
	line->setFrameShape(QFrame::VLine);
    this->mainHBoxLayout->addWidget(line);
	
	auto genresLabel = new QLabel("Genuri:");
	this->buttonsVLayout->addStretch();
	this->buttonsVLayout->addWidget(genresLabel);
	this->mainHBoxLayout->addLayout(this->buttonsVLayout);

	this->populateList(serv.getAllService());
	this->createGenreButtons();
	this->connect();
}

void BookUI::populateList(vector<Book> books) {
	this->booksList->clear();
	for (auto& book : books) {
		std::string res = book.getTitle() + " - " + book.getAuthor();
		QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(res), this->booksList);
	}

	this->booksVector = books;

	emit this->listChanged();
}

int BookUI::selectedIndex() {
	auto index = this->booksList->selectionModel()->currentIndex();
	return index.row();
}

void BookUI::createGenreButtons() {
	auto genres = this->serv.genreMap();
	for (auto el : buttons) {
		delete el;
	}
	this->buttons.clear();

	for (auto el : genres) {
		auto button = new QPushButton(QString::fromStdString(el.first), this);
		QObject::connect(button, &QPushButton::clicked,
			[el]() {
				auto number = new QLabel(QString::fromStdString(std::to_string(el.second.size())));
				number->show();
			});
		this->buttons.push_back(button);

		this->buttonsVLayout->addWidget(button);
	}
}

void BookUI::connect() {
	//shows the info of the selected book
	QObject::connect(this->booksList, &QListWidget::itemSelectionChanged,
		[this]() {
			int index = this->selectedIndex();
			auto selectedBook = this->booksVector[index];
			
			this->titleEdit->setText(QString::fromStdString(selectedBook.getTitle()));
			this->authorEdit->setText(QString::fromStdString(selectedBook.getAuthor()));
			this->genreEdit->setText(QString::fromStdString(selectedBook.getGenre()));
			this->yearEdit->setText(QString::fromStdString(std::to_string(selectedBook.getYear())));
		});

	//the add button
	QObject::connect(this->addButton, &QPushButton::clicked,
		[this]() {
			try {
				auto title = this->titleEdit->text().toStdString();
				auto author = this->authorEdit->text().toStdString();
				auto genre = this->genreEdit->text().toStdString();
				auto year = this->yearEdit->text().toInt();

				this->serv.addService(title, author, genre, year);
				this->populateList(this->serv.getAllService());
			}
			catch (StandardError& error) {
				QMessageBox::warning(this, "Eroare", QString::fromStdString(error.getMessage()));
			}
		});

	//the modify button
	QObject::connect(this->modifyButton, &QPushButton::clicked,
		[this]() {
			auto index = this->selectedIndex();
			if (index == -1) {
				QMessageBox::warning(this, "Eroare", "Nimic nu a fost selectat");
				return;
			}

			auto selectedBook = this->booksVector[index];

			try {
				auto title = this->titleEdit->text().toStdString();
				auto author = this->authorEdit->text().toStdString();
				auto genre = this->genreEdit->text().toStdString();
				auto year = this->yearEdit->text().toInt();

				this->serv.modifyService(selectedBook.getTitle(), selectedBook.getAuthor(), title, author, genre, year);
				this->populateList(this->serv.getAllService());
			}
			catch (StandardError& error) {
				QMessageBox::warning(this, "Eroare", QString::fromStdString(error.getMessage()));
			}
		});

	//the remove button
	QObject::connect(this->removeButton, &QPushButton::clicked,
		[this]() {
			auto index = this->selectedIndex();

			if (index == -1) {
				QMessageBox::warning(this, "Eroare", "Nimic nu a fost selectat");
				return;
			}

			auto selectedBook = this->booksVector[index];

			try {
				this->serv.removeService(selectedBook.getTitle(), selectedBook.getAuthor());
				this->populateList(this->serv.getAllService());
			}
			catch (StandardError& error) {
				QMessageBox::warning(this, "Eroare", QString::fromStdString(error.getMessage()));
			}
		});

	//the undo button
	QObject::connect(this->undoButton, &QPushButton::clicked,
		[this]() {
			try {
				this->serv.undoService();
				this->populateList(this->serv.getAllService());
			}
			catch (StandardError& error) {
				QMessageBox::warning(this, "Eroare", "Nu mai exista actiuni de refacut.");
			}
		});

	//the sort button
	QObject::connect(this->sortButton, &QPushButton::clicked,
		[this]() {
			auto index = this->sortCBox->currentIndex();
			if (index == 0) {
				this->populateList(this->serv.titleSort());
			}

			else if (index == 1) {
				this->populateList(this->serv.authorSort());
			}

			else {
				this->populateList(this->serv.yearGenreSort());
			}
		});

	//the filter edit line
	QObject::connect(this->filterEdit, &QLineEdit::textChanged,
		[this]() {
			auto index = this->filterCBox->currentIndex();
			auto text = this->filterEdit->text();

			if (text.toStdString() == "") {
				this->populateList(this->serv.getAllService());
				return;
			}

			if (index == 0) {
				this->populateList(this->serv.titleFilter(text.toStdString()));
			}

			else{
				this->populateList(this->serv.yearFilter(text.toInt()));
			}
		});

	QObject::connect(this, &BookUI::listChanged,
		[this]() {
			this->createGenreButtons();
		});

	QObject::connect(this->viewBasketButton, &QPushButton::clicked,
		[this]() {
		//	this->basketWidget->show();
			CosCRUDGUI* basketWindow = new CosCRUDGUI(this->servBasket);
			basketWindow->show();
			this->cosCRUDWindows.push_back(basketWindow);
		});

	QObject::connect(this->viewPaintBasketButton, &QPushButton::clicked, 
		[this] {
			CosReadOnlyGUI* newWindow = new CosReadOnlyGUI(this->servBasket);
			newWindow->show();
			this->cosRONLYWindows.push_back(newWindow);
		});

	QObject::connect(this->addInBasketButton, &QPushButton::clicked,
		[this]() {
			auto index = this->selectedIndex();

			if (index == -1) {
				QMessageBox::warning(this, "Eroare", "Nimic nu a fost selectat");
				return;
			}

			auto selectedBook = this->booksVector[index];
			this->servBasket.addInBasket(selectedBook.getTitle());
		});
}

void BookUI::update() {
	this->basketBooksNumberLabel->setText(QString::fromStdString(std::to_string(this->servBasket.size())));
}