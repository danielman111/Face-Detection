#ifndef CUSTOMERSHEADERS_H_
#define CUSTOMERSHEADERS_H_
#include "../include/Customer.h"
#include "../include/VipCustomer.h"
#include "../include/RegularCustomer.h"
#include <string>
#include <vector>

class Customers
{
 private:
	std::vector<Customer *> m_customers;


  public:
	Customers(); // constructor
	void AddCustomer(const std::string& name, const std::string& favProd, bool isVip);
	int GetSize() const;
	Customer* GetCustomerAt(int i) const;
	virtual ~Customers();
	Customers(const Customers& aCustomers);
	Customers& operator=(const Customers &L);


};



#endif /* CUSTOMERSHEADERS_H_ */
