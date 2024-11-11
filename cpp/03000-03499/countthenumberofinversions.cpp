
// 3193. Count the Number of Inversions
// https://leetcode.com/problems/count-the-number-of-inversions/


// https://leetcode.com/problems/count-the-number-of-inversions/discuss/5354671/Learn-to-Think-or-Detailed-Thought-Process-or-How-to-Approach-or-Permutations-and-DP
/*
 *
 * inversions added = l - pos
 *
 *            permutation  add-1-at-idx-0  add-1-at-idx-1
 *            0            1,0             0,1
 * inversions 0            0+(1-0)         0+(1-1)
 *
 *            permutation  add-2-at-idx-0  add-2-at-idx-1  add-2-at-idx-2
 *            0,1          2,0,1           0,2,1           0,1,2
 * inversions 0            0+(2-0)         0+(2-1)         0+(2-2)
 *            1,0          2,1,0           1,2,0           1,0,2
 * inversions 1            1+(2-0)         1+(2-1)         1+(2-2)
 * 
 * ...
 */

class Solution {
private:
    const long mod = 1000000007;
public:
    int numberOfPermutations(int n, vector<vector<int>>& requirements) {
        
        // requirements[i] = [endi, cnti]
        // sort requirements by end 
        sort(requirements.begin(),requirements.end());
        // if we have a requirement that ends at index 0
        // which can only have 0 zero inversions as it is only one element
        // then it has to have an inversion count of 0
        int idx = 0; // index into requirements
        if( requirements[0][0] == 0 ) {
            if( requirements[0][1] == 0 ) {
                idx = 1;
            } else {
                return 0;
            }
        }
        
       int req_sz = requirements.size();
       int limit  = requirements[idx][1];

        // state[i][j] key: inversion_count, value: permutation_count
        map<int,int> state;
        
        // Initialize state with slice of one element 
        // [0] has only one permutation, 0 inversions        
        state[0] = 1;
        
       for(int i = 2; i <= n+1; ++i) {
            // i is our new length
            // i-1 is our current length
           
            // add one number to all existing permutations
            // current length = l-1; add one element to make length l 
            // positions to add new element: l
            // since every num in all perms is smaller than x (x is the num we are adding), 
            //     inversions created by x is determined by pos of 'x':[0,l-1] 
           
           map<int,int> state_new;
           for(auto p : state) {
               int inversion_count   = p.first;
               int permutation_count = p.second;
               
                // if inversion_count > limit of next req,
                // then all these permutations will be thrown out at next requirement
               if( inversion_count > limit )
                   continue;
               
               // add new element 
               for(int j = 0; j < i; ++j) {
                   state_new[inversion_count + j] = (state_new[inversion_count + j] + state[inversion_count]) % mod;
               }
           }
           
           state.clear();
           if( idx < req_sz && (i-1) == requirements[idx][0] ) {
               // a requirement has been placed on inversion counts at this index
               if( state_new.find(requirements[idx][1]) == state_new.end() ) {
                   // no permutation satisfies this requirement
                   return 0;
               }
               
               state[requirements[idx][1]] = state_new[requirements[idx][1]];
               ++idx;
               if( idx < req_sz ) {
                   limit = requirements[idx][1];
               } else {
                   limit = 400;
               }
           } else {
               state = state_new;
           }
       } 

       return state[requirements[req_sz-1][1]] % mod;
    }
};





// playground
// this has to do with Mahonian numbers


/* resources
 * https://mathworld.wolfram.com/PermutationInversion.html
 * https://www.baeldung.com/cs/counting-inversions-array
 * most helpful https://stackoverflow.com/questions/19372991/number-of-n-element-permutations-with-exactly-k-inversions
 * https://nima101.github.io/mahonian
 *
 * given n integers 0 ... n-1
 * lets figure out how many permutations with exactly cnt inversions
 * min inversion cnt 0, which is when the integers are sorted asc
 * max inversion cnt n * (n-1)/2, which is when the integers are sorted desc
 * so each permutation has a given number of inversions between [0,maxinversion] inclusive
 * how many permutations do we have per inversion count
 * we know we have 1 permutation with 0 inversions
 * we know we have 1 permutation with max inversions
 * the total must match number of permutations
 *
 * example n = 4 -> 0,1,2,3
 * nbr_permutations 24
 * mx_inversion_cnt 6
 * 0:1 1:3 2:5 3:6 4:5 5:3 6:1
 *
 * example n = 5 -> 0,1,2,3,4
 * nbr_permutations 120
 * mx_inversion_cnt 10
 * 0:1 1:4 2:9 3:15 4:20 5:22 6:20 7:15 8:9 9:4 10:1
 *
 * example n = 6 -> 0,1,2,3,4,5
 * nbr_permutations 720
 * mx_inversion_cnt 15
 * 0:1 1:5 2:14 3:29 4:49 5:71 6:90 7:101 8:101 9:90 10:71 11:49 12:29 13:14 14:5 15:1


 * now we need to count down as we will have lower length to see out of those meet all requirements
 */

// initialize once
long factorial[301];
bool init = false;

class Solution {
private:
    const long mod = 1000000007;
    int n;

    long count_inversions(vector<int>& nums) {
        long cnt = 0L;
        for(int i = 0; i < n-1; ++i)
            for(int j = i+1; j < n; ++j)
                if( nums[i] > nums[j] )
                    cnt = (cnt + 1) % mod;
        return cnt;
    }

    vector<int> * pNums;

    vector<int> inversions;

    void permute(int n) {
        if( n == 1 ) {
            ++inversions[count_inversions(*pNums)];
            return;
        }

        int t;
        for(int i = 0; i < n; ++i) {
            permute(n-1);

            if( n % 2 == 1 ) {
                // size is odd,: swap first and size-1 element
                t = (*pNums)[0];
                (*pNums)[0] = (*pNums)[n-1];
                (*pNums)[n-1] = t;
            } else {
                // size is even: swap ith and size-1 element
                t = (*pNums)[i];
                (*pNums)[i] = (*pNums)[n-1];
                (*pNums)[n-1] = t;
            }
        }
    }

    static const int n_max = 200;
    // vector<unsigned long long> dp1[n_max+1];
    long ** dp1;
    // int dp[100][100];
    unsigned long long inversions1(int n, int k)
    {
        // cout << "inversions n " << n << " k " << k << endl;

        if (n == 0) return 0;
        if (k == 0) return dp1[n][k] = 1;

        int kmax = n * (n-1)/2;
        if( k > kmax )
            return 0;

        if (dp1[n][k] != -1) return dp1[n][k];


        int j = 0;
        unsigned long long val = 0;
        int kmax_new = (n-1) * (n-1-1)/2;
        // for (j = 0; j < n && min(kmax_new-j,k-j) >= 0; j++)
        for (j = 0; j < n && k-j >= 0; j++)
            val += inversions1(n-1, k-j);
        return dp1[n][k] = val;
    }


    vector<int> mahonian_row(int n) {
        // 1 <= n <= 300
        /*
        '''Generates coefficients in expansion of
        Product_{i=0..n-1} (1+x+...+x^i)
        **Requires that n is a positive integer'''
        # Allocate space for resulting list of coefficients?
        # Initialize them all to zero?
        #max_zero_holder = [0] * int(1 + (n * 0.5) * (n - 1))

        # Current max power of x i.e. x^0, x^0 + x^1, x^0 + x^1 + x^2, etc.
        # i + 1 is current row number we are computing
        */

        int mx_inversion_cnt = n * (n-1)/2;
        long _pre[mx_inversion_cnt+1]; long * pre = _pre;
        long _cur[mx_inversion_cnt+1]; long * cur = _cur;


        int i = 1;
        // Preallocate result
        // Initialize to answer for n = 1
        cur[0] = 1;
        int curl = 1;
        int prel;
        // result = [1]
        while( i < n ) {
            // # Copy previous row of n into prev
            // prev = result[:]
            // swap
            long * t = pre;
            pre = cur;
            cur = t;
            prel = curl;
            curl = (int)(1 + ((i + 1) * 0.5) * (i));


            // # Get space to hold (i+1)st row
            // result = [0] * int(1 + ((i + 1) * 0.5) * (i))
            memset(cur,0,sizeof(unsigned long long)*(mx_inversion_cnt+1));


            // # Initialize multiplier for this row
            // m = [1] * (i + 1)

            int m = i+1;

            // # Multiply
            // for j in range(len(m)):
            for(int j = 0; j < m; ++j) {
                // for k in range(len(prev)):
                for(int k = 0; k < prel; ++k) {
                    //result[k+j] += m[j] * prev[k]
                    cur[k+j] = (cur[k+j] + pre[k]) % mod;
                }
            }
            // # Result now equals mahonian_row(i+1)
            // # Possibly should be memoized?
            i = i + 1;
       }
        cout << cur[2] << endl;
        //for(int i = 0; i <= mx_inversion_cnt; ++i)
        //    cout << cur[i] << " ";
        //cout << endl;

        // return result
        return {};
    }



long long comb2(long long n, long long p) {
    return (p & (n - p)) ? 0 : 1;
}

long long g(long long n) {
    return (3 * n * n - n) / 2;
}

long long calc(long long r, long long c, long long n, long long num) {
    // return (2 + comb2(r + c - n, r) * (num % 2 == 0 ? 1 : -1) ) % 2;
    return (2 + comb2(r + c - n, r) );
}

long long mahonian(long long r, long long c) {
    long long res = calc(r, c, 0, 0);
    for (long long num = 1; ; num++) {
        for (long long mul: {1, -1}) {
            long long nxt = g(num * mul);
            if (nxt >= c + 1) return res;
            // res = (res + calc(r, c, nxt, num)) % 2;
            res = (res + calc(r, c, nxt, num));
        }
    }
}







public:
    int numberOfPermutations(int n, vector<vector<int>>& requirements) {

        long tt2 = mahonian(5-1,5);
        cout << tt2 << endl;
        return 99;


        if( !init ) {
            init = true;
            factorial[0] = 1L;
            for(long i = 1; i <= 300; ++i)
                factorial[i] = (factorial[i-1] * i) % mod;
        }

        this->n = n;

        // brute force
        int nbr_permutations = factorial[n];
        cout << "nbr_permutations " << nbr_permutations << endl;
        int mx_inversion_cnt = n * (n-1)/2;
        cout << "mx_inversion_cnt " << mx_inversion_cnt << endl;


        mahonian_row(200);


        return 99;

/*

        inversions.assign(mx_inversion_cnt + 1, 0);
        vector<int> v(n);
        iota(v.begin(), v.end(), 0);
        pNums = &v;
        permute(n);

        int t = 0;
        for(int i = 0; i <= mx_inversion_cnt; ++i) {
            cout << i << ":" << inversions[i] << " ";
            t += inversions[i];
        }
        cout << endl;
        cout << t << endl; // t matches number of inversions


        long long tt1 = 300 * (300-1)/2; // 44850 -> 44851 * 301 = 13,500,151
        // cout << tt1 << endl;
        // but not every n requires 44851 inversion counts, so we can do something like vector<int> cnt[301]


        dp1 = new unsigned long long *[n_max+1];

        for(int i = 1; i <= n_max; ++i) {
            int inversion_cnt = i * (i-1)/2;
            dp1[i] = new unsigned long long[inversion_cnt+1];
            for(int j = 0; j <= inversion_cnt; ++j)
                dp1[i][j] = -1;
            // dp1[i].assign(inversion_cnt+1,-1);
        }

        int mx_mx_inversion_cnt = n_max * (n_max-1)/2;
        for(int i = mx_mx_inversion_cnt; i >= 0; --i)
            inversions1(n_max,i);

        // Mahonian numbers
        for(int i = 1; i < 10; ++i) {
            cout << "i " << i << " ";
            int inversion_cnt = i * (i-1)/2;
            for(int j = 0; j <= inversion_cnt; ++j)
                cout << dp1[i][j] << " ";
            cout << endl;
        }


*/
        return 99;
    }
};
