package euler.solutions

import euler.helpers._
import collection.immutable.BitSet

/**
 * @author louis
 *
 */

object p51 extends ProjectEulerApp {

  def text =
    """
      |By replacing the 1st digit of *3, it turns out that six of the nine possible values:
      |13, 23, 43, 53, 73, and 83, are all prime.
      |
      |By replacing the 3rd and 4th digits of 56**3 with the same digit, this 5-digit
      |number is the first example having seven primes among the ten generated numbers,
      |yielding the family: 56003, 56113, 56333, 56443, 56663, 56773, and 56993.
      |Consequently 56003, being the first member of this family, is the smallest prime with this property.
      |
      |Find the smallest prime which, by replacing part of the number
      |(not necessarily adjacent digits) with the same digit, is part
      |of an eight prime value family.
    """
  def number = 51

  val START = 100
  val LIMIT = 1000000
  Primes.initializeSieve(LIMIT)


  def getDigits(n: Int, b: BitSet) : BitSet =
    if (n == 0) b else getDigits(n / 10, b + (n % 10))

  // Generate "offsets": an offset is a base 10 "binary-literal" _mask_ in the form of 101, 1001, 11101, etc.
  // Given any number, we take its digits (Int) and map it the possible masks (Int) based on how it repeats
  // __For example:__ 120133 generates { 0 -> [00]1000, 1 -> 100100, 2 -> [0]10000, 3 -> [0000]11 },
  //    where [0...0] marks leading zeroes
  // By adding these masks, we can generate the solution by "replacing part of the number"
  // There are other cases th
  def getOffsets(x: Int): Map[Int, Int] = {
    val digits = getDigits(x, BitSet())
    def inner(rem: Int, count: Int, offsets: Map[Int, Int]) : Map[Int, Int] = {
      val currentDigit = rem % 10
      rem match {
        case 0 if offsets.getOrElse(currentDigit, 1) % 2 == 0 => offsets - currentDigit // Skip even-number repetitions
        case 0 => offsets                                                               // Terminate
        case _ if digits contains currentDigit =>
          inner(rem / 10, count + 1,                                                     // Update map
            offsets + ((currentDigit, offsets.getOrElse(currentDigit, 0) + math.pow(10, count).toInt)))
      }
    }
    inner(x, 0, Map[Int, Int]()) - (x % 10) // Remove mask with last digit
  }

  // Go through each mask for each prime, tackling three cases:
  // 1. Subtraction -- iteratively subtract the mask and check for primes
  // 2. Addition -- iteratively add the mask and check for primes
  // 3. The number itself -- is it prime?
  def search (plst: List[Int]) : Option[Int] = {
    plst match {
      case Nil => None
      case ph::pt => {
        // For the given prime, map over the offsets
        val candidates = getOffsets(ph).map {
          case (digit, offset) => {
            def oneIfPrime(n: Int) = if (Primes.isPrime(n)) 1 else 0
            def primeCount (op: Int => Int, count: Int, num: Int, iter: Int, limit: Int) : Int = {
              val delta = offset * (iter + 1)
              val result = op(delta)

              if (iter >= limit) count
              else primeCount(op, count + oneIfPrime(result), result, iter + 1, limit)
            }
            if (primeCount(ph + _, 0, ph, 0, 9 - digit) + primeCount(ph - _, 0, ph, 0, digit - 1) + oneIfPrime(ph) == 8)
              Some(ph)
            else None
          }
        }

        // Search the results for our answer
        candidates.find(_.isDefined) match {
          case None => search(pt)
          case Some(x) => x
        }
      }
    }
  }
  printAnswer(search(Primes.primes))
  val displayedAnswer = 121313
}
