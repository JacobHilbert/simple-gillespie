import sys
import numpy as np
import matplotlib.pyplot as plt


fig,ax = plt.subplots(len(sys.argv)-1)

for i,fname in enumerate(sys.argv[1:]):
	ax[i].plot(*(np.genfromtxt(fname).T),c='k')
	ax[i].set_title(fname[:-4])
fig.subplots_adjust(hspace=0.5)
plt.savefig("graph.pdf");
#plt.show()
