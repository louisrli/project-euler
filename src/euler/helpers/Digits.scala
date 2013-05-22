package euler.helpers

/**
 * @author Louis
 *
 */

object Digits {

  def digitSum(n: BigInt) = {
    def inner(rem: BigInt, sum: BigInt): BigInt =
      if (rem == 0) sum else inner(rem / 10, sum + (rem % 10))
    inner(n, 0)
  }

  def digitCount(n: BigInt): Int = {
    def inner(rem: BigInt, count: Int): Int = {
      if (rem == 0) count else inner(rem / 10, count + 1)
    }
    inner(n, 0)
  }

  def digitCount(n: Int) =
    toDigitList(n).size

  // Returns a list of integers as permutations
  def permutationsOf(n: Int) : List[Int] =
    lazyPermutationsOf(n).toList.map(fromDigitList)

  // Returns a raw Iterator of List[Int] (i.e. iterator over digit lists)
  // Filters permutations that begin with zero
  def lazyPermutationsOf(n: Int) : Iterator[List[Int]] =
    toDigitList(n).permutations.filter(x => (x.dropWhile(_ == 0)) == x)

  def isPermutation(n1: Int, n2: Int) : Boolean =
    toDigitList(n1).permutations.contains(toDigitList(n2))

  // Support only positive numbers for now
  private def toDigitList(n: Int) = {
    require (n >= 0)
    def inner(rem: Int, xs: List[Int]) : List[Int] =
      if (rem == 0) xs else inner(rem / 10, (rem % 10)::xs)
    inner(n, Nil)
  }

  private def fromDigitList(xs: List[Int]) = {
    xs.foldLeft(0)((p, dig) => { require(dig >= 0 && dig < 10); p * 10 + dig })
  }
}
