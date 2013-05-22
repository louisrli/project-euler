package euler.solutions

import euler.helpers.{Digits, ProjectEulerApp}

/**
 * Author: louis (8/8/12)
 */

object p57 extends ProjectEulerApp {
  def number = 57

  def text =
    """
      |It is possible to show that the square root of two can be expressed as an infinite
      |continued fraction.
      |
      | 2 = 1 + 1/(2 + 1/(2 + 1/(2 + ... ))) = 1.414213...
      |
      |By expanding this for the first four iterations, we get:
      |
      |1 + 1/2 = 3/2 = 1.5
      |1 + 1/(2 + 1/2) = 7/5 = 1.4
      |1 + 1/(2 + 1/(2 + 1/2)) = 17/12 = 1.41666...
      |1 + 1/(2 + 1/(2 + 1/(2 + 1/2))) = 41/29 = 1.41379...
      |
      |The next three expansions are 99/70, 239/169, and 577/408, but the
      |eighth expansion, 1393/985, is the first example where the number of digits
      |in the numerator exceeds the number of digits in the denominator.
      |
      |In the first one-thousand expansions, how many fractions contain a numerator
      |with more digits than denominator?
    """

  val fractions: Stream[(BigInt, BigInt)] =
    Stream.cons((3, 2), Stream.cons((7, 5), fractions.zip(fractions.tail).map {
      case ((n1, d1), (n2, d2)) => ((2 * n2) + n1, (2 * d2) + d1)
    }))

  println(fractions.take(1000).count { case (n, d) => Digits.digitCount(n) > Digits.digitCount(d) } )
  val displayedAnswer = 153

  // Uses the following properties of continued fractions
  // where h_n is the nth numerator and k_n is the nth denominator:
  // h_n = a_n * h_(n - 1) + h_(n - 2)
  // k_n = a_n * k_(n - 1) + k_(n - 2)

}
