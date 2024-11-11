
// 3211. Generate Binary Strings Without Adjacent Zeros
// https://leetcode.com/problems/generate-binary-strings-without-adjacent-zeros/


class Solution {
private:
    vector<string> ans;

    void rec(string& s, const int n) {
        int s_sz = s.size();
        if( s_sz == n ) {
            ans.push_back(s);
            return;
        }

        if( s_sz == 0 ) {
            s.push_back('0');
            rec(s, n);
            // backtrack
            s.pop_back();
            s.push_back('1');
            rec(s, n);

        } else {
            char pre = s.back();
            if( pre == '1' ) {
                s.push_back('0');
                rec(s, n);
                // backtrack
                s.pop_back();
            }
            s.push_back('1');
            rec(s, n);
            // backtrack
            s.pop_back();
        }

        return;
    }


public:
    vector<string> validStrings(int n) {
        string s = "";
        rec(s, n);
        return ans;
    }
};
