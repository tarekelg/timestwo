#include "NodeController.h"
#include "QueueController.h"
#include <thread>
#include <memory>


NodeController::NodeController() {

	//Initialisieren
	this->qPtr = std::make_unique<QueueController>();

	//status des Programms auf running=true
	setNodesStatus(true);

	//Thread objekte erstellen
	this->t1Ptr = std::make_unique<std::thread>(std::thread(&NodeController::ioNode, this));
	this->t2Ptr = std::make_unique<std::thread>(std::thread(&NodeController::operationNode, this));

}

void NodeController::run() {

	//Beide Nodes bzw.Threads werden gestartet
	this->t1Ptr->join();
	this->t2Ptr->join();


}


//Knoten A kümmert sich um UI Operationen
void NodeController::ioNode() {
	int userInput;
	int output;
	bool inputMode = true;
	std::string message= "Warte auf Eingabe:\n";
	while (getNodesStatus()) {

		while (qPtr->readFromFIFO2(output)) {
			std::cout << "Output: " << output << "\n";
			inputMode = true;
		}
		if (inputMode) {
			std::cout << message;
			std::cin >> userInput;
			if (!std::cin.fail()) {

				if (userInput == 0) {
					setNodesStatus(false);
					qPtr->sendToFIFO1(userInput);
					return;
				}
				qPtr->sendToFIFO1(userInput);
				inputMode = false;
				message = "Warte auf Eingabe:\n";
			}
			else {
				message= "Bitte geben sie eine integer Zahl ein\n";
				std::cin.clear();
				std::cin.ignore(256, '\n');
			}
		}


	}
}


//knoten B kümmert sich um die multiplikation
void NodeController::operationNode() {
	int userInput;
	while (getNodesStatus()) {
		while (qPtr->readFromFIFO1(userInput)) {
			if (userInput == 0) {
				setNodesStatus(false);
				return;
			}
			qPtr->sendToFIFO2(userInput * 2);

		}
	}
}


bool NodeController::checkForInvalidSymbols(std::string input) {
	if (input.find(".") || input.find(";") || input.find("")) {
		return true;
	}
}

