/**
 * Companion object and class for dealing with primes
 * @author Louis
 *
 */

package euler.helpers

/**
 * The companion object wraps the inner primes class
 * It needs to be "initialized" with a certain limit
 */

object Primes {
  private var helper : Primes = null

  def primeFactorization(n : Int) : Map[Int, Int] = {
    if (helper == null || helper.limit < n) {
      helper = new Primes(n)
    }

    def factor(m: Map[Int, Int], leftover: Int) : Map[Int, Int] = {
      if (leftover <= 1) m
      else {
        helper.factors(leftover) match {
          case None => m ++ Map(leftover -> (1 + m.getOrElse(leftover, 0)))
          case Some(num) => factor(m ++ Map(num -> (1 + m.getOrElse(num, 0))), leftover / num)
        }
      }
    }
    factor(Map(), n)
  /*  // Implementation: Simple trial division by examining primes only
    def inner(factored: Int, xs: List[Int], m: Map[Int, Int]) : Map[Int, Int] = {
      def divideCount(x: Int, d: Int, count: Int) : (Int, Int) =
        if (x % d == 0) divideCount(x / d, d, count + 1) else (x, count)

      xs match {
        case prime::xt => {
          val (leftover, exp) = divideCount(factored, prime, 0)
          if (exp != 0) inner(leftover, xt, m + (prime -> exp))
          else inner(leftover, xt, m)
        }
        case Nil => m
      }
    }

    inner(n, primesLEq(n).toList, Map[Int, Int]())*/
  }

  /** Initialize a prime sieve to a certain limit. Required to generate primes */
  def initializeSieve(lim: Int) = { helper = new Primes(lim) }

  def isPrime (x : Int) : Boolean = helper.sieve(x)
  def nthPrime(n: Int) : Int = helper.primes(n)

  def primes = helper.primes
  def primesLEq(n : Int) = helper.primes.dropRight(n - 1)

}

private class Primes(val limit: Int) {
  require(limit > 1)
  /**
   * `Sieve`: Sieve of Eratosthenes. sieve(n) returns whether n is prime
   * `Primes`: A list of primes up until limit
   * `Factors`: factors(n) returns a factor of n. convenient for factoring
   */
  private lazy val (sieve, primes, factors) = initializeSieve(limit + 1)

  private def initializeSieve(lim: Int): (Seq[Boolean], List[Int], Seq[Option[Int]]) = {
    // Let sieve(n) represent n for simplicity
    // The sieve itself is a pair (Bool, Option[Int]) where Option[Int] is a factor
    println("Initializing sieve...")
    val tmpSieve = Array.fill(lim)(true);
    val tmpFactors = Array.fill[Option[Int]](lim)(None)
    tmpSieve.update(0, false); tmpSieve.update(1, false)
    for (i <- 2 until lim if tmpSieve(i) == true) {
      for (j <- i * 2 until lim by i) {
        tmpSieve.update(j, false)
        tmpFactors.update(j, Some(i))
      }
    }
    (tmpSieve.toSeq, tmpSieve.indices.filter(tmpSieve(_) == true).toList, tmpFactors)
  }

}
