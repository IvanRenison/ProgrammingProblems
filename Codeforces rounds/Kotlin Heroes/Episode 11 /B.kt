// https://codeforces.com/contest/2011/problem/B
fun main() {
  // Read number of test cases
  val t = readLine()!!.toInt()

  // Process each test case
  repeat(t) {
      val n = readLine()!!.toInt()
      print(1)
      for (i in 1 until n) {
          print(" ")
          print(n - i + 1)
      }
      println()
  }
}
