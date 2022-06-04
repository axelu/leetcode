
// 1655. Distribute Repeating Integers
// https://leetcode.com/problems/distribute-repeating-integers/



class Solution {
private:
    void printBinary(long x, int c) {
        /*
        for(int i = c-1; i >= 0; --i) {
            if( x & (1UL << i) ) cout << 1;
            else cout << 0;
        }
        */
        for(int i = 0; i < c; ++i) {
            if( x & (1UL << i) ) cout << 1;
            else cout << 0;
        }
        cout << endl;
    }

    int mem[51][1024];

    bool rec(vector<int>& frequencies, int i, vector<int>& quantity, int mask) {
        // mask indicates the customers that we already have integers assigned to
        // bit is unset -> customer has an integer assigned

        /*
        cout << "rec i " << i << " mask ";printBinary(mask,quantity.size());
        cout << "    frequencies ";
        for(int j : frequencies)
            cout << j << " ";
        cout << endl;
        */

        if( mask == 0 )
            return true;

        if( i == frequencies.size() )
            return false;

        if( mem[i][mask] != -1 )
           return mem[i][mask];

        // we have a choice how to assign the current integer
        // amongst the customers who don't have an integer assigned yet

        // don't use the current integer at all
        bool f = rec(frequencies,i+1,quantity,mask);
        if( !f ) {
            // we need to distribute the current integer to all
            // possible permutations of customers that have not been satisfied yet
            vector<int> v; // customers not yet satisfied -> set bits in mask
            for(int k = 0; k < quantity.size(); ++k)
                if( (mask >> k) & 1 )
                    v.push_back(k);
            for(int x = 1; x < (1 << v.size()); ++x) {
                int local_mask = mask;
                int frequency  = frequencies[i];
                for(int k = 0; k < v.size(); ++k) {
                    if( ((x >> k) & 1) && frequency >= quantity[v[k]] ) {
                        frequency -= quantity[v[k]];
                        local_mask &= ~(1 << v[k]);
                        if( frequency == 0 )
                            break;
                    }
                }
                f = rec(frequencies,i+1,quantity,local_mask);
                if( f )
                    break;
            }
        }

        return mem[i][mask] = f;
    }

public:
    bool canDistribute(vector<int>& nums, vector<int>& quantity) {
        int mx_order = 0;
        int mn_order = 100001;
        int integers_ordered_total = 0;
        for(int i : quantity ) {
            integers_ordered_total += i;
            mx_order = max(mx_order,i);
            mn_order = min(mn_order,i);
        }

        // if the number of integers ordered > nums.size(),
        //     then we cannot fullfill the order
        if( integers_ordered_total > nums.size() )
            return false;

        bool has_count_greaterequal_mx_order = false;
        unordered_map<int,int> um;
        for(int key : nums) {
            auto p = um.insert({key,1});
            if( !p.second )
                ++p.first->second;
            if( p.first->second >= mx_order )
                has_count_greaterequal_mx_order = true;
        }
        // if there is an order that is greater than the greatest count
        // of any integer we have, then we cannot fullfill the order
        if( !has_count_greaterequal_mx_order )
            return false;

        int integers_cnt = 0;
        vector<int> frequencies;
        for(auto p : um) {
            // only consider frequencies >= the smallest order
            if( p.second >= mn_order ) {
                integers_cnt += p.second;
                frequencies.push_back(p.second);
            }
        }
        if( integers_cnt < integers_ordered_total )
            return false;
        /*
        // debug
        for(int i : frequencies)
            cout << i << " ";
        cout << endl;
        */

        memset(mem,-1,sizeof mem);
        int mask = (1 << quantity.size()) - 1;
        return rec(frequencies,0,quantity,mask);
    }
};
