
// 3272. Find the Count of Good Integers
// https://leetcode.com/problems/find-the-count-of-good-integers/




/* two reqirements for an n-digit number
 *
 * The number of permutations of n objects with n1 identical objects of type 1,
 * n2 identical objects of type 2, ..., and nk identical objects of type k is
 * n! / (n1!n2!...nk!)
 * this is permutations with repitition
 *
 * example n = 3, k = 5 -> answer 27
 *       0 1 2 3 4 5 6 7 8 9  permutations
 * 505   1         2          3 -> 3! / 1!2!
 * 515     1       2          3
 * 525       1     2          3
 * 535         1   2          3
 * 545           1 2          3
 * 555             3          1 -> 3! / 3!
 * 565             2 1        3
 * 575             2   1      3
 * 585             2     1    3
 * 595             2       1  3
 *                           ---
 *                           28
 * BUT, 505 permutations: 055, 505, 550, we cannot have leading zero, hence
 * we need to discount in this case 1 permutation => 28 - 1 = 27

 */

// initialize once
long long factorial[11];
bool init = false;

class Solution {
private:
    long long ans;
    set<vector<int>> st;

    long long calc(vector<int>& v, int n) {
        long long div = 1LL;
        for(int j = 0; j < 10; ++j)
            div *= factorial[v[j]];

        long long ret = factorial[n] / div;

        // if this contains one or more 0s
        // then we need to discount permutations that start with 0
        if( v[0] != 0 ) {
            div = factorial[v[0]-1];
            for(int j = 1; j < 10; ++j)
                div *= factorial[v[j]];

            ret = ret - (factorial[n-1] / div);
        }

        return ret;
    }

    // generate palindromic number with n digits
    // and check if divisible by k
    void rec(int l, int r, string& t, int k) {
        // cout << "rec l " << l << " r " << r << endl;

        int s = l == 0 ? 1 : 0; // a number cannot have a leading zero

        if( l == r ) {
            for(int i = s; i < 10; ++i) {
                t[l] = '0'+i;
                long long a = stoll(t);
                if( a % k == 0 ) {
                    vector<int> v(10,0);
                    int n = t.size();
                    for(int j = 0; j < n; ++j)
                        ++v[t[j]-'0'];
                    if( st.insert(v).second ) {
                        // cout << t << endl;
                        ans += calc(v,n);
                    }
                }
            }
            return;

        } else if( l+1 == r ) {
            for(int i = s; i < 10; ++i) {
                t[l] = '0'+i;
                t[r] = '0'+i;
                long long a = stoll(t);
                if( a % k == 0 ) {
                    vector<int> v(10,0);
                    int n = t.size();
                    for(int j = 0; j < n; ++j)
                        ++v[t[j]-'0'];
                    if( st.insert(v).second ) {
                        // cout << t << endl;
                        ans += calc(v,n);
                    }
                }
            }
            return;

        } else {
            for(int i = s; i < 10; ++i) {
                t[l] = '0'+i;
                t[r] = '0'+i;
                rec(l+1,r-1,t,k);
            }
        }
    }

public:
    long long countGoodIntegers(int n, int k) {
        if( !init ) {
            init = true;
            factorial[0]  = 1LL;
            factorial[1]  = 1LL;
            factorial[2]  = 2LL;
            factorial[3]  = 6LL;
            factorial[4]  = 24LL;
            factorial[5]  = 120LL;
            factorial[6]  = 720LL;
            factorial[7]  = 5040LL;
            factorial[8]  = 40320LL;
            factorial[9]  = 362880LL;
            factorial[10] = 3628800LL;
        }

        // edge case n = 1


        ans = 0LL;
        string t(n,'#');
        rec(0,n-1,t,k);

        return ans;
    }
};

