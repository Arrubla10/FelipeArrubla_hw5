import numpy as np
import corner
import matplotlib.pyplot as plt

d = np.loadtxt("data.dat")
x = d[:,0]
y = d[:,1]

data = np.zeros( (x.shape[0], 2) )
data[:,0] = x.copy()
data[:,1] = y.copy()

figure = corner.corner(data, bins=30, labels=[r"$x$", r"$y$"],
                        quantiles=[0.16, 0.5, 0.84],
                        show_titles=True, title_kwargs={"fontsize": 12})
figure.savefig('test.png',dpi=300)
