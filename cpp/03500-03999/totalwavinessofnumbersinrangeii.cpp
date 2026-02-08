
// 3753. Total Waviness of Numbers in Range II
// https://leetcode.com/problems/total-waviness-of-numbers-in-range-ii/






// see 3751. Total Waviness of Numbers in Range I
// https://leetcode.com/problems/total-waviness-of-numbers-in-range-i/
// same solution, except changed to long long and added caching


class Solution {
private:
    // debug
    void print_result(array<long long,4> a) {
        long long lt = a[0];
        long long gt = a[1];
        long long total = a[2];
        long long pv = a[3];
        cout << " lt " << lt << " gt " << gt << " total " << total;
        cout << " peaks+valeys " << pv << endl;
        return;
    }

    vector<int> ll2vector(long long num) {
        vector<int> ret;
        while( num > 0LL ) {
            ret.push_back(num % 10LL);
            num /= 10LL;
        }
        // reverse(begin(ret),end(ret));
        return ret;
    }

    vector<int> vnum1, vnum2;

    long long get_waviness() {
        // assumes vnum1 populated
        long long ret = 0;
        for(int i = vnum1.size()-2; i >= 1; --i) {
            int l = vnum1[i-1];
            int x = vnum1[i];
            int r = vnum1[i+1];
            if( (l < x && x > r) ||
                (l > x && x < r) )
                ++ret;
        }
        return ret;
    }

    // pos 16 pre 10 be 2 te 2 => 640
    array<long long,4> mem[16][10][2][2];

    array<long long,4> rec(int pos, int pre, bool be, bool te) {
        // cout << "rev pos " << pos << " pre " << pre << " be " << be << " te " << te << endl;
        // ret: 0: times pos can be smaller than pre,
        //         so that caller can count how many times it can be peak
        //      1: times pos can be greater than pre,
        //         so that caller can count how many times it can be value
        //      2: time pos can take on any value
        //      3: given pre, number of times pos is valey and peak cummulative

        // be true if moving on bottom edge
        // te true if moving on top edge

        long long lt = 0, gt = 0;
        long long total = 0, peaks = 0, valeys = 0;
        long long pvs = 0;

        int mn = be ? vnum1[pos] : 0;
        int mx = te ? vnum2[pos] : 9;

        if( mem[pos][pre][be][te][0] != -1 )
            return mem[pos][pre][be][te];

        if( pos == 0 ) {
            if( !be && !te ) {
                lt = pre;
                gt = 9-pre;
            } else if( be && !te ) {
                lt = max(0, pre-mn);
                gt = mn > pre ? mx-mn+1 : mx-pre;
            } else if( !be && te ) {
                lt = min(pre, mx+1);
                gt = max(0, mx-pre);
            } else { // be && te
                // lt
                if( mx < pre )
                    lt = mx-mn+1;
                else if( mx == pre )
                    lt = pre-mn;
                else // mx > pre
                    lt = max(0, pre-mn);
                // gt
                if( mx > pre )
                    gt = mn > pre ? mx-mn+1 : mx-pre;
            }
            total = mx - mn + 1; // can be any 0..9 => 10 posibilities
            // last digit of a number cannot be peak or valey
            // cout << "rev pos " << pos << " pre " << pre << " be " << be << " te " << te;
            // print_result({lt, gt, total, 0});
            return mem[pos][pre][be][te] = {lt, gt, total, 0};
        }


        for(int i = mn; i <= mx; ++i) {
            bool be_new = be && i == mn;
            bool te_new = te && i == mx;
            auto t = rec(pos-1, i, be_new, te_new);
            if( i < pre ) {
                // accumulating t[1] gives us count pos is a valey
                valeys += t[1];
                lt += t[2];
                total += t[2];
                pvs += t[3];

            } else if( i == pre ) {
                total += t[2];
                pvs += t[3];

            } else { // i > pre
                // accumulating t[0] gives us count pos is a peak
                peaks += t[0];
                gt += t[2];
                total += t[2];
                pvs += t[3];

            }
        }
        // cout << "rev pos " << pos << " pre " << pre << " be " << be << " te " << te;
        // print_result({lt, gt, total, pvs + peaks + valeys});
        return mem[pos][pre][be][te] = {lt, gt, total, pvs + peaks + valeys};
    }

public:
    long long totalWaviness(long long num1, long long num2) {
        // 1 <= num1 <= num2 <= 1e15

        if( num2 <= 99 )
            return 0;
        if( num1 <= 99 )
            num1 = 100;

        vnum1 = ll2vector(num1);
        if( num1 == num2 )
            return get_waviness();
        vnum2 = ll2vector(num2);

        long long ans = 0;

        for(int i = 0; i < 16; ++i)
            for(int j = 0; j < 10; ++j) {
                mem[i][j][0][0] = {-1,-1,-1,-1};
                mem[i][j][1][0] = {-1,-1,-1,-1};
                mem[i][j][0][1] = {-1,-1,-1,-1};
                mem[i][j][1][1] = {-1,-1,-1,-1};
            }

        int n1 = vnum1.size();
        int n2 = vnum2.size();
        if( n1 == n2 ) {
            int mn = vnum1[n1-1];
            int mx = vnum2[n2-1];
            for(int i = mn; i <= mx; ++i) {
                bool be = i == mn;
                bool te = i == mx;
                auto res = rec(n1-2, i, be, te);
                ans += res[3];
            }

        } else { // n2 > n1
            int mn = vnum1[n1-1];
            int mx = 9;
            for(int i = mn; i <= mx; ++i) {
                bool be = i == mn;
                auto res = rec(n1-2, i, be, false);
                ans += res[3];
            }

            for(int i = n1; i < n2; ++i) {
                mx = i != n2-1 ? 9 : vnum2[n2-1];
                for(int j = 1; j <= mx; ++j) {
                    bool te = i == n2-1 && j == mx;
                    auto res = rec(i-1, j, false, te);
                    ans += res[3];
                }
            }
        }

        return ans;

    }
};
