#include <cmath>
#include <iomanip>
#include <vector>
#include <span>
#include <algorithm>

#include "csvUtils.hpp"

using std::log, std::pow, std::sqrt;
using std::vector;
using std::span;
using std::max;

vector<double> getAllTimeLogReturns(span<double> close_data) {

    vector<double> logReturns = {};

    for (int i = 0; i < close_data.size() - 1; i++) {
        logReturns.push_back(
            log((double)close_data[i + 1] / (double)close_data[i]));
    }

    return logReturns;
}

double getAverage(span<double> data, bool sample=false) {
    double sum = 0.0;

    for (int i = 0; i < data.size(); i++) {
        sum += data[i];
    }
    if (sample) {
        return sum / ((double)data.size() - 1);
    } else {
        return sum / (double)data.size();
    }
}

double getStandardDeviation(span<double> data, bool sample=true) {
    double average = getAverage(data);

    vector<double> deviation = {};

    for (int i = 0; i < data.size(); i++) {
        deviation.push_back(pow(data[i] - average, 2));
    }

    double standardDeviation;
    if (sample) {
        standardDeviation = sqrt(getAverage(deviation, true));
    } else {
        standardDeviation = sqrt(getAverage(deviation));
    }
    return standardDeviation;
}

double getAnnualizedVolatility(double dailyStandardDeviation, int vol_time_period) {
    return dailyStandardDeviation * sqrt(252);
}

double getVolatility(span<double> closeLogReturns, int vol_time_period) {
    double standardDeviation = getStandardDeviation(closeLogReturns);
    double annualizedVolatility = getAnnualizedVolatility(standardDeviation, vol_time_period);

    return annualizedVolatility;
}

vector<double> get_moving_volatility(int window, stockDataStruct mainData) {
    vector<double> logReturns = getAllTimeLogReturns(mainData.Close);

    vector<double> avgVolatility(logReturns.size(), 0);

    for (int i = 2; i <= avgVolatility.size(); i++) {
        // Get a slice -> Calculate the standard deviation -> calculate the annualized volatility -> append it
        int initial_index = max(i-window, 0);
        span<double> view = span(logReturns).subspan(initial_index, i-initial_index);
        avgVolatility[i-1] = getVolatility(view, window);
    }

    avgVolatility.insert(avgVolatility.begin(), 0.0);
    return avgVolatility;

}