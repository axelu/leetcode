
// 3170. Lexicographically Minimum String After Removing Stars
// https://leetcode.com/problems/lexicographically-minimum-string-after-removing-stars/




class Solution {
public:
    string clearStars(string s) {
        int n = s.size();

        bool del[n]; memset(del,false,sizeof del);

        auto cmp = [](const pair<char,int>& a, const pair<char,int>& b){
            if( a.first > b.first ) {
                return true;
            } else if( a.first == b.first ) {
                if( a.second < b.second ) {
                    return true;
                }
            }
            return false;
        };
        priority_queue<pair<char,int>,vector<pair<char,int>>,decltype(cmp)> pq(cmp);

        for(int i = 0; i < n; ++i) {
            if( s[i] == '*' ) {
                del[pq.top().second] = true;
                pq.pop();
            } else {
                pq.push({s[i],i});
            }
        }

        string ans = "";
        for(int i = 0; i < n; ++i)
            if( s[i] != '*' && !del[i] )
                ans.push_back(s[i]);

        return ans;
    }
};
