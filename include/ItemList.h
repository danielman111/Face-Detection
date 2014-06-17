/*
 * ItemListHeaders.h
 *
 *  Created on: Nov 16, 2013
 *      Author: daniel
 */

#ifndef ITEMLISTHEADERS_H_
#define ITEMLISTHEADERS_H_

#include <vector>
#include <string>

//a class that contains the cheapest ingridiants, their's supplier's and price's, in three diffrent vectors
class ItemList {
  private:
	std::vector<std::string> _supplier;
	std::vector<std::string> _ingredient;
	std::vector<double> _price;

  public:
    ItemList(); // constructor

    void AddToList(const std::string& suppName, const std::string& ingName, double ingPrice);
    int FindInList(const std::string& ingName) const;
    const std::string& SuppInLoc(int loc) const;
    const std::string& IngInLoc(int loc) const;
    double PriceInLoc(int loc) const;
    int GetSize() const;
    void ChangePrice(const std::string& suppName, const std::string& ingName, double ingPrice);
    void UpdateIngData(const std::string& suppName, const std::string& ingName, double ingPrice);

    ItemList(const ItemList& aItemList);
    virtual ~ItemList();
    ItemList& operator=(const ItemList &L);
};




#endif /* ITEMLISTHEADERS_H_ */
