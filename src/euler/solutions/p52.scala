package euler.solutions

import euler.helpers.ProjectEulerApp

/**
 * Author: louis (7/27/12)
 */

object p52 extends ProjectEulerApp {
  def number = 52
  def text =
    """
      |It can be seen that the number, 125874, and its double, 251748,
      |contain exactly the same digits, but in a different order.
      |
      |Find the smallest positive integer, x, such that
      |2x, 3x, 4x, 5x, and 6x, contain the same digits.
    """

  def digitsMap(x: Int, m: Map[Int, Int]) : Map[Int, Int] =
    if (x == 0) m else digitsMap(x / 10, m + ((x % 10, m.getOrElse(x % 10, 0))))

  printAnswer(
    for (n <- 100000 to 1000000 / 6;
         map = digitsMap(n, Map());
         if (2 to 6) forall (mult => digitsMap(n * mult, Map()) == map))
    yield n
  )

  val displayedAnswer = 142857

  /* I had actually read the answer to this before in Ian Stewart's
   * Mathematical Cabinet of Curiosities, but I thought I'd retroactively
   * provide an answer. Looking at the forums, it seems like a lot of people
   * knew this one already. It's also the first number that shows up on
   * Google for "cyclic number."
   */
}
