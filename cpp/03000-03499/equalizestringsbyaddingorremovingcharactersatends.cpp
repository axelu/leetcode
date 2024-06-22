
// 3135. Equalize Strings by Adding or Removing Characters at Ends
// https://leetcode.com/problems/equalize-strings-by-adding-or-removing-characters-at-ends/

class Solution {
private:
    // https://en.wikipedia.org/wiki/Longest_common_substring
    // https://www.geeksforgeeks.org/longest-common-substring-dp-29/
    int longest_common_substring(string s, string t, int n, int m) {
        vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
        int res = 0;

        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= m; j++)
            {
                if (s[i - 1] == t[j - 1])
                {
                    dp[i][j] = dp[i - 1][j - 1] + 1;
                    if (dp[i][j] > res)
                        res = dp[i][j];
                }
                else
                    dp[i][j] = 0;
            }
        }
        return res;
    } 
    
    
public:
    int minOperations(string initial, string target) {
        // rephrasing the question
        //    find the laongest substring in initial that is a substring of target aka
        //    longest common substring
        //    once we have set, we can calculate the answer
        
        int target_sz = target.size();
        int initial_sz = initial.size();
        
        int l = longest_common_substring(initial, target, initial_sz, target_sz);
                
        int ans = initial_sz - l; // number of chars we need to delete from initial, after that initial.size() would be l
        ans += target_sz - l;     // number of chars we need to add to initial to make it target
        
        return ans;
    }
};
