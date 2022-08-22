class Solution:
    def isPowerOfFour(self, n: int) -> bool:
        # Obvious case: integer power of four can not be nor zero nor negative
        if n <= 0:
            return False
        # First check that 'n' is not a power of two using nice trick (n & (n - 1))
        if n & (n - 1) != 0:
            return False
        # Here n is a power of two (n = 2 ** k). We need to check, that `k` is even, because when
        # `k` is even (say k = 2 * s), n = 2 ** k = 2 ** (2 * s) = 4 ** s, `n` is a power of four
        # In binary form `n` is 00...00100...000. The only `1` bit should be at even position, i.e.
        # bits 0, 2, 4, 6 and so on up to 30 inclusive. We will form a mask with all these bits set
        # mask = 0101 0101 0101 0101 0101 0101 0101 0101 (b) = 0x55555555
        return True if n | 0x55555555 == 0x55555555 else False
