
// 2683. Neighboring Bitwise XOR
// https://leetcode.com/problems/neighboring-bitwise-xor/




/* 0 XOR 0 -> 0
 * 0 XOR 1 -> 1
 * 1 XOR 0 -> 1
 * 1 XOR 1 -> 0
 */
class Solution {
private:
    bool rec(vector<int>& derived, int n, int i, int original, int original0) {
        if( i == n-1 )
            return derived[i] == original ^ original0;

        bool ret = false;

        if( derived[i] == 0 ) {
            if( original == 0 ) {
                ret = rec(derived,n,i+1,0,original0);
            } else {
                ret = rec(derived,n,i+1,1,original0);
            }
        } else {
            if( original == 0 ) {
                ret = rec(derived,n,i+1,1,original0);
            } else {
                ret = rec(derived,n,i+1,0,original0);
            }
        }

        return ret;
    }

public:
    bool doesValidArrayExist(vector<int>& derived) {
        int n = derived.size();

        // derived[i] = original[i] ^ original[i + 1]
        // derived[i] = original[i] ^ original[0]      for i = n-1

        // derived[i] = original[i] ^ original[i + 1]
        // cases
        //      0             0            0
        //      0             1            1
        //      1             0            1
        //      1             1            0

        bool f = rec(derived,n,0,0,0);
        if( !f )
            f = rec(derived,n,0,1,1);

        return f;
    }
};
