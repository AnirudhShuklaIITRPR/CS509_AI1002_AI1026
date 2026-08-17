# Maxflow-Mincut Results

| File | V | E | Source | Sink | Expected Flow | Actual Flow | Cut Capacity | Time | Status |
|---|---:|---:|---:|---:|---:|---:|---:|---:|---|
| maxflow_10.txt | 10 | 17 | 0 | 9 | 43 | 43 | 43 | 0.004527 ms | Pass |
| maxflow_100.txt | 100 | 197 | 0 | 99 | 43 | 43 | 43 | 0.027010 ms | Pass |
| maxflow_1000.txt | 1,000 | 1,997 | 0 | 999 | 43 | 43 | 43 | 0.191163 ms | Pass |
| maxflow_10000.txt | 10,000 | 19,997 | 0 | 9,999 | 43 | 43 | 43 | 1.992343 ms | Pass |
| maxflow_50000.txt | 50,000 | 99,997 | 0 | 49,999 | 43 | 43 | 43 | 10.314469 ms | Pass |

All required tests satisfy Maximum Flow = Minimum Cut Capacity.
