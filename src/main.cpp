#include <vector>
#include <print>
#include <expected>
#include <iostream>
#include <string>

#include "csvUtils.hpp"
#include "volatilityUtils.hpp"

using std::vector;
using std::println;
using std::print;
using std::expected;
using std::cin;
using std::unexpected;
using std::string;
using std::getline;
using std::ws;

enum class InputError { InvalidInt };
enum class StringError { EmptyInput };

expected<int, InputError> get_int() {
    int user_input;
    if (!(cin >> user_input)) {
        return unexpected(InputError::InvalidInt);
    }
    return user_input;
}

expected<string, StringError> get_string() {
    string buffer;
    getline(cin >> ws, buffer);

    if (buffer.empty()) {
        return unexpected(StringError::EmptyInput);
    }

    return buffer;
}

int main() {
    // Change to proper logic - a loop with proper exits
    print("Please enter the time period: ");

    auto time_period = get_int();

    if (!time_period) {
        return 1; 
    }
    print("Please enter the volatility time period: ");

    auto vol_time_period = get_int();

    if (!vol_time_period) {
        return 1;
    }

    print("Please enter the ticker you want: ");
    auto ticker = get_string();

    if (!ticker) {
        return 1;
    }
    vector<double> close_data = {3, 4, 5, 6, 7, 8, 3, 4};
    println("{:.20g}", getVolatility(close_data));

    auto stockData = returnCsvStockData("PCLN");
    return 0;
}
