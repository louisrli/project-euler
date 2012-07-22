package euler.helpers

/**
 * @author Louis
 *
 */

object Squares {
   def isPerfectSquare(n: Int) : Boolean = {
     val lastDig = n & 0x0F
     if (n < 0 || !Array[Int](0, 1, 4, 5, 9).contains(lastDig))
       false

     val s = math.round(math.sqrt(n)) // could be improved
     s * s == n
   }
}
