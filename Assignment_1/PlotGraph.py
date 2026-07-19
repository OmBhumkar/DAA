"""
PlotGraph.py
Plots empirical sorting-algorithm timing data on a log-scale graph.

Usage:
    python3 PlotGraph.py

Requires: matplotlib  (pip install matplotlib)

Data source: output of  g++ *.cpp -o Sort && ./Sort
"""

import matplotlib
matplotlib.use("Agg")   # non-interactive backend — no display needed
import matplotlib.pyplot as plt
import matplotlib.ticker as ticker
import numpy as np

# ── Empirical timing data (seconds) from a single run on this machine ────────
sizes = [1, 10, 100, 1_000, 10_000, 100_000]

# fmt: off
bubble    = [0.000000667, 0.000002000, 0.000217042, 0.002496250, 0.042755500, 6.998532542]
selection = [0.000000334, 0.000001458, 0.000056792, 0.001482542, 0.027136334, 1.539018458]
insertion = [0.000000375, 0.000001209, 0.000029833, 0.001196959, 0.013228584, 1.371856625]
merge     = [0.000000416, 0.000005083, 0.000037917, 0.000085916, 0.004829792, 0.008193625]
quick     = [0.000000334, 0.000003125, 0.000019959, 0.000188750, 0.000617292, 0.004417042]
heap      = [0.000000500, 0.000003708, 0.000048375, 0.000108750, 0.001042875, 0.008745083]
# fmt: on

# ── Plot ──────────────────────────────────────────────────────────────────────
fig, ax = plt.subplots(figsize=(11, 7))

ax.set_title("Sorting Algorithm Comparison — Log Scale\n(random input, measured on one machine)",
             fontsize=14, fontweight="bold", pad=14)

# O(n²) algorithms — warmer colours
ax.plot(sizes, bubble,    "o-",  color="#E84855", linewidth=2, markersize=6, label="Bubble Sort  — O(n²)")
ax.plot(sizes, selection, "s-",  color="#F4A261", linewidth=2, markersize=6, label="Selection Sort — O(n²)")
ax.plot(sizes, insertion, "^-",  color="#E9C46A", linewidth=2, markersize=6, label="Insertion Sort — O(n²)")

# O(n log n) algorithms — cooler colours
ax.plot(sizes, merge,     "D--", color="#2A9D8F", linewidth=2, markersize=6, label="Merge Sort  — O(n log n)")
ax.plot(sizes, quick,     "P--", color="#264653", linewidth=2, markersize=6, label="Quick Sort  — O(n log n)")
ax.plot(sizes, heap,      "h--", color="#457B9D", linewidth=2, markersize=6, label="Heap Sort   — O(n log n)")

# Log scale on both axes
ax.set_xscale("log")
ax.set_yscale("log")

ax.set_xlabel("Input Size  n", fontsize=12)
ax.set_ylabel("Time Taken (seconds)", fontsize=12)

# Show all input sizes on the x-axis
ax.set_xticks(sizes)
ax.get_xaxis().set_major_formatter(ticker.ScalarFormatter())
ax.xaxis.set_tick_params(which="minor", bottom=False)

ax.grid(True, which="both", linestyle="--", linewidth=0.5, alpha=0.6)
ax.legend(fontsize=10, loc="upper left")

plt.tight_layout()
plt.savefig("sorting_comparison_logscale.png", dpi=150)
print("Graph saved to  sorting_comparison_logscale.png")
