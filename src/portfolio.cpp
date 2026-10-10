
#include <iostream>
#include <iomanip>
#include "../include/portfolio.h"

using namespace std;

void addInvestment(vector<Investment>& portfolio) {
    Investment investment;

    cout << "\nEnter investment name: ";
    getline(cin >> ws, investment.name);

    cout << "Enter invested amount (Rs.): ";
    cin >> investment.amount;

    cout << "Enter expected annual return (%): ";
    cin >> investment.annualReturn;

    if (cin.fail() || investment.amount <= 0 ||
        investment.annualReturn < 0) {
        cout << "Invalid investment details. Investment not added.\n";
        cin.clear();
        cin.ignore(10000, '\n');
        return;
    }

    portfolio.push_back(investment);
    cout << "Investment added successfully!\n";
}

void displayPortfolio(const vector<Investment>& portfolio) {
    if (portfolio.empty()) {
        cout << "\nNo investments added yet.\n";
        return;
    }

    cout << fixed << setprecision(2);
    cout << "\n=============== YOUR PORTFOLIO ===============\n";
    cout << left << setw(22) << "Investment"
         << setw(18) << "Amount (Rs.)"
         << "Expected Return (%)\n";

    cout << string(60, '-') << "\n";

    for (const Investment& investment : portfolio) {
        cout << left << setw(22) << investment.name
             << setw(18) << investment.amount
             << investment.annualReturn << "%\n";
    }

    cout << string(60, '=') << "\n";
}
