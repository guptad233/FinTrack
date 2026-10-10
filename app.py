
import streamlit as st
import pandas as pd
import matplotlib.pyplot as plt

from cpp_bridge import analyze_portfolio

st.set_page_config(
    page_title="Investment Portfolio Analyzer",
    page_icon="📈",
    layout="wide"
)

st.title("📈 Personal Investment Portfolio Analyzer")
st.caption("Investment analysis powered by your existing C++ calculations")

if "investments" not in st.session_state:
    st.session_state.investments = []

st.subheader("Add an Investment")

with st.form("investment_form", clear_on_submit=True):
    name = st.text_input("Investment name", placeholder="e.g. Mutual Funds")
    amount = st.number_input(
        "Amount invested (₹)",
        min_value=0.01,
        value=1000.0,
        step=500.0
    )
    annual_return = st.number_input(
        "Expected annual return (%)",
        min_value=0.0,
        max_value=1000.0,
        value=8.0,
        step=0.5
    )

    submitted = st.form_submit_button("Add Investment")

    if submitted:
        if not name.strip():
            st.error("Please enter an investment name.")
        else:
            st.session_state.investments.append({
                "name": name.strip(),
                "amount": amount,
                "annualReturn": annual_return
            })
            st.success(f"{name.strip()} added successfully!")

investments = st.session_state.investments

st.divider()
st.subheader("Your Portfolio")

if investments:
    df = pd.DataFrame([
        {
            "Investment": item["name"],
            "Amount (₹)": item["amount"],
            "Expected Return (%)": item["annualReturn"]
        }
        for item in investments
    ])

    st.dataframe(df, use_container_width=True, hide_index=True)

    selected_index = st.selectbox(
        "Select an investment to remove",
        options=list(range(len(investments))),
        format_func=lambda i: investments[i]["name"]
    )

    if st.button("Remove Selected Investment"):
        investments.pop(selected_index)
        st.rerun()

    if st.button("Clear Entire Portfolio"):
        st.session_state.investments = []
        st.rerun()

    st.divider()
    st.subheader("Portfolio Analysis")

    try:
        results = analyze_portfolio(investments)

        col1, col2 = st.columns(2)

        with col1:
            st.metric(
                "Total Invested",
                f"₹{results['total_investment']:,.2f}"
            )

        with col2:
            st.metric(
                "Weighted Annual Return",
                f"{results['weighted_return']:.2f}%"
            )

        st.subheader("Projected Portfolio Value")

        projection_data = pd.DataFrame({
            "Years": ["Today", "1 Year", "5 Years", "10 Years"],
            "Projected Value (₹)": [
                results["total_investment"],
                results["projections"][1],
                results["projections"][5],
                results["projections"][10]
            ]
        })

        st.dataframe(
            projection_data,
            use_container_width=True,
            hide_index=True
        )

        chart_data = projection_data.set_index("Years")
        st.line_chart(chart_data)

        st.subheader("Portfolio Allocation")

        allocation_df = pd.DataFrame({
            "Investment": [item["name"] for item in investments],
            "Allocation (%)": results["allocations"]
        })

        fig, ax = plt.subplots()
        ax.pie(
            allocation_df["Allocation (%)"],
            labels=allocation_df["Investment"],
            autopct="%1.1f%%",
            startangle=90
        )
        ax.axis("equal")
        st.pyplot(fig)
        plt.close(fig)

        st.download_button(
            "Download Portfolio CSV",
            data=df.to_csv(index=False).encode("utf-8"),
            file_name="portfolio.csv",
            mime="text/csv"
        )

    except Exception as error:
        st.error(f"Could not run the C++ analysis: {error}")

else:
    st.info("Add an investment above to begin your analysis.")
