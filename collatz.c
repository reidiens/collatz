/*
    Collatz Conjecture Automator
    Ruben Toledo
    3/18/2024
    
    Find how many iterations it takes for a number to reach 1
    when the Collatz conjecture is applied
    
    - Prints the different iterations
    - Counts total number of iterations
    - Times how long certain actions take
    - Can output the data to a file
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <time.h>

typedef struct Array {
    int cap;
    int size;
    unsigned long *arr;
    float elapsed_ms;
} arr_t;

unsigned long checkargs(char *argv[], unsigned long *num);
unsigned char ulget(unsigned long *num);
int sixtypercent(int num);
arr_t collatz(unsigned long num);
unsigned char SaveToFile();
char* getFname();
unsigned char WriteFile(FILE *fp, arr_t a);

int main(int argc, char *argv[]) {
    unsigned long num;
    if (!checkargs(argv, &num)) {
        puts("input the starting value:");
        while (!ulget(&num))
            puts("\ntry again.\nhint: it has to be a positive, non-zero integer");
    }

    arr_t a = collatz(num);

    puts(" ");
    
    for (int i = 0; i < a.size; i++)
        printf("%lu\n", a.arr[i]);

    printf("\nthe number %lu takes %d iterations to reach 1.\n", a.arr[0], a.size - 1);
    printf("it took a total of %f milliseconds to finish calulations\n", a.elapsed_ms);

    puts("\nwrite to file? (y/n)");
    if (!SaveToFile()) return 0;

    puts("\nwhat do you wish to name the file?");
    puts("hit enter for default name (collatz-out)");

    char fname[32];
    fgets(fname, sizeof(fname), stdin);
    fname[strlen(fname) - 1] = '\0';

    if (strlen(fname) < 1)
        memccpy(fname, "collatz-out", 0, strlen("collatz-out"));
    
    puts("\ncreating file...");
    FILE *fp = fopen(fname, "w");
    if (fp == NULL) {
        fprintf(stderr, "couldn't open file :(\n");
        perror(strerror(errno));
        return -1;
    }

    if (!WriteFile(fp, a)) {
        fprintf(stderr, "could not write file :(\n");
        return -2;
    }

    if (fclose(fp) == EOF) {
        fprintf(stderr, "Could not close file (could not flush buffer)\n");
        perror(strerror(errno));
        return -3;
    }

    printf("file %s created!\n", fname);
    return 0;
}

unsigned long checkargs(char *argv[], unsigned long *num) {
    if (argv[1] == NULL) return 0;
    
    if (!sscanf(argv[1], "%lu", num)) return 0;
    return 1;
}


unsigned char ulget(unsigned long *num) {
    char temp[64];
    fgets(temp, sizeof(temp), stdin);

    if (strlen(temp) > 1) {
        if (!sscanf(temp, "%lu", num)) return 0;
        else return 1;
    }
    else return 0;
}

int sixtypercent(int num) {
    float temp = (float)num;
    return (int)(temp * 0.6);
}

arr_t collatz(unsigned long num) {
    arr_t a;

    a.cap = 5;
    a.size = 0;
    a.arr = malloc(a.cap * sizeof(unsigned long));
    a.arr[0] = num;
    a.size++;
    a.elapsed_ms = 0;

    clock_t time = clock();

    while (num != 1) {
        if (num % 2) {
            num = num * 3 + 1;

            time = clock() - time;
            a.elapsed_ms = a.elapsed_ms + ( ((float)time) / CLOCKS_PER_SEC ) * 1000;

            a.arr[a.size] = num;
            a.size++;

            if (a.size >= sixtypercent(a.cap)) {
                a.cap *= 2;
                a.arr = realloc(a.arr, a.cap * sizeof(unsigned long));
            }
        }
        else {
            num /= 2;

            time = clock() - time;
            a.elapsed_ms = a.elapsed_ms + ( ((float)time) / CLOCKS_PER_SEC) * 1000;

            a.arr[a.size] = num;
            a.size++;

            if (a.size >= sixtypercent(a.cap)) {
                a.cap *= 2;
                a.arr = realloc(a.arr, a.cap * sizeof(unsigned long));
            }
        }
    }

    a.cap = a.size;
    a.arr = realloc(a.arr, a.cap * sizeof(unsigned long));

    return a;
}

unsigned char SaveToFile() {
    char temp[8];
    fgets(temp, sizeof(temp), stdin);

    if (strlen(temp) < 1) return 0;

    if (temp[0] == 'y' || temp[0] == 'Y') return 1;
    return 0;
}

unsigned char WriteFile(FILE *fp, arr_t a) {
    if (fprintf(fp, "original number: %lu\n", a.arr[0]) < 0)
        return 0;

    for (int i = 0; i < a.size; i++)
        if (fprintf(fp, "%lu\n", a.arr[i]) < 0)
            return 0;

    if (fprintf(fp, "total iterations: %d\n", a.size - 1) < 0)
        return 0;
    if (fprintf(fp, "calculation time: %f ms\n", a.elapsed_ms) < 0)
        return 0;

    return 1;
}