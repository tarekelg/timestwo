#include "NodeController.h"
#include "QueueController.h"
//#include "Nodes.h"
#include <thread>
#include <memory>


NodeController::NodeController() {
	//Thread Objekte werden erstellt

	auto qControl = std::make_shared<QueueController>();

	this->t1Ptr = std::make_unique<std::thread>(std::thread(&QueueController::NodeA, qControl));
	this->t2Ptr = std::make_unique<std::thread>(std::thread(&QueueController::NodeB, qControl));

}

void NodeController::run() {

	//Threads werden gestartet
	this->t1Ptr->join();
	this->t2Ptr->join();


}