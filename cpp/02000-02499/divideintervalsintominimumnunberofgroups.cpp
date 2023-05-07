
// 2406. Divide Intervals Into Minimum Number of Groups
// https://leetcode.com/problems/divide-intervals-into-minimum-number-of-groups/




class Solution {
public:
    int minGroups(vector<vector<int>>& intervals) {

        sort(intervals.begin(),intervals.end(),[](const vector<int>& a, const vector<int>& b){
            if( a[0] < b[0] ) {
                return true;
            } else if( a[0] == b[0] ) {
                if( a[1] < b[1] ) {
                    return true;
                }
            }
            return false;
        });


        priority_queue<int, vector<int>, greater<int>> pq;
        pq.push(intervals[0][1]);

        for(int i = 1; i < intervals.size(); ++i) {

            if( pq.top() < intervals[i][0] ) {
                // add to group
                pq.pop();
                pq.push(intervals[i][1]);
            } else {
                // start a new group
                pq.push(intervals[i][1]);
            }
        }

        return pq.size();
    }
};
