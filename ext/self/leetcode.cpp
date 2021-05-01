/**
 * @author yuzining
 * @date $CURRENT_YEAR/$CURRENT_MONTH/$CURRENT_DATE $CURRENT_HOUR:$CURRENT_MINUTE"
 */
 
#ifdef local
# include "D:\VSCODE\debug.hpp"
#else
#define DEBUG(...) do { } while(false)
#endif
 
 
 
#ifdef local
void Main() {
  Solution o;
  DEBUG(o.solve(...));
}
#endif