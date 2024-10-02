// https://codeforces.com/contest/2012/problem/B

fun sqrt(n: Int): Int? {
  for (i in 1..n) {
    val ii = i * i
    if (ii == n) {
      return i
    }
    if (ii > n) {
      return null
    }
  }
  return null
}

fun solve(s: String): Boolean {
  val n = s.length

  val x = sqrt(n)
  if (x == null) {
    return false
  }

  var j = 0
  repeat(x) {
    if (s[j] != '1') return false
    j++
  }
  repeat(x-2) {
    if (s[j] != '1') return false
    j++
    repeat(x-2) {
      if (s[j] != '0') return false
      j++
    }
    if (s[j] != '1') return false
    j++
  }
  repeat(x) {
    if (s[j] != '1') return false
    j++
  }

  return true
}

fun main() {
  // Read number of test cases
  val t = readLine()!!.toInt()

  // Process each test case
  repeat(t) {
    // Read n
    val n = readLine()!!.toInt()
    // Read s
    val s = readLine()!!
    val ans = solve(s)
    println(if (ans) "Yes" else "No")
  }
}

