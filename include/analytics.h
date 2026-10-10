
#ifndef ANALYTICS_H
#define ANALYTICS_H

#include <vector>
#include "portfolio.h"

double calculateTotalInvestment(const vector<Investment>& portfolio);

double calculateWeightedReturn(const vector<Investment>& portfolio);

double calculateProjectedValue(
    const vector<Investment>& portfolio,
    int years
);

void analyzePortfolio(const vector<Investment>& portfolio);

#endif
