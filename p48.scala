package euler.solutions

import euler.helpers._

/**
 * @author Louis
 *
 */

object p48 extends ProjectEulerApp {
  def number = 48
  def text =
    """
      |The series, 1^1 + 2^2 + 3^3 + ... + 10^10 = 10405071317.
      |
      |Find the last ten digits of the series, 1^1 + 2^2 + 3^3 + ... + 1000^1000.
    """

  // The most straight forward way is just to fold left summing i^i,
  // but this solution prevents us from dealing with numbers much larger than `val mod`
  // however, Scala doesn't have an unsigned long, so we still need BigInt
  val mod : BigInt = BigInt("10000000000")

  val a = (BigInt(1) to BigInt(1000)).foldLeft(BigInt(0))(
    (sum, i) => {
      val trim = (BigInt(1) to i).foldLeft(BigInt(1))(
        (prod, f) => if (prod < mod) prod * i else (prod * i) % mod
      )
      if (sum < mod) sum + trim else (sum + trim) % mod
    }
  )

  println(a)
}