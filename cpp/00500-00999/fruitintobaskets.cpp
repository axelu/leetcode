
// 904. Fruit Into Baskets
// https://leetcode.com/problems/fruit-into-baskets/



class Solution {
public:
    int totalFruit(vector<int>& fruits) {
        int n = fruits.size();
        if( n <= 2 )
            return n;

        int cnt[n];memset(cnt,0,sizeof cnt);
        int ans = 1;

        // we can only have two fruit types in our
        // sliding window
        int a = fruits[0],b = -1;
        int last_seen_a = 0,last_seen_b;
        cnt[a] = 1;
        for(int i = 0,j = 1; j < n; ++j) {
            int curr_fruit = fruits[j];

            if( b == -1 ) {
                if( curr_fruit == a ) {
                    ++cnt[a];
                    last_seen_a = j;
                    ++ans;
                } else {
                    b = curr_fruit;
                    cnt[b] = 1;
                    last_seen_b = j;
                    ++ans;
                }
                continue;
            }

            if( curr_fruit != a && curr_fruit != b ) {
                ans = max(ans,cnt[a]+cnt[b]);

                // reduce sliding window till we only have
                // two fruits in our window

                if( last_seen_a < last_seen_b ) {
                    i = last_seen_a+1;
                    cnt[b] = j-i;
                    cnt[a] = 0;
                    a = fruits[j];
                    cnt[a] = 1;
                    last_seen_a = j;
                } else {
                    i = last_seen_b+1;
                    cnt[a] = j-i;
                    cnt[b] = 0;
                    b = fruits[j];
                    cnt[b] = 1;
                    last_seen_b = j;
                }
            } else {
                if( curr_fruit == a ) {
                    ++cnt[a];
                    last_seen_a = j;
                } else {
                    ++cnt[b];
                    last_seen_b = j;
                }
            }
        }
        // finish up
        if( b != -1 )
            ans = max(ans,cnt[a]+cnt[b]);

        return ans;
    }
};
