/*
 * CustomerHeaders.h
 *
 *  Created on: Nov 16, 2013
 *      Author: daniel
 */

#ifndef CUSTOMERHEADERS_H_
#define CUSTOMERHEADERS_H_
#include <string>


class Customer {

	public:
		Customer(const std::string& name, const std::string& favProduct);//constructor
		void setName(const std::string& newName);
		void setFavProduct(const std::string& favProd);
		const std::string& getName() const;
		const std::string& getFavProduct() const;
		virtual bool isVip()=0;
		virtual double computeProductPrice(double originalPrice)=0;
		virtual ~Customer();
		Customer(const Customer& aCustomer);
		Customer& operator=(const Customer& aCustomer);


	private:
		std::string _name;
		std::string _favProduct;
};



#endif /* CUSTOMERHEADERS_H_ */
