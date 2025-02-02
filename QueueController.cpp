#include "QueueController.h"
#include <iostream>


// Konstruktor
QueueController::QueueController()
	: ptrF1(std::make_unique<boost::lockfree::queue<int>>(100)),
	ptrF2(std::make_unique<boost::lockfree::queue<int>>(100)),
	running(true) { // running wird auf true gesetzt

	
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

//Knoten A kümmert sich um UI Operationen
void QueueController::NodeA() {
	int userInput;
	int output;
	bool inputMode=true;
	while (this->getNodesStatus()) {

		while (this->readFromFIFO2(output)) {
			std::cout << "Output: " << output << "\n";
			inputMode = true;
		}
		if (inputMode) {
			std::cout << "Warte auf Eingabe:\n";
			std::cin >> userInput;
			if (userInput == 0) {
				this->setNodesStatus(false);
				this->sendToFIFO1(userInput);
				return;
			}
			this->sendToFIFO1(userInput);
			inputMode = false;
		}


	}
}


//knoten B kümmert sich um die multiplikation
void QueueController::NodeB() {
	int userInput;
	while (this->getNodesStatus()) {
		while (this->readFromFIFO1(userInput)) {
			if (userInput == 0) {
				this->setNodesStatus(false);
				return;
			}
			this->sendToFIFO2(userInput * 2);
	
		}
	}

	//try catch einfügen when etwas schief läuft weil könnte fehlerhaft sein wenn sich noch etwas in fifo1 befindet
	while (this->readFromFIFO1(userInput)){
		this->sendToFIFO2(userInput * 2);
	}
}

void QueueController::menu(){
	std::cout << "Willkommen, dieses Programm multipliziert ihre Eingabe mit 2.\n 0: zum beenden des Programms.\n";
}

bool QueueController::checkInput(int input) {
	
	std::cout << "Checking input...";
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
