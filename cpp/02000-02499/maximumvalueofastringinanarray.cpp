
// 2496. Maximum Value of a String in an Array
// https://leetcode.com/problems/maximum-value-of-a-string-in-an-array/



class Solution {
public:
    int maximumValue(vector<string>& strs) {
        int mx = 0;
        for(auto& s: strs) {
            bool digitsonly = true;
            for(char c: s)
                if( !isdigit(c) ) {
                    digitsonly = false;
                    break;
                }
            if( digitsonly )
                mx = max(mx,stoi(s));
            else
                mx = max(mx,(int)s.size());
        }

        return mx;
    }
};
