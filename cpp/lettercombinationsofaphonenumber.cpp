
// 17. Letter Combinations of a Phone Number
// https://leetcode.com/problems/letter-combinations-of-a-phone-number/
// day 8 April 2021 challenge
// https://leetcode.com/explore/challenge/card/april-leetcoding-challenge-2021/594/week-2-april-8th-april-14th/3701/



class Solution {
private:
    vector<string> kp = {"","","abc","def","ghi","jkl","mno","pqrs","tuv","wxyz"};

    void rec(string& digits, int n, int idx, string& path, vector<string>& ans) {
        int digit = digits[idx]-'0';
        for(int i = 0; i < kp[digit].size(); ++i) {
            path += kp[digit][i];
            if( idx == n-1 ) ans.push_back(path);
            else rec(digits,n,idx+1,path,ans);
            path.pop_back();
        }
    }

public:
    vector<string> letterCombinations(string& digits) {
        int n = digits.size(); // 0 <= digits.length <= 4, digits[i] is a digit in the range ['2', '9']
        vector<string> ans;
        if( n == 0 ) return ans;

        string path = "";
        rec(digits,n,0,path,ans);
        return ans;
    }
};
