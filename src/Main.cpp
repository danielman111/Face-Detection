#include "../include/Simulation.h"
#include <stdlib.h>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>



int main(int argc, char *argv[]) {
	if (1 == argc){
		MyOwnLogger *errorLog= new MyOwnLogger(7,7, "fileError.log");
		errorLog->Log("configuration file not found.", Poco::Message::PRIO_CRITICAL);
		delete errorLog;
		return 1;
	}
	if (2 == argc){
		MyOwnLogger *errorLog= new MyOwnLogger(7,7, "fileError.log");;
		errorLog->Log("suppliers file not found.", Poco::Message::PRIO_CRITICAL);
		delete errorLog;
		return 1;
	}
	else if (3 == argc){
		MyOwnLogger *errorLog= new MyOwnLogger(7,7, "fileError.log");;
		errorLog->Log("products file not found.", Poco::Message::PRIO_CRITICAL);
		delete errorLog;
		return 1;
	}
	else if (4 == argc){
		MyOwnLogger *errorLog= new MyOwnLogger(7,7, "fileError.log");;
		errorLog->Log("events file not found.", Poco::Message::PRIO_CRITICAL);
		delete errorLog;
		return 1;
	}
	Simulation sim(argv[2], argv[3], argv[4]);
	std::ifstream ifs(argv[1]);
	std::string *lineP= sim.Read_Line_From_File(ifs);
	std::string line= *lineP;
	std::string *fileNameP= sim.split(line, " = ");
	std::string fileName= *fileNameP;
	fileName= line;
	delete lineP;
	lineP= sim.Read_Line_From_File(ifs);
	line= *lineP;
	std::string *filePrioP= sim.split(line, " = ");
	std::string filePrio= *filePrioP;
	filePrio= line;
	delete lineP;
	lineP= sim.Read_Line_From_File(ifs);
	line= *lineP;
	std::string *consolePrioP= sim.split(line, " = ");
	std::string consolePrio= *consolePrioP;
	consolePrio= line;
	int fPrio= atoi(filePrio.c_str());
	int conPrio= atoi(consolePrio.c_str());
	delete lineP;
	delete filePrioP;
	delete consolePrioP;
	delete fileNameP;
	MyOwnLogger *logger= new MyOwnLogger(fPrio, conPrio, fileName);
	sim.Run_Simulation(logger);
	delete logger;
}
