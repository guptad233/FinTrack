
#ifndef REPORT_H
#define REPORT_H

#include <vector>
#include "portfolio.h"

bool exportPortfolioCSV(const vector<Investment>& portfolio,const char* filename);

#endif