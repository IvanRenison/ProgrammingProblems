// https://codeforces.com/contest/2011/problem/A
fun main() {
  // Read number of test cases
  val t = readLine()!!.toInt()

  // Process each test case
  repeat(t) {
      // Read list
      val n = readLine()!!.toInt()
      val list = readLine()!!.split(" ").map { it.toInt() }.sorted()
      if (list[n-2]+1 == list[n-1]) {
          println(list[n-2])
      } else {
          println("Ambiguous")
      }
  }
}
