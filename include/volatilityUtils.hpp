#pragma once

#include <vector>

std::vector<double> getAllTimeLogReturns(std::vector<int> close_data);
double getAverage(std::vector<double> data, bool sample = false);
double getStandardDeviation(std::vector<double> data, bool sample = true);
double getAnnualizedVolatility(double dailyStandardDeviation);
double getVolatility(std::vector<double> closeData);