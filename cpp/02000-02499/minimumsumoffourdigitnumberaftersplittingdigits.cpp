
// 2160. Minimum Sum of Four Digit Number After Splitting Digits
// https://leetcode.com/problems/minimum-sum-of-four-digit-number-after-splitting-digits/



class Solution {
private:

    // generate all permutations
    void permute(int n, string& s, vector<string>& res) {
        if( n == 1 ) {
            res.push_back(s);
            return;
        }

        char t;
        for(int i = 0; i < n; ++i) {
            permute(n-1,s,res);

            if( n % 2 == 1 ) {
                // size is odd,: swap first and size-1 element
                t = s[0];
                s[0] = s[n-1];
                s[n-1] = t;
            } else {
                // size is even: swap ith and size-1 element
                t = s[i];
                s[i] = s[n-1];
                s[n-1] = t;
            }
        }
    }

public:
    int minimumSum(int num) {
        // 4 digits -> 4! permutations -> 24 permutations
        // each permutation can be cut 3 times
        // 0|123; 01|23; 012|3
        // hence 24 * 3 possibilities -> 72 possibilities

        string s = to_string(num);
        vector<string> v;
        permute(4,s,v);

        int ans = INT_MAX;

        for(string str : v)
            for(int i = 1; i < 4; ++i)
                ans = min(ans, stoi(str.substr(0,i)) + stoi(str.substr(i)));

        return ans;
    }
};
