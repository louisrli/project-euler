package euler.solutions

import euler.helpers.{MiscUtils, ProjectEulerApp}

/**
 * Author: louis (7/27/12)
 */

object p53 extends ProjectEulerApp {
  def number = 53
  def text =
    """
      |There are exactly ten ways of selecting three from five, 12345:
      |123, 124, 125, 134, 135, 145, 234, 235, 245, and 345
      |
      |In combinatorics, we use the notation, 5C3 = 1. In general,
      |
      |nCr = n! / (r!(n - r)!) ,where r <= n, n! = n x (n - 1)...3 x 2x 1, and 0! = 1.
      |It is not until n = 23, that a value exceeds one-million: 23C10 = 1144066.
      |
      |How many, not necessarily distinct, values of  nCr, for 1 <= n <= 100, are greater than one-million?
    """

  def combination(n: BigInt, r: BigInt): BigInt =
    (n - r + BigInt(1) to n).product / (BigInt(1) to r).product
  val LIMIT = BigInt(1000000)

  // Counts the left half, then accounts for even n
  // i.e. n = 2 -> 0, 1, 2, if 1 > limit, should not be multiplied twice)
  printAnswer(
    (BigInt(23) to BigInt(100)).foldLeft[BigInt](0) (
      (total, n) => total + 2 * (BigInt(0) to n / 2).count(r => combination(n, r) > LIMIT) -
        MiscUtils.boolToInt(n % 2 == 0 && combination(n, n / 2) > LIMIT)
    )
  )

  val displayedAnswer = 4075

  // Brute force: for n <- 1 to 100, r <- 1 to n, compute factorial
  // Combinations follow the binomial expansion, so we can split them in a half
}
