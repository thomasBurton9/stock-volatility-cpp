#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>

#include "myHeader.hpp"

using std::cout, std::endl;
using std::vector;


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
