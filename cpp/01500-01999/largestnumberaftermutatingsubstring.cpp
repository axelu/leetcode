
// 1946. Largest Number After Mutating Substring
// https://leetcode.com/problems/largest-number-after-mutating-substring/
// https://leetcode.com/contest/weekly-contest-251/problems/largest-number-after-mutating-substring/




class Solution {
public:
    string maximumNumber(string& num, vector<int>& change) {

        bool f = false;
        int t;
        for(int i = 0; i < num.size(); ++i) {
            t = num[i]-'0';

            if( !f ) {
                if( change[t] > t ) {
                    f = true;
                    num[i] = (char)(change[t]+'0');
                 }
            } else {
                if( change[t] > t ) {
                    num[i] = (char)(change[t]+'0');
                } else if( change[t] < t ) {
                    break;
                }
            }
        }

        return num;
    }
};
