
// 3697. Compute Decimal Representation
// https://leetcode.com/problems/compute-decimal-representation/


class Solution {
public:
    vector<int> decimalRepresentation(int n) {

        vector<int> ans;

        long f = 1L;
        while( n ) {
            int rem = n % 10;
            if( rem != 0 )
                ans.push_back((int)f*rem);
            n /= 10;
            f *= 10L;
        }
        // reverse
        reverse(begin(ans), end(ans));

        return ans;
    }
};
