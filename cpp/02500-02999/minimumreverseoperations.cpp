
// 2612. Minimum Reverse Operations
// https://leetcode.com/problems/minimum-reverse-operations/

class Solution {
public:
    vector<int> minReverseOperations(int n, int p, vector<int>& banned, int k) {
        // for position p, the answer is 0
        // for the positions in banned, the answer is -1
        
        // let x be the position of our 1
        // (k * -1) + 1, (k * -1) + 3, ... as long as that is < k
        // for(int i = (k * -1) + 1;  i < k; i += 2)
        //     cout << i << " ";
        // cout << endl;

        // BFS
        
        vector<int> ans(n, INT_MIN);
        ans[p] = 0;
        vector<bool> is_banned(n,false);
        for(int i: banned)
            ans[i] = -1;

        // edge cases
        if( banned.size() == n-1 ) {
            return ans;
        }
        if( k == 1 ) {
            for(int i = 0; i < n; ++i) {
                if( i == p )
                    continue;    
                ans[i] = -1;
            }

            return ans;            
        }
        if( n == k ) {
            // we have one move only
            int p_new = (n-1) - p;
            if( ans[p_new] == INT_MIN )
                ans[p_new] = 1;
            
            for(int i = 0; i < n; ++i)
                if( ans[i] == INT_MIN )
                    ans[i] = -1;

            return ans;
        }
        // if k is odd, certain positions are never reachable
        /*
        if( k % 2 ) {
            for(int i = p - 1; i >= 0; i -= 2)
                ans[i] = -1;
            for(int i = p + 1; i < n; i += 2)
                ans[i] = -1;
        }
        */
        
        // we need to distinguish between even and odd indicies
        // if k is even
        //     if we are at an i that is even, we would explore odds
        //     if we are at an i that is odd, we would explore evens
        // if k is odd
        //     if we are at an i that is even, we would explore evens
        //     if we are at an i that is odd, we would explore odds
        // keep track of non-banned indicies
        set<int> odd;
        set<int> even;
        for(int i = 0; i < n; ++i) {
            if( ans[i] == INT_MIN ) {
                if( i % 2 == 0 ) 
                    even.insert(i);
                else 
                    odd.insert(i);
            }
        }
        
        queue<int> q;
        q.push(p);
        while( !q.empty() ) {
            int i = q.front();
            q.pop();
            
            set<int> * indicies;
            if(i % 2 == 0) {
                if(k % 2 == 0) indicies = &odd;
                else indicies = &even;
            } else {
                if(k % 2 == 0) indicies = &even;
                else indicies = &odd;
            }

            // what is the smallest index we can reach?
            int i_mn = i;
            int s = max(0, i - (k-1));
            int e = s + (k-1);
            if( e < n ) {
                int d = i - s;
                i_mn = e - d;
            }
            
            // what is the greatest index we can reach?
            int i_mx = i;
            e = min(n - 1, i + (k-1));
            s = e - (k-1);
            if( s >= 0 ) {
                int d = i - s;
                i_mx = e - d;
            }
            
            auto it = indicies->lower_bound(i_mn);            
            while( it != indicies->end() && *it <= i_mx ) {
                ans[*it] = ans[i] + 1;
                q.push(*it);
                it = indicies->erase(it);
            }
       }
        
        for(int i = 0; i < n; ++i)
            if( ans[i] == INT_MIN )
                ans[i] = -1;
        
        return ans;
    }
};
