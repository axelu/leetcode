
// 887. Super Egg Drop
// https://leetcode.com/problems/super-egg-drop/



// Solution Approach #1
class Solution {
private:
    unordered_map<int,int> mem;

    int rec(int k, int n) {
        int key = (n << 7) + k;
        auto f = mem.find(key);
        if( f != mem.end() )
            return f->second;

        int ret;

        if( n == 0 ) {
            ret = 0;
        } else if( k == 1 ) {
            ret = n;
        } else {
            int s = 1, e = n;
            while(s + 1 < e) {
                int mid = s + ((e-s)/2);
                int t1 = rec(k-1, mid-1);
                int t2 = rec(k, n-mid);

                if( t1 < t2 ) {
                    s = mid;
                } else if( t1 > t2 ) {
                    e = mid;
                } else {
                    s = mid;
                    e = mid;
                }
            }

            ret = 1 + min(max(rec(k-1, s-1), rec(k, n-s)),
                          max(rec(k-1, e-1), rec(k, n-e)));
        }

        mem.insert({key,ret});
        return ret;
    }

public:
    int superEggDrop(int k, int n) {
        // 1 <= k <= 100
        // 1 <= n <= 10000
        if( k == 1 ) // we must drop the egg from every floor
            return n;

        // if we have k eggs, how high can we start at to determine
        // if our egg breaks from the starting floor, at which floor f is
        // once we know that, we can just repeat the process upwards

        return rec(k,n);
    }
};
