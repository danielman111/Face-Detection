#include "../include/RegularCustomer.h"
#include "../include/Customer.h"
#include <string>

using namespace std;

// constructor
RegularCustomer::RegularCustomer(const string& name, const string& favProduct) :
		Customer::Customer(name, favProduct)
{
}

//function that gets the original price of the product, and calculates the amount of money the customer should pay
double RegularCustomer::computeProductPrice(double originalPrice)
{
	return originalPrice;
}


//returns true if the customer is vip, false otherwise
bool RegularCustomer::isVip(){
	return false;
}

   /**
 * Copy Constructor:deep copy of a RegularCustomer
 */
RegularCustomer::RegularCustomer(const RegularCustomer& Regcus): Customer::Customer(Regcus.getName(), Regcus.getFavProduct())
{
}

  /**
 * Assignment Operator
 */
RegularCustomer & RegularCustomer::operator=(const RegularCustomer& Regcus)//Vipcus go into this
{
  // check for "self assignment" and do nothing in that case
  if (this == &Regcus) {
    return *this;
  }
  Customer::setName(Regcus.getName());
  Customer::setFavProduct(Regcus.getFavProduct());
  return *this;
}

//destructor
RegularCustomer::~RegularCustomer()
{
}
