
// 1011. Capacity To Ship Packages Within D Days
// https://leetcode.com/problems/capacity-to-ship-packages-within-d-days/


class Solution {
private:
    size_t N;

    bool isPossible(vector<int>& weights, int& D, int capacity) {
        // load the ship
        int minCapacity = 0;
        int days = 1;
        int load = 0;
        for(int i = 0; i < N; ++i) {
            minCapacity = max(minCapacity,weights[i]);
            if( load + weights[i] > capacity ) {
                ++days;
                load = 0;
            }
            load += weights[i];
        }
        if( capacity < minCapacity ) return false;
        return days <= D;
    }

public:
    int shipWithinDays(vector<int>& weights, int D) {
        N = weights.size();
        if( 1 == N ) return weights[0];

        int s = 0; // max weight == min capacity (we need a ship that can at least carry the heaviest package)
        int e = 0; // sum of all weights (we could ship all packages in 1 day)
        for(int i = 0; i < N; ++i) {
            e += weights[i];
            s = max(s,weights[i]);
        }
        if( 1 == D ) return e;

        int ans = e;
        while( s <= e ) {
            int mid = s + ((e - s)/2);
            bool possible = isPossible(weights,D,mid);
            if( possible ) {
                // ship exactly right or could be smaller
                ans = mid;
                e = mid-1;
            } else {
                // ship too small
                s = mid+1;
            }
        }

        return ans;
    }
};
