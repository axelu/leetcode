
// 1773. Count Items Matching a Rule
// https://leetcode.com/problems/count-items-matching-a-rule/


class Solution {
public:
    int countMatches(vector<vector<string>>& items, string ruleKey, string ruleValue) {
        int n = items.size();

        int ans = 0;
        for(int i = 0; i < n; ++i) {
            if( (ruleKey == "type" && ruleValue == items[i][0]) ||
                (ruleKey == "color" && ruleValue == items[i][1]) ||
                (ruleKey == "name" && ruleValue == items[i][2]) )
                ++ans;
        }
        return ans;
    }
};
