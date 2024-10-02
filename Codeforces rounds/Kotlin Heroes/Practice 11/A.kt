// https://codeforces.com/contest/2012/problem/A

fun main() {
  // Read number of test cases
  val t = readLine()!!.toInt()

  // Process each test case
  repeat(t) {
    // Read a and b
    val (a, b) = readLine()!!.split(" ").map { it.toInt() }
    // Print the sum of a and b
    print(minOf(a, b))
    print(" ")
    println(maxOf(a, b))
  }
}

