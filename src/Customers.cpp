#include "../include/Customers.h"
#include <string>
#include <vector>

using namespace std;

// constructor
Customers::Customers() : m_customers()
{
}

//adds a new customer to the customers vector, with the given info of his name, favorite product, and if he is a vip
void Customers::AddCustomer(const string& name, const string& favProd, bool isVip)
{
  Customer *p;
  if (isVip)
	p= new VipCustomer(name, favProd);
  else
	p= new RegularCustomer(name, favProd);
  m_customers.push_back(p);
}

//return the amount of customers 
int Customers::GetSize() const
{
	return m_customers.size();
}

//returns a pointer to the customer that is located at i in the customers vector
Customer* Customers::GetCustomerAt(int i) const
{
	return m_customers[i];
}

/**
 * Destructor
 */
Customers::~Customers()
{
  int size= m_customers.size();
  for (int i= 0; i < size; i++)
    delete m_customers.at(i);
}

   /**
 * Copy Constructor:deep copy of Customers
 */
Customers::Customers(const Customers &Custs) : m_customers()
{
  int size= Custs.m_customers.size();
  for (int i= 0; i < size; i++)
    m_customers.push_back(Custs.m_customers[i]);
}

  /**
 * Assignment Operator
 */
 Customers & Customers::operator=(const Customers &Custs)
{
  // check for "self assignment" and do nothing in that case
  if (this == &Custs) {
    return *this;
  }
  int thisLenghVec= m_customers.size();
  for (int i= 0; i < thisLenghVec; i++)
	  delete m_customers[i];
  m_customers.clear();
  int size= Custs.m_customers.size();
  for (int i= 0; i < size; i++)
    m_customers.push_back(Custs.m_customers[i]);
  return *this;
}
