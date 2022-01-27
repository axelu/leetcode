
// 475. Heaters
// https://leetcode.com/problems/heaters/



class Solution {
private:

    int upperbound(vector<int>& nums, int target) {
        // returns 'n' if nums[n-1] <= target
        // returns  0  if nums[0] > target
        // binary search upper bound while loop
        // upper bound -> greater than target
        int s = 0;
        int n = nums.size();
        int e = n;
        int mid;
        while(s < e) {
            mid = s + ((e-s)/2);
            if( target >= nums[mid] )
                s = mid + 1;
            else
                e = mid;
        }
        if( s < n && nums[s] <= target )
            ++s;

        return s;
    }

    int search(vector<int>& houses, int hl, int hr, int s, int e) {
        if( s > e )
            return -1;

        int mid = s + (e-s)/2;
        int a = upperbound(houses,hl+mid);
        if( a == houses.size() || houses[a] >= hr-mid ) {
            // can we do better?
            int t = search(houses,hl,hr,s,mid-1);
            return t != -1 ? t : mid;
        } else {
            return search(houses,hl,hr,mid+1,e);
        }
    }
public:
    int findRadius(vector<int>& houses, vector<int>& heaters) {
        sort(houses.begin(),houses.end());
        sort(heaters.begin(),heaters.end());

        int ans = 0;

        // check to the left of first heater
        if( houses[0] < heaters[0] )
            ans = heaters[0] - houses[0];

        // check to the right of last heater
        if( houses[houses.size()-1] > heaters[heaters.size()-1] )
            ans = max(ans,houses[houses.size()-1]-heaters[heaters.size()-1]);

        if( heaters.size() == 1 )
            return ans;

        for(int i = 0,j = 1; j < heaters.size(); ++i,++j) {
            if( heaters[i] == heaters[j] )
                continue;

            int i_right = heaters[i]+ans;
            int j_left  = heaters[j]-ans;

            if( i_right+1 >= j_left ) // overlap or touch
                continue;

            // is there one or more houses in the gap?
            int a = upperbound(houses,i_right);
            if( a == houses.size() )
                break;

            if( houses[a] >= j_left )
                continue;

            // we need to increase the radius of our heater
            int worst = ans + (j_left - i_right)/2;
            ans = search(houses,heaters[i],heaters[j],ans,worst);
        }

        return ans;
    }
};
