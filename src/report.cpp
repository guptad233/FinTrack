
#include <fstream>
#include <iomanip>
#include "../include/report.h"
#include "../include/analytics.h"

using namespace std;

bool exportPortfolioCSV(const vector<Investment>& portfolio,
                        const char* filename) {
    ofstream file(filename);

    if (!file.is_open()) {
        return false;
    }

    double total = calculateTotalInvestment(portfolio);
    double weightedReturn = calculateWeightedReturn(portfolio);

    file << fixed << setprecision(2);

    // Investment details
    file << "Investment Name,Invested Amount,Expected Annual Return (%)\n";

    for (const Investment& investment : portfolio) {
        file << "\"" << investment.name << "\","
             << investment.amount << ","
             << investment.annualReturn << "\n";
    }

    // Portfolio summary
    file << "\nPortfolio Summary\n";
    file << "Total Investment,Weighted Expected Annual Return (%)\n";
    file << total << "," << weightedReturn << "\n";

    // Allocation details
    file << "\nPortfolio Allocation\n";
    file << "Investment Name,Allocation (%)\n";

    for (const Investment& investment : portfolio) {
        double allocation = (investment.amount / total) * 100.0;

        file << "\"" << investment.name << "\","
             << allocation << "\n";
    }

    // Projected portfolio values
    file << "\nProjected Portfolio Value\n";
    file << "Duration (Years),Projected Value (Rs.)\n";
    file << "1," << calculateProjectedValue(portfolio, 1) << "\n";
    file << "5," << calculateProjectedValue(portfolio, 5) << "\n";
    file << "10," << calculateProjectedValue(portfolio, 10) << "\n";

    file.close();
    return true;
}
