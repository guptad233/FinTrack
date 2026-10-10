
#ifndef PORTFOLIO_H
#define PORTFOLIO_H

#include <string>
#include <vector>

using namespace std;

struct Investment {
    string name;
    double amount;
    double annualReturn;
};

void addInvestment(vector<Investment>& portfolio);
void displayPortfolio(const vector<Investment>& portfolio);

#endif
