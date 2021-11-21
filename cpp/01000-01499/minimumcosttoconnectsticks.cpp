
// 1167. Minimum Cost to Connect Sticks
// https://leetcode.com/problems/minimum-cost-to-connect-sticks/



class Solution {
public:
    int connectSticks(vector<int>& sticks) {

        priority_queue<int, std::vector<int>, std::greater<int>> pq;
        for(int i = 0; i < sticks.size(); ++i)
            pq.push(sticks[i]);


        int ans = 0,a;
        while(pq.size()>1) {
            a = pq.top();
            pq.pop();
            a += pq.top();
            pq.pop();
            ans += a;
            pq.push(a);
        }
        return ans;
    }
};
