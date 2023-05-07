
// 2558. Take Gifts From the Richest Pile
// https://leetcode.com/problems/take-gifts-from-the-richest-pile/



class Solution {
public:
    long long pickGifts(vector<int>& gifts, int k) {

        long long ans = 0LL;

        priority_queue<int> pq;
        for(int x: gifts)
            pq.push(x);

        for(int i = 0; i < k; ++i) {

            int t = pq.top();
            pq.pop();

            int leave = floor(sqrt(t));
            if( leave > 0 )
                pq.push(leave);

        }

        while( !pq.empty() ) {
            ans += pq.top();
            pq.pop();
        }

        return ans;
    }
};
