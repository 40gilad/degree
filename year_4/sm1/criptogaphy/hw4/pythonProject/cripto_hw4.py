import random
import math
import ctypes


# ------------------------ CRYPTO HW4 GILAD MEIR ------------------------#

# region Square & Multiply
def square_and_multiply(base, exponent, mod):
    bin_exp = bin(exponent)[3:]  # starts the number one after the lsb which = 1
    ans = base % mod  # lsb must be 1
    for bit in bin_exp:
        ans = (ans ** 2) % mod
        if bit == '1':
            ans = (ans * base) % mod
    return ans


# endregion

# region GCD
def euclidean_gcd(a, b):
    """
    | left{counter}    | right{counter}   | (amount{counter})
    | left{counter+1} | right{counter+1} | (amount{counter+1})
                        .
                       .
                      .
    | ignore         |          0       | ignore



    :param a:
    :param b:
    :return:
    """
    counter = 0
    table = {f'left{counter}': a, f'right{counter}': b, f'amount{counter}': 0}
    while table[f'right{counter}'] != 0:
        # go down in table until left is 0
        table[f'amount{counter}'] = (
            math.floor(table[f'left{counter}'] / table[f'right{counter}'])
        )

        counter += 1

        table[f'left{counter}'] = table[f'right{counter - 1}']
        table[f'right{counter}'] = table[f'left{counter - 1}'] % table[f'right{counter - 1}']

    return table[f'left{counter}']


# endregion

# region Question 1
def generate_odd_unsigned_long_long():
    random_32_bit_number = 1
    for _ in range(30):
        bit = random.randint(0, 1)
        random_32_bit_number = (random_32_bit_number << 1) | bit
    return (random_32_bit_number << 1) | 1


# endregion

# region Question 2

def rabin_miller(num_to_check, rounds=20):
    """
    :param num_to_check: odd 32-bit integer
    :return: bool: True if number is probably prime, False if its surly isn't
    """
    exp=num_to_check-1
    curr_round = rounds
    while rounds != 0:
        if 22 < num_to_check:
            a = random.randint(2, 22)
        else:
            a = random.randint(2, num_to_check)
        div = 1
        while curr_round != 0 and exp % 2 == 0:
            exp = int(exp / div)
            div=2
            ans = square_and_multiply(base=a,exponent=exp,mod=num_to_check)
            if ans != 1 and (ans - num_to_check) != -1:
                return (
                    False,
                    [
                        euclidean_gcd(num_to_check, ans + 1)
                        , euclidean_gcd(num_to_check, ans - 1)
                    ]
                )
            curr_round -= 1
        rounds -= 1

    return True, None


# endregion


if __name__ == "__main__":
    gcd = []
    is_prime, gcd = rabin_miller(75)
    kaki = 1
