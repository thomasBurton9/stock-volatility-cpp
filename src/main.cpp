#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>

using std::cout, std::endl;
using std::log, std::pow, std::sqrt;
using std::vector;

vector<double> getAllTimeLogReturns(vector<int> close_data)
{

    vector<double> logReturns = {};

    for (int i = 0; i < close_data.size() - 1; i++)
    {
        logReturns.push_back(log((double)close_data[i + 1] / (double)close_data[i]));
    }

    return logReturns;
}

double getAverage(vector<double> data, bool sample = false)
{
    double sum = 0.0;

    for (int i = 0; i < data.size(); i++)
    {
        sum += data[i];
    }
    if (sample)
    {
        return sum / ((double)data.size() - 1);
    }
    else
    {
        return sum / (double)data.size();
    }
}

double getStandardDeviation(vector<double> data, bool sample = true)
{
    double average = getAverage(data);

    vector<double> deviation = {};

    for (int i = 0; i < data.size(); i++)
    {
        deviation.push_back(pow(data[i] - average, 2));
    }

    double standardDeviation;
    if (sample)
    {
        standardDeviation = sqrt(getAverage(deviation, true));
    }
    else
    {
        standardDeviation = sqrt(getAverage(deviation));
    }
    return standardDeviation;
}

double getAnnualizedVolatility(double dailyStandardDeviation)
{
    return dailyStandardDeviation * sqrt(252);
}
int main()
{
    vector<int> close_data = {3, 4, 5, 6, 7, 8, 3, 4};

    vector<double> logReturns = getAllTimeLogReturns(close_data);

    for (int i = 0; i < logReturns.size(); i++)
    {
        cout << std::setprecision(20) << logReturns[i] << " ";
    }
    double standardDeviation = getStandardDeviation(logReturns);

    cout << "\n" 
    << standardDeviation;
    double annualizedVolatility = getAnnualizedVolatility(standardDeviation);
    cout << "\n" 
    << annualizedVolatility;
    return 0;
}
