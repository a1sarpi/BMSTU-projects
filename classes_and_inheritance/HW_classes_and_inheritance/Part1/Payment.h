// 52.   Payment ( 39),   - 
// -  Date   29.   , 
//    Date

#pragma once
#include <iostream>
#include <string>
#include "Date.h"

using namespace std; 

class Payment {
private:
	string mSNP[3];

	double mSalary;

	Date mAdmissionDate;

	double mAllowancePercentage;
	static constexpr double mIncomeTax = 0.13;

	unsigned int mDaysWorked;
	unsigned int mWorkingDays;

	static unsigned int emloyers;

public: 
	Payment();
	
	//!!! Вы менять будуте pSNP? Добавил const
	Payment(const string &pSNP, double pSalary, const Date pAdmissionDate, 
			double pAllowancePercentage, double pIncomeTax, 
			unsigned int pDaysWorked, unsigned int pWorkingDays);
	//Убрал деструктор

	double getAccuredAmount() const;
	double getWithheldAmount() const;
	
	double actualAmount() const;
	unsigned int workExperience() const;

	static unsigned int getNumOfEmployers() {
		return emloyers;
	}

	friend ostream& operator<<(ostream& os, const Payment &pObj);
	friend istream& operator>>(istream& is, Payment &pObj);

};
