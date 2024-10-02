// https://codeforces.com/contest/2012/problem/C


fun solve(a: List<Int>): Int {
  val n = a.size

  val first = a[0]
  val last = a[n - 1]

  var first_count = 0
  for (i in 0..n-1) {
    if (a[i] == first) {
      first_count++
    } else {
      break
    }
  }
  var last_count = 0
  for (i in n-1 downTo 0) {
    if (a[i] == last) {
      last_count++
    } else {
      break
    }
  }

  if (first == last) {
    return n - minOf(n, first_count + last_count)
  } else {
    return n - maxOf(first_count, last_count)
  }
}

fun main() {
  // Read number of test cases
  val t = readLine()!!.toInt()

  // Process each test case
  repeat(t) {
    // Read n
    val n = readLine()!!.toInt()
    // Read array a
    val a: List<Int> = readLine()!!.split(" ").map { it.toInt() }
    val ans = solve(a)
    println(ans)
  }
}

