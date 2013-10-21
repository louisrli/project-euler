/**
 * Companion object and class for dealing with primes
 * @author Louis
 *
 */

package euler.helpers

import collection.mutable.BitSet

/**
 * The companion object wraps the inner primes class
 * It needs to be "initialized" with a certain limit
 */

object Primes {
  private var helper : Primes = null

  /** Finds the prime factorization using factors from the sieve. See Primes class. */
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
  }

  /** Initialize a prime sieve to a certain limit. Required to generate primes */
  def initializeSieve(lim: Int) = { helper = new Primes(lim) }

  def isPrime (x : Int) : Boolean =
    if (x > helper.limit) throw new IndexOutOfBoundsException(x.toString) else helper.sieve(x)

  def nthPrime(n: Int) : Int = helper.sieve.toIndexedSeq(n)

  def primes : List[Int] = helper.sieve.toList
  def primesLEq(n : Int) = helper.sieve.filter(_ <= n)

}

private class Primes(val limit: Int) {
  require(limit > 1)
  /**
   * `Sieve`: Sieve of Eratosthenes. sieve(n) returns whether n is prime
   * `Primes`: A list of primes up until limit
   * `Factors`: factors(n) returns a factor of n. convenient for factoring numbers known to be not-prime in the sieve.
   */
  private lazy val (sieve, factors) = initializeSieve(limit + 1)

  private def initializeSieve(lim: Int): (scala.collection.mutable.BitSet, Seq[Option[Int]]) = {
    // Uses a bitset to store whether a number is prime or not
    println("Initializing sieve...")
    val tmpSieve = scala.collection.mutable.BitSet()
    val searched = scala.collection.mutable.BitSet()
    val tmpFactors = Array.fill[Option[Int]](lim)(None)

    for (i <- 2 until lim if !searched(i)) {
      tmpSieve.add(i); searched.add(i)
      for (j <- i * 2 until lim by i) {
        searched.add(j)
        tmpFactors.update(j, Some(i))
      }
    }
    (tmpSieve, tmpFactors)
  }

}
