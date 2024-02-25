from scipy import signal
import numpy as np
import matplotlib.pyplot as plt


Li = (0.001 * 3)
Ri = (3.5 * 3)

Lg = (0.001 * 2)
Rg = (3.5 * 2)

Cf = (0.000001 * 4)
Rf = (0.0 * 4)


H_LCL1 = signal.TransferFunction([1],[(Li*Lg*Cf), 0, (Li*Lg), 0])
H_LCL2 = signal.TransferFunction([Rf*Cf, 1], [(Lg*Li*Cf), (Cf*(Lg*(Rf+Ri) + Li*(Rf+Rg))), (Lg+Li+Cf*(Rf*Rg + Rf*Ri + Rg*Ri)), Rg+Ri])

#print(H_LCL2)
resonance_angular_freq = np.sqrt((Li+Lg)/(Li*Lg*Cf))

w = np.linspace(0.1, 100000, num=1000000, endpoint=True)

w, mag, phase = signal.bode(H_LCL2, w=w)

#w = w * (np.pi/180)


plt.figure()
plt.title("Mag")
plt.semilogx(w, mag)    # Bode magnitude plot
plt.plot(w,mag)
plt.grid()
#plt.savefig("mag.png")

plt.figure()
plt.title("Phase")
plt.semilogx(w, phase)  # Bode phase plot
plt.plot(w, phase)
plt.grid()
#plt.savefig("phase.png")
plt.show()
