#pragma once

#include <expected>
#include <string>
#include <vector>

struct stockDataStruct {
    std::vector<std::string> Dates;
    std::vector<double> Open;
    std::vector<double> High;
    std::vector<double> Low;
    std::vector<double> Close;
    std::vector<double> Volume;
    std::vector<double> Dividends;
    std::vector<double> StockSplits;

    stockDataStruct(const std::vector<std::string>& dates, const std::vector<std::vector<double>> &v) 
      : Dates(dates), Open(v[0]), High(v[1]), Low(v[2]), Close(v[3]), Volume(v[4]), Dividends(v[5]), StockSplits(v[6]) {}
    
};

std::expected<stockDataStruct, std::string> returnCsvStockData(std::string ticker);