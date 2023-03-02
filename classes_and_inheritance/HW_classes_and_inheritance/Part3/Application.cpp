#include "Application.h"
#include "Money124.h"
#include "Money133.h"
#include "Pair.h"
#include <iostream>

using namespace std;

void Application::run()
{
	bool finished = false;
	while (!finished) {
		unsigned int input;
		cout << "Choose one of this options: " << endl
			<< "1) Test Money 1.24" << endl
			<< "2) Test Money 1.33" << endl
			<< "3) Exit" << endl;
		cin >> input;
		switch (input) {
		case 1:
			Money124_Test();
			break;
		case 2:
			Money133_Test();
			break;
		case 3:
			finished = true;
			break;
		default:
			cout << "ERROR. THERE IS NO SUCH OPTION. TRY  AGAIN." << endl;
		}
	}
}

void Application::Money124_Test()
{
	cout << "        ~~~Test Money 1.24~~~        " << endl;
	cout << "Let's create some objects: " << endl;
	Pair* M(new Money), * N(new Money);
	Money* m = dynamic_cast <Money*> (M);
	Money* n = dynamic_cast <Money*> (N);
	Money *m1, *n1;
	cout << "m: ";
	cin >> *m;
	cout << "n: ";
	cin >> *n;
	if (*m < *n) {
		m1 = n;
		n1 = m;
	}
	else {
		m1 = m;
		n1 = n;
	}
	cout << endl << "Let's test some operations: " << endl;
	Pair* result(new Money);
	cout << "m       = " << *m << endl;
	cout << "n       = " << *n << endl;
	m1->sum(n1, result);
	cout << "m + n   = " << *dynamic_cast <Money*> (result) << endl;
	m1->sub(n1, result);
	cout << "m - n   = " << *dynamic_cast <Money*> (result) << endl;
	m1->div(0.5, result);
	cout << "n / 0.5 = " << *dynamic_cast <Money*> (result) << endl;
	n1->mult(0.5, result);
	cout << "m * 0.5 = " << *dynamic_cast <Money*> (result) << endl;
	cout << "m * n   = " << m1->mult(n1) << endl;
	cout << "m / n   = " << m1->div(n1)  << endl;
	cout << "m == n? : " << (*m == *n)   << endl
		 << "m >= n? : " << (*m >= *n)   << endl
		 << "m <= n? : " << (*m <= *n)   << endl
		 << "m < n ? : " << (*m < *n)    << endl
		 << "m > n ? : " << (*m > *n)    << endl;
	delete M;
	delete N;
}

void Application::Money133_Test()
{
	cout << "        ~~~Test Money_Amount 1.24~~~        " << endl;
	cout << "Let's create some objects: " << endl;
	Pair* M(new Money_Amount), * N(new Money_Amount);
	Money_Amount* m = dynamic_cast <Money_Amount*> (M);
	Money_Amount* n = dynamic_cast <Money_Amount*> (N);
	Money_Amount* m1, * n1;
	cout << "m: ";
	cin >> *m;
	cout << "n: ";
	cin >> *n;
	if (*m < *n) {
		m1 = n;
		n1 = m;
	}
	else {
		m1 = m;
		n1 = n;
	}
	cout << endl << "Let's test some operations: " << endl;
	Pair* result(new Money_Amount);
	cout << "m       = " << *m << endl;
	cout << "n       = " << *n << endl;
	m1->sum(n1, result);
	cout << "m + n   = " << *dynamic_cast <Money_Amount*> (result) << endl;
	m1->sub(n1, result);
	cout << "m - n   = " << *dynamic_cast <Money_Amount*> (result) << endl;
	m1->div(0.5, result);
	cout << "n / 0.5 = " << *dynamic_cast <Money_Amount*> (result) << endl;
	n1->mult(0.5, result);
	cout << "m * 0.5 = " << *dynamic_cast <Money_Amount*> (result) << endl;
	cout << "m * n   = " << m1->mult(n1) << endl;
	cout << "m / n   = " << m1->div(n1) << endl;
	cout << "m == n? : " << (*m == *n) << endl
		<< "m >= n? : " << (*m >= *n) << endl
		<< "m <= n? : " << (*m <= *n) << endl
		<< "m < n ? : " << (*m < *n) << endl
		<< "m > n ? : " << (*m > *n) << endl;
	delete M;
	delete N;
}
