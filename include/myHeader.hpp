#include <vector>
using std::vector;

#ifndef MYHEADER

#define MYHEADER

vector<double> getAllTimeLogReturns(vector<int> close_data);
double getAverage(vector<double> data, bool sample = false);
double getStandardDeviation(vector<double> data, bool sample = true);
double getAnnualizedVolatility(double dailyStandardDeviation);

#endif