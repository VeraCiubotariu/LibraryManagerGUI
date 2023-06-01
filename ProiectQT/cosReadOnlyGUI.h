#pragma once
#include "serviceBasket.h"

#include <qwidget.h>
#include <qpainter.h>

class CosReadOnlyGUI: public QWidget, public Observer {
	Q_OBJECT
	ServiceBasket& servBasket;

	void paintEvent(QPaintEvent* ev) override;
	void update() override;
	double generateRandomNumber(double min, double max) const;

public:
	CosReadOnlyGUI(ServiceBasket& serv) :servBasket{ serv } {
		this->servBasket.addObserver(this);
	};
};