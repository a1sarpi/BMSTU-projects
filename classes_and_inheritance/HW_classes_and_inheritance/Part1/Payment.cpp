#include <iostream>
#include <string>
#include <iomanip>
#include "Payment.h"
#include "Date.h"

unsigned int Payment::emloyers;

Payment::Payment() 
		: mSNP{ "Ivanov", "Ivan", "Ivanovich" }, mSalary(.0),
		  mAdmissionDate(Date()), mAllowancePercentage(.0), 
		  mDaysWorked(0), mWorkingDays(21)
{
	emloyers++;
}

Payment::Payment(const string &pSNP, double pSalary, Date pAdmissionDate, 
				 double pAllowancePercentage, double pIncomeTax, 
				 unsigned int pDaysWorked, unsigned int pWorkingDays) 
		: mSalary(pSalary), mAdmissionDate(pAdmissionDate),
		  mAllowancePercentage(pAllowancePercentage),
		  mDaysWorked(pDaysWorked), mWorkingDays(pWorkingDays)
{
	for (unsigned int i = 0; i < 3; i++) {
		mSNP[i] = pSNP[i];
	}
	emloyers++;
}

double Payment::getAccuredAmount() const
{

	if (mDaysWorked > mWorkingDays) {
		return ((mDaysWorked / mWorkingDays - 1) + mAllowancePercentage) * mSalary;
	}
	else return mAllowancePercentage * mSalary;
}

double Payment::getWithheldAmount() const
{
	return (mIncomeTax + 0.1) * (getAccuredAmount() + mSalary);
}

double Payment::actualAmount() const
{
	return getAccuredAmount() + mSalary * mDaysWorked / mWorkingDays - getWithheldAmount();
}

unsigned int Payment::workExperience() const
{
	unsigned int result = 0;
	Date today = Date();
	unsigned int totalDaysWorked = today.datesDifference(mAdmissionDate);
	unsigned int i = mAdmissionDate.getYear();
	while ((totalDaysWorked >= 365) && (i <= today.getYear())) {
		if (i % 4 == 0) {
			totalDaysWorked -= 366;
		}
		else {
			totalDaysWorked -= 365;
		}
		i++;
		result++;
	}
	return result;
}

ostream& operator<<(ostream& os, const Payment& pObj)
{
	os << "____________________________________________"								<< endl
	<<	  "|Emloyer's SNP       |" << setw(21)		<< pObj.mSNP[0]				 << "|" << endl
	<<	  "|                    |" << setw(21)		<< pObj.mSNP[1]				 << "|" << endl
	<<	  "|                    |" << setw(21)		<< pObj.mSNP[2]				 << "|" << endl
	<<    "|Salary              |" << setw(21)		<< pObj.mSalary				 << "|" << endl
    <<    "|Admission Date      |" << "           " << pObj.mAdmissionDate		 << "|" << endl
	<<    "|Allowance Percentage|" << setw(21)		<< pObj.mAllowancePercentage << "|" << endl
	<<    "|Income Tax          |" << setw(21)		<< pObj.mIncomeTax           << "|" << endl
	<<    "|Days Worked         |" << setw(21)		<< pObj.mDaysWorked          << "|" << endl
	<<    "|Working Days        |" << setw(21)		<< pObj.mWorkingDays         << "|" << endl
	<<    "|Accured Amount      |" << setw(21)		<< pObj.getAccuredAmount()   << "|" << endl
	<<    "|Withheld Amount     |" << setw(21)		<< pObj.getWithheldAmount()  << "|" << endl
	<<    "|Actual Amount       |" << setw(21)		<< pObj.actualAmount()       << "|" << endl
	<<    "|Work Experience     |" << setw(21)		<< pObj.workExperience()     << "|" << endl
	<<    "|__________________________________________|"								<< endl;
	return os;
}

istream& operator>>(istream& is, Payment& pObj)
{
	string pDate;
	cout << "Enter initials of employer: ";
	is >> pObj.mSNP[0];
	is >> pObj.mSNP[1];
	is >> pObj.mSNP[2];
	cout << "Enter salary of employer: ";
	is >> pObj.mSalary;
	cout << "Enter date of admission: ";
	is >> pDate;
	pObj.mAdmissionDate = Date(pDate);
	cout << "Enter days worked: ";
	is >> pObj.mDaysWorked;
	cout << "Enter number of working dates: ";
	is >> pObj.mWorkingDays;
	cout << "Enter allowance percentage for this employer: ";
	is >> pObj.mAllowancePercentage;
	return is;
}
