
// 3811. Number of Alternating XOR Partitions
// https://leetcode.com/problems/number-of-alternating-xor-partitions/

class Solution {
public:
    int alternatingXOR(vector<int>& nums, int target1, int target2) {
        int n = nums.size(); // 1 <= n <= 1e5; 0 <= nums[i], target1, target2 <= 1e5; target1 != target2

        // xor of subarray [left, right] is equal to prefix_xor[left] ^ prefix_xor[right+1]
        // if ask to find subarray with a certain xor target, we have to look for 
        // indices where prefix_xor[left] ^ target = y
        // for every index j where prefix_xor[j] = y, the subarray[left,j-1] has xor target

        const long mod = 1000000007;

        int prefix_xor[100001]; // TODO could use vector<int> prefix_xor(n+1, 0);
        prefix_xor[0] = 0;
        vector<int> xor_pos[131072][2]; // 100000 -> binary 17 digits -> 11111111111111111 -> 131071
        xor_pos[0][0].push_back(0);
        xor_pos[0][1].push_back(0);
        for(int i = 1; i <= n; ++i) {
            prefix_xor[i] = prefix_xor[i-1] ^ nums[i-1];
            xor_pos[prefix_xor[i]][0].push_back(i);
            xor_pos[prefix_xor[i]][1].push_back(i);
        }

        // our partitions all start with target1 block, but
        // can end with either target1 or target2 block
        long res[100001][2]; // TODO could use vector<vector<long>> res(n+1, vector<long>(2, 0));
        res[n][0] = 1L;
        res[n][1] = 1L;
        long dp[131072][2]; memset(dp,0,sizeof dp);
        for(int i = n-1; i >= 0; --i) {
            // investigating subarrays starting at i
            
            // subarrays starting at i with xor = target1
            int y = prefix_xor[i] ^ target1;
            long b1 = dp[y][0];
            for(int k = xor_pos[y][0].size()-1; k >= 0; --k) {
                int j = xor_pos[y][0][k];
                if( j <= i )
                    break;
                // xor subarray[i, j-1] = target1
                // so we would continue a subarray at j with xor target2
                b1 = (b1 + res[j][1]) % mod;
                xor_pos[y][0].pop_back();
            }
            dp[y][0] = b1;
            res[i][0] = b1;

            // subarrays starting at i with xor = target2
            y = prefix_xor[i] ^ target2;
            long b2 = dp[y][1];
            for(int k = xor_pos[y][1].size()-1; k >= 0; --k) {
                int j = xor_pos[y][1][k];
                if( j <= i )
                    break;
                // xor subarray[i, j-1] = target2
                // so we would continue a subarray at j with xor target1
                b2 = (b2 + res[j][0]) % mod;
                xor_pos[y][1].pop_back();
            }
            dp[y][1] = b2;
            res[i][1] = b2;
        }

        return res[0][0];
    }
};




// passes 982/1033 test cases, then TLE
// tast case 983 runs in about ~790ms returning correct result, but obviously too slow


class Solution {
public:
    int alternatingXOR(vector<int>& nums, int target1, int target2) {
        int n = nums.size(); // 1 <= n <= 1e5; 0 <= nums[i], target1, target2 <= 1e5; target1 != target2


        // xor of subarray [left, right] is equal to prefix_xor[left] ^ prefix_xor[right+1]
        // if ask to find subarray with a certain xor target, we have to look for
        // indices where prefix_xor[left] ^ target = y
        // for every index j where prefix_xor[j] = y, the subarray[left,j-1] has xor target

        const long mod = 1000000007;

        int prefix_xor[100001];
        prefix_xor[0] = 0;
        vector<int> xor_pos[131072]; // 100000 -> binary 17 digits -> 11111111111111111 -> 131071
        xor_pos[0].push_back(0);
        for(int i = 1; i <= n; ++i) {
            prefix_xor[i] = prefix_xor[i-1] ^ nums[i-1];
            xor_pos[prefix_xor[i]].push_back(i);
        }

        // our partitions all start with target1 block, but
        // can end with either target1 or target2 block
        long dp[100001][2];
        dp[n][0] = 1L;
        dp[n][1] = 1L;
        for(int i = n-1; i >= 0; --i) {
            // investigating subarrays starting at i

            // subarrays starting at i with xor = target1
            long b1 = 0;
            int y = prefix_xor[i] ^ target1;
            for(int k = xor_pos[y].size()-1; k >= 0; --k) {
                int j = xor_pos[y][k];
                if( j <= i )
                    continue;
                // xor subarray[i, j-1] = target1
                // so we would continue a subarray at j with xor target2
                b1 = (b1 + dp[j][1]) % mod;
            }

            // subarrays starting at i with xor = target2
            long b2 = 0;
            y = prefix_xor[i] ^ target2;
            for(int k = xor_pos[y].size()-1; k >= 0; --k) {
                int j = xor_pos[y][k];
                if( j <= i )
                    continue;
                // xor subarray[i, j-1] = target2
                // so we would continue a subarray at j with xor target1
                b2 = (b2 + dp[j][0]) % mod;
            }

            dp[i][0] = b1;
            dp[i][1] = b2;
        }

        return dp[0][0];
    }
};
