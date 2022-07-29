
// 756. Pyramid Transition Matrix
// https://leetcode.com/problems/pyramid-transition-matrix/


class Solution {
private:
    unordered_set<string> seen;

    bool dfs(string& bottom, int lvl, int pos, string& top, unordered_map<string,vector<char>>& um) {
        if( lvl == 1 )
            return true;

        if( pos == 0 && seen.count(bottom) )
            return false;

        string curr = bottom.substr(pos,2);
        for(auto& c : um[curr]) {
            top += c;
            if( pos == lvl - 2 ) {
                string new_top = "";
                if( dfs(top,lvl-1,0,new_top,um) )
                    return true;
            } else {
                if( dfs(bottom,lvl,pos+1,top,um) )
                    return true;
            }
            // backtrack
            top.pop_back();
         }

        if( pos == 0 )
            seen.insert(bottom);

        return false;
    }

public:
    bool pyramidTransition(string bottom, vector<string>& allowed) {
        int lvl = bottom.size();

        unordered_map<string,vector<char>> um;
        for(auto& s : allowed)
            um[s.substr(0,2)].push_back(s.back());

        string top = "";
        return dfs(bottom,lvl,0,top,um);
    }
};
