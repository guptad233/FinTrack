
#include <iostream>
#include <limits>
#include <vector>

#include "../include/portfolio.h"
#include "../include/analytics.h"
#include "../include/report.h"

using namespace std;

void pressEnterToContinue() {
    cout << "\nPress Enter to return to the menu...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

int main() {
    vector<Investment> portfolio;
    int choice;

    do {
        cout << "\n========================================\n";
        cout << "    PERSONAL INVESTMENT PORTFOLIO ANALYZER\n";
        cout << "========================================\n";
        cout << "1. Add Investment\n";
        cout << "2. View Portfolio\n";
        cout << "3. Analyze Portfolio\n";
        cout << "4. Export Portfolio to CSV\n";
        cout << "0. Exit\n";
        cout << "========================================\n";
        cout << "Enter your choice: ";

        if (!(cin >> choice)) {
            cout << "Invalid input. Please enter a menu number.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            pressEnterToContinue();
            continue;
        }

        switch (choice) {
            case 1:
                addInvestment(portfolio);
                pressEnterToContinue();
                break;

            case 2:
                displayPortfolio(portfolio);
                pressEnterToContinue();
                break;

            case 3:
                analyzePortfolio(portfolio);
                pressEnterToContinue();
                break;

            case 4:
                if (portfolio.empty()) {
                    cout << "Add investments before exporting a report.\n";
                } else if (exportPortfolioCSV(
                               portfolio,
                               "reports/portfolio_report.csv")) {
                    cout << "Report exported to reports/portfolio_report.csv\n";
                } else {
                    cout << "Export failed. Ensure the reports folder exists.\n";
                }

                pressEnterToContinue();
                break;

            case 0:
                cout << "Thank you for using the Portfolio Analyzer!\n";
                break;

            default:
                cout << "Invalid choice. Select 0 to 4.\n";
                pressEnterToContinue();
        }

    } while (choice != 0);

    return 0;
}
