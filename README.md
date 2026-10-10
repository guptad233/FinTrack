# Personal Investment Portfolio Analyzer

A C++-based investment portfolio analysis tool with a Streamlit web interface. The application allows users to manage investments, analyze portfolio allocation, calculate weighted annual returns, and estimate future portfolio values.

The project combines **C++ for financial calculations** with **Python and Streamlit for the user interface**.

## Features

- **Investment Management:** Add investments with a name, invested amount, and expected annual return.
- **Portfolio Overview:** View all investments in a structured table.
- **Total Investment:** Calculate the total amount invested across the portfolio.
- **Weighted Annual Return:** Calculate the portfolio's weighted expected annual return based on individual investment amounts and expected returns.
- **Portfolio Allocation:** Visualize the percentage allocation of each investment using a pie chart.
- **Future Value Projections:** Estimate the portfolio's future value after 1, 5, and 10 years.
- **Investment Management Controls:** Remove individual investments or clear the entire portfolio.
- **CSV Export:** Download portfolio data for further analysis.

## Technologies Used

- **C++** — Core financial calculations and portfolio analytics.
- **Python** — Integration between the C++ executable and the web interface.
- **Streamlit** — Interactive web application.
- **Pandas** — Portfolio data management and tabular display.
- **Matplotlib** — Portfolio allocation visualization.
- **g++** — C++ compilation.

## Project Structure

```text
Investment-Portfolio-Analyzer/
│
├── include/
│   ├── portfolio.h
│   ├── analytics.h
│   └── report.h
│
├── src/
│   ├── main.cpp
│   ├── portfolio.cpp
│   ├── analytics.cpp
│   ├── report.cpp
│   └── bridge.cpp
│
├── reports/
│
├── app.py
├── cpp_bridge.py
├── portfolio_bridge.exe
├── README.md
└── .gitignore
```

The compiled executable, `portfolio_bridge.exe`, is generated during setup. It does not need to be committed to GitHub because users can compile it themselves.

## Prerequisites

Before running the application, ensure you have:

1. Python 3 installed.
2. A C++ compiler supporting C++14 or later, such as g++.
3. Git, if you want to clone the repository.

Verify your installations using:

```bash
python --version
g++ --version
git --version
```

On Windows, install a compatible g++ distribution, such as MinGW-w64, and ensure its `bin` directory is added to your system PATH.

## Installation and Setup

### 1. Clone the repository

```bash
git clone <YOUR_GITHUB_REPOSITORY_URL>
cd Investment-Portfolio-Analyzer
```

Replace `<YOUR_GITHUB_REPOSITORY_URL>` with the actual URL of your GitHub repository.

Alternatively, download the repository as a ZIP file and extract it.

### 2. Install Python dependencies

Run the following command from the project directory:

```bash
python -m pip install streamlit pandas matplotlib
```

### 3. Compile the C++ bridge

From the project's root directory, run:

```bash
g++ -std=c++14 src/bridge.cpp src/portfolio.cpp src/analytics.cpp -o portfolio_bridge.exe
```

This creates `portfolio_bridge.exe` in the project root.

The bridge accepts investment data from Python, invokes the existing C++ analytics functions, and returns the calculated results.

**Important:** Compile the bridge rather than `main.cpp` for the Streamlit application. The existing `main.cpp` belongs to the original console-based application.

### 4. Launch the application

Run:

```bash
python -m streamlit run app.py
```

Streamlit will provide a local URL, usually:

```text
http://localhost:8501
```

Open the URL in your browser to use the application.

## How to Use

### 1. Add investments

Enter the following details in the investment form:

- Investment name — for example, Mutual Funds.
- Amount invested — the amount invested in rupees.
- Expected annual return — the estimated annual percentage return.

Click **Add Investment** to add the entry to your portfolio.

### 2. Manage your portfolio

Review the investments in the portfolio table. You can remove a selected investment or clear the entire portfolio.

### 3. Analyze portfolio performance

Once you have added investments, the application displays:

- Total amount invested.
- Weighted expected annual return.
- Projected portfolio values after 1, 5, and 10 years.
- A line chart of projected values.
- A pie chart showing the portfolio allocation.

### 4. Export your data

Use the CSV download option to save the portfolio's investment names, invested amounts, and expected annual returns.

## Architecture

The application uses a simple integration between a C++ calculation engine and a Python-based interface.

```text
User
  |
  v
Streamlit Interface (app.py)
  |
  v
Python Bridge (cpp_bridge.py)
  |
  v
Compiled C++ Bridge (bridge.cpp)
  |
  v
Existing C++ Analytics Functions
  |
  v
Calculated Results
  |
  v
Streamlit Displays Results
```

- **Streamlit (`app.py`):** Collects investment inputs and presents portfolio results.
- **Python bridge (`cpp_bridge.py`):** Sends portfolio data to the compiled executable and parses its output.
- **C++ bridge (`src/bridge.cpp`):** Receives the investment records and calls the existing analytics functions.
- **Analytics module (`src/analytics.cpp`):** Calculates total investment, weighted return, and projected portfolio value.

This architecture keeps the main financial calculations in C++ while using Python for interface integration and visualization.

## Calculation Methodology

### Total Investment

The total investment is the sum of all individual investment amounts.

\[
T=\sum_{i=1}^{n} A_i
\]

### Weighted Expected Annual Return

The weighted return accounts for the amount invested in each asset.

\[
R_w=\frac{\sum_{i=1}^{n} A_iR_i}{\sum_{i=1}^{n}A_i}
\]

Here, \(A_i\) represents the amount invested and \(R_i\) represents the expected annual return percentage.

### Projected Portfolio Value

Each investment is projected independently using annual compounding.

\[
V_n=\sum_{i=1}^{n} A_i\left(1+\frac{R_i}{100}\right)^t
\]

Here, \(t\) is the number of years. The portfolio's projected value is the sum of the projected values of its individual investments.

## Assumptions and Limitations

- Expected returns are user-provided estimates, not guaranteed returns.
- Projections assume a constant annual return and annual compounding.
- The current model does not account for taxes, inflation, transaction fees, or additional contributions.
- Projections are mathematical estimates and do not predict actual market performance.
- Portfolio entries are maintained in the application's active session and are not automatically saved to a permanent database.
- The application runs locally and is not publicly hosted by default.

## Future Improvements

Potential extensions include:

- Persistent portfolio storage.
- Historical investment performance tracking.
- Risk and volatility analysis.
- Inflation-adjusted projections.
- Additional asset allocation visualizations.
- Portfolio comparison and benchmarking.

## Disclaimer

This project is intended for educational and analytical purposes only. It does not constitute financial advice or a recommendation to buy or sell any investment.
