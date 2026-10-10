
import subprocess
from pathlib import Path

PROJECT_DIR = Path(__file__).resolve().parent

# Support both Windows and Linux/WSL
if (PROJECT_DIR / "portfolio_bridge.exe").exists():
    EXECUTABLE = PROJECT_DIR / "portfolio_bridge.exe"
else:
    EXECUTABLE = PROJECT_DIR / "portfolio_bridge"


def analyze_portfolio(investments):
    """
    investments: list of dictionaries containing:
        name, amount, annualReturn
    """

    if not EXECUTABLE.exists():
        raise FileNotFoundError(
            f"C++ executable not found: {EXECUTABLE}. "
            "Compile src/bridge.cpp first."
        )

    lines = [str(len(investments))]

    for item in investments:
        name = item["name"].replace("\\", "\\\\").replace('"', '\\"')

        lines.append(
            f'"{name}" {float(item["amount"])} '
            f'{float(item["annualReturn"])}'
        )

    input_data = "\n".join(lines) + "\n"

    result = subprocess.run(
        [str(EXECUTABLE)],
        input=input_data,
        capture_output=True,
        text=True,
        check=True
    )

    values = [float(line) for line in result.stdout.splitlines()]

    count = len(investments)

    if len(values) != 5 + count:
        raise ValueError(
            f"Unexpected output from C++ program: {result.stdout}"
        )

    return {
        "total_investment": values[0],
        "weighted_return": values[1],
        "projections": {
            1: values[2],
            5: values[3],
            10: values[4],
        },
        "allocations": values[5:],
    }
