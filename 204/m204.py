def _buildNextCoprimesList(coprimes: list, M: int) -> tuple[list, int, int]:
    """
    Building next co-primes list using previous one for new modulus M(i) = M(i-1) * P(i)
    :param coprimes: Current co-primes list
    :param M: Current modulus M(i-1) = P(1)*P(2)*P(i-1)
    :return: Tuple of (new list, totient, new modulus)
    """
    P = coprimes[1]
    cnew = []
    k = 0

    for _ in range(0, P):
        for x in coprimes:
            n = k + x
            if n % P != 0:
                cnew.append(n)
        k += M

    phi = len(coprimes) * (P - 1)  # New Euler's function for new modulus
    return cnew, phi, M * P


def _reduceCoprimesList(coprimes: list, N: int) -> list:
    """
    Reduce coprimes list, excluding all next prime multiples
    :param coprimes: Current co-primes list
    :param nMax: maximal value
    :return: New list
    """
    P = coprimes[1]
    kMax = N // coprimes[2]  # Using next to next prime to determine kMax
    cnew = [1]

    for x in coprimes[2:]:
        if x > kMax:
            break
        if x % P != 0:
            cnew.append(x)

    return cnew


class Solution:
    # Primes count for n = 0...5
    prime_count = (0, 0, 1, 2, 2, 3)

    def countPrimes(self, n: int) -> int:
        # Decrementing M, so we will count primes up to N including N itself
        if n > 0:
            n -= 1
        # Quick answer for small N
        if n < len(self.prime_count):
            return self.prime_count[n]

        # We will use principle of "Sieve of Eratosthenes" to count primes
        # We will assume that all 2's and 3's multiples already excluded from the Sieve,
        # so we count all numbers in form of 6*k + 1 and 6*k + 5 as prime candidates.
        # And we prepare to exclude composites that are 5's multiples

        # At each step we take next prime Pj and try to count all numbers in form of Pj * k,
        # where 1 < k <= floor(N/Pj) and k co-prime to modulus M = P1*P2*...*P(j-1)
        # (modulus is the product of all primes which multiples already excluded)

        M = 2 * 3           # Our modulus equals to 2*3 because we start 2's and 3's excluded
        coprimes = [1, 5]   # List of all numbers co-prime to modulus M
        phi = 2             # Euler function of M, i.e. Phi(M), equals to length of co-primes list
        P = coprimes[1]     # Our next prime Pj will always be the second number in co-primes list

        # Initial count of all prime candidates
        # +2 means we add "2" and "3" as primes; -1 means we remove "1"
        Cp = (n // M) * phi + 2 - 1
        r = n % M  # Taking in mind the reminder of division N by M
        if r == 5:
            Cp += 2  # Adding two last prime candidates 6*k + 1 and 6*k + 5
        elif r >= 1:
            Cp += 1  # Adding last prime candidate 6*k + 1

        while P * P <= n:
            kMax = n // P  # max value of k, so Pj * k <= N
            # Now we should count all k's such that 1 < k <= kMax and (k, M) = 1, i.e. co-prime to M
            cNums = (kMax // M) * phi  # At first, we count all full inclusions of co-primes list
            k = kMax % M  # At next, we take care of the remainder, to count co-primes element-wise
            for x in coprimes:
                if x <= k:
                    cNums += 1
                else:
                    break
            Cp -= (cNums - 1)

            # When there will be no more full inclusions, we don't need to build expensive co-primes list
            if kMax // M == 0:
                # If there are many elements in co-primes list, we go to reduce part of algorythm
                if len(coprimes) > 2:
                    coprimes = _reduceCoprimesList(coprimes, n)
                    P = coprimes[1] if len(coprimes) > 1 else n
                else:
                    P = n  # Just to skip reduce part of algorythm
                break

            # Well done for this step, preparing for next one (taking new prime, creating co-primes list)
            coprimes, phi, M = _buildNextCoprimesList(coprimes, M)
            P = coprimes[1]

        # Continue only by reducing co-primes list
        while P * P <= n:
            Cp -= (len(coprimes) - 1)
            # Well done for this step, preparing for next one (taking new prime, creating co-primes list)
            if len(coprimes) > 2:
                coprimes = _reduceCoprimesList(coprimes, n)
                P = coprimes[1] if len(coprimes) > 1 else n
            else:
                break

        return Cp


x = Solution()

# for n in range(44, 231, 3):
#     print(f"{n} - {x.countPrimes(n)}")

n = 100
print(f"{n} - {x.countPrimes(n)}")
