#include "../include/Customer.h"
#include <string>


//constructor
Customer::Customer(const std::string& name, const std::string& favProduct): _name(name), _favProduct(favProduct)
{
}


//sets the customer name, with the given name 
void Customer::setName(const std::string& newName)
{
	_name= newName;
}

//sets the customer favorite product, with the given product name 
void Customer::setFavProduct(const std::string& favProd)
{
	_favProduct= favProd;
}

//returns the name of the customer
const std::string& Customer::getName() const{
	return _name;
}
//returns the name of the customer favorite product
const std::string& Customer::getFavProduct() const{
	return _favProduct;
}


/**
 * Destructor
 */
Customer::~Customer()
{
}

/**
* Copy Constructor:deep copy of Customers
*/
Customer::Customer(const Customer& aCustomer): _name(aCustomer.getName()), _favProduct(aCustomer.getFavProduct())
{
}

 /**
* Assignment Operator
*/
Customer & Customer::operator=(const Customer& aCustomer)
{
 // check for "self assignment" and do nothing in that case
 if (this == &aCustomer) {
   return *this;
 }
 _name= aCustomer.getName();
 _favProduct= aCustomer.getFavProduct();
 return *this;
}

