
// 1067. Digit Count in Range
// https://leetcode.com/problems/digit-count-in-range/


/*
 * example int low = 1, high = 84486, d = 3
 *
 * 6                           6 * 0 + 1
 * 8                     8 * (10 * 0 + 1) + 10
 * 4               4 * (10 * (10 * 0 + 1) + 10) + 100
 * 4         4 * (10 * (10 * (10 * 0 + 1) + 10) + 100) + 1000
 * 8   8 * (10 * (10 * (10 * (10 * 0 + 1) + 10) + 100) + 1000) + 10000
 */
class Solution {
private:
    int D;

    int f(int x) {
        string x_str = to_string(x);
        int n = x_str.size();

        int ret = x_str[n-1] - 48 >= D ? 1 : 0;

        int fac =  1;
        int sum = 10;
        for(int i = n-2; i >= 0; --i) {
            int k = x_str[i] - 48;

            ret += k * fac;
            if( k == D )
                ret += 1;
            else if( k > D && D > 0 )
                ret += sum;

            if( k == 0 && D == 0 )
                ret -= sum;

            fac = 10 * fac + sum;
            sum = 10 * sum;
        }

        // finish up
        for(int i = 0; i < n-1; ++i) {
            int k = x_str[i] - 48;
            if( k == D )
                ret += stoi(x_str.substr(i+1));
        }

        return ret;
    }
public:
    int digitsCount(int d, int low, int high) {
        D = d;

        int t1 = f(high);
        int t2 = f(low-1);
        // cout << "f(hi) " << t1 << " f(lo-1) " << t2 << endl;

        return t1-t2;
    }
};
