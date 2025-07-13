
// 3527. Find the Most Common Response
// https://leetcode.com/problems/find-the-most-common-response/





class Solution {
private:
    bool cmp(string& a, string& b) {
        // returns true if string a is lexicographically smaller than string b
        // it is guaranteed that a and b are non-empty

        int a_sz = a.size();
        int b_sz = b.size();
        for(int i = 0; i < a_sz && i < b_sz; ++i)
            if( a[i] != b[i] )
                return a[i] < b[i];

        return a_sz < b_sz;
    }

public:
    string findCommonResponse(vector<vector<string>>& responses) {

        map<string,unordered_set<int>> dic;
        int most_common_response_cnt = 0;
        string ans;

        int response_sz = responses.size();
        for(int i = 0; i < response_sz; ++i) {
            int n = responses[i].size();
            for(int j = 0; j < n; ++j) {
                auto p = dic.insert({responses[i][j],{i}});
                if( !p.second )
                    p.first->second.insert(i);

                if( p.first->second.size() > most_common_response_cnt ) {
                    most_common_response_cnt = p.first->second.size();
                    ans = responses[i][j];
                } else if( p.first->second.size() == most_common_response_cnt ) {
                    if( cmp(responses[i][j],ans) )
                        ans = responses[i][j];
                }
            }
        }

        return ans;
    }
};
