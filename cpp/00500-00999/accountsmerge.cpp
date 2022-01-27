
// 721. Merge Accounts
// https://leetcode.com/problems/accounts-merge/



class Solution {
private:
    void explore(string src, unordered_map<string,vector<string>>& t, unordered_set<string>& seen, vector<string>& path) {
        if( !seen.insert(src).second ) return;
        path.push_back(src);

        vector<string> aliases = t.find(src)->second;
        for(int i = 0; i < aliases.size(); ++i)
            explore(aliases[i],t,seen,path);
    }

public:
    vector<vector<string>> accountsMerge(vector<vector<string>>& accounts) {
        size_t n = accounts.size();
        if( n == 1 ) return accounts;

        unordered_map<string,string> emailtoname;
        unordered_map<string,vector<string>> t; // undirected graph
        unordered_map<string,vector<string>>::iterator f;
        pair<unordered_map<string,vector<string>>::iterator,bool> p;
        size_t asz;
        string name,em1;
        for(int i = 0; i < n; ++i) {
            asz = accounts[i].size();
            if( asz < 2 ) continue; // ignore accounts with no email

            // 1st element is the name
            name = accounts[i][0];
            // 1st email in list of emails on this account
            em1 = accounts[i][1];

            f = t.find(em1);
            if( f == t.end() ) {
                // emailtoname for 1st email
                emailtoname.insert({em1,name});

                vector<string> v;
                for(int j = 2; j < asz; ++j) {
                    if( accounts[i][j] != em1 ) {
                        v.push_back(accounts[i][j]);

                        p = t.insert({accounts[i][j],{em1}});
                        if( !p.second )
                            p.first->second.push_back(em1);

                        emailtoname.insert({accounts[i][j],name});
                    }
                }
                // insert all edges from the 1st email
                t.insert({em1,v});
            } else {
                for(int j = 2; j < asz; ++j) {
                    if( accounts[i][j] != em1 ) {
                        f->second.push_back(accounts[i][j]);

                        p = t.insert({accounts[i][j],{em1}});
                        if( !p.second )
                            p.first->second.push_back(em1);

                        emailtoname.insert({accounts[i][j],name});
                    }
                }
            }
        }

        size_t k = emailtoname.size();
        unordered_map<string,string>::iterator it = emailtoname.begin();
        unordered_set<string> seen;
        vector<vector<string>> ans;
        vector<string> path;
        for(int i = 0; i < k; ++i) {
            if( seen.find(it->first) == seen.end() ) {
                explore(it->first,t,seen,path);
                sort(path.begin(),path.end());
                path.insert(path.begin(),it->second);
                ans.push_back(path);
                path.clear();
            }
            ++it;
        }

        return ans;
    }
};
