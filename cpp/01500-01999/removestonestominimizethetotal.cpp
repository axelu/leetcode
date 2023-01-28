
// 1962. Remove Stones to Minimize the Total
// https://leetcode.com/problems/remove-stones-to-minimize-the-total/


class Solution {
public:
    int minStoneSum(vector<int>& piles, int k) {

        priority_queue<int> pq;
        for(int x: piles)
            pq.push(x);

        while( !pq.empty() ) {
            int x = pq.top();
            pq.pop();

            x = x - x/2;
            pq.push(x);
            if( --k == 0 )
                break;
        }

        int ans = 0;
        while( !pq.empty() ) {
            ans += pq.top();
            pq.pop();
        }

        return ans;
    }
};
