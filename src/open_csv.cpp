#include <cstdio>
#include <fstream>
#include <print>
#include <string>
#include <vector>
#include <expected>

#include "csvUtils.hpp"

using std::getline;
using std::ifstream;
using std::println;
using std::stod;
using std::string;
using std::vector;
using std::expected, std::unexpected;

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

expected<stockDataStruct, string> returnCsvStockData(string ticker) {
    string filename = "data/" + ticker + "-10y-stock.csv";

    ifstream myfile(filename);
    char c;

    if (!myfile.is_open()) {
        println("Unable to open file");
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

    vector<string> tempDates;
    vector<vector<double>> tempData;

    for (vector<string> line : data) {
        vector<double> tempLine;
        for (int i = 1; i < line.size(); i++) {
            tempLine.push_back(stod(line[i]));
        }
        tempData.push_back(tempLine);
        tempDates.push_back(line[0]);
    }
    stockDataStruct stockData(tempDates, tempData);

    return stockData;
}
