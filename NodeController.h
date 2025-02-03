#pragma once
#include <boost/lockfree/queue.hpp>
#include <atomic>
#include <thread>
#include "QueueController.h"
#include <iostream>
#include <string>


class NodeController {

public:
	
	
	NodeController(void);
	void run();

	////getter um Nodes status abzufragen
	bool getNodesStatus(void) {
		return running;
	};


	////setter um running zu verändern
	void setNodesStatus(bool state) {
		running = state;
	};

private:
	std::atomic<bool> running; //Variable checked ob programm noch laufen soll
	std::unique_ptr <std::thread> t1Ptr;
	std::unique_ptr <std::thread> t2Ptr;
	std::unique_ptr <QueueController> qPtr;

	void ioNode();
	void operationNode();

	bool checkForInvalidSymbols(std::string);
};
