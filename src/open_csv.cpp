#include <chrono>
#include <cstdio>
#include <expected>
#include <fstream>
#include <print>
#include <string>
#include <vector>
#include <span>
#include "csvUtils.hpp"

using std::expected, std::unexpected;
using std::getline;
using std::ifstream;
using std::println;
using std::stod;
using std::stoi;
using std::string;
using std::vector;
using std::max;
using std::span;

string cleanDate(string date) {
    int whiteSpaceIndex;
    for (int i = 0; i < date.size(); i++) {
        if (date[i] == ' ') {
            whiteSpaceIndex = i;
            break;
        }
    }
    return date.substr(0, whiteSpaceIndex);
}

vector<string> splitLine(string line, char splitValue) {
    vector<string> output;
    string currentValue;
    for (int i = 0; i < line.size(); i++) {
        if (line[i] == splitValue) {
            output.push_back(currentValue);
            currentValue.clear();
        } else {
            currentValue.push_back(line[i]);
        }
    }
    output.push_back(currentValue);

    return output;
}

double getUnixTime(string full_date) {
    vector<string> dates = splitLine(full_date, '-');

    vector<int> int_dates = {stoi(dates[0]), stoi(dates[1]), stoi(dates[2])};

    auto date = std::chrono::year_month_day{std::chrono::year{int_dates[0]},
                                            std::chrono::month{static_cast<unsigned>(int_dates[1])},
                                            std::chrono::day{static_cast<unsigned>(int_dates[2])}};

    auto tp = std::chrono::sys_days(date);

    double ts = (double)std::chrono::duration_cast<std::chrono::seconds>(
                    tp.time_since_epoch())
                    .count();
    return ts;
}


expected<stockDataStruct, string> returnCsvStockData(string ticker, int time_period) {
    string filename =
        "../../data/" + ticker + "-10y-stock.csv"; // Temporary path for data

    ifstream myfile(filename);
    char c;

    if (!myfile.is_open()) {
        return unexpected("Unable to open file");
    }
    string line;
    int i = 0;
    vector<vector<string>> data;
    while (getline(myfile, line)) {
        if (i == 0) {
        } else {
            data.push_back(splitLine(line, ','));
        }
        i++;
    }

    if (data.size() < 3) {
        return unexpected("Not enough Data");
    }
    vector<double> tempDates;
    vector<vector<double>> tempData(7);

    int starting_index = max(0, static_cast<int>(data.size() - time_period));

    for (vector<string> line : span(data).subspan(starting_index, data.size() - starting_index - 1)) {
        vector<double> tempLine;
        for (int i = 1; i < line.size(); i++) {
            tempLine.push_back(stod(line[i]));
        }
        for (int i = 0; i < tempLine.size(); i++) {
            tempData[i].push_back(tempLine[i]);
        }
        tempDates.push_back(getUnixTime(cleanDate(line[0])));
    }
    stockDataStruct stockData(tempDates, tempData);

    return stockData;
}
