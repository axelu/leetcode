
// 2614. Prime In Diagonal
// https://leetcode.com/problems/prime-in-diagonal/



class Solution {
private:
    bool isPrime(int n) {
        if( n == 2 || n == 3 )
            return true;

        if( n <= 1 || n % 2 == 0 || n % 3 == 0  )
            return false;

        for(int i = 5; i * i <= n; i += 6 ) {
            if( n % i == 0 || n % (i + 2) == 0 )
                return false;
        }

        return true;
    }

public:
    int diagonalPrime(vector<vector<int>>& nums) {
        int n = nums.size();

        int ans = 0;


        // top left to bottom right
        for(int i = 0; i < n; ++i) {

            if( isPrime(nums[i][i]) && nums[i][i] > ans )
                ans = nums[i][i];

            if( isPrime(nums[i][n-1-i]) && nums[i][n-1-i] > ans )
                ans = nums[i][n-1-i];

        }

        return ans;
    }
};
