
// 1925. Count Square Sum Triples
// https://leetcode.com/problems/count-square-sum-triples/




class Solution {
public:
    int countTriples(int n) {
        unordered_set<int> c2;

        for(int i = 1; i <= n; ++i)
            c2.insert(i*i);

        int ans = 0;
        int a2,b2;
        for(int i = 1; i <= n; ++i) {
            a2 = i*i;
            for(int j = i; j <= n; ++j) {
                b2 = j*j;

                if( c2.count(a2+b2) ) {
                    if( i == j )
                        ans += 1;
                    else
                        ans += 2;
                }
            }
        }

        return ans;
    }
};
