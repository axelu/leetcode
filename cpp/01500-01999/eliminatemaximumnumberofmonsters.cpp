
// 1921. Eliminate Maximum Number of Monsters
// https://leetcode.com/problems/eliminate-maximum-number-of-monsters/






class Solution {
public:
    int eliminateMaximum(vector<int>& dist, vector<int>& speed) {
        int n = dist.size();
        vector<double> vd(n);

        double t;
        for(int i = 0; i < n; ++i)
            vd[i] = (double)dist[i]/(double)speed[i];
        sort(begin(vd),end(vd));

        int i = 1;
        for(; i < n; ++i)
            if( vd[i] <= (double)i )
                break;

        return i;
    }
};
