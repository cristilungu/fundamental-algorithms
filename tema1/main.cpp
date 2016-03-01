#include <iostream>

#include "utils.h"

void insertion_sort(int *A, int size);
void bubble_sort(int *A, int size);
void selection_sort(int *A, int size);

void exchange(int &a, int &b);
int indexOfMinimum(int first, int end, int *A);

void assertAscending(const int *rnd, int size);
void print(int *array, int size);

using namespace std;

int main() {
    int size = 10;
    int min = 0;
    int max = 100;

    //Exercise 1    (bubble sort)
    {
        int *rnd = genRandomArray(size, min, max);
        bubble_sort(rnd, size);
        assertAscending(rnd, size);
    }

    //Exercise 2    (insertion sort)
    {
        int *rnd = genRandomArray(size, min, max);
        insertion_sort(rnd, size);
        assertAscending(rnd, size);
    }

    //Exercise 3    (selection sort)
    {
        int *rnd = genRandomArray(size, min, max);
        selection_sort(rnd, size);
        assertAscending(rnd, size);

    }

    return 0;
}

void print(int *array, int size) {
    for(int i = 0; i<size; i++) {
        DUMP(array[i]);
    }
}

/**
 * [1] "Introduction To Algorithms, 3rd ed." Pag. 40
 * for i = 1 to A.length - 1
 *   for j = A.length downto i + 1
 *      if A[j] < A[j-1]
 *          exchange A[j] with A[j - 1]
 */
void bubble_sort(int *A, int size) {
    for(int i = 0; i<size-1; i++) {
        for(int j = size; j>= i+1; j--) {
            if(A[j]<A[j-1])
                exchange(A[j], A[j - 1]);
        }
    }
}


//can you find a way of doing the exchange without the aux variable?
void exchange(int &a, int &b) {
    int aux = a;
    a = b;
    b = aux;
}

/**
 * [2] "Introduction To Algorithms, 3rd ed." Pag. 18
 * for j = 2 to A.length
 *      key = A[j]
 *      //Insert A[j] into sorted sequence A[i...j-1]
 *      i = j - 1
 *      while i > 0 and A[i] > key
 *          A[i+1] = A[i]
 *          i = i - 1
 *      A[i+1] = key
 */
void insertion_sort(int *A, int size) {
    int i = 0;
    for (int j = 1; j < size; j++) {
        int key = A[j];
        i = j - 1;
        while (i > -1 && A[i] > key) {      //be careful when adapting a [1 to n] algo to a [0 to n-1] one!
            A[i + 1] = A[i];
            i = i - 1;
        }
        A[i + 1] = key;
    }
}

/**
 * for each element of the array
 *      search for the minimum element in the array beginning with the current one
 *      exchange the minimum found with the current one
 */
void selection_sort(int *A, int size) {
    for(int i = 0; i<size-1; i++) {
        int minim = indexOfMinimum(i, size, A);
        exchange(A[i], A[minim]);
    }
}

int indexOfMinimum(int first, int end, int *A) {
    int min = first;
    for(int i = first + 1; i < end; i++) {
        if(A[i] < A[min]) {
            min = i;
        }
    }
    return min;
}


void assertAscending(const int *rnd, int size) {
    for (int i = 0; i < size - 1; i++) {
        if (rnd[i] > rnd[i + 1]) {
            FAIL("Array is not sorted ascending!");
            DUMP(rnd[i]);
            DUMP(rnd[i + 1]);
            exit(ERROR);
        }
    }
}
