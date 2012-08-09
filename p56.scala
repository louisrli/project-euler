package euler.solutions

import euler.helpers.{Digits, ProjectEulerApp}

/**
 * Author: louis (8/5/12)
 */

object p56 extends ProjectEulerApp {
  def number = 56

  def text = """A googol (10^100) is a massive number: one followed by one-hundred zeros;
                100^100 is almost unimaginably large: one followed by two-hundred zeros.
                Despite their size, the sum of the digits in each number is only 1.
               |
               |Considering natural numbers of the form, a^b, where a, b < 100,
               |what is the maximum digital sum?"""

  val GUESS = Digits.digitSum(BigInt(99).pow(99)).toInt
  val digitSums = for (a <- 1 to 100;
                       b <- 1 to 100
                       if (b * math.log10(a) * 9 >= GUESS))  // Predicts number of digits
  yield Digits.digitSum(BigInt(a).pow(b))

  println(digitSums.max)

  /* Strategy: make an arbitrary guess by computing a single large digit sum, D, first
   * After that, we should only search numbers, n, where numdigits(n) * 9 > D.
   * In other words, the maximum possible digit sum (9 * numdigits) should be greater
   * than our initial guess.
   *
   * println(digitSum.size) = 3335, cutting our search space by 1/3
   */

  val displayedAnswer = 972
}
