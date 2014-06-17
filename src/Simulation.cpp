#include "../include/Simulation.h"
#include "../include/ItemList.h"
#include "../include/AllItemList.h"
#include "../include/ItemList.h"
#include "../include/Customer.h"
#include "../include/Simulation.h"
#include "../include/RegularCustomer.h"
#include "../include/VipCustomer.h"
#include "../include/FaceDetection.h"

#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>


//constructor
Simulation::Simulation(const std::string& suppFileName, const std::string& prodFileName, const std::string& eventFileName):
_suppFile(suppFileName), _prodFile(prodFileName), _eventFile(eventFileName), _prodList(new ItemList()),
_allItems(new AllItemList()), _menu(new std::vector<std::string>()), _prodComponents(new std::vector<std::string>()), _logger(0)
{
}

//returns the first part of the string (until the first delim), while changing the original string
std::string* Simulation::split(std::string& line, const std::string& delim){
	int pos= line.find(delim);
	std::string *ans= new std::string();
	if (pos >= 0){
	      (*ans)= line.substr(0, pos);
	      line= line.substr(pos + delim.size());
	      return ans;
	}
	(*ans)= line;
	line= "";
	return ans;
}


//reads the suppliers.conf file and breaks it into 3 vectors- one for the supplier's name, one for the product, and one for the price
void Simulation::Sort_Suppliers(){ //will do only once in the program, in the begging of it
	std::string line;
	std::ifstream ifs (_suppFile.c_str());
	std::string *lineP= Read_Line_From_File(ifs);
	line= *lineP;
	delete lineP;
	while (line != ""){
		std::string suppName;
		std::string ingName;
		double priceOfIng;
		Break_Line(line, suppName, ingName, priceOfIng);
		_prodList->AddToList(suppName, ingName, priceOfIng);
		_allItems->AddToList(suppName, ingName, priceOfIng);
		lineP= Read_Line_From_File(ifs);
		line= *lineP;
		delete lineP;
	}
	ifs.close();
}


//gets a line containing this format "supp,ing,price" and breaks it down
void Simulation::Break_Line(std::string& line, std::string& supp, std::string& ing, double& price){
	std::string price_num;
	std::string *suppP= split(line,",");
	std::string *ingP= split(line,",");
	std::string *priceP= split(line,",");
	supp= *suppP;
	ing= *ingP;
	price_num= *priceP;
	delete priceP;
	delete ingP;
	delete suppP;
	price= atof(price_num.c_str());
}


//reads a line from the text file
std::string* Simulation::Read_Line_From_File(std::ifstream& ifs){
	std::string *ans= new std::string();
	if (ifs.is_open()){
		getline(ifs, (*ans));
		return ans;
	}
	else
		std::cout << "Error opening file";
	return ans;
}


//writes a line to the text file
void Simulation::Write_Line_To_File(const std::string& line, std::ofstream& ofs){
  ofs << line << std::endl;
}


//calculates the price of a product, while saving all of his ingredients into a vector
double Simulation::Calc_Products_Price(std::string& line){
	double cost= 0;
	while (line != ""){
		std::string *curIngP= split(line, ",");
		std::string curIng= *curIngP;
		int ing_place= _prodList->FindInList(curIng);
		if (0 <= ing_place){
		  cost+= _prodList->PriceInLoc(ing_place);
		  std::string newLine= std::string(_prodList->SuppInLoc(ing_place)) + "," + curIng;
		}
		delete curIngP;
	}
	return ((cost + 0.25)*1.5);
}

//breaks the products.conf into the _prodComponents vector, line by line
void Simulation::ProdComponents_build(){
	std::string prodLine;
	std::ifstream ifs (_prodFile.c_str());
	std::string *prodLineP= Read_Line_From_File(ifs);
	prodLine= *prodLineP;
	delete prodLineP;
	while (prodLine != ""){
		_prodComponents->push_back(prodLine); //prodLine as: granola cookies,quaker,honey,nuts,raisins
		prodLineP= Read_Line_From_File(ifs);
		prodLine= *prodLineP;
		delete prodLineP;
	}
	ifs.close();
}


/*a function that compares beetwen two menus, counts the amount of price changes between "compare_menu" and "menu", and the amount
of removed/added items, and insert the lines needed to the logger, to the "tolog" vector*/ 
void Simulation::ComapreMenu(const std::vector<std::string>& compare_menu,const std::vector<std::string>& menu, std::vector<std::string>& tolog, const std::string& print, int& count, bool firstCompare){
	int menu_size= menu.size();
	int compare_menu_size= compare_menu.size();
	for(int i=0; i < menu_size; i++){
		bool foundItem= false;
		std::string temp_line= menu.at(i);
		std::string menu_line= temp_line;
		std::string *menu_productP= split(menu_line, ",");
		std::string menu_product= *menu_productP;
		std::string *temp= split(menu_line,",");
		double menu_price= atof((*temp).c_str());
		delete menu_productP;
		delete temp;
		for(int j=0; ((j < compare_menu_size) && (!foundItem)); j++){
			std::string temp_compare_line= compare_menu.at(j);
			std::string compare_line= temp_compare_line;
			std::string *compare_productP= split(compare_line, ",");
			std::string compare_product= *compare_productP;
			delete compare_productP;
			double compare_price= atof(compare_line.c_str());
			if(menu_product == compare_product){//checks if the item in the "compare_menu" exits in the "menu"
				foundItem= true; 
				if (menu_price != compare_price){//checks if there was a price change of a product in the menu
					count= count+1;
				}
			}
		}
		if (foundItem == false){
			//insert the proper messege to the vector, later will go to the logger
			std::string messege= "Product " + menu_product + " was " + print + " from the menu.";
			tolog.push_back(messege);
		}
	}
}

//gets the updated menu, prints the amount of prducts updated, and prints all the messege of the added/removed items to the logger
void Simulation::LogUpdatedItems(std::vector<std::string>& compare_menu){
	std::vector<std::string> tolog;
	int countUpdatedItems=0;
	ComapreMenu(compare_menu, *_menu, tolog, "removed", countUpdatedItems, true);
	std::ostringstream ss;
	ss << "Product updated: " << countUpdatedItems;
	_logger->Log(ss.str(), Poco::Message::PRIO_NOTICE);
	ComapreMenu(*_menu, compare_menu, tolog, "added", countUpdatedItems, false);
	int toLogSize= tolog.size();
	for(int i=0; i<toLogSize; i++){
		std::string str= tolog.at(i);
		_logger->Log(str.c_str(), Poco::Message::PRIO_WARNING);
	}
}

//given if a supply change made or not, builds the menu vector containing the product and its price.
void Simulation::Build_Menu (bool suppChange){
	bool firstbuild= true;
	std::vector<std::string> *compare_menu= new std::vector<std::string>;
	if(_menu->size() != 0){ //checks if this is the first time building the menu
		firstbuild= false;
	}
	std::string prodline;
	int size= _prodComponents->size();
	for(int i=0; i < size; i++){
		prodline= _prodComponents->at(i);
		std::string templine= prodline;
		std::string *curProdP= split(templine, ",");
		std::string curProd= *curProdP;   
		delete curProdP;
		double prodPrice= Calc_Products_Price(templine);
		if (prodPrice <= 5){ //checks if the product can be inserted to the menu
			std::ostringstream convert;
			convert << prodPrice;
			std::string newLine= std::string(curProd) + "," + convert.str();
			compare_menu->push_back(newLine);
		}
	}
	if(firstbuild == true){
		firstbuild= false;
	}
	if((firstbuild == false) && (suppChange == true)){//if a supply change was made, we need to prints the require lines to the logger.
		LogUpdatedItems(*compare_menu);
	}
	*_menu= *compare_menu;
	delete compare_menu;
}

//updated the ItemList and the AllItemList vectors, with the supplier change event
void Simulation::SupplierChange(std::string& eventLine){
	std::string *suppNameP= split(eventLine,",");
	std::string suppName= *suppNameP;
	std::string *ingNameP= split(eventLine,",");
	std::string ingName= *ingNameP;
	std::string *newPriceP= split(eventLine,",");
	double newPrice= atof((*newPriceP).c_str());
	delete suppNameP;
	delete ingNameP;
	delete newPriceP;
	std::string message= "Supplier " + suppName + " changed the price of " + ingName;
	_logger->Log(message.c_str(), Poco::Message::PRIO_NOTICE);
	_allItems->ChangePrice(suppName, ingName, newPrice);
	_prodList->ChangePrice(suppName, ingName, newPrice);
	int loc= _allItems->FindCheapest(ingName);
	double lowestIn_allItems= _allItems->PriceInLoc(loc);
	int lowestLoc= _prodList->FindInList(ingName);
	double priceOfIng= 99999;
	if (0 <= lowestLoc)
	  priceOfIng= _prodList->PriceInLoc(lowestLoc);
	std::string lowestSupp= _allItems->SuppInLoc(loc);
	if (lowestIn_allItems < priceOfIng){// checks if the price of the ingridiant in AllItemList is cheaper than Itemlist,
		_prodList->UpdateIngData(lowestSupp, ingName, lowestIn_allItems);//if so, we need to udpate the ItemList with these supplier and price of the ingridiant
	}

}


//returns the price of the product in the menu. if the product does not exits in the menu, returns 0.
double Simulation::buyFavProduct(const std::string& favProduct)  {
	int size= _menu->size();
	double price= 0;
	for (int i=0; i<size; i++) {
		std::string element = _menu->at(i);
		std::string to_delim= element;
		std::string *itemP= split(to_delim, ",");
		std::string item= *itemP;
		delete itemP;
		if(item==favProduct){
			std::string *price_numP= split(to_delim, ",");
			std::string price_num= *price_numP;
			delete price_numP;
			price= atof(price_num.c_str());
		}
	}
	return price;
}


/*given an image name of customer(s), the customers vector and the current profit, return the added revenue by the costumer(s),
and updates the profit*/
double Simulation::BuyItem(Customers& custs, const std::string& custImg, double& profit){
	double currentProfit= 0;
	double currentRevenue= 0;
	FaceDetection FD;
	std::vector<int> *custsFound= FD.Detect(custImg, custs);//gets a vector of the customers place, in the costumers vector
	int size= custsFound->size();
	for (int i= 0; i < size; i++){
		Customer *curCust= custs.GetCustomerAt((*custsFound)[i]);
		std::string favProduct= curCust->getFavProduct();
		double priceFavPro= buyFavProduct(favProduct);		
		if (0 == priceFavPro){
			std::string message= "Costumer " + curCust->getName() + " failed to purchase " + favProduct;
			_logger->Log(message.c_str(), Poco::Message::PRIO_NOTICE);
		}
		else{
			if (curCust->isVip()){
				currentProfit= currentProfit+ 2.0/15 * priceFavPro; //(1/3 * priceFavPro) - (0.2 * priceFavPro);
			}
			else
				currentProfit= currentProfit + 1.0/3 * priceFavPro;
			currentRevenue= currentRevenue + curCust->computeProductPrice(priceFavPro);
			std::string message= "Costumer " + curCust->getName() + " purchased " + favProduct;
			_logger->Log(message.c_str(), Poco::Message::PRIO_NOTICE);
		}
	}
	profit= profit + currentProfit;
	delete custsFound;
	return currentRevenue;
}


//gets the MyOwnLogger pointer, and runs the simulation of the coffee shop
void Simulation::Run_Simulation(MyOwnLogger *logger){
	_logger= logger;
	Sort_Suppliers();
	ProdComponents_build();
	Build_Menu(false);
	double revenue= 0;
	double profit= 0;
	Customers *custs= new Customers();
	std::ifstream ifs (_eventFile.c_str());
	std::string *eventLineP= Read_Line_From_File(ifs);
	std::string eventLine= *eventLineP;
	delete eventLineP;
	while ("" != eventLine){
		std::string *eventP= split(eventLine, ",");
		std::string event= *eventP;
		delete eventP;
		if ("register" == event){
			const std::string *custNameP= split(eventLine, ",");
			const std::string custName= *custNameP;
			const std::string *favProdP= split(eventLine, ",");
			const std::string favProd= *favProdP;
			delete custNameP;
			delete favProdP;
			const std::string *isVipP= split(eventLine, ",");
			bool isVip= ("1" == (*isVipP));
			delete isVipP;
			custs->AddCustomer(custName, favProd, isVip);
			std::string message= "";
			if (isVip)
				message= "New Vip Costumer registered - " + custName + ", Favorite product - " + favProd + ".";
			else
				message= "New Regular Costumer registered - " + custName + ", Favorite product - " + favProd + ".";
			_logger->Log(message.c_str(), Poco::Message::PRIO_NOTICE);
		}
		else if ("purchase" == event){
			std::string *custImgP= split(eventLine, ",");
			std::string custImg= *custImgP;
			delete custImgP;
			revenue= revenue + BuyItem(*custs, custImg, profit);
		}
		else if ("supplier_change" == event){
			SupplierChange(eventLine);
			Build_Menu(true);
		}
		eventLineP= Read_Line_From_File(ifs);
		eventLine= *eventLineP;
		delete eventLineP;
	}
	std::ostringstream ss;
	ss << "The total revenue is " << revenue << ", while the total profit is " << profit;
	_logger->Log(ss.str(), Poco::Message::PRIO_WARNING);
	ifs.close();
	FaceDetection FD;
	FD.CreateCollage(*custs);
	delete custs;
}


/**
 * Destructor
 */
Simulation::~Simulation()
{
  delete _prodList;
  delete _allItems;
  delete _menu;
  delete _prodComponents;
}

   /**
 * Copy Constructor:deep copy of Simulation
 */
Simulation::Simulation(Simulation& sim) :
_suppFile(sim._suppFile), _prodFile(sim._prodFile), _eventFile(sim._eventFile), _prodList(sim._prodList),
_allItems(sim._allItems), _menu(sim._menu), _prodComponents(sim._prodComponents), _logger(sim._logger)
{
}

  /**
 * Assignment Operator
 */
 Simulation& Simulation::operator=(const Simulation &sim)
{
  // check for "self assignment" and do nothing in that case
  if (this == &sim) {
    return *this;
  }
  	_suppFile= sim._suppFile;
    _prodFile= sim._prodFile;
    _eventFile= sim._eventFile;
    _prodList= sim._prodList;
    _allItems= sim._allItems;
    _menu= sim._menu;
    _prodComponents= sim._prodComponents;
    _logger= sim._logger;
  return *this;
}

