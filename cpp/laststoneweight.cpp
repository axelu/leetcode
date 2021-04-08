
// 1046. Last Stone Weight
// https://leetcode.com/problems/last-stone-weight/

class Solution {
public:
    int lastStoneWeight(vector<int>& stones) {
        size_t n = stones.size();
        priority_queue<int> q;
        for(int i = 0; i < n; ++i)
            q.push(stones[i]);

        int x,y;
        while(q.size() >= 2) {
            y = q.top();
            q.pop();
            x = q.top();
            q.pop();
            if( x != y ) q.push(y-x);
        }

        return q.empty() ? 0 : q.top();
    }
};
