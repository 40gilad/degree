import random

#------------------------ CRYPTO HW4 GILAD MEIR ------------------------#

#region square&multiply
def square_and_multiply(base,exponent,mod):
    bin_exp=bin(exponent)[3:]#starts the number one after the lsb which = 1
    ans=base%mod #lsb must be 1

    for bit in bin_exp:
        ans=(ans**2)%mod
        if bit == '1':
            ans=(ans*base)%mod
    return ans


#endregion

#region GCD

#endregion

#region Question 1
def generate_odd_unsignedLongLong():
    random_32_bit_number = 1
    for _ in range(30):
        bit = random.randint(0, 1)
        random_32_bit_number = (random_32_bit_number << 1) | bit
    return (random_32_bit_number << 1) | 1

#endregion

#region Question 2

def rabin_miller(num_to_check,rounds=20):
    """
    :param num_to_check: odd 32-bit integer
    :return: bool: True if number is probably prime, False if its surly isn't
    """
    exp=num_to_check-1

#endregion
if __name__=="__main__":
    square_and_multiply(base=3,exponent=97,mod=101)