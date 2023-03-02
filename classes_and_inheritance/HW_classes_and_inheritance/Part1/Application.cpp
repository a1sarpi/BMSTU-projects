#include <iostream>
#include "Application.h"
#include "Date.h"
#include "Payment.h"

using namespace std;

void Application::run()
{
	bool finished = false;
	while (!finished) {
		unsigned int input;
		cout << "Choose one of this options: " << endl
			 << "1) Test Date"				   << endl
			 << "2) Test Payment"			   << endl
			 << "3) Exit"					   << endl;
		cin >> input;
		switch (input) {
		case 1:
			DateTest();
			break;
		case 2:
			PaymentTest();
			break;
		case 3:
			finished = true;
			break;
		default:
			cout << "ERROR. THERE IS NO SUCH OPTION. TRY AGAIN." << endl;
		}
	}
}

void Application::DateTest()
{
	cout << "     ~~~Test Date~~~     " << endl;
	cout << "Enter first date (for example, 2022.05.15)" << endl;
	string dateL;
	cin >> dateL;
	Date Date1(dateL);
	cout << "First date: " << endl << Date1 << endl;
	Date Date2(2022, Months::may, 15); 
	cout << "Second date: " << endl << Date2 << endl;
	cout << "Comparing: " << endl;
	cout << "Date1 == Date2? : " << (Date1 == Date2) << endl
		 << "Date1 > Date2?  : " << (Date1 > Date2) << endl
		 << "Date1 < Date2?  : " << (Date1 < Date2) << endl;
	cout << "Arithmetical operations: " << endl;
	int days;
	cout << "Enter number of days to add to the first date: " << endl;
	cin >> days;
	cout << "Result: " << Date1 << " + " << days << " days = ";
	Date1 = Date1 + days;
	cout << Date1 << endl;
	cout << "Difference between today's date and Date1: " << endl;
	Date Today = Date(); 
	cout << Date1.datesDifference(Today) << endl;
}

void Application::PaymentTest()
{
	cout << "     ~~~Test Payment~~~     " << endl;
	cout << "Empty Payment-object: " << endl;
	Payment P1;
	cout << "P1 (empty): " << endl << P1 << endl;
	cout << "Creating a non-empty object. Fill in its fields: " << endl;
	Payment P2;
	cin >> P2;
	cout << "P2 (filled): " << endl << P2 << endl;
	cout << "Number og employers for the moment: " << Payment::getNumOfEmployers() << endl;
}
