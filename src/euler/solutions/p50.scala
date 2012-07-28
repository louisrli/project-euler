package euler.solutions

import euler.helpers._

/**
 * @author Louis
 *
 */

object p50 extends ProjectEulerApp {
  def number = 50
  def text =
    """
      |The prime 41, can be written as the sum of six consecutive primes:
      |
      |41 = 2 + 3 + 5 + 7 + 11 + 13
      |This is the longest sum of consecutive primes that adds to a prime below one-hundred.
      |
      |The longest sum of consecutive primes below one-thousand that adds to a prime, contains 21 terms, and is equal to 953.
      |
      |Which prime, below one-million, can be written as the sum of the most consecutive primes?
    """

  val LIMIT = 1000000
  Primes.initializeSieve(LIMIT)
  val GAP_GUESS = 750
  val primes = Primes.primes

  def search(lst : Array[Int], gap: Int) : Option[Int] = {
    println("Gap %d" format gap)
    def gapIterator(cut: List[Int]) : Option[Int] = {
      val ch = cut.head
      lazy val sum = cut.take(gap).foldLeft(0)(_ + _)
      cut match {
        case Nil => None
        case h::t if (cut.size < gap) => None
        case h::t if (sum > LIMIT) => None
        case h::t => if (Primes.isPrime(sum)) Some(sum) else gapIterator(t)
      }
    }

    if (gap % 2 == 0) search(lst, gap - 1) else
    gapIterator(primes) match {
      case None => search(lst, gap - 1)
      case Some(x) => Some(x)
    }
  }

  println(search(primes.toArray, GAP_GUESS))
  val displayedAnswer = 997651
  // Define a "gap" as the length of consecutive numbers
  // Iterate over the list with `gap`, search for a sum that's a prime until sum > 1m
  // If found, return the prime and search with gap - 1
  // If not found, search with gap - 1 and the original list until sum > 1m
  // Terminate when the very first gap is > 1million
  // Note that even gaps are not relevant -- yields an even number except when it starts with 2

}
