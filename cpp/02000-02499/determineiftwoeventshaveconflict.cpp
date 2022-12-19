
// 2446. Determine if Two Events Have Conflict
// https://leetcode.com/problems/determine-if-two-events-have-conflict/


class Solution {
public:
    bool haveConflict(vector<string>& event1, vector<string>& event2) {
        return !( event1[1] < event2[0] || event1[0] > event2[1] );
    }
};
