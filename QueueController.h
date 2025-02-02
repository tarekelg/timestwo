#pragma once
#include <boost/lockfree/queue.hpp>

//Klasse f�r Operationen bzgl. FIFO1 und FIFO2

class QueueController {

public:
	
	//Kontruktor reserviert speicher f�r FIFOs
	QueueController();
	
	//Sendet neuen Wert an FIFO1
	bool sendToFIFO1(int );

	//Sendet neuen Wert an FIFO^2
	bool sendToFIFO2(int );

	//Liest Wert aus FIFO1
	bool readFromFIFO1(int&);

	//Liest Wert aus FIFO2
	bool readFromFIFO2(int&);

	//Pr�ft ob FIFO1 leer ist
	bool checkIfFIFOEmpty1(void);

	//Pr�ft ob FIFO2 leer ist
	bool checkIfFIFOEmpty2(void);

	////getter um Nodes status abzufragen
	bool getNodesStatus(void) {
		return running;
	};


	////setter um running zu ver�ndern
	void setNodesStatus(bool state) {
		running = state;
	};

	//Destruktor leert die FIFOs
	~QueueController(void);


private:
	//boost::lockfree::queue Objecte werden Abgekapselt und so vor unbefugten Zugriff gesch�tzt
	std::unique_ptr<boost::lockfree::queue<int>> ptrF1;
	std::unique_ptr<boost::lockfree::queue<int>> ptrF2;
	std::atomic<bool> running; //Variable checked ob programm noch laufen soll
	
	//Knoten welcher sich um die Ein- und Ausgabe der Werte k�mmert
	void NodeA();
	//Knoten welcher sich um die Verarbeitung der Eingabewerte k�mmert
	void NodeB();
	//Men� mit kruzer erkl�rung
	void menu();
	//�berpr�ft die Eingabewerte
	bool checkInput(int);

};