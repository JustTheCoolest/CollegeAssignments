#include <stdio.h>
#include <math.h>

int getGenerator(){
    int n;
    printf("Enter the degree of the family of polynomial generators: ");
    scanf("%d", &n);
    int generator = 0;
    for(int i = 0; i <= n; i++){
        int coeff;
        printf("Enter the coefficient of x^%d: ", n-i);
        scanf("%d", &coeff);
        generator = generator << 1;
        generator = generator | coeff;
    }
    return generator;        
}

int num_len(int n, int base){
    int len = 0;
    while(n > 0){
        n = n / base;
        len++;
    }
    return len;
}

int binary_len(int n){
    num_len(n, 2);
}

int decimal_len(int n){
    num_len(n, 10);
}

int reverse(int n, int base){
    int rev = 0;
    while(n > 0){
        rev = rev * base;
        rev = rev + (n % base);
        n = n / base;
    }
    return rev;
}

int binary_reverse(int n){
    reverse(n, 2);
}

int decimal_reverse(int n){
    reverse(n, 10);
}

int binary_read(int n){
    int bin = 0;
    while(n > 0){
        bin = bin << 1;
        bin = bin | (n % 10);
        n = n / 10;
    }
    return binary_reverse(bin);
}

int binary_print(int n){
    int length = binary_len(n);
    int dec = 0;
    while(n > 0){
        dec = dec * 10;
        dec = dec + (n % 2);
        n = n >> 1;
    }
    int response = decimal_reverse(dec);
    // printf("Binary length: %d\n", length);
    // printf("Decimal length: %d\n", decimal_len(response));
    response *= pow(10, (length - decimal_len(response)));
    return response;
}

int codeword_adjuster(int xor_dividend, int generator_len){
    int codeword_len = binary_len(xor_dividend);
    int diff = generator_len - codeword_len - 1;
    int codeword = binary_reverse(xor_dividend);
    codeword <<= diff;
    // printf("xor_dividend: %d\n", binary_print(xor_dividend));
    // printf("codeword_len: %d\n", codeword_len);
    // printf("diff: %d\n", diff);
    // printf("The codeword is: %d\n", binary_print(codeword));
    // printf("The codeword is: %d\n", codeword);
    return codeword;
}

int main(){
    // Inputs
    int generator, dataword;
    // printf("Enter the generator: ");
    // scanf("%d", &generator);
    generator = getGenerator();
    printf("Enter the dataword: ");
    scanf("%d", &dataword);

    // Debugging: Print inputs
    // printf("The generator is: %d\n", binary_print(generator));
    // printf("The dataword is: %d\n", binary_print(dataword));

    // Prep data
    // int generator_len = decimal_len(generator);
    // generator = binary_read(generator);
    int generator_len = binary_len(generator);
    int dataword_len = decimal_len(dataword);
    dataword = binary_read(dataword);
    int xor_divisor = binary_reverse(generator);
    int xor_dividend = binary_reverse(dataword);

    // Calculate CRC
    for(int i = 0; i < dataword_len; i++){
        // printf("Step %d: %d\n", i, binary_print(xor_dividend));
        if(xor_dividend % 2 == 1){
            xor_dividend = xor_dividend ^ xor_divisor;
        }
        xor_dividend = xor_dividend >> 1;
    }

    // Adjust codeword
    int codeword = codeword_adjuster(xor_dividend, generator_len);

    // Print result
    printf("The codeword is: %d\n", binary_print(codeword));
}