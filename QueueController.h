#pragma once
#include <boost/lockfree/queue.hpp>

//Klasse für Operationen bzgl. FIFO1 und FIFO2

class QueueController {

public:
	
	//Kontruktor reserviert speicher für FIFOs
	QueueController();
	
	//Sendet neuen Wert an FIFO1
	bool sendToFIFO1(int );

	//Sendet neuen Wert an FIFO^2
	bool sendToFIFO2(int );

	//Liest Wert aus FIFO1
	bool readFromFIFO1(int&);

	//Liest Wert aus FIFO2
	bool readFromFIFO2(int&);

	//Prüft ob FIFO1 leer ist
	bool checkIfFIFOEmpty1(void);

	//Prüft ob FIFO2 leer ist
	bool checkIfFIFOEmpty2(void);

	////getter um Nodes status abzufragen
	bool getNodesStatus(void) {
		return running;
	};


	////setter um running zu verändern
	void setNodesStatus(bool state) {
		running = state;
	};

	//Destruktor leert die FIFOs
	~QueueController(void);


private:
	//boost::lockfree::queue Objecte werden Abgekapselt und so vor unbefugten Zugriff geschützt
	std::unique_ptr<boost::lockfree::queue<int>> ptrF1;
	std::unique_ptr<boost::lockfree::queue<int>> ptrF2;
	std::atomic<bool> running; //Variable checked ob programm noch laufen soll
	
	//Knoten welcher sich um die Ein- und Ausgabe der Werte kümmert
	void NodeA();
	//Knoten welcher sich um die Verarbeitung der Eingabewerte kümmert
	void NodeB();
	//Menü mit kruzer erklärung
	void menu();
	//Überprüft die Eingabewerte
	bool checkInput(int);

};