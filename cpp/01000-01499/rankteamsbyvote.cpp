
// 1366. Rank Teams by Votes
// https://leetcode.com/problems/rank-teams-by-votes/



class Solution {
public:
    string rankTeams(vector<string>& votes) {
        if( votes.size() == 1 )
            return votes[0];

        int m = votes[0].size();    // number of teams

        // build set of team letters
        set<char> st;
        for(char c: votes[0] )
            st.insert(c);

        // build map of teams
        // we assign lowest letter the highest index
        unordered_map<char,int> um;
        unordered_map<int,char> umr;
        int idx = m-1;
        vector<vector<int>> vv(m,vector<int>(m+1,0));
        for(auto it = st.begin(); it != st.end(); ++it) {
            um[*it] = idx;
            umr[idx] = *it;
            vv[idx][m] = idx;
            --idx;
        }

        // count the votes
        for(string& s: votes) {
            for(int i = 0; i < m; ++i) {
                // get team index
                char t = s[i];
                int t_idx = um[t];

                // cast the vote
                ++vv[t_idx][i];
            }
        }

        // sort
        sort(vv.begin(),vv.end(),[](vector<int>& a, vector<int>& b){
            return a > b;
        });

        string ans = "";

        for(auto& vi: vv) {
            ans.push_back(umr[vi[m]]);
        }

        return ans;
    }
};
