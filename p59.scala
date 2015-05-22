package euler.solutions

import euler.helpers.{Primes, Digits, ProjectEulerApp}
import io.Source

/**
 * Author: louis (5/22/13)
 */

object p59 extends ProjectEulerApp {
  def number = 59

  def text = """Each character on a computer is assigned a unique code and the preferred standard is ASCII
               |(American Standard Code for Information Interchange). For example, uppercase A = 65,
               |asterisk (*) = 42, and lowercase k = 107.
               |
               |A modern encryption method is to take a text file, convert the bytes to ASCII,
               |then XOR each byte with a given value, taken from a secret key. The advantage with
               |the XOR function is that using the same encryption key on the cipher text,
               |restores the plain text; for example, 65 XOR 42 = 107, then 107 XOR 42 = 65.
               |
               |For unbreakable encryption, the key is the same length as the plain text
               |message, and the key is made up of random bytes. The user would keep the
               |encrypted message and the encryption key in different locations, and without
               |both "halves", it is impossible to decrypt the message.
               |
               |Unfortunately, this method is impractical for most users, so the
               |modified method is to use a password as a key. If the password is
               |shorter than the message, which is likely, the key is repeated cyclically
               |throughout the message. The balance for this method is using a sufficiently
               |long password key for security, but short enough to be memorable.
               |
               |Your task has been made easy, as the encryption key consists of three lower
               |case characters. Using cipher1.txt (right click and 'Save Link/Target As...'),
               |a file containing the encrypted ASCII codes, and the knowledge that the plain
               |text must contain common English words, decrypt the message and
               |find the sum of the ASCII values in the original text."""

  // Converts a string to a list of ASCII ints
  def strToAscii(s: String) : List[Int] = s.map(_.toInt).toList

  val rawChars = Source.fromFile("./src/euler/solutions/cipher1.txt").mkString
  val asciiChars = rawChars.split(",").map(_.trim.toInt)

  val ASCII_MAX = 256
  val ASCII_RANGE = 0 until ASCII_MAX

  val (half1, half2) = asciiChars.splitAt(asciiChars.length / 2)

  // Get the XOR of the two original, unencrypted messages
  val messagePairs = half1.zip(half2)
  val originalXor = messagePairs.map { case (x1, x2) => x1 ^ x2 }
  println(originalXor.toList)

  // Explore parts of the original message that are "0"
  // meaning that both halves of the message have the same character there
  val zeroIndices = originalXor.zip(originalXor.indices)
    .filter { case (xor, i) => xor == 0 }
    .map(_._2)
  println(zeroIndices.toList)

  val displayedAnswer = 0
}
