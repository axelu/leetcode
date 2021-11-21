
// 71. Simplify Path
// https://leetcode.com/problems/simplify-path/
// day 5 February 2021 challenge
// https://leetcode.com/explore/featured/card/february-leetcoding-challenge-2021/584/week-1-february-1st-february-7th/3629/



class Solution {
private:
    pair<string,string> getOp(string& s) {
        pair<string,string> ans = make_pair("","");
        if( s.empty() ) return ans;
        if( s == "." ) return ans;
        if( s == ".." ) {
            ans.first = "up";
            return ans;
        }
        ans.first = "down";
        ans.second = s;
        return ans;
    }
public:
    string simplifyPath(string path) {
        size_t n = path.size();
        string ans = "/";
        string ins = "";
        pair<string,string> p;
        for(int i = 0; i < n; ++i) {
            if( path[i] != '/' ) {
                ins += path[i];
            } else {
                p = getOp(ins);
                if( !p.first.empty() ) {
                    if( p.first == "down" ) {
                        ans += p.second+"/";
                    } else {
                        if( ans.size() > 1 ) {
                            int idx = ans.rfind("/",ans.size()-2)+1;
                            ans = ans.substr(0,idx);
                        }
                    }
                }
                ins = "";
            }
        }
        // last op
        p = getOp(ins);
        if( !p.first.empty() ) {
            if( p.first == "down" ) {
                ans += p.second;
            } else {
                if( ans.size() > 1 ) {
                    int idx = ans.rfind("/",ans.size()-2)+1;
                    ans = ans.substr(0,idx);
                }
            }
        }
        if( ans.size() > 1 && ans[ans.size()-1] == '/' )
                ans = ans.substr(0,ans.size()-1);

        return ans;
    }
};
