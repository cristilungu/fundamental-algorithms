/**
  * Cristian Lungu <lungu.cristian@gmail.com>
  * 29.02.2016
  */


#ifndef CLUNGU_UTILS_H
#define CLUNGU_UTILS_H

#include <iostream>
#include <random>
#include <malloc.h>
#include <stdlib.h>
#include <error.h>
#include <string.h>


#define FAIL(message) {std::cout<<"[ERROR]"<<message<<std::endl;}
#define CHECK(x, message) if(x == NULL) { FAIL(message); return ERROR; }
#define OK(x, message) if(x != SUCCESS) { FAIL(message); }
#define SET(var, value, message) {int val = value; if(val != INVALID) {var = val;} else {FAIL(message);}}
#define DUMP(varname) printf("[%s:%d] %s = %d\n", trim(__FILE__), __LINE__, #varname, varname);

#define ERROR   0
#define SUCCESS 1

#define MAX_SIZE 1000
#define INVALID -1234566789

FILE*scriptFile = NULL;

/**
 * Series functions
 */
int *genRandomArray(int size, int min, int max);
int *genAscendingArray(int size, int min, int max);
int *genDescendingArray(int n, int min, int max);


/**
 * Random utils
 */
int randomInt(int min, int max);

/**
 * IO functions
 */
#define readInt(var) readInt_i(var, #var)
int readInt_fl(FILE *f);
int readInt_kb();


int *genRandomArray(int size, int min, int max) {
    int *array = (int*) malloc(size * sizeof(int));
    for(int i = 0; i<size; i++) {
        array[i] = randomInt(min, max);
    }
    return array;
}

int randomInt(int min, int max) { return rand() % (max-min == 0 ? 1 : max - min) + min; }

double number(int n, double& lnCurMax) {
    lnCurMax = lnCurMax + log(drand48()) / n;
    return exp(lnCurMax);
}

int scale(double value, int min, int range) {
    return (int)(value * range + min);
}

// Efficient algorithm to generate ascending numbers
// [1] http://repository.cmu.edu/cgi/viewcontent.cgi?article=3483&context=compsci
int* genAscendingArray(int size, int min, int max) {
    int *array = (int*)malloc(size*sizeof(int));
    int range = max - min;
    double lnCurMax = 0.0;
    double biggestValue = number(size + 1, lnCurMax);
    for(int i=size; i>=1; i--) {
        double currentValue = number(i, lnCurMax);
        array[i - 1] = scale(currentValue / biggestValue, min, range);
    }
    return array;
}

int* genDescendingArray(int size, int min, int max) {
    int *array = (int*)malloc(size*sizeof(int));
    int range = max - min;
    double lnCurMax = 0.0;
    double biggestValue = number(size + 1, lnCurMax);
    for(int i=size; i>=1; i--) {
        double currentValue = number(i, lnCurMax);
        array[size - i - 1] = scale(currentValue / biggestValue, min, range);
    }
    return array;
}

/**
 * IO functions
 */
int ensureFileOpened(char filename[]) {
    if(scriptFile == NULL) {
        scriptFile = fopen(filename, "rt");
        CHECK(scriptFile, "Could not open the autoscript");
    }
    return SUCCESS;
}

void readInt_i(int &read, char varname[]) {
    printf("[INPUT] %s = ", varname);
    #ifdef AUTO
        OK(ensureFileOpened(AUTO_SCRIPT), "Script missing or unreachable!");
        SET(read, readInt_fl(scriptFile), "Could not read int from keyboard");
        printf("%d\n", read);
    #else
        SET(read, readInt_kb(), "Could not read int from keyboard");
    #endif
}

int readInt_fl(FILE *f) {
    int var = 0;
    if(fscanf(f, "%d\n", &var) != SUCCESS) {
        FAIL("Could not get int from file");
        var = INVALID;
    }
    return var;
}

int readInt_kb() {
    int var;
    if(scanf("%d", &var) != SUCCESS) {
        FAIL("Could not get int from keyboard");
        var = INVALID;
    }
    return var;
}

inline char separator()
{
#ifdef _WIN32
    return '\\';
#else
    return '/';
#endif
}

char* trim(char* str) {
    size_t length = strlen(str);
    size_t i = 0;
    for(i = length; str[i] != separator() && i>0; i--);
    return str + i;
}

#endif //TEMA0_UTILS_H
