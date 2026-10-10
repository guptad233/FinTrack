
#include <iostream>
#include <iomanip>
#include "../include/analytics.h"

using namespace std;

double calculateTotalInvestment(const vector<Investment>& portfolio) {
    double total = 0.0;

    for (const Investment& investment : portfolio) {
        total += investment.amount;
    }

    return total;
}

double calculateWeightedReturn(const vector<Investment>& portfolio) {
    double total = calculateTotalInvestment(portfolio);

    if (total == 0.0) {
        return 0.0;
    }

    double weightedSum = 0.0;

    for (const Investment& investment : portfolio) {
        weightedSum += investment.amount * investment.annualReturn;
    }

    return weightedSum / total;
}

double calculateProjectedValue(
    const vector<Investment>& portfolio,
    int years
) {
    double total = 0.0;

    for (const Investment& investment : portfolio) {
        double amount = investment.amount;

        for (int year = 0; year < years; year++) {
            amount *= (1.0 + investment.annualReturn / 100.0);
        }

        total += amount;
    }

    return total;
}

void analyzePortfolio(const vector<Investment>& portfolio) {
    if (portfolio.empty()) {
        cout << "\nAdd investments before running analysis.\n";
        return;
    }

    double total = calculateTotalInvestment(portfolio);
    double weightedReturn = calculateWeightedReturn(portfolio);

    cout << fixed << setprecision(2);
    cout << "\n========== PORTFOLIO ANALYSIS ==========\n";
    cout << "Total Invested: Rs. " << total << "\n";
    cout << "Weighted Expected Annual Return: "
         << weightedReturn << "%\n";

    cout << "\nPortfolio Allocation:\n";

    for (const Investment& investment : portfolio) {
        double allocation = (investment.amount / total) * 100.0;

        cout << investment.name << ": "
             << allocation << "% of portfolio\n";
    }

    cout << "\nProjected Portfolio Value:\n";

    cout << "After 1 year: Rs. "
         << calculateProjectedValue(portfolio, 1) << "\n";

    cout << "After 5 years: Rs. "
         << calculateProjectedValue(portfolio, 5) << "\n";

    cout << "After 10 years: Rs. "
         << calculateProjectedValue(portfolio, 10) << "\n";

    cout << "\nHighest Expected Return:\n";

    const Investment* best = &portfolio[0];

    for (const Investment& investment : portfolio) {
        if (investment.annualReturn > best->annualReturn) {
            best = &investment;
        }
    }

    cout << best->name << " at "
         << best->annualReturn << "% annually\n";

    cout << "\n=======================================\n";
}
