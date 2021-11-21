
// 45. Jump Game II
// https://leetcode.com/problems/jump-game-ii/



class Solution {
public:
    int jump(vector<int>& nums) {
        int n = nums.size();
        if( n == 1 ) 
            return 0;

        int seen[n];memset(seen,0,sizeof seen);

        
        // array<int,2> jumps,idx        
        auto comp = [](const array<int,2>& a, const array<int,2>& b){
            if( a[0] > b[0] ) {
                return true;
            } else if( a[0] == b[0] ) {
                if( a[1] <  b[1] ) {
                    return true;
                }
            }
            return false;
        };

        
        priority_queue<array<int,2>,vector<array<int,2>>,decltype(comp)> q(comp);
        for(int i = nums[0]; i >= 1; --i) {
            if( i >= n-1) 
                return 1;
            q.push({1,i});
            seen[i] = 1;
        }

        
        int r = INT_MAX;
        
        array<int,2> qe;
        int jumps,idx,nxt;
        while( !q.empty() ) {
            
            qe = q.top();
            q.pop();

            jumps = qe[0];
            idx = qe[1];
            

            for(int i = idx+nums[idx]; i >= idx ; --i) {
                if( i >= n-1 )
                    return jumps+1;
                
                if( !seen[i] ) {
                    q.push({jumps+1,i});
                    seen[i] = 1;
                }
            }
        }

        return r;
        
    }
};




