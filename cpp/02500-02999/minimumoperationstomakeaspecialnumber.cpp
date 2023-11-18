
// 2844. Minimum Operations to Make a Special Number
// https://leetcode.com/problems/minimum-operations-to-make-a-special-number/





/*     0 1 2 3 4 5 6 7 8 9
 *         0       0
 */
class Solution {
private:

public:
    int minimumOperations(string num) {
        int n = num.size();
        if( n == 1 )
            return num[0] == '0' ? 0 : 1;

        // after our operations, our string must end in either:
        // 00, 25, 50 or 75

        int a = n; // 00
        int b = n; // 25
        int c = n; // 50
        int d = n; // 75

        // find last 0
        auto last0 = num.find_last_of('0');

        // 00
        if( last0 != string::npos && last0 > 1 ) {
            // we would need to delete n-1 to last0+1 positions
            int t1 = (n-1) - last0;
            // do we have another 0 left of last0?
            auto secondlast0 = num.find_last_of('0',last0-1);
            if( secondlast0 != string::npos ) {
                // we would need to delete last0-1 t0 secondlast0+1 positions
                int t2 = last0 - 1 - secondlast0;
                a = t1 + t2;
            }
        }

        // 50
        if( last0 != string::npos && last0 > 0 ) {
            // we would need to delete n-1 to last0+1 positions
            int t1 = (n-1) - last0;
            // do we have a 5 left of last0?
            auto secondlast5 = num.find_last_of('5',last0-1);
            if( secondlast5 != string::npos ) {
                // we would need to delete last0-1 t0 secondlast5+1 positions
                int t2 = last0 - 1 - secondlast5;
                c = t1 + t2;
            }
        }

        // find last 5
        auto last5 = num.find_last_of('5');

        // 25
        if( last5 != string::npos && last5 > 0 ) {
            // we would need to delete n-1 to last0+1 positions
            int t1 = (n-1) - last5;
            // do we have a 2 left of last5?
            auto secondlast2 = num.find_last_of('2',last5-1);
            if( secondlast2 != string::npos ) {
                // we would need to delete last5-1 t0 secondlast2+1 positions
                int t2 = last5 - 1 - secondlast2;
                b = t1 + t2;
            }
        }

        // 75
        if( last5 != string::npos && last5 > 0 ) {
            // we would need to delete n-1 to last0+1 positions
            int t1 = (n-1) - last5;
            // do we have a 2 left of last5?
            auto secondlast7 = num.find_last_of('7',last5-1);
            if( secondlast7 != string::npos ) {
                // we would need to delete last5-1 t0 secondlast7+1 positions
                int t2 = last5 - 1 - secondlast7;
                d = t1 + t2;
            }
        }

        // cout << "a " << a << endl;
        // cout << "b " << b << endl;
        // cout << "c " << c << endl;
        // cout << "d " << d << endl;
        int ans = min({a,b,c,d});
        return ans == n ? (last0 != string::npos ? n-1 : n) : ans;
    }
};
