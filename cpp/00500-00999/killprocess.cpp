
// 582. Kill Process
// https://leetcode.com/problems/kill-process/




class Solution {
private:
    void dfs(int pid, unordered_map<int,vector<int>>& t, vector<int>& ans) {
        ans.push_back(pid);
        unordered_map<int,vector<int>>::iterator f;
        f = t.find(pid);
        for(int i = 0; i < f->second.size(); ++i)
           dfs(f->second[i],t,ans);
    }
public:
    vector<int> killProcess(vector<int>& pid, vector<int>& ppid, int kill) {
        int n = pid.size();
        if( n == 1 ) return pid;

        unordered_map<int,vector<int>> t;
        unordered_map<int,vector<int>>::iterator f;
        int root;
        for(int i = 0; i < n; ++i) {
            t.insert({pid[i],{}});
            if( ppid[i] == 0 ) {
                root = pid[i];
                continue;
            }
            f = t.find(ppid[i]);
            if( f == t.end() )
                t.insert({ppid[i],{pid[i]}});
            else
                f->second.push_back(pid[i]);
        }
        if( kill == root ) return pid;

        vector<int> ans;
        dfs(kill,t,ans);
        return ans;
    }
};
