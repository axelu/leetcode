
// 1304. Find N Unique Integers Sum up to Zero
// https://leetcode.com/problems/find-n-unique-integers-sum-up-to-zero/

class Solution {
public:
    vector<int> sumZero(int n) {
        if( n == 1 ) return {0};

        vector<int> r;

        int N = n / 2;
        for(int i = 1; i <= N; ++i) {
            r.push_back(i);
            r.push_back(i * -1);
        }
        if( n % 2 != 0 ) r.push_back(0);

        return r;
    }
};
