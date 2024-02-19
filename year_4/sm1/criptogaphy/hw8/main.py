import sys
import os
import math

sys.path.append(os.path.abspath(r'C:\Users\40gil\Desktop\degree\year_4\sm1\criptogaphy\hw4'))
from PythonProject import cripto_hw4 as chw


# region Q3 - BSGS Algorithm

def BS_solve(generator, mod):
    mod_root_floor = int(math.sqrt(mod))
    BS = {}
    # BS:
    for j in range(1, mod_root_floor + 1):
        BS[j] = chw.square_and_multiply(generator, j, mod)
    return BS


# region modular inverse

def egcd(a, b):
    if a == 0:
        return (b, 0, 1)
    g, y, x = egcd(b % a, a)
    return (g, x - (b // a) * y, y)


def modinv(a, m):
    g, x, y = egcd(a, m)
    if g != 1:
        raise Exception('No modular inverse')
    return x % m


# endregion
def GS_solve(generator, result, mod, bs):
    mod_root_floor = int(math.sqrt(mod))
    generator_inverse = modinv(generator, mod)
    # result*k^i:
    k = chw.square_and_multiply(generator_inverse, mod_root_floor, mod)
    for i in range(1, mod_root_floor + 1):
        kaki = result * (chw.square_and_multiply(k, i, mod)) % mod
        for j in range(1, mod_root_floor + 1):
            if kaki == bs[j]:
                return i, j
    return -1, -1


def BSGS_solve(generator, result, mod):
    mod_root_floor = int(math.sqrt(mod))
    bs = BS_solve(generator=generator, mod=mod)

    # generator^j,=generator^(-1*sqrt(m)*i)
    i, j = GS_solve(generator=generator, result=result, mod=mod, bs=bs)
    return j + (mod_root_floor * i)


# endregion

# region Q4 - Pollard rho Algorithm

def pollard_solve(generator, result, mod):
    a, b = 1, 1
    print("i | %3 | r | a | b ")
    pol_res = {}
    for i in range(0, mod + 1):
        r = (chw.square_and_multiply(base=generator, exponent=a, mod=mod)
             *
             chw.square_and_multiply(base=result, exponent=b, mod=mod)
             % mod)
        pol_res[i] = {'r': r, 'comb': (a, b)}
        print(f"{i} | {r % 3} | {r} | {a} | {b} ")

        if  i!=0 and i % 2 == 0 and pol_res[i]['r'] == pol_res[i / 2]['r']:
            return pol_res[i]['comb'], pol_res[i / 2]['comb']
        if r % 3 == 0:
            a = (a + 1) % mod
        elif r % 3 == 1:
            b = (b + 1) % mod
        elif r % 3 == 2:
            a = (2 * a) % mod
            b = (2 * b) % mod


# endregion

if '__main__' == __name__:
    kaki = pollard_solve(2, 13, 59)
    pipi = 1
