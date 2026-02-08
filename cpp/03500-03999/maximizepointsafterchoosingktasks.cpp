
// 3767. Maximize Points After Choosing K Tasks
// https://leetcode.com/problems/maximize-points-after-choosing-k-tasks/


class Solution {
public:
    long long maxPoints(vector<int>& technique1, vector<int>& technique2, int k) {
        int n = technique1.size(); // technique1.size() == technique2.size()
        if( k == n ) {
            // all tasks have to completed by technique1
            long long ret = 0LL;
            for(long long x: technique1)
                ret += x;
            return ret;
        }
        if( k == 0 ) {
            // we choose the greater points at each position
            long long ret = 0LL;
            for(int i = 0; i < n; ++i)
                ret += (long long)max(technique1[i],technique2[i]);
            return ret;
        }

        // let diff[i] = technique1[i] - technique2[i]
        // we greedily chose abs(diff[i]) and keep track if it choose
        //     technique1 or technique2
        // if abs(diff[i]) == abs(diff[j]), we prefer technique1
        // we count how many that is from technique1
        // if that number is ge k, we are done
        // else we flip smallest diffs to use technique1

        long long score = 0LL;
        int t1 = 0; // chose from t1
        vector<pair<int,int>> v(n); // {{technique1[i], technique2[i]},...}
        for(int i = 0; i < n; ++i) {
            v[i] = {technique1[i], technique2[i]};
            if( technique1[i] >= technique2[i] )
                ++t1;
            score += (long long)max(technique1[i],technique2[i]);
        }
        if( t1 >= k )
            return score;

        sort(begin(v), end(v), [](const pair<int,int>& a, const pair<int,int>& b){
            return abs(a.first - a.second) < abs(b.first-b.second);
        });

        for(int i = 0; i < n && t1 < k; ++i) {
            if( v[i].first >= v[i].second ) {
                // we already chose technique1
                continue;
            }
            // v[i].first < v[i].second
            // for our score we use v[i].second
            // but we need to use v[i].first
            score -= (long long)v[i].second;
            score += (long long)v[i].first;
            ++t1;
        }

        return score;
    }
};
