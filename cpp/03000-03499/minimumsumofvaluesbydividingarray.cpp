
// 3117. Minimum Sum of Values by Dividing Array
// https://leetcode.com/problems/minimum-sum-of-values-by-dividing-array/

// initialize once
int Log[10001];
bool init = false;


class Solution {
private:
    int st[10000][26];
    
    int getMin(int L, int R) {
        int j = Log[R - L + 1];
        return min(st[L][j], st[R - (1 << j) + 1][j]);
    }
    
public:
    int minimumValueSum(vector<int>& nums, vector<int>& andValues) {
        if( !init ) {
            init = true;

            // precomputing all logarithms
            Log[1] = 0;
            for(int i = 2; i <= 10000; ++i)
                Log[i] = Log[i/2] + 1;
        }
        
        
        
        int n = nums.size();
        int m = andValues.size(); // 1 <= m <= min(n, 10)
                
        // precompute closest pos where a given bit is not set
        // basically, the pos of the last 0 seen before
        int pre0[10000][18];
        for(int i = 0; i < n; ++i) {
            for(int k = 0; k < 18; ++k) {
                if( !(nums[i] & (1<<k)) )
                    pre0[i][k] = i;
                else
                    pre0[i][k] = i != 0 ? pre0[i-1][k] : -1;
            }
        }
        /*
        for(int k = 0; k < 18; ++k) {
            cout << k << ":" << pre0[1][k] << " ";
        }
        cout << endl;
        */
        
        // precompute the start and end index of subarrays ending at i, 
        // whose AND value is andValues
        // 01234567890123456789
        //    s   e    i
        pair<int,int> se[10][10000];
        for(int j = 0; j < m; ++j) {
            int andValue = andValues[j];
            
            for(int i = 0; i < n; ++i) {
                int s = 0;
                int e = i+1;
                for(int k = 0; k < 18; ++k)
                    if( !(andValue & (1<<k)) )
                        e = min(e, pre0[i][k]);
                    else
                        s = max(s, pre0[i][k] + 1);
                se[j][i] = {s,e};
            }
        }
        // cout << se[0][0].first << " " << se[0][0].second << endl;
        // cout << se[0][1].first << " " << se[0][1].second << endl;
        
        // Let dp[i][j] be the optimal answer to split nums[0..i] into the 0..j andValues.
        // there are no solutions for i < j !!!
        int dp[n][m];
        int a = nums[0];
        for(int i = 0; i < n; ++i) {
            a &= nums[i];
            dp[i][0] = a == andValues[0] ? nums[i] : 1000000001; 
        }
        
        for(int j = 1; j < m; ++j) {
            // cout << "we are partitioning nums into " << j+1 << " partitions" << endl;
            int andValue = andValues[j];
            

            // precompute the Sparse Table structure for range minimum query
            for(int i = 0; i < n; ++i)
                st[i][0] = dp[i][j-1];
            for(int k = 1; k <= 25; ++k)
                for(int i = 0; i + (1 << k) <= n; ++i)
                    st[i][k] = min(st[i][k-1], st[i + (1 << (k - 1))][k - 1]);

            
            
            for(int i = j; i < n; ++i) {
                // cout << "i " << i << endl;
            
                // min(dp[(i - z)][j - 1]) with x <= x <= y 
                // where x and y are the longest and shortest subarrays ending with nums[i - 1] and the bitwise-and of all the values in it is andValues[j - 1]
                
                int s = se[j][i].first; 
                int e = se[j][i].second ;
                // cout << "s " << s << " e " << e << endl;
                // TODO speed this up
                int t = 1000000001;
                if( max({s-1,j-1}) <= e-1 )
                    t = getMin(max({s-1,j-1}), e-1);
                /*
                int t = 1000000001;
                for(int k = max({s-1,j-1}); k <= e-1; ++k) {
                    // cout << "dp[" << k << "][" << j-1 << "] " << dp[k][j-1] << endl;
                    t = min(t, dp[k][j-1]);
                    
                }
                */
            
                
                // dp[i][j] = min(dp[(i - z)][j - 1]) + nums[i - 1]
                dp[i][j] = t + nums[i];
            }
        }
        
        return dp[n-1][m-1] < 1000000001 ? dp[n-1][m-1] : -1;
    }
};



// passes 503/512 test cases, then TLE
// computes the correct result for the 504th test case in about 2.5s, which is obviously too slow

class Solution {
private:
    int mem[10001][11];
    int last[10000];
    int nxt0[10001][18];
    pair<int,int> se[10][10000];

    int rec(vector<int>& nums, int n, vector<int>& andValues, int m, int i, int j) {
        if( j == m-1 )
            // we are at the last element in andValues
            // we must use all nums[i]...nums[n-1]
            return last[i];

        if( mem[i][j] != -1 )
            return mem[i][j];

        int ret = 1000000001;

        // we need to have enough runway in andValues
        int nbr_rem_elements_in_andValues = m - j - 1;
        int mx_i = n - nbr_rem_elements_in_andValues - 1;

        // early exit opportunity
        // if val & andValues[j] != andValues[j]

        //    bit in
        // andValues[j]
        //      1               [look for 1st 0 to our right, pos-1 is our end]
        //      0               look for the 1st 0 to our right, that is our starting pointing, need max
        /*
        int s = i;
        int e = n;
        for(int k = 0; k < 18; ++k)
            if( !(andValues[j] & (1<<k)) )
                s = max(s, nxt0[i][k]);
            else
                e = min(e, nxt0[i][k]);
        */

        int s = se[j][i].first;
        int e = se[j][i].second;

        if( e <= s )
            return mem[i][j] = ret;

        //int a = nums[i];
        //bool f = false; // set to true on first find
        for(int k = s; k <= min(mx_i,e-1); ++k) {
            //a &= nums[k];
            //if( a & andValues[j] != andValues[j] )
            //    break;
            //if( a == andValues[j] ) {
            //    f = true;
                ret = min(ret, nums[k] + rec(nums, n, andValues, m, k+1, j+1));
            //} else if( f ) {
            //    // we found it once, if we loose it, we never get it back (property of AND)
            //    break;
            //}
        }

        return mem[i][j] = ret;
    }


public:
    int minimumValueSum(vector<int>& nums, vector<int>& andValues) {
        int n = nums.size();
        int m = andValues.size(); // 1 <= m <= min(n, 10)

        // precompute the last m
        int i_mn = m-1;
        int c = nums[n-1];
        for(int i = n-1; i >= i_mn; --i) {
            c &= nums[i];
            last[i] = c == andValues[m-1] ? nums[n-1] : 1000000001;
        }

        // precompute next pos where a given bit is not set
        for(int k = 0; k < 18; ++k)
            nxt0[n][k] = n;
        for(int i = n-1; i >= 0; --i) {
            for(int k = 0; k < 18; ++k) {
                if( !(nums[i] & (1<<k)) )
                    nxt0[i][k] = i;
                else
                    nxt0[i][k] = nxt0[i+1][k];
            }
        }

        // TODO precompute  at every position s and e for a given andValue (10000x10x17 checks)
        // pair<int,int> se[m][n];
        for(int j = 0; j < m; ++j) {
            for(int i = 0; i < n; ++i) {
                int s = i;
                int e = n;
                for(int k = 0; k < 18; ++k)
                    if( !(andValues[j] & (1<<k)) )
                        s = max(s, nxt0[i][k]);
                    else
                        e = min(e, nxt0[i][k]);
                se[j][i] = {s,e};
            }
        }


        memset(mem,-1,sizeof mem);

        int ans = rec(nums, n, andValues, m, 0, 0);

        return ans < 1000000001 ? ans : -1;
    }
};
