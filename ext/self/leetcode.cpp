/**
 * @author yuzining
 * @date $CURRENT_YEAR/$CURRENT_MONTH/$CURRENT_DATE $CURRENT_HOUR:$CURRENT_MINUTE"
 */
 
#ifdef local
# include "D:\VSCODE\local.hpp"
template<typename T>
ostream &operator<<(ostream &out, const vector<T> &vec) {
  bool isPrint = false;
  for (auto &x : vec) {
    out << (isPrint ? ',' : '[') << x;
    isPrint = true;
  }
  out << ']';
  return out;
}
#else
#define debug(...) do { } while(false)
#endif
 
 
 
#ifdef local
void Main() {
  Solution o;
  cout << o.solve(xxx) << '\n';
}
#endif