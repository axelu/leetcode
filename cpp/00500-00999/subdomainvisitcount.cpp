
// 811. Subdomain Visit Count
// https://leetcode.com/problems/subdomain-visit-count/


class Solution {
public:
    vector<string> subdomainVisits(vector<string>& cpdomains) {
        int n = cpdomains.size();
        unordered_map<string,int> um;
        pair<unordered_map<string,int>::iterator,bool> p;
        string sdomain;
        int cnt;
        for(int i = 0; i < n; ++i)
            for(int j = 0; j < cpdomains[i].size(); ++j) {
                if( cpdomains[i][j] == ' ' )
                    cnt = stoi(cpdomains[i].substr(0,j));
                if( cpdomains[i][j] == ' ' || cpdomains[i][j] == '.' ) {
                    sdomain = cpdomains[i].substr(j+1);
                    p = um.insert({sdomain,cnt});
                    if( !p.second )
                        p.first->second += cnt;
                }
            }

        vector<string> ans;
        for(auto it = um.begin(); it != um.end(); ++it)
            ans.push_back(to_string(it->second)+' '+it->first);

        return ans;
    }
};
