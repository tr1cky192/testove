#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void convertToWords(int n, char *result);
void convertCents(int cents, char *result);

const char *ones[] = {"", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
const char *teens[] = {"ten", "eleven", "twelve", "thirteen", "fourteen", "fifteen", "sixteen", "seventeen", "eighteen", "nineteen"};
const char *tens[] = {"", "", "twenty", "thirty", "forty", "fifty", "sixty", "seventy", "eighty", "ninety"};
const char *thousands[] = {"", "thousand", "million", "billion"};

void numberToWords(int n, char *result) {
    int part;
    int place = 0;
    
    if (n == 0) {
        strcpy(result, "zero dollars");
        return;
    }

    while (n > 0) {
        part = n % 1000;
        if (part != 0) {
            char temp[256] = "";
            convertToWords(part, temp);

            if (strlen(result) > 0) {
                char result_copy[256];
                strcpy(result_copy, result);
                sprintf(result, "%s %s %s", temp, thousands[place], result_copy);
            } else {
                sprintf(result, "%s %s", temp, thousands[place]);
            }
        }
        place++;
        n /= 1000;  
    }
}

void convertToWords(int n, char *result) {
    if (n >= 100) {
        sprintf(result, "%s hundred", ones[n / 100]);
        n %= 100;
        if (n > 0) {
            strcat(result, " ");
        }
    }
    if (n >= 20) {
        strcat(result, tens[n / 10]);
        n %= 10;
        if (n > 0) {
            strcat(result, "-");
            strcat(result, ones[n]);
        }
    } else if (n >= 10) {
        strcat(result, teens[n - 10]);
    } else if (n > 0) {
        strcat(result, ones[n]);
    }
}

void convertCents(int cents, char *result) {
    if (cents == 0) {
        return;
    }
    char temp[256] = "";
    if (cents >= 20) {
        strcat(temp, tens[cents / 10]);
        cents %= 10;
        if (cents > 0) {
            strcat(temp, "-");
            strcat(temp, ones[cents]);
        }
    } else if (cents >= 10) {
        strcat(temp, teens[cents - 10]);
    } else if (cents > 0) {
        strcat(temp, ones[cents]);
    }
    sprintf(result, "%s cents", temp);
}

int main() {
    double input;
    
    while (1) {
        printf("Enter an amount (-1 to exit): ");
        scanf("%lf", &input);

        if (input == -1) {
            printf("Exiting...\n");
            break;
        }

        if (input < 0 || input > 1000000000) {
            printf("Error: Enter a value between 0 and 1 billion.\n");
            continue;
        }

        int dollars = (int)input;
        int cents = (int)((input - dollars) * 100 + 0.5);  


        char result[1024] = "";
        numberToWords(dollars, result);


        if (dollars == 1) {
            strcat(result, " dollar");
        } else {
            strcat(result, " dollars");
        }

        if (cents > 0) {
            char cents_result[256] = "";
            convertCents(cents, cents_result);
            strcat(result, " and ");
            strcat(result, cents_result);
        }

        printf("Result: \"%s\"\n", result);
    }

    return 0;
}
