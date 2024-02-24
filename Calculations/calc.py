import numpy as np

import matplotlib.pyplot as plt


N = int(2e3)
#x = np.linspace(0, 1, int(N))
x = np.zeros(N)
x1 = np.zeros(N)

radial_speed = (10*2*np.pi)/10e3

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

def transf_abc_to_alphabeta(a, b, c):
    alpha = (0.6666*a) + (-0.33333*b) + (-0.33333*c)
    beta = (0.57753*b) + (-0.57735*c)

    return [alpha, beta]

def transf_alphabeta_to_dq(alpha, beta, theta):
    d = np.cos(theta)*alpha + np.sin(theta)*beta
    q = -np.sin(theta)*alpha + np.cos(theta)*beta

    return [d, q]

def transf_dq_to_alphabeta(d, q, theta):
    alpha = np.cos(theta)*d + -np.sin(theta)*q
    beta = np.sin(theta)*d + np.cos(theta)*q

    return [alpha, beta]

def transf_alphabeta_to_abc(alpha, beta):
    a = alpha
    b = -0.5*alpha + 0.86602*beta
    c = -0.5*alpha + -0.86602*beta
    return [a, b, c]

def transf_abc_to_dq(a, b, c, theta):
    [alpha, beta] = transf_abc_to_alphabeta(a, b, c)
    [d, q] = transf_alphabeta_to_dq(alpha, beta, theta)
    return [d, q]

def transf_dq_to_abc(d, q, theta):
    [alpha, beta] = transf_dq_to_alphabeta(d, q, theta)
    [a, b, c] = transf_alphabeta_to_abc(alpha, beta)
    return [a, b, c]


Ud = 1.7
Uq = 0

for i in range(1, N):
    x[i] = x[i-1] + radial_speed
    if(x[i] > (2*np.pi)):
        x[i] -= 2*np.pi

for i in range(1, N):
    x1[i] = x[i-1] + radial_speed + np.pi
    if(x1[i] > (2*np.pi)):
        x1[i] -= 2*np.pi

[Ua, Ub, Uc] = transf_dq_to_abc(Ud, Uq, x)

plt.figure()
plt.plot(Ua)
plt.plot(Ub)
plt.plot(Uc)
plt.grid()
#plt.savefig("phases")
#plt.show()


[Ua, Ub, Uc] = transf_dq_to_abc(Ud, Uq, x1)

plt.figure()
plt.plot(Ua)
plt.plot(Ub)
plt.plot(Uc)
plt.grid()
#plt.savefig("phases")
plt.show()




