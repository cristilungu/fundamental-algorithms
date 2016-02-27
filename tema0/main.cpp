#include <iostream>
#include <random>

using namespace std;

#define ERROR   0
#define SUCCESS 1

#define INPUT_FILE  "/home/cristi/Applications/GITHub/experiments/AF/teme/tema0/input.txt"
#define OUTPUT_FILE "/home/cristi/Applications/GITHub/experiments/AF/teme/tema0/output.txt"

#define MAX_SIZE 1000
#define INVALID -1234566789


#define FAIL(message) cout<<"[ERROR]"<<message<<endl;
#define CHECK(x, message) if(x == NULL) { FAIL(message); return ERROR; }
#define OK(x, message) if(x != SUCCESS) { FAIL(message); return ERROR; }
#define SET(var, value, message) {int val = value; if(val != INVALID) {var = val;} else {FAIL(message);}}
#define DUMP(varname) printf("[DUMP] %s = %d\n", #varname, varname);


#define AUTO
#define AUTO_SCRIPT "/home/cristi/Applications/GITHub/experiments/AF/teme/tema0/script.txt"
FILE* autoFile = NULL;

int ensureFileOpened(char filename[]) {
    if(autoFile == NULL) {
        autoFile = fopen(filename, "rt");
        CHECK(autoFile, "Could not open the autoscript");
    }
    return SUCCESS;
}

int readInt_kb();
int readInt_fl(FILE *f);

int readInt_i(char varname[]) {
    int read = 0;
    printf("[INPUT] %s = ", varname);
    #ifdef AUTO
        OK(ensureFileOpened(AUTO_SCRIPT), "Script missing or unreachable!");
        read = readInt_fl(autoFile);
        printf("%d\n", read);
    #else
        read = readInt_kb();
    #endif
    return read;
}
#define readInt(var) readInt_i(#var)

void read_i(int& var, char varname[]) {
    printf("[INPUT] %s = ", varname);
    SET(var, readInt_kb(), "Could not read int from keyboard");
}

#define read(var) read_i(var, #var)


int randomInt(int min, int max);
int *genRandomArray(int size, int min, int max);
int * genAscendingArray(int size, int min, int max);
int *genDescendingArray(int n, int min, int max);

int scale(double value, int min, int range);

int main() {
    //Exercise 1
    {
        //read int n
        //open a file
        //read n ints from inside
        //open another file
        //store the ints in reverse order
        int n = 0, v[MAX_SIZE];
        read(n);

        SET(n, readInt(n), "Could not read int from keyboard");

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
        SET(n, readInt(n), "Could not read int from keyboard");
        SET(lowerBound, readInt(lowerBound), "Could not read int from keyboard");
        SET(upperBound, readInt(upperBound), "Could not read int from keyboard");

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

int *genRandomArray(int size, int min, int max) {
    int *array = (int*)malloc(size*sizeof(int));
    for(int i = 0; i<size; i++) {
        array[i] = randomInt(min, max);
    }
    return array;
}

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

//int *genDescendingArray(int size, int min, int max) {
//    int *array = (int*)malloc(size*sizeof(int));
//    int lastMax = max;
//    for(int i = 0; i<size; i++) {
//        array[i] = randomInt(min, lastMax);
//        lastMax = array[i];
//    }
//    return array;
//}

//int *genAscendingArray(int size, int min, int max) {
//    int *array = (int*)malloc(size*sizeof(int));
//    int lastMin = min;
//    for(int i = 0; i<size; i++) {
//        array[i] = randomInt(lastMin, max);
//        lastMin = array[i];
//    }
//    return array;
//}

int randomInt(int min, int max) { return rand() % (max-min == 0 ? 1 : max - min) + min; }

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
