#include <cstdio>
#include <fstream>
#include <print>
#include <string>
#include <vector>

#include "myHeader.hpp"

using std::getline;
using std::ifstream;
using std::println;
using std::stod;
using std::string;
using std::vector;


struct stockDataStruct {
    string Date;
    double Open;
    double High;
    double Low;
    double Close;
    double Volume;
    double Dividends;
    double StockSplits;

    stockDataStruct(const string& date, const std::vector<double> &v) 
      : Date(date), Open(v[0]), High(v[1]), Low(v[2]), Close(v[3]), Volume(v[4]), Dividends(v[5]), StockSplits(v[6]) {}
    
};

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

int displayCsvContents(string filename) {
    ifstream myfile(filename);
    char c;

    if (!myfile.is_open()) {
        println("Unable to open file");
    }
    string line;
    int i = 0;
    string header;
    vector<vector<string>> data;
    while (getline(myfile, line)) {
        if (i == 0) {
            header = line;
        } else {
        data.push_back(splitLine(line, ','));
        }
        i++;
    }

    vector<string> headers = splitLine(header, ',');

    for (string header : headers) {
        println("{}", header);
    }

    vector<stockDataStruct> stockData;

    for (vector<string> line : data) {
        vector<double> tempLine;
        for (int i = 1; i < line.size(); i++) {
            tempLine.push_back(stod(line[i]));
        }
        stockDataStruct lineData(line[0], tempLine);
        stockData.push_back(lineData);
    }
    return 0;
}
