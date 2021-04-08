
// 997. Find the Town Judge
// https://leetcode.com/problems/find-the-town-judge/


class Solution {
public:
    int findJudge(int N, vector<vector<int>>& trust) {
        set<int> outgoing[N+1];

        for(int i = 0; i < trust.size(); ++i)
            outgoing[trust[i][0]].insert(trust[i][1]);

        // is there a person with no outgoing connections?
        int townJudge = -1;
        for(int i = 1; i <= N; ++i)
            if( outgoing[i].empty() ) {
                townJudge = i;
                break;
            }
        if( townJudge == -1 ) return -1;

        // does everyone except the town judge have an outgoing connection to the town judge?
        for(int i = 1; i <= N; ++i)
            if( i != townJudge && outgoing[i].find(townJudge) ==  outgoing[i].end() )
                return -1;

        return townJudge;
    }
};
