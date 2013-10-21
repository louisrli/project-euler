package euler.solutions

import euler.helpers._

/**
 * @author Louis
 * After completing problem 50, I was curious as to how others solved it. It seemed that the more common (procedural)
 * solution was to subtract from the top, which was much more simple and elegant. I wanted to make sure that I
 * understood, but I made a quick and dirty (very dirty) solution that chains `List` functions together to simulate
 * short-circuited, opposite-indexed, nested for-loops.
 */

object p50fast extends ProjectEulerApp {
  val LIMIT = 1000000
  Primes.initializeSieve(LIMIT)

  def generatePrimeSums(primes: List[Int], sums: List[Int]) : List[Int] = {
    val (ph, sh) = (primes.head, sums.head)
    primes match {
      case Nil => sums
      case _ if (ph + sh > LIMIT) => sums
      case ph::pt => generatePrimeSums(pt, (ph + sh)::sums)
    }
  }
  val primeSums = generatePrimeSums(Primes.primes, List(0))
  val rev = primeSums reverse
  // Ugly one-liner: Takes a descending list of prime sums and finds the first prime sum where, when subtracted by
  // an ascending prime sum (rev), yields a prime number. Prints the number as a side-effect of the computation
  val ans = primeSums find (x =>
    rev.map(y => if (x > y) Some(x - y) else None)
      exists (z => { val t = z exists (Primes.isPrime); if (t) println(z); t } ) )

  def number = p50.number
  def text = p50.text
  val displayedAnswer = 997651
}
