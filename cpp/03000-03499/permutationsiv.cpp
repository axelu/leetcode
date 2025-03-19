
// 3470. Permutations IV
// https://leetcode.com/problems/permutations-iv/






class Solution {
private:
    unsigned long long k;
    bool can_reach_k;

    unsigned long long start_odd(int n, int i, int even, int odd) {
        if( i == n )
            return 1LL;

        if( i % 2 == 0 ) { // need to place an odd
            unsigned long long ret = (unsigned long long)odd * start_odd(n, i+1, even, odd-1);
            if( ret >= k )
                can_reach_k = true;
            return ret;
        } else { // need to place an even
            unsigned long long ret = (unsigned long long)even * start_odd(n, i+1, even-1, odd);
            if( ret >= k )
                can_reach_k = true;
            return ret;        }
    }

    unsigned long long start_even(int n, int i, int even, int odd) {
        if( i == n )
            return 1LL;

        if( i % 2 == 0 ) // need to place an even
            return (unsigned long long)even * start_even(n, i+1, even-1, odd);

        else // need to place an odd
            return (unsigned long long)odd * start_even(n, i+1, even, odd-1);
    }

    unsigned long long choices[101];
    unsigned long long pchoices[101];

    vector<int> finalize(int n, long long k, int i) {
        // populate odds and evens
        vector<int> odds;
        for(int o = 1; o <= n; o += 2)
            odds.push_back(o);
        vector<int> evens;
        for(int e = 2; e <= n; e += 2)
            evens.push_back(e);

        vector<int> ans(n);
        int j = 0;
        // populate the fixed ones from left to right
        for(; j < i; ++j) {
            if( j % 2 == 0 ) {
                ans[j] = *odds.begin(); // cout << ans[j] << " ";
                odds.erase(odds.begin());
            } else {
                ans[j] = *evens.begin(); // cout << ans[j] << " ";
                evens.erase(evens.begin());
            }
        }
        // populate the remaining ones from left to right
        for(; j < n; ++j) {
            // if j even, we are placing odds
            // if j odd, we are placing evens
            vector<int>::iterator it;
            if( j % 2 == 0 )
                it = odds.begin();
            else
                it = evens.begin();

            // if we are at n-2 or n-1, there will only be one choice left
            if( j == n-2 || j == n-1) {
                ans[j] = *it; // cout << ans[j] << " ";
                continue;
            }

            // at pos j we have choice[j] choices
            unsigned long long f = pchoices[j+1];
            // TODO we could find t by dividing or even binary search
            // more efficiently, but 100 are small hence just iterating
            unsigned long long t = 1;
            for(; t <= choices[j]; ++t) {
                if( t * f < k ) {
                    ++it;
                    continue;
                }
                ans[j] = *it; // cout << ans[j] << " ";
                if( j % 2 == 0 )
                    odds.erase(it);
                else
                    evens.erase(it);
                break;
            }
            k = k % f;
            if( k == 0 )
                k = f;
        }
        // cout << endl;

        return ans;
    }

    vector<int> odd_n(int n, long long k) {
        // lets say n = 7
        // pos     0 1 2 3 4 5 6
        // choices 4 3 3 2 2 1 1
        // if we go from right to left and multiply choices
        // the 1st index where the product >= k means,
        // that all indices before can be fixed, meaning just count up
        // and if we exit w/o hitting product >= k, it means no solution

        // populate choices and product of choices
        int choice = 1;
        int trigger = 0;
        for(int i = n-1; i >= 0; --i) {
            choices[i] = choice;
            ++trigger;
            if( trigger == 2 ) {
                ++choice;
                trigger = 0;
            }
        }
        // for(int i = 0; i < n; ++i)
        //     cout << i << ":" << choices[i] << " ";
        // cout << endl;
        pchoices[n-1] = 1ULL;
        int i = n-2;
        for(; i >= 0; --i) {
            pchoices[i] = choices[i] * pchoices[i+1];
            if( pchoices[i] >= k )
                break;
        }
        // cout << "i " << i << endl;
        // for(int m = i; m < n; ++m)
        //     cout << m << ":" << pchoices[m] << " ";
        // cout << endl;

        if( i == -1 )
            return {};

        return finalize(n, k, i);
    }

    vector<int> even_n(int n, long long k) {
        // populate choices and product of choices
        choices[0] = n;
        choices[1] = n/2;
        int trigger = 0;
        for(int i = 2; i < n; ++i) {
            choices[i] = trigger == 0 ? choices[i-1] - 1 : choices[i-1];
            ++trigger;
            if( trigger == 2 )
                trigger = 0;
        }
        //for(int i = 0; i < n; ++i)
        //    cout << i << ":" << choices[i] << " ";
        //cout << endl;
        pchoices[n-1] = 1ULL;
        int i = n-2;
        for(; i >= 0; --i) {
            pchoices[i] = choices[i] * pchoices[i+1];
            if( pchoices[i] >= k )
                break;
        }
        //cout << "i " << i << endl;
        //for(int m = i; m < n; ++m)
        //    cout << m << ":" << pchoices[m] << " ";
        // cout << endl;

        if( i == -1 )
            return {};

        // if i > 0 this becomes the exact same as in the odd_n solution
        if( i > 0 )
            return finalize(n, k, i);

        // we need to determine which integer we start from: even or odd
        // if odd, then again same solution
        // at pos 0 we have choice[0] choices
        unsigned long long f = pchoices[1];
        // TODO we could find t by dividing or even binary search
        // more efficiently, but 100 are small hence just iterating
        unsigned long long t = 1;
        for(; t <= choices[0]; ++t) {
            if( t * f < k )
                continue;
            break;
        }
        // cout << "ans[0] " << t << endl;

        vector<int> ans(n);
        ans[0] = t;

        // populate odds and evens
        vector<int> odds;
        for(int o = 1; o <= n; o += 2)
            odds.push_back(o);
        vector<int> evens;
        for(int e = 2; e <= n; e += 2)
            evens.push_back(e);

        int parity;
        if( t % 2 ) { // ans[0] odd, ans[1] even, ..., ans[n-1] even
            int d = (t/2);
            auto it = odds.begin();
            advance(it, d); // cout << "erasing " << *it << endl;
            odds.erase(it);
            parity = 1;
        } else {      // ans[0] even, ans[1] odd, ... , ans[n-1] odd
            int d = (t/2) - 1;
            auto it = evens.begin();
            advance(it, d); // cout << "erasing " << *it << endl;
            evens.erase(it);
            parity = 0;
        }


        k = k % f;
        if( k == 0 )
            k = f;


        int j = 1;
        for(; j < n; ++j) {
            parity = !parity;
            // parity = 1 -> we are placing an odd at j
            // parity = 0 -> we are placing an even at j
            vector<int>::iterator it;
            if( parity == 1 )
                it = odds.begin();
            else
                it = evens.begin();

            // if we are at n-2 or n-1, there will only be one choice left
            if( j == n-2 || j == n-1) {
                ans[j] = *it; // cout << ans[j] << " ";
                continue;
            }

            // at pos j we have choice[j] choices
            unsigned long long f = pchoices[j+1];
            // TODO we could find t by dividing or even binary search
            // more efficiently, but 100 are small hence just iterating
            unsigned long long t = 1;
            for(; t <= choices[j]; ++t) {
                if( t * f < k ) {
                    ++it;
                    continue;
                }
                ans[j] = *it; // cout << ans[j] << " ";
                if( parity == 1 )
                    odds.erase(it);
                else
                    evens.erase(it);
                break;
            }
            k = k % f;
            if( k == 0 )
                k = f;
        }
        // cout << endl;

        return ans;
    }

public:
    vector<int> permute(int n, long long k) {
        // 1 <= n <= 100 -> 9.33262154439e+157 permutations aka n!
        // 1 <= k <= 1e15
        // so brute force is not an option

        if( n == 1 )
            return k == 1 ? vector<int>{1} : vector<int>{};
        if( n == 2 ) {
            if( k == 1 )
                return vector<int>{1,2};
            else if( k == 2 )
                return vector<int>{2,1};
            else
                return vector<int>{};
        }

        //                   0  1  2      n-1
        // lets say we start 1, 2, 3, ... n
        // how many times choices do we have at position 1?
        // we can only use even numbers, and so on

       // if n is odd, we cannot start with an even number at pos 0 !!!
       if( n % 2 )
            return odd_n(n, k);

        return even_n(n, k);

        /*
        int even_cnt = n / 2;
        int odd_cnt  = n % 2 ? even_cnt + 1 : even_cnt;


        // start with an odd number, how many permutations can we make?
        // start with an even number, how many permutations can we make?
        this->k = k;
        can_reach_k = false;
        unsigned long long a =  start_odd(n, 0, even_cnt, odd_cnt); cout << "start_odd " << a << endl;
        if( can_reach_k ) {
                cout << "can reach k start with an odd" << endl;
        }

        // will be 0 if n is odd !!!
        unsigned long long b = start_even(n, 0, even_cnt, odd_cnt); cout << "start_even " << b << endl;
        if( !can_reach_k && a + b < k )
        // if( a + b < k )
            return {};
        // edge case if a + b == k, then answer is {n, n-1, n-2, ... , 1};


        // rec(0, odd_cnt, even_cnt, 1);


        return {99};
        */
    }
};
