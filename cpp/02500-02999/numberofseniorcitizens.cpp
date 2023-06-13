
// 2678. Number of Senior Citizens
// https://leetcode.com/problems/number-of-senior-citizens/



class Solution {
public:
    int countSeniors(vector<string>& details) {
        // age of passenger substr(11,2)

        int ans = 0;
        for(string& s: details)
            if( stoi(s.substr(11,2)) > 60 )
                ++ans;

        return ans;
    }
};
