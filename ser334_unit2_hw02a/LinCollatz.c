/**
* (basic description of the program or class)
*
* Completion time: 1 hrs
*
* @author Hung-ju, Acuna
* @version 2024-09-01
*/

////////////////////////////////////////////////////////////////////////////////
//INCLUDES
#include <stdio.h>

int termination(int n) {
    int count = 0;
    while(n != 1) {
        printf("N=%d\n", n);
        printf("Iterations: %d\n", count+1);
        if (n % 2 == 0) {
            n = n / 2;
        }
        else {
            n = 3 * n + 1;
        }
        count++;
    }
    return n;
}

int main(void)
{
    int input;
    char term;
    printf("Enter an integer for termination function :");
    while(scanf("%d%c", &input, &term) != 2 || term != '\n'){
        printf("Invalid input. Please enter an integer:");
        scanf("%d%c", &input, &term);
    }

    termination(input);
    printf("#########COMPLETED#########");
    return 0;
}
