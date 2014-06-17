/*
 * RegularCustomerHeaders.h
 *
 *  Created on: Nov 16, 2013
 *      Author: daniel
 */

#ifndef REGULARCUSTOMERHEADERS_H_
#define REGULARCUSTOMERHEADERS_H_

#include "../include/Customer.h"
#include <string>


class RegularCustomer: public Customer
{
	public:
	RegularCustomer(const std::string& name, const std::string& favProduct);// constructor
	double computeProductPrice(double originalPrice);
	bool isVip();
	RegularCustomer(const RegularCustomer& Regcus);
	RegularCustomer& operator=(const RegularCustomer& Regcus);
	virtual~RegularCustomer();


	//private:

};



#endif /* REGULARCUSTOMERHEADERS_H_ */
