package euler.helpers

/**
 * @author Louis
 *
 */

trait ProjectEulerApp extends App {
  def number: Int

  def text: String

  private def strippedText = text.stripMargin

  override def delayedInit(body: => Unit) = {
    super.delayedInit(body)
    val message =
      """
        |-----------------------------------------------
        |Project Euler %d
        |Author: Louis Li
        |Problem:
        |%s
        |------------------------------------------------
      """.stripMargin
    println(message format(number, strippedText))
  }

  def printAnswer(x : Any) : Unit = {
    println("== Answer: " + x)
  }

  val displayedAnswer : Any
}
