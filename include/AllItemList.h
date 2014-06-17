/*
 * AllItemListHeaders.h
 *
 *  Created on: Nov 16, 2013
 *      Author: daniel
 */

#ifndef ALLITEMLISTHEADERS_H_
#define ALLITEMLISTHEADERS_H_
#include <vector>
#include <string>


//a class that contains the all the ingridiants, their's supplier's and price's, in three diffrent vectors
class AllItemList {
  private:
    std::vector<std::string> _supplier;
    std::vector<std::string> _ingredient;
    std::vector<double> _price;

  public:
    AllItemList(); // constructor

    int FindInList(const std::string& ingName, const std::string& suppName) const;
    void AddToList(const std::string& suppName, const std::string& ingName, double ingPrice);
    std::string SuppInLoc(int loc) const;
    std::string IngInLoc(int loc) const;
    double PriceInLoc(int loc) const;
    int GetSize() const;
    void ChangePrice(const std::string& suppName, const std::string& ingName, double ingPrice);
    int FindCheapest(const std::string& ingName) const;

    AllItemList(const AllItemList& aItemList);
    virtual ~AllItemList();
    AllItemList& operator=(const AllItemList &L);
};




#endif /* ALLITEMLISTHEADERS_H_ */
