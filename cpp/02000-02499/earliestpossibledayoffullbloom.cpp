
// 2136. Earliest Possible Day of Full Bloom
// https://leetcode.com/problems/earliest-possible-day-of-full-bloom/




class Solution {
public:
    int earliestFullBloom(vector<int>& plantTime, vector<int>& growTime) {
        // our earliest full bloom cannot be less than
        // max(plantTime[i] + growTime[i])

        // we will arrange our planting so that we always plant!
        // and we will plant the plant with the shortest growing time last
        // that means we plant the plant with the shortest growing time
        // after all other plants are planted
        // more formaly: sum of all plant times + shortest growing time

        int n = plantTime.size(); // plantTime.length == growTime.length

        vector<array<int,2>> v(n);
        for(int i = 0; i < n; ++i)
            v[i] = {plantTime[i],growTime[i]};

        sort(v.begin(),v.end(),[](const array<int,2>& a, const array<int,2>& b){
            if( a[1] > b[1] ) {
                return true;
            } else if( a[1] == b[1] ) {
                if( a[0] > b[0] ) {
                    return true;
                }
            }
            return false;
        });

        int ans = 0;

        int plant_time_so_far = 0;
        for(int i = 0; i < n; ++i) {
            ans = max(ans,plant_time_so_far+v[i][0]+v[i][1]);
            plant_time_so_far += v[i][0];
        }

        return ans;
    }
};
