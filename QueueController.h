#include "QueueController.h"
#include <iostream>


// Konstruktor
QueueController::QueueController()
	: ptrF1(std::make_unique<boost::lockfree::queue<int>>(100)),
	ptrF2(std::make_unique<boost::lockfree::queue<int>>(100)) { 

	
}

//Sendet neuen Wert an FIFO1
bool QueueController::sendToFIFO1(int input) {
	if (!ptrF1) {
		std::cerr << "Error: ptrF1 is null in readFromFIFO1!" << std::endl;
		return false;
	}
	return ptrF1->push(input);
};

//Sendet neuen Wert an FIFO^2
bool QueueController::sendToFIFO2(int input) {
	if (!ptrF2) {
		std::cerr << "Error: ptrF1 is null in readFromFIFO1!" << std::endl;
		return false;
	}
	return ptrF2->push(input);
};

//Liest Wert aus FIFO1
bool QueueController::readFromFIFO1(int& value) {
	if (!ptrF1) {
		std::cerr << "Error: ptrF1 is null in readFromFIFO1!" << std::endl;
		return false;
	}
	return ptrF1->pop(value);
}

//Liest Wert aus FIFO2
bool QueueController::readFromFIFO2(int& value) {
	if (!ptrF2) {
		std::cerr << "Error: ptrF1 is null in readFromFIFO1!" << std::endl;
		return false;
	}
	return ptrF2->pop(value);
}

//Prüft ob FIFO1 leer ist
bool QueueController::checkIfFIFOEmpty1() {
	if (!ptrF1) {
		std::cerr << "Error: ptrF1 is null in readFromFIFO1!" << std::endl;
		return false;
	}
	return ptrF1->empty();
}

//Prüft ob FIFO2 leer ist
bool QueueController::checkIfFIFOEmpty2() {
	return ptrF2->empty();
}

// Destructor
QueueController::~QueueController() {
	int value;

	// FIFO1 leeren
	while (readFromFIFO1(value))
		;

	// FIFO2 leeren
	while (readFromFIFO2(value))
		;
}
