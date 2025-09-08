
// 3655. XOR After Range Multiplication Queries II
// https://leetcode.com/problems/xor-after-range-multiplication-queries-ii/





// see 3653. XOR After Range Multiplication Queries I
// https://leetcode.com/problems/xor-after-range-multiplication-queries-i/

// solution based on hints

class Solution {
private:
    long const mod = 1000000007L;

     long long modPow(long long a, long long x) {
        // return a^x mod MOD
        long long res = 1;
        while(x>0) {
            if( x & 1 ) res = (res*a) % mod;
            a = (a*a) % mod;
            x >>= 1;
        }
        return res;
    }

    long long modInverse(long long a) {
        // return modular multiplicative of: a mod MOD
        return modPow(a,mod-2);
    }

    // modular division
    long modDivide(long a, long b) {
        // a = a % mod;
        long inv = modInverse(b);
        return (inv * a) % mod;
    }

public:
    int xorAfterQueries(vector<int>& nums, vector<vector<int>>& queries) {
        int n = nums.size();
        int q_sz = queries.size();

        int B = sqrt(n);

        // query_groups
        // key: {k, l % k}
        // value: vector of pairs of vectors
        //                  first multiplier starting at pos (multiply)
        //                  second multiplier ending at pos (divide)
        map<pair<int,int>, vector<pair<vector<int>,vector<int>>>> query_groups;

        for(int i = 0; i < q_sz; ++i) {
            int l = queries[i][0];
            int r = queries[i][1];
            int k = queries[i][2];
            long v = queries[i][3];

            if( k <= B ) {
                // group queries by (k, l % k)
                // for each group we maintain a diff-array of length ceil(n/k) (we will do ceil(n/k) + 1)
                // to record multiplier updates
                // example
                // let n = 100 -> B = 10
                // let k = 3, 
                // let l = 19, 
                // let r = 29 (r may not fall on an index that is part of the sequence)
                // 0123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789
                //  0  1  2  3  4  5  6  7  8  9  0  1  2  3  4  5  6  7  8  9  0  1  2  3  4  5  6  7  8  9  0  1  2  3  4  5  6  7  8  9  
                //  x  x  x  x  x  x  x  x  x  x  x  x  x  x  x  x  x  x  x  x  x  x  x  x  x  x  x  x  x  x  x  x  x  x  x
                //                    l         r

                int diff_arr_length = ceil(n/(k*1.0)) + 1;
                // what index in our diff_array does l represent?
                int diff_arr_l_idx = l/k;

                // what index in our diff_array does r represent?
                // +1 because we will go the the next idx to record that the factor v is no longer in play
                int dist = r - l;
                int dist_indices = dist/k; // floor
                int diff_arr_r_idx = diff_arr_l_idx + dist_indices + 1;

                pair<int,int> key = make_pair(k, l % k);
                auto f = query_groups.find(key);
                if( f == query_groups.end() ) {
                    vector<pair<vector<int>,vector<int>>> diff_arr(diff_arr_length);
                    diff_arr[diff_arr_l_idx].first.push_back(v);
                    diff_arr[diff_arr_r_idx].second.push_back(v);

                    query_groups[key] = diff_arr;

                } else {
                    f->second[diff_arr_l_idx].first.push_back(v);
                    f->second[diff_arr_r_idx].second.push_back(v);
                }

            } else {

                int idx = l;
                while( idx <= r ) {
                    nums[idx] = ((long)nums[idx] * v) % mod;
                    idx += k;
                }
            }
        }

        // sweep query_groups
        for(auto& qg: query_groups) {
            pair<int,int> key = qg.first;
            int k = key.first;
            int l = key.second;

            int idx = l;
            long f = 1L;
            
            // vector<pair<vector<int>,vector<int>>> diff_arr = qg.second;
            for(int i = 0; i < qg.second.size(); ++i) {
                // cout << "idx " << idx << endl;

                for(long v: qg.second[i].first) {
                    f = (f * v) % mod;
                }
                for(long v: qg.second[i].second) {
                    f = modDivide(f, v);
                }

                nums[idx] = ((long)nums[idx] * f) % mod;

                idx += k;
                if( idx >= n )
                    break;
            }
        }

        int _xor = nums[0]; // cout << "final nums[0] " << nums[0] << endl;
        for(int i = 1; i < n; ++i) {
            // cout << "final nums[" << i << "] " << nums[i] << endl;
            _xor = _xor ^ nums[i];
        }

        return _xor;
    }
};
