
// 3505. Minimum Operations to Make Elements Within K Subarrays Equal
// https://leetcode.com/problems/minimum-operations-to-make-elements-within-k-subarrays-equal/

// see 3422. Minimum Operations to Make Subarray Elements Equal
// https://leetcode.com/problems/minimum-operations-to-make-subarray-elements-equal/
// see 480. Sliding Window Median
// https://leetcode.com/problems/sliding-window-median/

class Solution {
private:
    double m;

    // max heap, stores the smaller half elements, left side
    multiset<int> l; // look at last element for max
    long long l_sum; // sum of all elements in l

    // min heap, stores the greater half elements, right side
    multiset<int> r; // look at first element for min
    long long r_sum; // sum of all elements in r

    double addNum(int num) {
        if( l.size() > r.size() ) {
            // case 1: left side heap has more elements
            if( num < m ) {
                r_sum += (long long)*prev(l.end());
                r.insert(*prev(l.end()));
                l_sum -= (long long)*prev(l.end());
                l.erase(prev(l.end()));
                l_sum += (long long)num;
                l.insert(num);
            } else {
                r_sum += (long long)num;
                r.insert(num);
            }
            // now even
            m = ((double)*prev(l.end()) + *r.begin())/2.0;
        } else if( l.size() == r.size() ) {
            // case 2: left and right heaps are balanced
            if( num < m ) {
                l_sum += (long long)num;
                l.insert(num);
                m = *prev(l.end());
            } else {
                r_sum += (long long)num;
                r.insert(num);
                m = *r.begin();
            }
        } else {
            // case 3: right side heap has more elements
            if( num > m ) {
                l_sum += (long long)*r.begin();
                l.insert(*r.begin());
                r_sum -= (long long)*r.begin();
                r.erase(r.begin());
                r_sum += (long long)num;
                r.insert(num);
            } else {
                l_sum += (long long)num;
                l.insert(num);
            }
            // now even
            m = ((double)*prev(l.end()) + *r.begin())/2.0;
        }
        return m;
    }


    void removeNum(int num) {

        if( !l.empty() && num <= *prev(l.end()) ) {
            // num is in left half
            auto f = l.find(num);
            l_sum -= (long long)num;
            l.erase(f);
        } else if( !r.empty() && num >= *r.begin() ) {
            // num is in right half
            auto f = r.find(num);
            r_sum -= (long long)num;
            r.erase(f);
        }

        // balance
        if( l.size()+2 == r.size() ) {
            l_sum += (long long)*r.begin();
            l.insert(*r.begin());
            r_sum -= (long long)*r.begin();
            r.erase(r.begin());
            // now even
            m = ((double)*prev(l.end()) + *r.begin())/2.0;
        } else if( r.size()+2 == l.size() ) {
            r_sum += (long long)*prev(l.end());
            r.insert(*prev(l.end()));
            l_sum -= (long long)*prev(l.end());
            l.erase(prev(l.end()));
            // now even
            m = ((double)*prev(l.end()) + *r.begin())/2.0;
        } else if( l.size() > r.size() ) {
            m = *prev(l.end());
        } else if( r.size() > l.size() ) {
            m = *r.begin();
        } else {
           m = l.empty() ? DBL_MAX : ((double)*prev(l.end()) + *r.begin())/2.0;
        }

    }

    
    long long mem[100000][16];

    long long rec(vector<long long>& operations, int n, int pos, int x, int k) {
        // cout << "rec pos " << pos << " k " << k << endl;
        if( k == 0 )
            return 0LL;

        if( mem[pos][k] != -1LL )
            return mem[pos][k];

        long long ret = LLONG_MAX;

        // we have a choice
        //      skip the current position OR
        //      take the subarray at the current position

        // we are at pos in nums and have to form k subarrays of length x
        // what is our max pos for starting the current subarray?
        int pos_max = n - (k * x);

        // skip
        long long a = LLONG_MAX;
        if( pos < pos_max )
            a = rec(operations, n, pos+1, x, k);

        // take
        long long b = operations[pos] + rec(operations, n, pos+x, x, k-1);

        return mem[pos][k] = min(a,b);
    }

public:
    long long minOperations(vector<int>& nums, int x, int k) {
        int n = nums.size(); // 2 <= nums.length <= 1e5
        // cout << "n " << n << endl;
        
        // edge case k * x = n

        // for every starting point of a subarray length x (sliding window)
        // precalculate number of operations to make elements in subarray equal

        vector<long long> operations(n-x+1);


        m = DBL_MAX;
        l_sum = 0LL;
        r_sum = 0LL;
        int w;                          // size of sliding window
        int i = 0;                      // left index
        for(int j = 0; j < n; ++j) {    // right index
            m = addNum(nums[j]);

            w = j-i+1;
            if( w < x )
                continue;

            // "meet" at the median
            // cout << "median " << m << endl;
            // cout << "l_size " << l.size() << " l_sum " << l_sum << endl;
            // cout << "r_size " << r.size() << " r_sum " << r_sum << endl;

            long long mc = ceil(m);
            long long a = (l.size() * mc) - l_sum;
            long long b = r_sum - (r.size() * mc);
            long long ops = a+b;

            long long mf = floor(m);
            if( mf != mc ) {
                a = (l.size() * mf) - l_sum;
                b = r_sum - (r.size() * mf);
                ops = min(ops, a+b);
            }

            operations[i] = ops;

            removeNum(nums[i]);

            ++i;
        }

        memset(mem,-1,sizeof mem);
        return rec(operations, n, 0, x, k);
    }
};

