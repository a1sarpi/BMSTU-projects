#include <iostream>
#include <iomanip>
#include "bubbleSortStatic.h"
#include "bubbleSortDynamic.h"
#include <Windows.h>


using namespace std;

void fillArray(int* arr, int arrLen) {
	for (int i = 0; i < arrLen; i++)
		arr[i] = rand() % 100;
}

void printArray(int* arr, int arrLen) {
	for (int i = 0; i < arrLen; i++)
		cout << setw(5) << arr[i];
}

int main() {
	int n = 0;
	cout << "|STATIC LIBRARY|" << endl;
	cout << "Enter number of elements in the array: " << endl;
	cin >> n;
	int* arr = new int[n];
	fillArray(arr, n);
	cout << "Our array: " << endl;
	printArray(arr, n);
	cout << endl << "Our sorted array: " << endl;
	bubbleSortStatic(arr, n);
	printArray(arr, n);
	delete[] arr;
	cout << endl << endl;
	cout << "|DYNAMIC LIB (implicit)|" << endl;
	cout << "Let's create an array. Write down number of elements in this array " << endl;
	cin >> n;
	arr = new int[n];
	fillArray(arr, n);
	printArray(arr, n);
	bubbleSortDynamic(arr, n);
	cout << endl << "Sorted Array: " << endl;
	printArray(arr, n);
	delete[] arr;
	cout << endl << endl;
	cout << "|DYNAMIC LIB (explicit)|" << endl;
	HINSTANCE load;
	load = LoadLibraryA("DynamicLib.dll");
	if (load != 0) {
		typedef void (*sort) (int*, int);
		sort bubbleSortDyn;
		bubbleSortDyn = (sort)GetProcAddress(load, "bubbleSortDynamic");
		if (bubbleSortDyn != 0) {
			cout << "Let's create an array. Write down number of elements in this array " << endl;
			cin >> n;
			arr = new int[n];
			fillArray(arr, n);
			cout << "Our array: " << endl;
			printArray(arr, n);
			bubbleSortDyn(arr, n);
			cout << endl << "Sorted Array: " << endl;
			printArray(arr, n);
			delete[] arr;
		}
		else cout << "Error during function loading" << endl;
		FreeLibrary(load);
	}
	else cout << "Error during library loading" << endl;
	cout << endl << endl;
	system("pause");
	return 0;
}