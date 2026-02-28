#include <charconv>
#include <expected>
#include <iostream>
#include <optional>
#include <print>
#include <string>
#include <vector>

#include "csvUtils.hpp"
#include "volatilityUtils.hpp"

using std::cin;
using std::errc;
using std::expected;
using std::from_chars;
using std::getline;
using std::nullopt;
using std::optional;
using std::print;
using std::println;
using std::string;
using std::unexpected;
using std::vector;

enum class StringError { EmptyInput };

optional<int> tryParseInt(const string &s) {
    int x;
    auto [ptr, error_code] = from_chars(s.data(), s.data() + s.size(), x);
    if (error_code == errc{} && ptr == s.data() + s.size()) {
        return x;
    }
    return nullopt;
}

expected<string, StringError> get_string() {
    string buffer;
    getline(cin, buffer);

    if (buffer.empty()) {
        return unexpected(StringError::EmptyInput);
    }

    return buffer;
}
bool get_user_values(int &time_period, int &vol_time_period, string &ticker) {
    bool success = false;
    while (true) {
        print("Please enter the time period in days: ");

        auto user_str_entry = get_string();

        if (!user_str_entry) {
            println("You need to enter something. Enter 'q' to quit or a "
                    "number for the time period.");
            continue;
        }
        if (user_str_entry == "q") {
            return success;
        }

        if (auto x = tryParseInt(*user_str_entry)) {
            time_period = *x;
            break;
        } else {
            println("That is not a number. Please enter 'q' to quit or a "
                    "number for the time period. ");
        }
    }
    while (true) {
        print("Please enter the volatility time period in days: ");

        auto user_str_entry = get_string();

        if (!user_str_entry) {
            println("You need to enter something. Enter 'q' to quit or a "
                    "number for the volatility time period.");
            continue;
        }
        if (user_str_entry == "q") {
            return success;
        }

        if (auto x = tryParseInt(*user_str_entry)) {
            vol_time_period = *x;
            break;
        } else {
            println("That is not a number. Please enter 'q' to quit or a "
                    "number for the volatility time period. ");
        }
    }
    while (true) {
        print("Please enter the ticker you want: ");
        auto user_str_entry = get_string();

        if (!user_str_entry) {
            println("You need to enter something. Enter 'q' to quit or a "
                    "ticker symbol.");
            continue;
        }
        ticker = *user_str_entry;
        success = true;
        return success;
    }
}
int main() {
    println("Welcome to the stock volatility grapher, enter 'q' at any time to "
            "quit");
    while (true) {
        int time_period, vol_time_period;
        string ticker;

        if (!get_user_values(time_period, vol_time_period, ticker)) {
            return 0;
        }
        auto stockData = returnCsvStockData(ticker);

        if (!stockData) {
            return 1;
        }

        vector<double> volatilityStockData =
            get_moving_volatility(vol_time_period, *stockData);

        for (int i = 0; i < volatilityStockData.size(); i++) {
            print("{:.3f} ", volatilityStockData[i]);
        }
        println("");
    }

    return 0;
}
