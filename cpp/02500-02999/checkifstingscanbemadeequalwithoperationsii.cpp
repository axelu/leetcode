
// 2840. Check if Strings Can be Made Equal With Operations II
// https://leetcode.com/problems/check-if-strings-can-be-made-equal-with-operations-ii/



class Solution {
public:
    bool checkStrings(string& s1, string& s2) {
        int n = s1.size(); // s1.size() == s2.size()

        vector<int> s1cnteven(26,0);
        vector<int> s1cntodd(26,0);
        vector<int> s2cnteven(26,0);
        vector<int> s2cntodd(26,0);

        for(int i = 0; i < n; ++i) {
            if( i % 2 == 0 ) {
                ++s1cnteven[s1[i]-'a'];
                ++s2cnteven[s2[i]-'a'];
            } else {
                ++s1cntodd[s1[i]-'a'];
                ++s2cntodd[s2[i]-'a'];
            }
        }

        return s1cnteven == s2cnteven && s1cntodd == s2cntodd;
    }
};
