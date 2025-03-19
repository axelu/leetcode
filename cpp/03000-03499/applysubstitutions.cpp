
// 3481. Apply Substitutions
// https://leetcode.com/problems/apply-substitutions/







class Solution {
private:
    void dfs(unordered_map<string,vector<string>>& g, string u, unordered_map<string,bool>& seen, stack<string>& stck) {

        seen[u] = true;

        for(int i = 0; i < g[u].size(); ++i) {
            string v = g[u][i];
            if( !seen[v] )
                dfs(g,v,seen,stck);
        }

        // push vertex onto stack
        // parents pushed onto stack after children
        stck.push(u);
    }

public:
    string applySubstitutions(vector<vector<string>>& replacements, string text) {
        int n = replacements.size();

        // replacements to map
        unordered_map<string,string> um;
        for(auto& replacement: replacements) {
            string key = replacement[0]; // key are guaranteed to be unique
            string val = replacement[1];
            um[key] = val;
        }

        // pass 1 - create directed graph
        // we will need to do a topological sort in order to process
        // replacement values
        unordered_map<string,vector<string>> g;
        for(auto& p: um) {
            string key = p.first;
            string val = p.second;

            string pkey = "";
            int mode = 0; // 0 not in key, 1 in key
            for(int i = 0; i < val.size(); ++i) {
                if( mode == 0 ) {
                    if( val[i] == '%' )
                        mode = 1;

                } else {
                    if( val[i] != '%' ) {
                        pkey.push_back(val[i]);
                    } else {
                        // create a directed edge pkey -> key
                        g[pkey].push_back(key);
                        pkey = "";
                        mode = 0;
                    }
                }
            }
        }
        // topological sort
        stack<string> stck; // visited vertices in topological order
        unordered_map<string,bool> seen;
        for(auto& p: um) {
            string u = p.first;
            if( !seen[u] )
                dfs(g,u,seen,stck);


        }
        // process replacements in topological order replacing placeholders in values
        while( !stck.empty() ) {
            string u = stck.top();
            stck.pop();

            string val = um[u];
            string val_new = "";
            string key = "";
            int mode = 0; // 0 not in key, 1 in key
            for(int i = 0; i < val.size(); ++i) {
                if( mode == 0 ) {
                    if( val[i] != '%' )
                        val_new.push_back(val[i]);
                    else
                        mode = 1;

                } else {
                    if( val[i] != '%' ) {
                        key.push_back(val[i]);
                    } else {
                        val_new = val_new + um[key];
                        key = "";
                        mode = 0;
                    }
                }
            }

            um[u] = val_new;
        }

        // pass 2 - final string
        string ans = "";
        string key = "";
        int mode = 0; // 0 not in key, 1 in key
        for(int i = 0; i < text.size(); ++i) {
            if( mode == 0 ) {
                if( text[i] != '%' )
                    ans.push_back(text[i]);
                else
                    mode = 1;

            } else {
                if( text[i] != '%' ) {
                    key.push_back(text[i]);
                } else {
                    ans = ans + um[key];
                    key = "";
                    mode = 0;
                }
            }
        }

        return ans;
    }
};
