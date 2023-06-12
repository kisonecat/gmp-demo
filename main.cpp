#include <iostream>
#include <fstream>
#include <iomanip>
#include <gmp.h>
#include <gmpxx.h>
#include <vector>

/* Read numbers from coeffs.txt which contains coefficients for a
 * series, i.e., the zero-indexed n-th line is c_n and the series is
 * sum_n c_n * x^n.
 *
 * The program outputs the coefficients for the series (sum_n c_n * x^n) / (x - b).
 */
 
int main() {
    mpf_class b("0.09876543210987654321");

    // set the default precision
    mpf_set_default_prec(1024); 

    std::ifstream file("coeffs.txt");
    if (!file) {
        std::cerr << "Could not open the file." << std::endl;
        return 1;
    }

    // a vector is a dynamically resizable array
    std::vector<mpf_class> coeffs;
    std::string line;

    // read lines from the file...
    while (std::getline(file, line)) {
        mpf_class num(line);
        // store them
        coeffs.push_back(num);
    }

    // allocate storage for the result
    std::vector<mpf_class> result(coeffs.size());
    
    result[0] = - coeffs[0] / b;
        
    // Solve the recurrence
    for (std::size_t i = 1; i < coeffs.size(); ++i) {
        result[i] = (result[i - 1] - coeffs[i]) / b;
    }

    // Print out the result
    for (std::size_t i = 0; i < coeffs.size(); ++i) {
        std::cout << std::setprecision(mpf_get_default_prec()) << result[i] << std::endl;
    }
    
    return 0;
}
