
// 1447. Simplified Fractions
// https://leetcode.com/problems/simplified-fractions/



class Solution {
private:
   int gcd(int a, int b) {
        if( b == 0 )
            return a;
        return gcd(b,a % b);
    }

public:
    vector<string> simplifiedFractions(int n) {
        // dividend ÷ divisor = quotient
        vector<string> ans;

        for(int i = 1; i < n; ++i) {          // dividend
            string s = to_string(i) + '/';
            for(int j = i+1; j <=n; ++j) {    // divisor
                if( i != 1 && gcd(i,j) != 1 )
                    continue;

                ans.push_back(s + to_string(j));
            }
        }

        return ans;
    }
};
