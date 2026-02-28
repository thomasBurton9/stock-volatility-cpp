#include <cmath>
#include <iomanip>
#include <vector>
#include <print>

#include "myHeader.hpp"

using std::vector;
using std::println;

int main() {
    vector<int> close_data = {3, 4, 5, 6, 7, 8, 3, 4};
    println("{:.20g}", getVolatility(close_data));
    displayCsvContents("PCLN-10y-stock.csv");
    return 0;
}
