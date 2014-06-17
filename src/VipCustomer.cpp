#include "../include/VipCustomer.h"
#include "../include/Customer.h"
#include <string>

using namespace std;

// constructor
VipCustomer::VipCustomer(const string& name, const string& favProduct) :
		Customer::Customer(name, favProduct) // constructor
{
}

//function that gets the original price of the product,and calculates the amount of money the customer should pay
double VipCustomer::computeProductPrice(double originalPrice)
{
  return originalPrice * 0.8;
}

//returns true if the customer is vip, false otherwise
bool VipCustomer::isVip(){
	return true;
}


   /**
 * Copy Constructor:deep copy of aList
 */
VipCustomer::VipCustomer(const VipCustomer &Vipcus): Customer::Customer(Vipcus.getName(), Vipcus.getFavProduct())
{
}

  /**
 * Assignment Operator
 */
 VipCustomer & VipCustomer::operator=(const VipCustomer &Vipcus)//Vipcus go into this
{
	// check for "self assignment" and do nothing in that case
  if (this == &Vipcus) {
    return *this;
  }
  Customer::setName(Vipcus.Customer::getName());
  Customer::setFavProduct(Vipcus.Customer::getFavProduct());
  return *this;
}

//destructor
VipCustomer::~VipCustomer()
{
}
