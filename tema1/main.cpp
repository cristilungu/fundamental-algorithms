#include <iostream>

#include "utils.h"


struct Count {
    int compare = 0;
    int assign = 0;
};

void insertion_sort(int *A, int size, Count &counter);

void bubble_sort(int *A, int size, Count &count);

void selection_sort(int *A, int size);

void exchange(int &a, int &b);

int indexOfMinimum(int first, int end, int *A);

void assertAscending(const int *rnd, int size);

void print(int *array, int size);


using namespace std;

class Sort {
protected:
    Count counter;
public:
    virtual void sort(int *A, int size) = 0;
    virtual int *genBstCase(int size, int min, int max) = 0;
    virtual int *genWstCase(int size, int min, int max) = 0;
    virtual Count getCounter() { return counter; };
    virtual ~Sort() { }
};

class BubbleSort : public Sort {
public:
    /**
     * [1] "Introduction To Algorithms, 3rd ed." Pag. 40
     * for i = 1 to A.length - 1
     *   for j = A.length downto i + 1
     *      if A[j] < A[j-1]
     *          exchange A[j] with A[j - 1]
     */
    void sort(int *A, int size) {
        for (int i = 0; i < size - 1; i++) {
            for (int j = size; j >= i + 1; j--) {
                counter.compare++;
                if (A[j] < A[j - 1]) {
                    exchange(A[j], A[j - 1]);
                    counter.assign += 3;
                }
            }
        }
    }

    int *genBstCase(int size, int min, int max) {
        // ?!
        return NULL;
    }

    int *genWstCase(int size, int min, int max) {
        // ?!
        return NULL;
    }
};

class InsertionSort : public Sort {
public:
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
    void sort(int *A, int size) {
        int i = 0;
        for (int j = 1; j < size; j++) {
            int key = A[j];
            i = j - 1;
            while (i > -1 && A[i] > key) {      //be careful when adapting a [1 to n] algo to a [0 to n-1] one!
                A[i + 1] = A[i];
                i = i - 1;
                counter.compare += 1;
                counter.assign += 1;
            }
            A[i + 1] = key;
            counter.assign += 2;
        }
    }

    int *genBstCase(int size, int min, int max) {
        // ?!
        return NULL;
    }

    int *genWstCase(int size, int min, int max) {
        // ?!
        return NULL;
    }
};

class SelectionSort : public Sort {
private:
    int indexOfMinimum(int first, int end, int *A) {
        int min = first;
        for (int i = first + 1; i < end; i++) {
            if (A[i] < A[min]) {
                min = i;
            }
        }
        return min;
    }

public:
    /**
     * for each element of the array
     *      search for the minimum element in the array beginning with the current one
     *      exchange the minimum found with the current one
     */
    void sort(int *A, int size) {
        for (int i = 0; i < size - 1; i++) {
            int minim = indexOfMinimum(i, size, A);
            exchange(A[i], A[minim]);
        }
    }

    int *genBstCase(int size, int min, int max) {
        // ?!
        return NULL;
    }

    int *genWstCase(int size, int min, int max) {
        // ?!
        return NULL;
    }
};

int main() {
    int size = 10;
    int min = 0;
    int max = 100;

    //Exercise 1    (bubble sort)
    {
        int *rnd = genRandomArray(size, min, max);
        Sort* bubble = new BubbleSort();
        bubble->sort(rnd, size);
        assertAscending(rnd, size);
    }

    //Exercise 2    (insertion sort)
    {
        int *rnd = genRandomArray(size, min, max);
        Sort* insert = new InsertionSort();
        insert->sort(rnd, size);
        assertAscending(rnd, size);
    }

    //Exercise 3    (selection sort)
    {
        int *rnd = genRandomArray(size, min, max);
        Sort* selec = new SelectionSort();
        selec->sort(rnd, size);
        assertAscending(rnd, size);

    }

    //Best case analysis
    {
        Sort* insert = new BubbleSort();
        Sort* select = new InsertionSort();
        Sort* bubble = new SelectionSort();

        insert->sort(
                insert->genBstCase(size, min, max),
                size
        );

        bubble->sort(
                bubble->genBstCase(size, min, max),
                size
        );

        select->sort(
                select->genBstCase(size, min, max),
                size
        );

        DUMP(insert->getCounter().assign);
        DUMP(bubble->getCounter().assign);
        DUMP(select->getCounter().assign);
    }

    //Worst case analysis
    {
        Sort* insert = new BubbleSort();
        Sort* select = new InsertionSort();
        Sort* bubble = new SelectionSort();

        insert->sort(
                insert->genWstCase(size, min, max),
                size
        );

        bubble->sort(
                bubble->genWstCase(size, min, max),
                size
        );

        select->sort(
                select->genWstCase(size, min, max),
                size
        );

        DUMP(insert->getCounter().assign);
        DUMP(bubble->getCounter().assign);
        DUMP(select->getCounter().assign);
    }
    return 0;
}

void print(int *array, int size) {
    for (int i = 0; i < size; i++) {
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
void bubble_sort(int *A, int size, Count &count) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = size; j >= i + 1; j--) {
            if (A[j] < A[j - 1]) {
                count.compare++;
                exchange(A[j], A[j - 1]);
                count.assign += 3;
            }
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
void insertion_sort(int *A, int size, Count &counter) {
    int i = 0;
    for (int j = 1; j < size; j++) {
        int key = A[j];
        i = j - 1;
        while (i > -1 && A[i] > key) {      //be careful when adapting a [1 to n] algo to a [0 to n-1] one!
            A[i + 1] = A[i];
            i = i - 1;
            counter.compare += 1;
            counter.assign += 1;
        }
        A[i + 1] = key;
        counter.assign += 2;
    }
}

/**
 * for each element of the array
 *      search for the minimum element in the array beginning with the current one
 *      exchange the minimum found with the current one
 */
void selection_sort(int *A, int size) {
    for (int i = 0; i < size - 1; i++) {
        int minim = indexOfMinimum(i, size, A);
        exchange(A[i], A[minim]);
    }
}

int indexOfMinimum(int first, int end, int *A) {
    int min = first;
    for (int i = first + 1; i < end; i++) {
        if (A[i] < A[min]) {
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
