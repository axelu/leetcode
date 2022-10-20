
// 2332. The Latest Time to Catch a Bus
// https://leetcode.com/problems/the-latest-time-to-catch-a-bus/




class Solution {
private:
    int search(vector<int>& nums, int s, int n, int target) {
        // binary search greatest element less than target or equal target
        // returns n-1 if nums[n-1] < target
        // returns  -1 if nums[0] > target --> s - 1
        // int s = 0;
        int e = n; // n = nums.size()
        int mid;
        while(s < e) {
            mid = s + ((e-s)/2);
            if( nums[mid] > target )
                e = mid;
            else
                s = mid+1;
        }
        if( (s < n && nums[s] > target) || s == n )
            --s;

        return s;
    }

    int gap(vector<int>& passengers, int s, int e, int k) {
        // returns the left most index who's value has no gap to the value at e
        // k is the original end index

        if( s > e )
            return -1;

        int mid = s + ((e-s)/2);
        int index_dist = k - mid;
        int value_dist = passengers[k] - passengers[mid];
        // value_dist cannot be less than index_dist
        if( value_dist == index_dist ) {
            // can we do better?
            int t = gap(passengers,s,mid-1,k);
            return t != -1 ? t : mid;
        }

        // there is a gap somwhere between mid and k
        // meaning the answer lies to the right
        return gap(passengers,mid+1,e,k);
    }

public:
    int latestTimeCatchTheBus(vector<int>& buses, vector<int>& passengers, int capacity) {
        // 2 <= buses[i], passengers[i] <= 10^9

        int n = buses.size();
        sort(buses.begin(),buses.end());
        int m = passengers.size();
        sort(passengers.begin(),passengers.end());

        // let us traverse busses and determine the latest time we could
        // arrive to catch the current bus

        int ans = 1;

        int nxt_passenger = 0;
        for(int i = 0; i < n; ++i) {
            int curr_bus_arrival_time = buses[i];

            // find index of the last passenger that arrives in time for the current bus
            int lst_passenger = search(passengers,nxt_passenger,m,curr_bus_arrival_time);

            if( lst_passenger < nxt_passenger ) {
                // no passenger is waiting to board the current bus
                ans = curr_bus_arrival_time;
                continue;
            }

            // how many people are in line for the current bus?
            int k = lst_passenger - nxt_passenger + 1;

            if( k < capacity ) {
                // we can arrive as late as the bus
                // we need to find the 'latest gap'
                // between [1,curr_bus_arrival_time] inclusive
                if( passengers[lst_passenger] < curr_bus_arrival_time ) {
                    ans = curr_bus_arrival_time;
                } else {

                    int t = gap(passengers, 0,lst_passenger,lst_passenger);
                    ans = passengers[t] - 1;
                }

            } else if( k == capacity ) {
                // we need to arrive BEFORE the last passenger!
                // we need to find the 'latest gap'
                // between [1,passengers[lst_passenger]-1] inclusive

                int t = gap(passengers, 0,lst_passenger,lst_passenger);
                ans = passengers[t] - 1;
            } else { // k > capacity
                // the bus' capacity is our limiter

                lst_passenger = nxt_passenger + capacity - 1;
                // we need to arrive BEFORE the last passenger!
                // we need to find the 'latest gap'
                // between [1,passengers[lst_passenger]-1] inclusive

                int t = gap(passengers, 0,lst_passenger,lst_passenger);
                ans = passengers[t] - 1;
            }

            nxt_passenger = lst_passenger + 1;
        }

        return ans;
    }
};
