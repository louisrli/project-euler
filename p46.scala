/**
 * @author Louis
 *
 */

package euler.solutions

import euler.helpers._
import euler.helpers.Primes._
import euler.helpers.Squares._

object p46 extends ProjectEulerApp {

  def number = 46
  def text =
    """
      |It was proposed by Christian Goldbach that every odd composite number can be written as the sum of a prime and twice a square.
      |
      |9 = 7 + 2x1^2
      |15 = 7 + 2x2^2
      |21 = 3 + 2x3^2
      |25 = 7 + 2x3^2
      |27 = 19 + 2x2^2
      |33 = 31 + 2x1^2
      |
      |It turns out that the conjecture was false.
      |
      |What is the smallest odd composite that cannot be written as the sum of a prime and twice a square?
    """

  val GUESS = 1000000
  Primes.initializeSieve(GUESS)

  /** Expects a list of ODD, COMPOSITE numbers
    * Searches all primes less than xh (odd, composite) where (xh - {prime} / 2) is square
    * In other words, where xh is {prime} + square * 2 */

   def search (numbers: List[Int]) : Option[Int] =
    numbers match {
      case xh::xt => {
        println("-- Examining %d..." format xh)
        lazy val hasSum = primesLEq(xh).exists(y => isPerfectSquare((xh - y) / 2))
        if (!hasSum) Some(xh) else search(xt)
      }
      case Nil => None
    }

  printAnswer(search(
    (3 until GUESS by 2)    // All odd numbers
      .filter(!isPrime(_))  // Filter for composite numbers
      .toList))


  /* Scratch notes
  // Create a sieve
  // Iterate through odd numbers
  // If the number is composite:
  // Iterate through all primes lower than it
  // Check if it's a perfect square
  */
}
