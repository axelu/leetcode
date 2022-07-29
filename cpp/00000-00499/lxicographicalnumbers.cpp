
// 386. Lexicographical Numbers
// https://leetcode.com/problems/lexicographical-numbers/



class Solution {
private:
    void dfs(int u, int n, vector<int>& ans) {

        for(int i = 0; i < 10; ++i) {
            int u_new = u + i;
            if( u_new > n )
                return;
            ans.push_back(u_new);
            dfs(u_new*10,n,ans);
        }
    }

public:
    vector<int> lexicalOrder(int n) {
        vector<int> ans;
        for(int i = 1; i < 10; ++i) {
            if( i > n )
                break;
            ans.push_back(i);
            dfs(i*10,n,ans);



        }

        return ans;
    }
};
