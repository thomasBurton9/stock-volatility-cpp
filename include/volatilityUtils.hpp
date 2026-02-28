#pragma once

#include <vector>
#include <span>

std::vector<double> getAllTimeLogReturns(std::span<int> close_data);
double getAverage(std::span<double> data, bool sample = false);
double getStandardDeviation(std::span<double> data, bool sample = true);
double getAnnualizedVolatility(double dailyStandardDeviation, int vol_time_period);
double getVolatility(std::span<double> closeData, int vol_time_period);
std::vector<double> get_moving_volatility(int window, stockDataStruct mainData);