#include "cosReadOnlyGUI.h"
#include <random>

double CosReadOnlyGUI::generateRandomNumber(double min, double max) const {
	std::mt19937 mt{ std::random_device{}() };
	std::uniform_real_distribution<> dist(min, max);
	return dist(mt);
}

void CosReadOnlyGUI::paintEvent(QPaintEvent* ev) {
	QPainter p{ this };

	double x = this->generateRandomNumber(0, this->width());
	double y = this->generateRandomNumber(0, this->height());

	for (auto& el : this->servBasket.getAll()) {
		double width = this->generateRandomNumber(10, 50);
		double height = this->generateRandomNumber(10, 50);

		p.drawRect(x, y, width, height);
		

		x = this->generateRandomNumber(0, this->width() - width - 5);
		y = this->generateRandomNumber(0, this->height() - height - 5);
	}
}

void CosReadOnlyGUI::update() {
	repaint();
}