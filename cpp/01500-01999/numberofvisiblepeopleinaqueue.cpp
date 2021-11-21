
// 1944. Number of Visible People in a Queue
// https://leetcode.com/problems/number-of-visible-people-in-a-queue/
// https://leetcode.com/contest/biweekly-contest-57/problems/number-of-visible-people-in-a-queue/





class Solution {
public:
    vector<int> canSeePersonsCount(vector<int>& heights) {
        // we only need to consider what is to the right
        int n = heights.size();

        vector<int> ans(n,0);

        if( n == 1 )
            return ans;

        stack<int> stck;
        stck.push(heights[n-1]);

        for(int i = n-2; i >= 0; --i) {

            while(!stck.empty() && stck.top()<heights[i]){
                ++ans[i];
                stck.pop();
            }
            if( !stck.empty() )
                ++ans[i];

            stck.push(heights[i]);
        }

        return ans;
    }
};
