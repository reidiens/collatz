/*
    Collatz Conjecture Automator
    Ruben Toledo
    1/29/2024
    
    Find how many iterations it takes for a number to reach 1
    when the Collatz conjecture is applied
    
    - Prints the different iterations
    - Counts total number of iterations
    - Times how long certain actions take
    - Can output the data to a file
*/

#include <stdio.h>
#include <string.h>
#include <time.h>
#include <errno.h>

unsigned char ulget(unsigned long *num);            // get the user input (ulget = unsigned long get)
void collatz(unsigned long num, FILE *stream);      // do the conjecture & print it
unsigned char savequery();                          // process whether the user wants to output to file
unsigned char savedata(unsigned long num);          // output to file
unsigned char checkargs(char *argv[], unsigned long *num);  // check the command line arguments

int main(int argc, char *argv[]) {
    unsigned long num;

    if (!checkargs(argv, &num)) {
        printf("input a number: ");
        while (!ulget(&num))
            puts("try again:");
    }

    collatz(num, stdout);

    puts("\nsave to a file? (y/n)");

    if (!savequery()) return 0;

    if (!savedata(num)) return -1;
        
    return 0;
}

unsigned char ulget(unsigned long *num) {
    char temp[64];      // 64 is arbitrary
    long temp_num;
    fgets(temp, sizeof(temp), stdin);

    if (strlen(temp) > 1) {
        if (sscanf(temp, "%lu", &temp_num)) {
            if (temp_num <= 0) return 0;
            *num = temp_num;
            return 1;
        }
        return 0;
    }
    return 0;
}

void collatz(unsigned long num, FILE *stream) {
    unsigned long temp = num;
    int count = 0;

    fprintf(stream, "%lu\n", temp);

    clock_t time = clock();
    float elapsed_time = 0;

    while (temp > 1) {
        if (temp % 2) {
            temp = temp * 3 + 1;

            time = clock() - time;
            elapsed_time = elapsed_time + (((float)time) / CLOCKS_PER_SEC);

            count++;
        }
        else {
            temp /= 2;

            time = clock() - time;
            elapsed_time = elapsed_time + (((float)time) / CLOCKS_PER_SEC);

            count++;
        }
        fprintf(stream, "%lu\n", temp);
    }
    float elapsed_ms = elapsed_time * 1000;

    fprintf(stream, "\nthe number %lu takes %d iterations to reach 1.\n", num, count);

    if (elapsed_time * 1000 >= 250)     // 250 is arbitrary XD
        fprintf(stream, "it took %f milliseconds (%f seconds) to finish iterating.\n", elapsed_ms, elapsed_time);

    else 
        fprintf(stream, "it took %f milliseconds (%f microseconds) to finish iterating.\n", elapsed_ms, elapsed_ms * 1000);

}

unsigned char savequery() {
    char ans = getchar();
    
    switch (ans) {
        case '\n':
        case 'Y':
        case 'y': return 1;
        default: return 0;
    }
}

unsigned char savedata(unsigned long num) {
    FILE *fp = fopen("collatz_data", "w");
    if (fp == NULL) {
        perror(strerror(errno));
        return 0;
    }

    clock_t time = clock();
    collatz(num, fp);
    time = clock() - time;

    float elapsed_ms = ( ((float)time) / CLOCKS_PER_SEC ) * 1000;
    printf("\nfile saved successfully :)\n");
    printf("it took %f milliseconds (%f microseconds) to write the output file.\n\n", elapsed_ms, elapsed_ms * 1000);

    if (fclose(fp)) {
        perror(strerror(errno));
        return 0;
    }

    return 1;
}

unsigned char checkargs(char *argv[], unsigned long *num) {
    if (argv[1] == NULL) return 0;
    
    unsigned long temp;
    if (sscanf(argv[1], "%lu", &temp)) {
        if (temp <= 0) return 0;
        *num = temp;
        return 1;
    }
    return 0;
}