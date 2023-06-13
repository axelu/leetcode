
// 2594. Minimum Time to Repair Cars
// https://leetcode.com/problems/minimum-time-to-repair-cars/




/* worst case
 * we have 1 mechanic with lowest rank and 1,000,000 cars
 * ranks = {100}, cars = 1000000
 * answer: 100000000000000
 * best case
 * we have 1 or more mechanics with only the highest rank and only 1 car
 * ranks = {1, ..., 1}, cars = 1
 * answer: 1
 */
class Solution {
    bool canrepairall(vector<int>& ranks, int cars, long long minutes) {
        int n = ranks.size();

        for(int i = 0; i < n; ++i) {
            // calculate how many cars mechanic i can repair in minutes
            int cars_repaired = sqrt(minutes/ranks[i]);
            cars -= cars_repaired;
            if( cars <= 0 )
                return true;
        }

        return false;
    }

    // binary search
    long long search(vector<int>& ranks, int cars, long long s, long long e) {
        if( e < s )
            return -1;

        long long mid = s + ((e-s)/2);
        bool f = canrepairall(ranks,cars,mid);
        if( f ) {
            // can we do better?
            long long t = search(ranks,cars,s,mid-1);
            return t != -1 ? t : mid;
        } else {
            return search(ranks,cars,mid+1,e);
        }
    }

public:
    long long repairCars(vector<int>& ranks, int cars) {
        sort(ranks.begin(),ranks.end());
        return search(ranks,cars,1,100000000000000);
    }
};
