package euler.solutions

import euler.helpers._

/**
 * @author Louis
 *
 */

object p47 extends ProjectEulerApp {

  def number = 47
  def text =
    """
      |The first two consecutive numbers to have two distinct prime factors are:
      |
      |14 = 2 x 7
      |15 = 3 x 5
      |
      |The first three consecutive numbers to have three distinct prime factors are:
      |
      |644 = 2² x 7 x 23
      |645 = 3 x 5 x 43
      |646 = 2 x 17 x 19.
      |
      |Find the first four consecutive integers to have four distinct primes factors. What is the first of these numbers?
    """

  val GUESS = 2000000
  Primes.initializeSieve(GUESS)

  /**
   * This solution first narrows the solution space by iterating through the list of primes
   * and only going for those that have at least a gap of 4, since a prime only has one distinct prime factor.
   * It then performs a prime factorization of the sequence and searches for 4 consecutive "four-counts"
   * of distinct primes.
   */
  def find (xs: List[Int]) : Option[Int] = {
    xs match {
      case p1::p2::xt => {
        if (p2 - p1 <= 4) find(p2::xt)
        else {
          println("Examining primes %d and %d (delta %d)..." format (p1, p2, p2 - p1))

          // For each number, find the size of the prime factorization map (i.e. the distinct factors)
          // then find whether there exist 4 consecutive numbers with 4 distinct factors
          val distinctCounts: Map[Int, Int] = (p1 + 1 until p2)
            .map(s => (s, Primes.primeFactorization(s).size)).toMap
          def isConsecutive (m1: Map[Int, Int]) : ((Int, Int)) => Boolean =
            { case (k, v) => !((k until k + 4).exists(m1(_) != 4)) }

          distinctCounts
            .filter({ case (k, _) => k + 3 < p2})
            .find(isConsecutive(distinctCounts)) match {
            case None => find(p2::xt)
            case Some((x, y)) => {
              println("Answer found: " + (x until x + 4).map(distinctCounts(_)))
              Some(x)
            }
          }
        }
      }
      case p::xt => None
      case Nil => None
    }
  }
  println(find(Primes.primes))

  /**
   * Scratch
   * narrow: search list of primes where x_(n + 1) - x(n) > = 4
   */
}
