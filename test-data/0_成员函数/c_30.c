/*
0_成员函数.md
为struct BigInteger添加add和multiply成员函数
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure to represent a big integer
struct BigInteger {
    int* digits;      // Array to store digits (in reverse order for easier arithmetic)
    int length;       // Number of digits
    int sign;         // Sign of the number (1 for positive, -1 for negative)
};

// Function to initialize a BigInteger
void initBigInteger(struct BigInteger* num, const char* str) {
    int len = strlen(str);
    int start = 0;
    
    // Check for sign
    if (str[0] == '-') {
        num->sign = -1;
        start = 1;
        len--;
    } else {
        num->sign = 1;
    }
    
    // Allocate memory for digits
    num->length = len;
    num->digits = (int*)malloc(len * sizeof(int));
    
    // Store digits in reverse order for easier arithmetic
    for (int i = 0; i < len; i++) {
        num->digits[i] = str[start + len - 1 - i] - '0';
    }
}

// Function to free a BigInteger
void freeBigInteger(struct BigInteger* num) {
    free(num->digits);
    num->digits = NULL;
    num->length = 0;
}

// Function to print a BigInteger
void printBigInteger(struct BigInteger* num) {
    if (num->sign == -1) {
        printf("-");
    }
    
    for (int i = num->length - 1; i >= 0; i--) {
        printf("%d", num->digits[i]);
    }
    printf("\n");
}

// Function to add two BigIntegers
void add(struct BigInteger* a, struct BigInteger* b, struct BigInteger* result) {
    // Determine the maximum length needed for the result
    int maxLen = (a->length > b->length) ? a->length : b->length;
    result->digits = (int*)malloc((maxLen + 1) * sizeof(int)); // +1 for possible carry
    result->length = 0;
    
    int carry = 0;
    
    // Add corresponding digits from both numbers
    for (int i = 0; i < maxLen || carry; i++) {
        int sum = carry;
        
        if (i < a->length) {
            sum += a->digits[i];
        }
        
        if (i < b->length) {
            sum += b->digits[i];
        }
        
        result->digits[result->length++] = sum % 10; // Store the last digit
        carry = sum / 10; // Carry the remaining digits
    }
    
    // Set the sign (simplified: assumes both numbers are positive)
    result->sign = 1;
    
    // Remove leading zeros
    while (result->length > 1 && result->digits[result->length - 1] == 0) {
        result->length--;
    }
}

// Function to multiply two BigIntegers
void multiply(struct BigInteger* a, struct BigInteger* b, struct BigInteger* result) {
    // Allocate memory for the result
    int resultLen = a->length + b->length;
    result->digits = (int*)calloc(resultLen, sizeof(int)); // Initialize with zeros
    result->length = resultLen;
    
    // Multiply each digit of a with each digit of b
    for (int i = 0; i < a->length; i++) {
        int carry = 0;
        
        for (int j = 0; j < b->length || carry; j++) {
            int current = result->digits[i + j] + carry;
            
            if (j < b->length) {
                current += a->digits[i] * b->digits[j];
            }
            
            result->digits[i + j] = current % 10;
            carry = current / 10;
        }
    }
    
    // Set the sign
    result->sign = a->sign * b->sign;
    
    // Remove leading zeros
    while (result->length > 1 && result->digits[result->length - 1] == 0) {
        result->length--;
    }
}

int main() {
    struct BigInteger num1, num2, sum, product;
    
    // Initialize two big integers
    initBigInteger(&num1, "12345678901234567890");
    initBigInteger(&num2, "98765432109876543210");
    
    // Add the two big integers
    add(&num1, &num2, &sum);
    
    // Multiply the two big integers
    multiply(&num1, &num2, &product);
    
    // Print the results
    printf("Number 1: ");
    printBigInteger(&num1);
    
    printf("Number 2: ");
    printBigInteger(&num2);
    
    printf("Sum: ");
    printBigInteger(&sum);
    
    printf("Product: ");
    printBigInteger(&product);
    
    // Free memory
    freeBigInteger(&num1);
    freeBigInteger(&num2);
    freeBigInteger(&sum);
    freeBigInteger(&product);
    
    return 0;
}
