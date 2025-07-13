
// 3594. Minimum Time to Transport All Individuals
// https://leetcode.com/problems/minimum-time-to-transport-all-individuals/


class Solution {
private:
    // debug
    void printBinary(int x, int c) {
        for(int i = c-1; i >= 0; --i) {
            if( x & (1UL << i) ) cout << 1;
            else cout << 0;
        }
        // cout << endl;
    }

    int countSetBits(int i) {
        unsigned int count = 0;
        while (i) {
            count += i & 1;
            i >>= 1;
        }
        return count;
    }

public:
    double minTime(int n, int k, int m, vector<int>& time, vector<double>& mul) {
        // n = time.size(); // 1 <= n <= 12,   1 <= time[i] <= 100
        // m = mul.size();  // 1 <= m <= 5,  0.5 <= mul[i]  <= 2.0

        if( n == 1 ) {
            return time[0] * mul[0];
        }

        if( k == 1 ) { // n > 1
            // there is no Solution
            return -1.0;
        }
        
        // initially all individuals are at the base
        // we will use a mask to indicate who still is to be transported
        
        int initial_mask = pow(2,n)-1;

        // prioritization
        // time smallest, TODO but there could be more criteria needed
        struct T {
            double time;
            int mask;
            int stage;
            T(double time, int mask, int stage) : time(time), mask(mask), stage(stage) {}
        };
        auto cmp = [](const T& a, const T& b) {
            return a.time > b.time;
        };
        priority_queue<T, vector<T>, decltype(cmp)> pq(cmp);

        double A[4096][5];
        for(int i = 0; i <= initial_mask; ++i)
            for(int j = 0; j < m; ++j)
                A[i][j] = DBL_MAX;
        
        double ans = DBL_MAX;

        pq.push(T(0.0, initial_mask, 0));
        A[initial_mask][0] = 0.0;
        while( !pq.empty() ) {
            double t = pq.top().time;
            int mask = pq.top().mask;   // at base camp
            int stage = pq.top().stage;
            pq.pop();

            // early exit: if time > best time, we can skip
            if( t >= ans || A[mask][stage] < t )
                continue;

            // cout << "to be taken "; printBinary(mask,n); cout << " stage " << stage << " time " << t << endl;

            // transport the people to be transported
            // we must take at least two, we cannot take more than k
            // only one going may not make sense at first, but we may catch a better time[i] * state,
            // hence we will try sending also one only
            bool seen_taken[4096];memset(seen_taken,false,sizeof seen_taken);
            for(int take = 1; take <= initial_mask; ++take) {
                int taken = mask & take;
                if( seen_taken[taken] )
                    continue;
                seen_taken[taken] = true;
                int setbits = countSetBits(taken);
                if( setbits >= 1 && setbits <= k ) {

                    int max_time = 0;
                    for(int i = 0; i < n; ++i) {
                        if( taken & (1<<i) ) {
                            max_time = max(max_time, time[i]);
                        }
                    }
                    double crossing_time = (double)max_time * mul[stage];
                    // early exit
                    if( t + crossing_time > ans )
                        continue;
                    int stage_addend_after_crossing = (int)floor(crossing_time) % m;
                    int stage_after_crossing = (stage + stage_addend_after_crossing) % m;

                    // cout << "  taken "; printBinary(taken,n); cout << " stage after crossing " << stage_addend_after_crossing << " crossing time " << crossing_time << endl;
                    // cout << "  max_time " << max_time << " mul[" << stage << "] " << mul[stage] << endl;

                    // we need to send someone back, unless our mask becomes 0
                    int rem = mask ^ taken;
                    if( rem > 0 ) {
                        // we can send anyone back who is at destination,
                        // which would be anyone who just crossed (taken) or anyone who was 
                        // already at destination
                        int at_dest_already = mask ^ initial_mask; 
                        for(int i = 0; i < n; ++i) {
                            if( (taken & (1<<i)) || (at_dest_already & (1<<i)) ) {
                                double return_time = (double)time[i] * mul[stage_after_crossing];
                                double time_new = t + crossing_time + return_time;

                                // early exit
                                if( time_new > ans )
                                    continue;

                                int stage_addend_after_return = (int)floor(return_time) % m;
                                int stage_after_return = (stage_after_crossing + stage_addend_after_return) % m;
                                int mask_new = rem | (1<<i);

                                if( A[mask_new][stage_after_return] > time_new ) {
                                    // cout << "    sending back " << i << " return time " << return_time << " to be taken "; printBinary(mask_new,n); cout << " stage " << stage_after_return << " total time " << time_new << endl;
                                    A[mask_new][stage_after_return] = time_new;
                                    pq.push(T(time_new, mask_new, stage_after_return));
                                }
                            }
                        }
                    } else {
                        // cout << "    ALL crossed in " << t + crossing_time << endl;
                        ans = min(ans, t + crossing_time);
                        // A[0][stage_after_crossing] = min(A[0][stage_after_crossing], t + crossing_time);
                    }
                }
            }
        }

//        double ans = DBL_MAX;
//        for(int i = 0; i < m; ++i)
//            ans = min(ans, A[0][i]);


        return ans != DBL_MAX ? ans : -1.0;
    }
};


