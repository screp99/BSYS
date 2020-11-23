#!/usr/bin/env python

import matplotlib.pyplot as plt
import numpy as np

data = np.genfromtxt("tlb.csv", delimiter=",", names=["x", "y"])

fig, ax = plt.subplots()
ax.set_xscale('log', basex=2)
ax.plot(data["x"], data["y"])
plt.xlabel("Number Of Pages")
plt.ylabel("Time Per Access (ns)")
plt.show()