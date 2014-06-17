/*
 * VipCustomerHeaders.h
 *
 *  Created on: Nov 16, 2013
 *      Author: daniel
 */

#ifndef VIPCUSTOMERHEADERS_H_
#define VIPCUSTOMERHEADERS_H_

#include "../include/Customer.h"
#include <string>

class VipCustomer: public Customer
{
	public:
	VipCustomer(const std::string& name,const std::string& favProduct);// constructor
	double computeProductPrice(double originalPrice);
	bool isVip();
    virtual ~VipCustomer();
    VipCustomer(const VipCustomer &Vipcus);
    VipCustomer& operator=(const VipCustomer &Vipcus);

	//private:

};



#endif /* VIPCUSTOMERHEADERS_H_ */
