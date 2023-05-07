
// 2489. Number of Substrings With Fixed Ratio
// https://leetcode.com/problems/number-of-substrings-with-fixed-ratio/



/* from the hints
 * Let Func(i) denote the number of 0’s in the prefix [0…i]
 * find the number of pairs of indices L and R such that
 * Func(R) - Func(L) : R - L - Func(R) + Func(L) = num1 : num2
 *
 *          0123456
 * example  0110011   num1 = 1, num2 = 2
 * L = 0 => Func(L) = 1
 * R = 6 => Func(R) = 3
 *
 * 3 - 1 : 6 - 0 - 3 + 1 = 1 : 2
 *   2   :       4       = 1 : 2
 *
 * simplify formula => get all L on one side, and all R on the other side
 * Func(R) - Func(L) : R - L - Func(R) + Func(L) = num1 : num2
 * (Func(R) - Func(L)) * num2                    = (R - L - Func(R) + Func(L)) * num1
 * Func(R) * num2  -  Func(L) * num2             =  R * num1 - L * num1 - Func(R) * num1 + Func(L) * num1
 * Func(R) * num2  +  Func(R) * num1 - R * num1  = Func(L) * num2 + Func(L) * num1 - L * num1
 * Func(R) * (num1 + num2)           - R * num1  = Func(L) * (num1 + num2)         - L * num1
 */
class Solution {
public:
    long long fixedRatio(string& s, int num1, int num2) {
        int n = s.size();

        long long ans = 0;

        unordered_map<long long,long long> um; // val,cnt
        ++um[num1]; // account for index before 0
        long long cnt = 0;
        for(long long i = 0; i < n; ++i) {
            if( s[i] == '0' )
                ++cnt;

            // rvalue (left side of above equation)
            long long xvalue = cnt * (num1+num2) - i * num1;
            ans += um[xvalue];

            // lvalue (right side of above equation)
            ++um[xvalue];
        }

        return ans;
    }
};
