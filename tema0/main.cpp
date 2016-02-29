/**
  * Cristian Lungu <lungu.cristian@gmail.com>
  * 29.02.2016
  */

#include <iostream>
#include <random>

#define AUTO
#define AUTO_SCRIPT "/home/cristi/Applications/GITHub/experiments/AF/teme/tema0/script.txt"
#include "utils.h"


using namespace std;

#define INPUT_FILE  "/home/cristi/Applications/GITHub/experiments/AF/teme/tema0/input.txt"
#define OUTPUT_FILE "/home/cristi/Applications/GITHub/experiments/AF/teme/tema0/output.txt"

int main() {
    //Exercise 1
    {
        //read int n
        //open a file
        //read n ints from inside
        //open another file
        //store the ints in reverse order
        int n = 0, v[MAX_SIZE];
        readInt(n);
        FILE *in = fopen(INPUT_FILE, "rt");
        CHECK(in, "Invalid input file");
        for (int i = n - 1; i >= 0; i--) {
            SET(v[i], readInt_fl(in), "Could not read value");
            DUMP(v[i]);
        }
        fclose(in);

        FILE *output = fopen(OUTPUT_FILE, "wt");
        CHECK(output, "Could not open output file!");
        for (int i = 0; i < n; i++) {
            fprintf(output, "%d\n", v[i]);
        }
        fclose(output);
    }

    //Exercise 2
    {
        //read variable n, min and max
        //generate random array of size n with values between min and max
        //generate ascending array of size n with values between min and max
        //generate descending array of size n with values between min and max
        //save contents of random array into output.tx file

        int n=0, lowerBound, upperBound;
        readInt(n);
        readInt(lowerBound);
        readInt(upperBound);

        int *rnd = genRandomArray(n, lowerBound, upperBound);
        int *asc = genAscendingArray(n, lowerBound, upperBound);
        int *des = genDescendingArray(n, lowerBound, upperBound);

        FILE *output = fopen(OUTPUT_FILE, "wt");
        CHECK(output, "Could not open output file!");
        for (int i = 0; i < n; i++) {
            DUMP(asc[i]);
            fprintf(output, "%d\n", des[i]);
        }
        fclose(output);
    }
    return SUCCESS;
}

