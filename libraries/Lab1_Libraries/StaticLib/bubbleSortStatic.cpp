#include "bubbleSortStatic.h"

void bubbleSortStatic(int* array, int arrLen) {
	for (int i = 0; i < arrLen - 1; i++) {
		for (int j = 0; j < arrLen - 1 - i; j++) {
			if (array[j + 1] < array[j]) {
				int tmp = array[j + 1];
				array[j + 1] = array[j];
				array[j] = tmp;
			}
		}
	}
}