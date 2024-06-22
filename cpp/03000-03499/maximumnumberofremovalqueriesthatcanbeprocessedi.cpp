
// 3018. Maximum Number of Removal Queries That Can Be Processed I
// https://leetcode.com/problems/maximum-number-of-removal-queries-that-can-be-processed-i/

class Solution {
private:
    int rec(vector<int>& nums, vector<int>& queries, int i, int j, vector<vector<int>>& mem) {
        // i current left index
        // j current right index (half closed)
        if( mem[i][j] != -1 ) 
            return mem[i][j];
        
        // expand to the left
        int lft = 0;
        if( i > 0 )
            lft = rec(nums, queries, i - 1, j, mem);
        
        // expand to the right
        int rgt = 0;
        if( j < nums.size() )
            rgt = rec(nums, queries, i, j + 1, mem);
             
        // record the max to the left or right, basically as if we would ignore current range
        // -> subsequence
        int ret = max(lft, rgt);
        
        if( i > 0 && lft < queries.size() && nums[i - 1] >= queries[lft] )
            ret = max(ret, lft + 1);
        
        if ( j < nums.size() && rgt < queries.size() && nums[j] >= queries[rgt])
            ret = max(ret, rgt + 1);
        
        return mem[i][j] = ret;
    }
    
public:
    int maximumProcessableQueries(vector<int>& nums, vector<int>& queries) {
        int nums_sz = nums.size();
        
        int ans = 0;
        
        // mem[i][j] is the maximum number of queries we can answer when at least nums[i..(j - 1)] are NOT removed
        // in other words, mem[0][n] is 0, because if we have not removed 0...n-1, we have not answered any question
        vector<vector<int>> mem(nums_sz, vector<int>(nums_sz + 1, -1));
        mem[0][nums_sz] = 0;
        for(int i = 0; i < nums_sz; ++i)
            ans = max(ans, rec(nums, queries, i, i, mem));
                
        return ans;
    }
};


/* this was my initial solution, which on 1/25/2023 passed 550 / 643 test cases
 * it got wrong answer on 
 * [41,14,26,4,45]
 * [35,41,19]
 * the description of the problem at that time said 'subarrary', see 
 * https://leetcode.com/problems/maximum-number-of-removal-queries-that-can-be-processed-i/discuss/4622175/Whoever-got-AC-please-enlighten-me
 * https://leetcode.com/problems/maximum-number-of-removal-queries-that-can-be-processed-i/discuss/4621532/DP-in-C%2B%2B-java-and-Python.
 * https://leetcode.com/problems/maximum-number-of-removal-queries-that-can-be-processed-i/discuss/4621723/Python-3-AC-but-confused
 * the description got then changed to say 'subsequence'
 * below answered correctly if 'subarray'
 */

class Solution {
private:
    unordered_map<int,int> mem;

    int rec(vector<int>& nums, vector<int>& queries, int i, int j, int k) {
        // i left index in nums
        // j right index in nums
        // k index in queries

        if( i > j || k == queries.size() )
            return -1;

        int key = (i<<20) + (j<<10) + k;
        auto f = mem.find(key);
        if( f != mem.end() )
            return f->second;

        // if first and last element of nums is less than queries[i],
        // the processing of queries ends
        if( nums[i] < queries[k] && nums[j] < queries[k] )
            return -1;

        int ret = k;

        // either nums[i] >= queries[k] or nums[j] >= queries[k]
        if( nums[i] >= queries[k] ) {
            ret = max(ret, rec(nums, queries, i+1, j, k+1));
        }

        if( nums[j] >= queries[k] ) {
            ret = max(ret, rec(nums, queries, i, j-1, k+1));
        }

        return mem[key] = ret;
    }


public:
    int maximumProcessableQueries(vector<int>& nums, vector<int>& queries) {
        int nums_sz = nums.size();
        int q_sz = queries.size();

        // our answer can only be as good as min(nums_sz q_sz),
        // hence starting with a base line of not removing anything from nums
        int base = rec(nums, queries, 0, nums_sz - 1, 0) + 1; // rec turns the index in queries, hence + 1
        if( base == min(nums_sz, q_sz) )
            return base;

        // sliding window of length l
        for(int l = min(nums_sz, q_sz); l > base; --l) {
            // cout << "l " << l << " base " << base << endl;

            for(int i = 0; i + l <= nums_sz; ++i) {
                int j = i + l - 1;
                // cout << "  i " << i << " j " << j << endl;
                int res = rec(nums, queries, i, j, 0) + 1;
                base = max(base, res);
            }
        }

        return base;
    }
};
