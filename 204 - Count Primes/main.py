import m204

x = m204.Solution()

# for n in range(44, 231, 3):
#     print(f"{n} - {x.countPrimes(n)}")

n = 3572
print(f"{n} - {x.countPrimes(n)}")

# M = 2 * 3  # Our modulus equals to 2*3 because we start 2's and 3's excluded
# coprimes = [1, 5]  # List of all numbers co-prime to modulus M

# for n in range(1, 4):
#     coprimes, phi, M = m204._getNextCoprimesList(coprimes, M, 100)
#     print(coprimes, phi, M)
#
