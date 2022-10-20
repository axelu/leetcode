

// 2358. Maximum Number of Groups Entering a Competition
// https://leetcode.com/problems/maximum-number-of-groups-entering-a-competition/




class Solution {
public:
    int maximumGroups(vector<int>& grades) {
        int n = grades.size();
        if( n <= 2 )
            return 1;
        if( n == 3 )
            return 2;

        // sort(grades.begin(),grades.end());

        // 1 <= grades[i] <= 10^5
        // because of 1 <= grades[i], the sum of group with more members
        // is always greater than the sum of the group with less members
        // so the only thing to check is how many groups we can form
        // based on n

        int cnt = 0;
        int i = 0;
        int l = 1;
        while(true) {
            int nxt_i = i + l;
            if( nxt_i > n-1 ) {
                // current group's length
                int curr_l = n - i;
                if( curr_l == l )
                    ++cnt;
                break;
            }
            ++cnt;
            ++l;
            i = nxt_i;
        }

        return cnt;
    }
};
