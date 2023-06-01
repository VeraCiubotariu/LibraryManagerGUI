#pragma once
#include <vector>

class Observer {
public:
	/// <summary>
	/// Invoked when the observable object notifies
	/// </summary>
	virtual void update() = 0;
};

class Observable {
private:
	std::vector<Observer*> observers;

public:
	/// <summary>
	/// Adds an observer to the list
	/// </summary>
	/// <param name="obs"></param>
	void addObserver(Observer* obs);

	/// <summary>
	/// Removes an observer from the list
	/// </summary>
	/// <param name="obs"></param>
	void removeObserver(Observer* obs);

protected:
	/// <summary>
	/// Notifies all the observers
	/// </summary>
	void notify();
};