
// 1323. Maximum 69 Number
// https://leetcode.com/problems/maximum-69-number/


class Solution {
public:
    int maximum69Number (int num) {
        string s = to_string(num);
        auto n = s.size();
        int mx = num;
        string s0,s1,s2;
        for(int i = 0; i < n; ++i) {
            s0 = s.substr(0,i);
            s1 = s.substr(i,1) == "6" ? "9" : "6";
            s2 = i == n - 1 ? "" : s.substr(i+1);
            mx = max(mx,stoi(s0+s1+s2));
        }

        return mx;
    }
};
