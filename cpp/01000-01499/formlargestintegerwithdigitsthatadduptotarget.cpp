
// 1449. Form Largest Integer With Digits That Add up to Target
// https://leetcode.com/problems/form-largest-integer-with-digits-that-add-up-to-target/





class Solution {
private:
    bool cmp(int a[], int b[]) {
        /*
        int cnt_a = 0;
        for(int i = 1; i <= 9; ++i)
            cnt_a += a[i];
        int cnt_b = 0;
        for(int i = 1; i <= 9; ++i)
            cnt_b += b[i];

        if( cnt_a > cnt_b ) {
            return true;
        } else if( cnt_a == cnt_b ) { */
            for(int i = 9; i >= 1; --i) {
                if( a[i] > b[i] ) {
                    return true;
                } else if( a[i] < b[i] ) {
                    break;
                }
            }
        //}
        return false;
    }
public:
    string largestNumber(vector<int>& cost, int target) {
        // quick check
        // if there is no digit with cost <= target,
        // then we cannot paint any integer at all
        // also, if two digits have the same cost,
        // we will only keep the higher digit

        bool f = false;
        int mn_cost = 5001;
        unordered_map<int,int> um; // cost,digit
        for(int i = 0; i < 9; ++i) {
            um[cost[i]] = i+1;
            if( cost[i] <= target )
                f = true;
            mn_cost = min(mn_cost,cost[i]);
        }
        // cout << "mn_cost " << mn_cost << endl;
        if( !f )
            return "0";

        int dp[5001][10];memset(dp,0,sizeof dp); // total cost,count of given digit
        for(auto& p : um) {
            dp[p.first][p.second] = 1;
            dp[p.first][0] = 1;
        }

        /*
        for(int i = 1; i <= target; ++i) {
            for(int j = 1; j <= 9; ++j)
                cout << dp[i][j] << " ";
            cout << endl;
        }
        */
                // init
        for(int cost = mn_cost+1; cost <= target; ++cost) {
            // for(int k = 1; k <= 9; ++k)
            //     pre_arr[k] = 0;

            // cout << "curr cost " << cost << endl;
            // our current cost can be composed out of:
            // example let cost be 11: 10+1,9+2,8+3,7+4,6+5
            for(int i = 1; i <= cost/2; ++i) {

                if( dp[cost-i][0] > 0 && dp[i][0] > 0 && dp[cost-i][0] + dp[i][0] >= dp[cost][0] ) {
                    // cout << "    collecting " << cost-i << "+" << i << endl;

                    // collect all digits
                    int cur_arr[10];
                    for(int j = 1; j <= 9; ++j)
                        cur_arr[j] = dp[cost-i][j] + dp[i][j];

                    if( dp[cost-i][0] + dp[i][0] > dp[cost][0] || cmp(cur_arr,dp[cost]) ) {
                       for(int j = 1; j <= 9; ++j)
                            dp[cost][j] = cur_arr[j];
                        dp[cost][0] = dp[cost-i][0] + dp[i][0];
                    }
                }

            }
        }

        string s = "";
        for(int i = 9; i >= 1; --i)
            for(int j = 1; j <= dp[target][i]; ++j)
                s += i+'0';

        return s.empty() ? "0" : s;
    }
};
