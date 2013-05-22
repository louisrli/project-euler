package euler.solutions

import euler.helpers.{Primes, Digits, ProjectEulerApp}
import euler.helpers
import java.math.BigInteger

/**
 * Author: louis (5/22/13)
 */

object p58 extends ProjectEulerApp {
  def number = 58

  def text = """Starting with 1 and spiralling anticlockwise in the following way, a square spiral with side length 7 is formed.
               |
               |37 36 35 34 33 32 31
               |38 17 16 15 14 13 30
               |39 18  5  4  3 12 29
               |40 19  6  1  2 11 28
               |41 20  7  8  9 10 27
               |42 21 22 23 24 25 26
               |43 44 45 46 47 48 49
               |
               |It is interesting to note that the odd squares lie along the bottom right diagonal,
               |but what is more interesting is that 8 out of the 13 numbers lying along both diagonals are prime; that is, a ratio of 8/13  62%.
               |
               |If one complete new layer is wrapped around the spiral above,
               |a square spiral with side length 9 will be formed.
               |If this process is continued, what is the side length of the square spiral
               |for which the ratio of primes along both diagonals first falls below 10%?"""

  // Given a length and a *previous* number of primes and diagonal, computes a new ratio
  def computeSpiral(length: Int, numPrimes: Int, numDiagonal: Int) : Int = {
    // Compute the starting and ending points for this spiral, i.e. 10 and 25
    val startingPoint = (length - 2) * (length - 2) + 1
    val endingPoint = length * length

    // The starting point starts one slot "above" a corner (i.e. 10 is above 25)
    // and we really only need three diagonals, so we take 2nd, 3rd, 4th
    val corners = (startingPoint + length - 2) to endingPoint by (length - 1)

    val numNewPrimes = numPrimes + corners.count(BigInteger.valueOf(_).isProbablePrime(10))
    val numNewDiagonal = numDiagonal + 4

    val ratio = numNewPrimes / numNewDiagonal.toFloat
    println(ratio)
    if (ratio < 0.10)
      length
    else
      computeSpiral(length + 2, numNewPrimes, numNewDiagonal)
  }

  // Start computing at length 3 (before that, we only have "1" in the center)
  println("Answer: " + computeSpiral(3, 0, 1))

  val displayedAnswer = 0
}
