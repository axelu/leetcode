
// 2197. Replace Non-Coprime Numbers in Array
// https://leetcode.com/problems/replace-non-coprime-numbers-in-array/




class Solution {
private:
    // recursive function to return gcd of a and b
    long long gcd(long long a, long long b) {
        if( b == 0 )
            return a;
        return gcd(b,a % b);
    }

    // function to return Least Common Multiple (LCM) of two numbers
    // LCM definition:
    // LCM of two numbers is the smallest number which can be divided by both numbers
    long long lcm(long a, long b) {
        return (a / gcd(a,b)) * b;
    }


public:
    vector<int> replaceNonCoprimes(vector<int>& nums) {
        int n = nums.size();
        if( n == 1 )
            return nums;

        stack<long long> stck;
        stck.push(nums[0]);
        for(int i = 1; i < n; ++i) {

            long long b = nums[i];
            while( !stck.empty() ) {
                long long _gcd = gcd(stck.top(),b);
                if( _gcd > 1 ) {
                    b = lcm(stck.top(),b);
                    stck.pop();
                } else {
                    break;
                }
            }

            stck.push(b);
        }

        vector<int> ans;
        while( !stck.empty() ) {
            ans.push_back(stck.top());
            stck.pop();
        }

        reverse(ans.begin(),ans.end());
        return ans;
    }
};
