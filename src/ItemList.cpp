#include "../include/ItemList.h"
#include <string>
#include <vector>

//constructor
ItemList::ItemList() : _supplier(), _ingredient(), _price()
{
}

//gets an ingridiant name, returns his place, in all 3 vectores, if the ingridiant doesnot exits, returns -1
int ItemList::FindInList(const std::string& ingName) const
{
   int size= _supplier.size();
   for (int i=0; i < size; i++){
		if (_ingredient[i] == ingName)
			return i;
   }
   return -1;
}


//adds the ingridiant and his info(supplier name, price) to the vectors. if the ingridiant is already exits in the vector, does nothing.
void ItemList::AddToList(const std::string& suppName, const std::string& ingName, double ingPrice)
{
   int loc= FindInList(ingName);
   if (0 > loc){
		_supplier.push_back(suppName);
		_ingredient.push_back(ingName);
		_price.push_back(ingPrice);
   }
   else {
		if (_price[loc] > ingPrice){
			_supplier[loc]= suppName;
			_ingredient[loc]= ingName;
			_price[loc]= ingPrice;
		}
   }
}

//return the supplier name in the given location in the Itemlist
const std::string& ItemList::SuppInLoc(int loc) const
{
	return _supplier[loc];
}

//return the ingridiant name in the given location in the Itemlist
const std::string& ItemList::IngInLoc(int loc) const
{
	return _ingredient[loc];
}

//return the ingridiant price in the given location in the Itemlist
double ItemList::PriceInLoc(int loc) const
{
	return _price[loc];
}

//return the amount of diffrent ingridiants in the Itemlist
int ItemList::GetSize() const
{
	return _price.size();
}

//changes the price of the ingridiat, only if the given supplier is the same as the ingridiant's supplier
void ItemList::ChangePrice(const std::string& suppName, const std::string& ingName, double ingPrice)	
{
    int loc= FindInList(ingName);
	if ((0 <= loc) && (_supplier[loc] == suppName))
		_price[loc]= ingPrice;
}

//if the given ingridiant exists in ItemList, changes his price and Supplier
void ItemList::UpdateIngData(const std::string& suppName, const std::string& ingName, double ingPrice)	//updates the whole data of ing
{
	int loc= FindInList(ingName);
	if (0 <= loc){
	  _supplier[loc]= suppName;
	  _price[loc]= ingPrice;
	}
}
/**
 * Destructor
 */
ItemList::~ItemList()
{
}
/**
 * Copy Constructor:deep copy of aList
 */
ItemList::ItemList(const ItemList& aItemList) : _supplier(), _ingredient(), _price()
{
	int size= aItemList.GetSize();
	for (int i=0; i < size; i++){
		std::string newSupp= SuppInLoc(i);
		std::string newProd= IngInLoc(i);
		AddToList(newSupp, newProd, PriceInLoc(i));
	}
}
/**
 * Assignment Operator
 */
ItemList & ItemList::operator=(const ItemList& L) //L go into this
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
		std::string newSupp= SuppInLoc(i);
		std::string newProd= IngInLoc(i);
		AddToList(newSupp, newProd, PriceInLoc(i));
	}
  return *this;
}
