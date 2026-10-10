
#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include "../include/portfolio.h"
#include "../include/analytics.h"

using namespace std;

int main() {
    vector<Investment> portfolio;

    int count;
    cin >> count;

    if (cin.fail() || count < 0) {
        return 1;
    }

    for (int i = 0; i < count; i++) {
        Investment investment;
        cin >> quoted(investment.name)
            >> investment.amount
            >> investment.annualReturn;

        if (cin.fail() ||
            investment.name.empty() ||
            investment.amount <= 0 ||
            investment.annualReturn < 0) {
            return 1;
        }

        portfolio.push_back(investment);
    }

    cout << fixed << setprecision(2);

    cout << calculateTotalInvestment(portfolio) << '\n';
    cout << calculateWeightedReturn(portfolio) << '\n';
    cout << calculateProjectedValue(portfolio, 1) << '\n';
    cout << calculateProjectedValue(portfolio, 5) << '\n';
    cout << calculateProjectedValue(portfolio, 10) << '\n';

    for (const Investment& investment : portfolio) {
        double allocation =
            investment.amount / calculateTotalInvestment(portfolio) * 100.0;

        cout << allocation << '\n';
    }

    return 0;
}
