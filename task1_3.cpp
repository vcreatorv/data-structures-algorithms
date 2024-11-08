#include <iostream>

bool isPowerOfTwo(unsigned int number) {

	// если в записи числа хотя бы 2 единичных бита,
    // то в результате побитового "и" получится число
    // с хотя бы 1 единичным битом.
    // поэтому лишь в случае, когда в числе 1 единичный бит,
    // n&(n-1) = 0, а 1 единичный бит - есть степень двойки
    
    return (number > 0) && (number & (number - 1)) == 0;
}

int main()
{
    unsigned int number;
    
    std::cin >> number;
    
    if (isPowerOfTwo(number)) {
        std::cout << "OK";
    }
    
    else {
        std::cout << "FAIL";
    }

    return 0;
}