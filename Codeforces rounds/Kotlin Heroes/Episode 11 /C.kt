// https://codeforces.com/contest/2011/problem/C

// Convert a string of the form abc+def into an integer
fun get(s: String): Long {
  val p = s.indexOf('+')
  return s.substring(0, p).toLong() + s.substring(p + 1).toLong()
}

fun solve(s: String): Long {
  val n = s.length
  val dp = LongArray(n + 1)

  for (i in 1..n) {
      if (s[i - 1] != '+') {
          for (j in maxOf(0, i - 30) until i) {
              // Count amount of '+' in the substring
              val count = s.substring(j, i).count { it == '+' }

              if (count == 1 && s[j] != '+' && (j == 0 || s[j - 1] != '+')) {
                  val value = get(s.substring(j, i))
                  dp[i] = maxOf(dp[i], dp[j] + value)
              }
          }
      }
  }
  return dp[n]
}

fun main() {
  val t = readLine()!!.toInt()
  repeat(t) {
      val s = readLine()!!
      println(solve(s))
  }
}
