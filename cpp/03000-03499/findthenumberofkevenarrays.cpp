
// 3339. Find the Number of K-Even Arrays
// https://leetcode.com/problems/find-the-number-of-k-even-arrays/





/*
// initialize once
bool init = false;
vector<int> v_i[1001]; // include
vector<int> v_d[1001]; // don't include
*/

class Solution {
private:
    const long mod = 1000000007;

    long odds;
    long evens;

    long mem[750][2][750];

    long rec(int n, int pos, int val, int k) {
        if( pos == n - 1 ) {
            return k == 0;
        }

        if( mem[pos][val][k] != -1 )
            return mem[pos][val][k];

        // val 0 even
        // val 1 odd

        //     if we are at odd  and want to include the current index       -> there is no where to go
        //     if we are at odd  and don't want to include the current index -> we go to 1,2,3,4,...m next
        //     if we are at even and want to include the current index       -> go to even 2,4,6,...<=m
        //     if we are at even and don't want to include the current index -> go to odd 1,3,5,...<=m next

        long ret = 0L;

        if( val == 1 ) {
            ret = (ret + (odds  * rec(n, pos+1, 1, k))) % mod;
            ret = (ret + (evens * rec(n, pos+1, 0, k))) % mod;

        } else {
            if( k > 0 )
                ret = (ret + (evens * rec(n, pos+1, 0, k-1))) % mod;

            ret = (ret + (odds * rec(n, pos+1, 1, k))) % mod;
        }

        return mem[pos][val][k] = ret;
    }


public:
    int countOfArrays(int n, int m, int k) {

        /*
        if( !init ) {
            init = true;
            for(int i = 1; i <= 1000; ++i) {        // let i be arr[i]
                for(int j = 1; j <= 1000; ++j) {    // let j be arr[i+1]
                    int t = (i*j) - i - j;
                    if( t % 2 == 0 )
                        v_i[i].push_back(j);
                    else
                        v_d[i].push_back(j);
                }
            }
        }
        */
        /*
        for(int i = 1; i <= 1000; ++i) {        // let i be arr[i]
            cout << i << " include ";
            if( v_i[i].empty() )
                cout << "empty";
            //for(int j = 0; j < v_i[i].size(); ++j) {    // let j be arr[i+1]
            //    cout << v_i[i][j] << " ";
            //
            // }
            cout << endl;
            // cout << i << " exclude ";
            for(int j = 0; j < v_d[i].size(); ++j) {    // let j be arr[i+1]
                // cout << v_d[i][j] << " ";
            }
            // cout << endl;
        }
        */

        // observation from above commented out code
        //     1 include ->
        //     1 exclude -> 1,2,3,4,...m
        //     2 include -> 2,4,6,8,...<=m
        //     2 exclude -> 1,3,5,7,...<=m
        //     3 include ->
        //     3 exclude -> 1,2,3,4,...m
        //     ...
        // to generalize
        //     if we are at odd  and want to include the current index       -> there is no where to go
        //     if we are at odd  and don't want to include the current index -> we go to 1,2,3,4,...m next
        //     if we are at even and want to include the current index       -> go to even 2,4,6,...<=m
        //     if we are at even and don't want to include the current index -> go to odd 1,3,5,...<=m next


        if( m % 2 ) {
            evens = m / 2;
            odds  = evens + 1;
        } else {
            evens = m / 2;
            odds  = evens;
        }

        memset(mem,-1,sizeof mem);

        long ans = 0L;

        ans = (ans + (evens * rec(n, 0, 0, k))) % mod;
        ans = (ans + (odds  * rec(n, 0, 1, k))) % mod;

        return ans;
    }
};
