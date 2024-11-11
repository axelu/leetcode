
// 3228. Maximum Number of Operations to Move Ones to the End
// https://leetcode.com/problems/maximum-number-of-operations-to-move-ones-to-the-end/



// 0123456789
//       1001
//       *

class Solution {
public:
    int maxOperations(string s) {
        int n = s.size();
                
        // consecutive blocks of 1s from left to right
        vector<int> a;
        int cnt = 0;
        for(int i = 0; i < n; ++i) {
            if( s[i] == '1' ) {
                ++cnt;
            } else { // s[i] == '0'
                if( cnt > 0 ) {
                    a.push_back(cnt);
                    cnt = 0;
                }
            }
        }
        // we will not add a block of consecutive ones
        // that ends at n-1, because we cannot move it.
        
        int ans = 0;
        int pre = 0;
        for(int i = 0; i < a.size(); ++i) {
            ans += pre + a[i];
            pre += a[i];
        }
        
        
        
        
        return ans;
    }
};
