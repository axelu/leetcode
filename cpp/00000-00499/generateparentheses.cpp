
// 22. Generate Parentheses
// https://leetcode.com/problems/generate-parentheses/



class Solution {
private:

    void rec(int n, int step, string& prefx, string& suffx, vector<string>& ans) {
        // cout << step << " prefx " << prefx << " suffx " << suffx << endl;

        // go down
        prefx += '(';
        suffx.insert(0,1,')');
        if( step == n-1 ) {
            // cout << prefx << suffx << endl;
            ans.push_back(prefx+suffx);
            // backtrack
            prefx.pop_back();
            suffx.erase(0,1);
            return;

        }

        // go right
        string tprefx = prefx;
        string tsuffx = suffx;
        for(int i = 0; i <= suffx.size(); ++i) {
            rec(n,step+1,tprefx,tsuffx,ans);
            tsuffx.erase(0,1);
            tprefx += ')';
        }

        // backtrack
        prefx.pop_back();
        suffx.erase(0,1);
    }


public:
    vector<string> generateParenthesis(int n) {
        string prefx = "";
        string suffx = "";
        vector<string> ans;
        rec(n,0,prefx,suffx,ans);
        return ans;
    }
};
