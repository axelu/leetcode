
// 55. Jump Game
// https://leetcode.com/problems/jump-game/



class Solution {
public:
    bool canJump(vector<int>& nums) {
        size_t n = nums.size();
        if( n == 1 ) return true;
        if( nums[0] == 0 ) return false;

        int seen[n];
        for(int i = 0; i < n; ++i) seen[i] = 0;

        queue<int> q;

        for(int i = nums[0]; i >= 1; --i) {
            if( i >= n-1) return true;
            q.push(i);
        }
        seen[0] = 1;

        int pos,nxt;
        while( !q.empty() ) {

            pos = q.front();
            q.pop();
            seen[pos] = 1;

            for(int i = nums[pos]; i >= 1 ; --i) {
                nxt = pos + i;
                if( nxt >= n-1 ) return true;
                if( seen[nxt] == 0 ) q.push(nxt);
            }
        }

        return false;
    }
};
