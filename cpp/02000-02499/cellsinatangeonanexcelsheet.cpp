
// 2194. Cells in a Range on an Excel Sheet
// https://leetcode.com/problems/cells-in-a-range-on-an-excel-sheet/



class Solution {
public:
    vector<string> cellsInRange(string s) {
        // s in the format "<col1><row1>:<col2><row2>"
        // cols A - Z, rows 1 - 9

        int c_mn = s[0]-'A';
        int c_mx = s[3]-'A';
        int r_mn = s[1]-'0';
        int r_mx = s[4]-'0';

        vector<string> ans;

        string t = "";
        for(int j = c_mn; j <= c_mx; ++j) {
            t += j + 'A';
            for(int i = r_mn; i <= r_mx; ++i) {
                t += i + '0';
                ans.push_back(t);
                t.pop_back();
            }
            t.pop_back();
        }

        return ans;
    }
};
