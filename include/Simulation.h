
#ifndef SimulationHEADERS_H_
#define SimulationHEADERS_H_
#include "../include/Customer.h"
#include "../include/Customers.h"
#include "../include/ItemList.h"
#include "../include/AllItemList.h"
#include "../include/MyOwnLogger.h"
#include "../include/RegularCustomer.h"
#include "../include/VipCustomer.h"
#include "../include/FaceDetection.h"

#include <vector>
#include <string>


class Simulation {

private:
	std::string _suppFile;
	std::string _prodFile;
	std::string _eventFile;
	ItemList *_prodList;
	AllItemList *_allItems;
	std::vector<std::string> *_menu;
	std::vector<std::string> *_prodComponents;
	MyOwnLogger *_logger;

	void Sort_Suppliers();
	void Break_Line(std::string& line, std::string& supp, std::string& ing, double& price);
	void Write_Line_To_File(const std::string& line, std::ofstream& ofs);
	double Calc_Products_Price(std::string& line);
	void ProdComponents_build();
	void ComapreMenu(const std::vector<std::string>& compare_menu,const std::vector<std::string>& menu, std::vector<std::string>& tolog, const std::string& print, int& count, bool firstCompare);
	void LogUpdatedItems(std::vector<std::string>& compare_menu);
	void Build_Menu (bool suppChange);
	void SupplierChange(std::string& eventLine);
	double BuyItem(Customers& custs, const std::string& custImg, double& profit);
	double buyFavProduct(const std::string& favProduct) ;



public:
	Simulation(const std::string& suppFileName, const std::string& prodFileName, const std::string& eventFileName);
	void Run_Simulation(MyOwnLogger *logger);
	std::string* split(std::string& line, const std::string& delim);
	std::string* Read_Line_From_File(std::ifstream& ifs);
	virtual ~Simulation();
	Simulation(Simulation &sim);
	Simulation& operator=(const Simulation &sim);



};

#endif /* SimulationHEADERS_H_ */
