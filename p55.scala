package euler.solutions

import euler.helpers.ProjectEulerApp

/**
 * Author: louis (8/5/12)
 */

object p55 extends ProjectEulerApp {
  def number = 55
  def text = """If we take 47, reverse and add, 47 + 74 = 121, which is palindromic.
               |
               |Not all numbers produce palindromes so quickly. For example,
               |
               |349 + 943 = 1292,
               |1292 + 2921 = 4213
               |4213 + 3124 = 7337
               |
               |That is, 349 took three iterations to arrive at a palindrome.
               |
               |Although no one has proved it yet, it is thought that some numbers, like 196,
               |never produce a palindrome. A number that never forms a palindrome through the
               |reverse and add process is called a Lychrel number. Due to the theoretical
               |nature of these numbers, and for the purpose of this problem, we shall assume
               |that a number is Lychrel until proven otherwise. In addition you are
               |given that for every number below ten-thousand, it will either
               |(i) become a palindrome in less than fifty iterations, or,
               |(ii) no one, with all the computing power that exists, has managed so far
               |to map it to a palindrome. In fact, 10677 is the first number to be shown
               |to require over fifty iterations before producing a palindrome: 4
               |668731596684224866951378664 (53 iterations, 28-digits).
               |
               |Surprisingly, there are palindromic numbers that are themselves Lychrel numbers;
               |the first example is 4994.
               |
               |How many Lychrel numbers are there below ten-thousand?"""

  def reverse(x: BigInt) = {
    def inner(rem: BigInt, rev: BigInt): BigInt = {
      if (rem == 0) rev else inner(rem / 10, (rem % 10) + rev * 10)
    }
    inner(x, 0)
  }

  def isPalindrome(x: BigInt) = (reverse(x) == x)

  def isLychrel(current: BigInt, counter: Int): Boolean = {
    if (counter == 50) true
    else {
      val next = current + reverse(current)
      if (isPalindrome(next)) false else isLychrel(next, counter + 1)
    }
  }

  val ans = (BigInt(1) to 10000).count(isLychrel(_, 0))
  println(ans)
  val displayedAnswer = 249
}
