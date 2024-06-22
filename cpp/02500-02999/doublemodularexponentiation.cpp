
// 2961. Double Modular Exponentiation
// https://leetcode.com/problems/double-modular-exponentiation/


class Solution {
private:
    // exponention using bit manipulation
    long modular_pow(long base, long exponent, long mod) {

        long ret = 1;

        while(exponent > 0) {

            int last_bit = (exponent & 1);
            if( last_bit )
                ret = (ret * base) % mod;

            base = (base * base) % mod;

            exponent = exponent >> 1;
        }

        return ret;
    }

public:
    vector<int> getGoodIndices(vector<vector<int>>& variables, int target) {
        int n = variables.size();

        vector<int> ans;

        for(int i = 0; i < n; ++i) {
            int a = variables[i][0];
            int b = variables[i][1];

            int base = modular_pow(a,b,10);
            int c = variables[i][2];
            int m = variables[i][3];

            int t = modular_pow(base,c,m);
            if( t == target )
                ans.push_back(i);
        }

        return ans;
    }
};
