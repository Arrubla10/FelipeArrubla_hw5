import numpy as np
import corner

d = np.loadtxt("data.dat")
m = np.array(d[:,0])
b = np.array(d[:,1])

data = np.zeros( (m.shape[0], 2) )
data[:,1] = m.copy()
data[:,0] = b.copy()

figure = corner.corner(data, labels=[r"$\mathrm{Log}(M_{\mathrm{sol}})$", r"$\alpha$"],
                        quantiles=[0.16, 0.5, 0.84],
                        show_titles=True, title_kwargs={"fontsize": 12})
figure.savefig('test.png',dpi=300)

