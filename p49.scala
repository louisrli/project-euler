package euler.solutions

import euler.helpers._

/**
 * @author Louis
 *
 */

object p49 extends ProjectEulerApp {
  def number = 49
  def text =
    """
      |The arithmetic sequence, 1487, 4817, 8147, in which each of the terms increases by 3330,
      |is unusual in two ways: (i) each of the three terms are prime, and, (ii) each of the
      |4-digit numbers are permutations of one another.
      |
      |There are no arithmetic sequences made up of three 1-, 2-, or 3-digit primes,
      |exhibiting this property, but there is one other 4-digit increasing sequence.
      |
      |What 12-digit number do you form by concatenating the three terms in this sequence?
    """

  val LIMIT = 10000
  val MAXGAP: Int = 9000 / 3
  Primes.initializeSieve(LIMIT)
  val fourDigitPrimes = Primes.primes.filter(x => (999 < x) && (x < 10000))
  val cleanSieve: Map[Int, Boolean] = fourDigitPrimes.map(k => (k, false)).toMap
  val knownSieve = cleanSieve ++ Digits.permutationsOf(1487).map((_, true)).toMap // Eliminate the given answer

  def search (checked: Map[Int, Boolean], primeList: List[Int]) : Option[List[Int]] = {

    primeList match {
      case Nil => None
      case prime::xt => {
        println("Checking prime: %d" format prime)
        if (checked(prime)) search(checked, xt)
        else {
          val primePerms = Digits.permutationsOf(prime) filter Primes.isPrime
          val newChecked = checked ++ primePerms.map(x => (x, true)).toMap
          if (primePerms.size < 3)
            search(newChecked, xt)
          else {
            // This section requires explanation to compensate for readability.
            // 1. Start with the prime permutations of a number (i.e. List(1234, 4321, 2314, 4312) filtered for prime)
            // 2. Generate sorted 3-combos of these (i.e. Iterator(List(1234, 4321, 2314), List(1234, 2314, 4312) ... )
            // 3. For each combo, zip the list into pairs of consecutive members { (1234, 2314), (2314, 4321) }
            // 4. Check that for every pair (p1, p2), (p2 - p1) equals combo(1) - combo(0) -- that the gap is the same
            val sortedCombos: Iterator[List[Int]] = primePerms.combinations(3) map (_.sorted)
            val result = sortedCombos.find(combo =>
              (combo zip combo.drop(1)) forall {
                case (n1, n2) => (n2 - n1) == (combo(1) - combo(0))
            } )

            if (result == None) search(newChecked, xt) else result
          }
        }
      }
    }
  }

  println(search(knownSieve, fourDigitPrimes))

  val displayedAnswer = "296962999629"

  // Narrow search space:
  // -- Eliminate any prime whose permutation has been checked already
  // -- Eliminate any prime 3 prime permutations in 1000 - 10000
  // -- Check primes where P0 + MAX_GAP (is P1) + MAX_GAP (is P2) is less than 10000 -- around the first 3000 numbers
}
