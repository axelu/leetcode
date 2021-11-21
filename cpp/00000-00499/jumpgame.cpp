
// 55. Jump Game
// https://leetcode.com/problems/jump-game/


class Solution {
public:
    bool canJump(vector<int>& nums) {
        size_t n = nums.size();
        if( n == 1 ) return true;
        if( nums[0] == 0 ) return false;

        int seen[n];memset(seen,0,sizeof seen);



        priority_queue<array<int,2>> pq;
        if( nums[0] >= n-1 )
            return true;
        pq.push({nums[0],0});
        seen[0] = 1;

        int pos,src,nxt,nxt_new;
        while( !pq.empty() ) {
            pos = pq.top()[0];
            src = pq.top()[1];
            pq.pop();
            // cout << "pos " << pos << " src " << src << endl;

            nxt = pos + nums[pos];
            if( nxt >= n-1 )
                return true;
            for(int i = nxt; i > src; --i) {
                if( !seen[i] ) {
                    nxt_new = i + nums[i];
                    if( nxt_new >= n-1 )
                        return true;
                    pq.push({nxt_new,i});
                    seen[i] = 1;
                } else {
                    break;
                }
            }
        }

        return false;
    }
};
