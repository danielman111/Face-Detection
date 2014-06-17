#include "../include/AllItemList.h"
#include <string>
#include <vector>

using namespace std;


//empty constructor
AllItemList::AllItemList() : _supplier(), _ingredient(), _price()
{
}

//with the given ingridiant name and supplier, returns their's place in AllItemList, in case they not exits, return -1.
int AllItemList::FindInList(const string& ingName, const string& suppName) const
{
   int size= _supplier.size();
   for (int i=0; i < size; i++){
		if ((_ingredient[i] == ingName) && (_supplier[i] == suppName))
			return i;
   }
   return -1;
}


//adds to AllItemList an ingridiant with his supplier and it's price
void AllItemList::AddToList(const string& suppName, const string& ingName, double ingPrice)
{
	_supplier.push_back(suppName);
	_ingredient.push_back(ingName);
	_price.push_back(ingPrice);
}

//returns the supplier name in the given location
string AllItemList::SuppInLoc(int loc) const
{
	return _supplier[loc];
}

//returns the ingridiant name in the given location
string AllItemList::IngInLoc(int loc) const
{
	return _ingredient[loc];
}

//returns the ingridiant price in the given location
double AllItemList::PriceInLoc(int loc) const
{
	return _price[loc];
}

//returns the size of vector's in AllItemList
int AllItemList::GetSize() const
{
	return _price.size();
}

//changes the price of an ingridiant, with the given supplier and ingridiant name, does nothing if the given ingridiant and supplier do not exits in AllItemList
void AllItemList::ChangePrice(const string& suppName, const string& ingName, double ingPrice)	
{
    int loc= FindInList(ingName, suppName);
    if (0 <= loc)
      _price[loc]= ingPrice;
}

//returns the location of the cheapest ingridiant that was requested
int AllItemList::FindCheapest(const string& ingName) const	
{
	int size= _supplier.size();
	double lowestPrice= 99999;
	int lowestLoc= 0;
	for (int i=0; i < size; i++){
		if ((_ingredient[i] == ingName) && (_price[i] < lowestPrice)){
			lowestPrice= _price[i];
			lowestLoc= i;
		}
   }
   return lowestLoc;
}
/**
 * Destructor
 */
AllItemList::~AllItemList()
{
}
/**
 * Copy Constructor:deep copy of aList
 */
AllItemList::AllItemList(const AllItemList &aItemList) : _supplier(), _ingredient(), _price()//what the end mean?
{
	int size= aItemList.GetSize();
	for (int i=0; i < size; i++){
		string newSupp= SuppInLoc(i);
		string newProd= IngInLoc(i);
		AddToList(newSupp, newProd, PriceInLoc(i));
	}
}
/**
 * Assignment Operator
 */
AllItemList & AllItemList::operator=(const AllItemList &L) //L go into this
{
  // check for "self assignment" and do nothing in that case
  if (this == &L) {
    return *this;
  }
  _supplier.clear();
  _ingredient.clear();
  _price.clear();
  int size= L.GetSize();
	for (int i=0; i < size; i++){
		string newSupp= SuppInLoc(i);
		string newProd= IngInLoc(i);
		AddToList(newSupp, newProd, PriceInLoc(i));
	}
  return *this;
}
