
// 1090. Largest Values From Labels
// https://leetcode.com/problems/largest-values-from-labels/




class Solution {
public:
    int largestValsFromLabels(vector<int>& values, vector<int>& labels, int numWanted, int useLimit) {
        int n = values.size(); // values.size() == labels.size()

        vector<array<int,2>> v(n); // {{value,label},...}
        for(int i = 0; i < n; ++i)
            v[i] = {values[i],labels[i]};

        // sort by value desc
        sort(v.begin(),v.end(),[](array<int,2>& a, array<int,2>& b){
            return a[0] > b[0];
        });

        int score = 0;

        int cnt[20001];memset(cnt,0,sizeof cnt);

        int used = 0;
        for(int i = 0; i < n && used < numWanted; ++i)
            if( cnt[v[i][1]] < useLimit ) {
                ++cnt[v[i][1]];
                score += v[i][0];
                used += 1;
            }

        return score;
    }
};
