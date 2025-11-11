
// 3669. Balanced K-Factor Decomposition
// https://leetcode.com/problems/balanced-k-factor-decomposition/



class Solution {
private:
    // prime factorization
    int pf[16]; // 16 is largest number of prime factors for integers 4 to 1e5
    int pf_sz;
    void primeFactors(int n) {
        // fills pf with prime factors and sets pf_sz
        // pf is ordered from smallest to largest

        pf_sz = 0;

        // the number of 2s that divide n
        while(n % 2 == 0) {
            // cout << 2 << " ";
            pf[pf_sz++] = 2;
            n = n/2;
        }

        // n must be odd at this point.
        // skip one element (Note i = i +2)
        for(int i = 3; i <= sqrt(n); i = i + 2) {
            while(n % i == 0LL) {
                // cout << i << " ";
                pf[pf_sz++] = i;
                n = n/i;
            }
        }

        // n is a prime number greater than 2
        if( n > 2 ) {
            // cout << n << " ";
            pf[pf_sz++] = n;
        }

        return;
    }

    int k;
    int bin[5];
    vector<int> ans;
    int diff; // to be minimized

    map<vector<int>,bool> mem;

    // recursive
    bool solve(int pos, int limit) {
        if( pos == pf_sz ) {
            // even though we have a solution, is this
            // solution actually better?
            int mn = INT_MAX;
            int mx = INT_MIN;
            for(int i = 0; i < k; ++i) {
                mn = min(mn, bin[i]);
                mx = max(mx, bin[i]);
            }
            if( diff > mx - mn ) {
                diff = mx - mn;
                for(int i = 0; i < k; ++i)
                    ans[i] = bin[i];
                return true;
            }
            return false;
        }

        vector<int> state(k+1);
        for(int i = 0; i < k; ++i) {
            state[i] = bin[i];
            // cout << bin[i] << " ";
        }
        // cout << endl;
        sort(state.begin(), state.end());
        state[k] = pos;
        auto f = mem.find(state);
        if( f != mem.end() )
            return f->second;


        bool ret = false;

        // we have a choice
        //     put pf[pos] in bucket 0, 1 ... k-1 if we can
        for(int i = 0; i < k; ++i) {
            int f_new = bin[i] * pf[pos];
            if( f_new > limit )
                continue;

            int f_org = bin[i];
            bin[i] = f_new;

            bool res = solve(pos+1, limit);
            if( res )
                ret = true;

            // backtrack
            bin[i] = f_org;

        }

        return mem[state] = ret;
    }

    // binary search
    int search(int s, int e) {
        // cout << "search s " << s << " e " << e << endl;
        if( s > e )
            return -1;

        int mid = s + ((e-s)/2);
        // cout << "  solve " << mid << endl;
        auto f = solve(0, mid);
        if( f ) {
            // can we do better?
            mem.clear();
            int t = search(s, mid-1);
            return t != -1 ? t : mid;
        }
        mem.clear();
        return search(mid+1, e);
    }

public:
    vector<int> minDifference(int n, int k) {
        // what if we create k buckets
        // in each bucket we put factor 1
        // split n into primefactors
        // then we recurse, for each prime factor
        // we have a choice to put in each bucket

        this->k = k;
        for(int i = 0; i < k; ++i)
            bin[i] = 1;

        primeFactors(n);
        /*
        // debug
        cout << "n has " << pf_sz << " prime factors" << endl;
        for(int i = 0; i < pf_sz; ++i)
            cout << pf[i] << " ";
        cout << endl;
        */


        ans.assign(k, 1);

        if( pf_sz <= k ) {
            for(int i = 0; i < pf_sz; ++i)
                ans[i] = pf[i];
            return ans;
        }

        // we will put factor 1 in all but the last bucket
        // then start dividing n by its prime factors and
        // disburse the prime factor round robin to buckets
        // except last bucket.


        //ans = INT_MAX;
        //int _v[5]; v = _v;
        //int _ans_v[5]; ans_v = _ans_v;
        //rec(pf, 0); // cout << "ans " << ans << endl;

        diff = INT_MAX;
        search(pf[pf_sz-1], n);
        return ans;

        // TODO other ideas
        //     instead of pushing down max, we could push up the min
        //     work with divisors instead of with prime factors




        // vector<int> ret(k);
        //for(int i = 0; i < k; ++i)
        //    ret[i] = ans_v[i];

        // return ret;
        // return ans_v;

/*
        priority_queue<int, vector<int>, greater<int>> pq;
        for(int i = 0; i < k; ++i)
            pq.push(1);

        for(int j = 0; j < pf.size(); ++j ) {
            int f = pq.top();
            pq.pop();
            f *= pf[j];
            pq.push(f);
        }
        vector<int> res(k, 1);
        for(int i = 0; i < k; ++i) {
            res[i] = pq.top();
            pq.pop();
        }
        return res;
*/
/*
        vector<int> res(k, 1);
        int i = 0;
        for(int j = 0; j < pf.size(); ++j ) {
            res[i] *= pf[j];

            ++i;
            if( i == k )
                i = 0;
        }
        return res;
*/
/*



        vector<int> res(k, 1);
        res[k-1] = n;
        int i = 0;
        int diff = INT_MAX;
        int mn = INT_MAX;
        int mx = INT_MIN;
        for(int j = 0; j < pf.size()-1; ++j ) {

            // TODO either measure min and max as we go along
            // and if diff is min, store away our answer OR
            // let us try an observation
            // when the bucket we are modifying would get greater
            // than bucket res[k-1], then break before doing that
            // modification

            int res_i_new = res[i] * pf[j];
            int res_kminus1_new = res[k-1] / pf[j];

            if( res_i_new > res_kminus1_new )
                break;

            res[i] = res_i_new;
            res[k-1] = res_kminus1_new;

            ++i;
            if( i == k-1 )
                i = 0;
        }





        return res;
*/
    }
};
