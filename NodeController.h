#pragma once
#include <boost/lockfree/queue.hpp>
#include <atomic>
#include <thread>


class NodeController {

public:
	
	
	NodeController(void);
	void run();

private:

	std::unique_ptr <std::thread> t1Ptr;
	std::unique_ptr <std::thread> t2Ptr;

};