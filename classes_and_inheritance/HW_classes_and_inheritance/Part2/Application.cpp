#include "Application.h"
#include "Octal.h"
#include "Hex.h"

void Application::run()
{
	bool finished = false;
	while (!finished) {
		unsigned int input;
		cout << "Choose one of this options: " << endl
			 << "1) Test Octal"				   << endl
			 << "2) Test Hex"				   << endl
			 << "3) Exit"					   << endl;
		cin >> input;
		switch (input) {
		case 1:
			OctalTest();
			break;
		case 2: 
			HexTest();
			break;
		case 3:
			finished = true;
			break;
		default: 
			cout << "ERROR. THERE IS NO SUCH OPTION. TRY  AGAIN." << endl;
 		}
	}

}

void Application::OctalTest()
{
	cout << "        ~~~Test Octal~~~        " << endl;
	cout << "Let's create some objects: " << endl;
	Array *A(new Octal), *B(new Octal);
	Octal* aOct = dynamic_cast <Octal*> (A);
	Octal* bOct = dynamic_cast <Octal*> (B);
	Octal *mxOct, *mnOct;
	cout << "A: ";
	cin >> *aOct;
	cout << "B: ";
	cin >> *bOct;
	if (*aOct < *bOct) {
		mxOct = bOct;
		mnOct = aOct;
	}
	else {
		mxOct = aOct;
		mnOct = bOct;
	}
	cout <<  endl << "Let's test some operations: " << endl;
	
	Array* result(new Octal); //!!! Утечка памяти. Исправил
	
	A->sum(B, result);	
	cout << "A       = " <<	*aOct << endl;
	cout << "B       = " << *bOct << endl;
	cout << "A + B   = " << *dynamic_cast <Octal*> (result) << endl
		 << "A - B   = " << (*mxOct) - (*mnOct) << endl
		 << "A * B   = " << (*mxOct) * (*mnOct) << endl
		 << "A / B   = " << (*mxOct) / (*mnOct) << endl
		 << "A == B? : " << (*mxOct == *mnOct)  << endl
		 << "A != B? : " << (*mxOct != *mnOct)  << endl
		 << "A >= B? : " << (*mxOct >= *mnOct)  << endl
		 << "A <= B? : " << (*mxOct <= *mnOct)  << endl
		 << "A < B ? : " << (*mxOct < *mnOct)   << endl
		 << "A > B ? : " << (*mxOct > *mnOct)   << endl;
		 
	delete A; //!!! Применение delete не к тому указателю. Исправил
	delete B; //!!! Применение delete не к тому указателю. Исправил
	delete result;
}

void Application::HexTest()
{
	cout << "         ~~~Test Hex~~~         " << endl;
	cout << "Let's create some objects: " << endl;
	Array* A(new Hex), * B(new Hex);
	Hex* aHex = dynamic_cast <Hex*> (A);
	Hex* bHex = dynamic_cast <Hex*> (B);
	Hex *mxHex, *mnHex;
	cout << "A: ";
	cin >> *aHex;
	cout << "B: ";
	cin >> *bHex;
	if (*aHex < *bHex) {
		mxHex = bHex;
		mnHex = aHex;
	}
	else {
		mxHex = aHex;
		mnHex = bHex;
	}
	cout << endl << "Let's test some operations: " << endl;
	
	Array* result(new Hex); //!!! Утечка памяти. Исправил
	
	A->sum(B, result);
	cout << "A       = " << *aHex << endl;
	cout << "B       = " << *bHex << endl;
	cout << "A + B   = " << *dynamic_cast <Hex*> (result) << endl
		 << "A - B   = " << (*mxHex) - (*mnHex) << endl
		 << "A * B   = " << (*mxHex) * (*mnHex) << endl
		 << "A / B   = " << (*mxHex) / (*mnHex) << endl
		 << "A == B? : " << (*mxHex == *mnHex)  << endl
		 << "A != B? : " << (*mxHex != *mnHex)  << endl
		 << "A >= B? : " << (*mxHex >= *mnHex)  << endl
		 << "A <= B? : " << (*mxHex <= *mnHex)  << endl
		 << "A < B ? : " << (*mxHex < *mnHex)   << endl
		 << "A > B ? : " << (*mxHex > *mnHex)   << endl;
		 
	delete A; //!!! Применение delete не к тому указателю. Исправил
	delete B; //!!! Применение delete не к тому указателю. Исправил
	delete result;
}

