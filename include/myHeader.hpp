#include <vector>
#include <string>
using std::vector;
using std::string;

#ifndef MYHEADER

#define MYHEADER

// VOLATILITY
vector<double> getAllTimeLogReturns(vector<int> close_data);
double getAverage(vector<double> data, bool sample = false);
double getStandardDeviation(vector<double> data, bool sample = true);
double getAnnualizedVolatility(double dailyStandardDeviation);
double getVolatility(vector<int> closeData);

// CSV

int displayCsvContents(string filename);

#endif