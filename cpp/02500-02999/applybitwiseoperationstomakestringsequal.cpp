
// 2546. Apply Bitwise Operations to Make Strings Equal
// https://leetcode.com/problems/apply-bitwise-operations-to-make-strings-equal/




/* there is no constraint that i < j
 *          i  j
 *  org     0  0
 *  result  0  0
 *  org     0  1
 *  result  1  1
 *  org     1  0
 *  result  1  1
 *  org     1  1
 *  result  1  0
 *
 * so in order to turn a 0 into 1, we need a 1
 * and in ordder to turn 1 into 0, we need a 1
 */
class Solution {
public:
    bool makeStringsEqual(string s, string target) {
        int n = s.size(); // s.size() == target.size()

        int cnts1s = 0;
        int cnttarget1s = 0;
        bool is_equal = true;
        for(int i = 0; i < n; ++i) {
            if( s[i] != target[i] )
                is_equal = false;
            if( s[i] == '1' )
                ++cnts1s;
            if( target[i] == '1' )
                ++cnttarget1s;
        }
        if( is_equal )
            return true;
        
        // cout << "n " << n << " cnts1s " << cnts1s << " cnttarget1s " << cnttarget1s << endl;
        
        if( cnts1s == 0 || 
            (cnts1s > 0 && cnttarget1s == 0) )
            return false;
        
        return true;
    }
};
