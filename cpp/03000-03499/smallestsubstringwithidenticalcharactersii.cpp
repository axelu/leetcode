
// 3399. Smallest Substring With Identical Characters II
// https://leetcode.com/problems/smallest-substring-with-identical-characters-ii/




class Solution {
private:
    int get_max_consecutive(string& s) {
        int n = s.size();

        int max_consecutive = 1;
        int count_consecutive = 1;
        for(int i = 1; i < n; ++i) {
            if( s[i-1] == s[i] ) {
                ++count_consecutive;
            } else {
                max_consecutive = max(max_consecutive, count_consecutive);
                count_consecutive = 1;
            }
        }
        // finish up
        max_consecutive = max(max_consecutive, count_consecutive);

        return max_consecutive;
    }

    bool solve_for_1(string& str, int numOps) {
        int n = str.size();
        int maxConsecutive = 1;

        string s = str;
        int ops = numOps;

        bool ret = true;

        int count_consecutive = 1;
        for(int i = 1; i < n; ++i) {
            if( s[i-1] == s[i] ) {
                ++count_consecutive;
                if( count_consecutive > maxConsecutive ) {
                    --ops;
                    if( ops < 0 ) {
                        ret = false;
                        break;
                    }
                    s[i] = s[i] == '1' ? '0' : '1';
                    count_consecutive = 1;
                }
            } else {
                count_consecutive = 1;
            }
        }

        if( !ret ) {
            s = str;
            ops = numOps-1;
            s[0] = s[0] == '1' ? '0' : '1';

            count_consecutive = 1;
            for(int i = 1; i < n; ++i) {
                if( s[i-1] == s[i] ) {
                    ++count_consecutive;
                    if( count_consecutive > maxConsecutive ) {
                        --ops;
                        if( ops < 0 )
                            return false;
                        s[i] = s[i] == '1' ? '0' : '1';
                        count_consecutive = 1;
                    }
                } else {
                    count_consecutive = 1;
                }
            }
        }

        return true;
    }

    bool solve(string& s, int maxConsecutive, int numOps) {
        int n = s.size(); // 2 <= n

        int ops = 0;
        char pre = s[0];
        int count_consecutive = 1;
        for(int i = 1; i < n; ++i) {
            if( pre == s[i] ) {
                ++count_consecutive;
                if( count_consecutive > maxConsecutive ) {
                    // we have no choice but to flip
                    // and with that consume an op
                    ++ops;
                    // early exit
                    if( ops > numOps )
                        return false;

                    if( i < n-1 && s[i] == s[i+1] ) {
                        // we don't adversly impact the following seq
                        // by flipping us
                        pre = s[i] == '0' ? '1' : '0';
                    } else {
                        // we flip the prior one
                        // current one stays as is
                    }
                } else {
                    pre = s[i];
                }
            } else {
                count_consecutive = 1;
                pre = s[i];
            }
        }

        return true;
    }

    // binary search
    int search(string& str, int numOps, int s, int e) {
        if( s > e )
            return -1;

        int mid = s + ((e-s)/2);
        bool f = solve(str, mid, numOps);
        if( f ) {
            // can we do better?
            int t = search(str, numOps, s, mid-1);
            return t != -1 ? t : mid;
        }

        return search(str, numOps, mid+1, e);
    }

public:
    int minLength(string s, int numOps) {
        int n = s.size();

        if( n == 1 )
            return 1;

        int max_consecutive = get_max_consecutive(s);
        if( numOps == 0 || max_consecutive == 1 )
            return max_consecutive;

        // can we achive 1?
        if( solve_for_1(s, numOps) )
            return 1;

        // our solution lies somewhere between 2 and
        // the max consecutive run of 0s or 1s (which could be n)
        return search(s, numOps, 2, max_consecutive);
    }
};
