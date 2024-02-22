import numpy as np




N = int(10e3)
x = np.linspace(0, 1, int(N))

Uab = 2.7*np.sin(x)
Uac = 2.7*np.sin(x + 1.0472)
Ubc = 2.7*np.sin(x + 2.0944)
Ua = np.zeros(N)
Ub = np.zeros(N)
Uc = np.zeros(N)
UaRMS = np.zeros(N)
UbRMS = np.zeros(N)
UcRMS = np.zeros(N)
Ia = np.zeros(N)
Ib = np.zeros(N)
Ic = np.zeros(N)
IaRMS = np.zeros(N)
IbRMS = np.zeros(N)
IcRMS = np.zeros(N)




def calc_Uxx_to_Uxn(Uab, Uac, Ubc):
    Ua = (Uab + Uac)/3
    Ub = (Ubc - Uab)/3
    Uc = -Ua-Ub

    return [Ua, Ub, Uc]


[Ua, Ub, Uc] = calc_Uxx_to_Uxn(Uab, Uac, Ubc)


UaRMS = np.sqrt(np.mean(Ua**2))
UbRMS = np.sqrt(np.mean(Ub**2))
UcRMS = np.sqrt(np.mean(Uc**2))

RMS = (UaRMS + UbRMS + UcRMS)/3

print(RMS)

