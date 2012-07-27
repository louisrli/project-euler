package euler.solutions

import euler.helpers._

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

  val GUESS = 1000002
  Primes.initializeSieve(GUESS)
   /*
  // Retrive offset values below a certain limit (for example, for 111, we would only want offsets with 3 digits)
  def checkCeil(n: Int): Int = math.pow(10, Digits.digitCount(n) - 1).toInt
  def getOffsetValues(n: Int) = permutations filter (_ < checkCeil(n))

  val INITIAL_BIT_ARRAY = Integer.parseInt("1111111", 2);

  def offsetPermutations(bitarray: Int, perms: Map[Int, List[Int]]) : Map[Int, List[Int]] = {
    def toDecimalLiteral(rem: Int) : Int = if (rem == 0) rem else (rem & 1) + 10 * toDecimalLiteral(rem >> 1)
    def inverse = bitarray ^ bitarray // XOR with 1111, how do you find the closest power of 2 to itself?
    if (bitarray == 0) perms else offsetPermutations(bitarray - 1, toDecimalLiteral(bitarray)::perms)
  }
  val permutations = offsetPermutations(INITIAL_BIT_ARRAY, List())

  // Iterate through list of primes
  def search(pl: List[Int]) : Option[Int] = {
    pl match {
      case Nil => None
      case ph::pt => {
        // Iterates through the offset values ("binary" permutations) and adds them 0 to 9, or until it becomes too large
        // The checkCeil && isPrime comparison short circuits to prevent index out of bounds
        val primeCount = getOffsetValues(ph) map (o => (0 to (checkCeil(ph) / o)).foldLeft(0)(
         (acc, mult) => { val x = ph + o * mult; if (Primes.isPrime(x)) acc + 1 else acc }
        ))
        if (primeCount == 8) Some(ph) else search(pt)
      }
    }
  }
   */
  //println(search(Primes.primes))
  /**
   * Scratch
   * Algorithmic factors
   * -- total digits in number
   * -- number of digits to replace (foreach totaldigits, always less than numdigits)
   * -- permutation of digits to replace (foreach replacedigits, always less than numdigits)
   * -- whether permutation contains lastdigit
   * -- same as adding 1, 11, 101, 1101, etc.!
   *
   * Narrowing search space
   * -- ignore last swaps with last digit -- impossible to get an 8 family
   * -- skip those already checked
   *
   */
}
