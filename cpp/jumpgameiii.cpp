
// 1306. Jump Game III
// https://leetcode.com/problems/jump-game-iii/
// day 29 November 2020 challenge
// https://leetcode.com/explore/challenge/card/november-leetcoding-challenge/568/week-5-november-29th-november-30th/3548/



class Solution {
public:
    bool canReach(vector<int>& arr, int start) {
        size_t n = arr.size();
        if( n == 1 ) return arr[0] == 0;
        if( arr[start] == 0 ) return true;

        int seen[n];
        for(int i = 0; i < n; ++i) seen[i] = 0;

        queue<int> q;

        if( start + arr[start] <= n-1 ) q.push(start + arr[start]);
        if( start - arr[start] >= 0 ) q.push(start - arr[start]);
        seen[start] = 1;

        int pos,nxt;
        while( !q.empty() ) {

            pos = q.front();
            q.pop();
            if( arr[pos] == 0 ) return true;

            seen[pos] = 1;

            // forward
            nxt = pos + arr[pos];
            if( nxt <= n-1 && seen[nxt] == 0 ) q.push(nxt);
            // backward
            nxt = pos - arr[pos];
            if( nxt >= 0 && seen[nxt] == 0 ) q.push(nxt);
        }

        return false;
    }
};
