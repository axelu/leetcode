
// 609. Find Duplicate File in System
// https://leetcode.com/problems/find-duplicate-file-in-system/
// day 18 May 2021 challenge
// https://leetcode.com/explore/challenge/card/may-leetcoding-challenge-2021/600/week-3-may-15th-may-21st/3747/





class Solution {
private:
    pair<string,string> getNameAndContent(string& s) {
        int f = s.find('(');
        string name = s.substr(0,f);
        string content = s.substr(f+1,s.size()-f-1);
        return make_pair(name,content);
    }
public:
    vector<vector<string>> findDuplicate(vector<string>& paths) {
        unordered_map<string,vector<string>> um;
        pair<unordered_map<string,vector<string>>::iterator,bool> p;
        int i;
        for(i = 0; i < paths.size(); ++i) {

            stringstream ss(paths[i]);
            string path;
            string s;
            pair<string,string> namecontent;
            while( getline(ss,s,' ') ) {
                if( path.empty() ) {
                    path = s;
                    continue;
                }
                namecontent = getNameAndContent(s);
                p = um.insert({namecontent.second,{path+"/"+namecontent.first}});
                if( !p.second )
                    p.first->second.push_back(path+"/"+namecontent.first);
            }
        }

        vector<vector<string>> ans;
        for(auto it = um.begin(); it != um.end(); ++it)
            if( it->second.size() >= 2 )
                ans.push_back(it->second);

        return ans;
    }
};
