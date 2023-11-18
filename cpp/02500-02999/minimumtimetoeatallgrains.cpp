
// 2604. Minimum Time to Eat All Grains
// https://leetcode.com/problems/minimum-time-to-eat-all-grains/



class Solution {
private:
    int upper_bound(vector<int>& nums, int s, int target) {
        int n = nums.size();
        // returns 'n' if nums[n-1] <= target
        // returns  0  if nums[0] > target
        // binary search upper bound while loop
        // upper bound -> greater than target
        // int s = 0;
        int e = n; // n = nums.size();
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

    bool solve1hen(vector<int>& hens, vector<int>& grains, int mxtime) {
        // int n = 1;
        int m = grains.size();

        // try from left
        int tl = abs(hens[0]-grains[0]);   // time for hen to reach first grain
        // try from right
        int tr = abs(hens[0]-grains[m-1]); // time for hen to reach the last grain

        int tg = grains[m-1] - grains[0];  // time from last to 1st grain or vice versa

        if( min(tl,tr) + tg <= mxtime )
            return true;

        return false;
    }

    bool solve(vector<int>& hens, vector<int>& grains, int mxtime) {
        // cout << "solve mxtime " << mxtime << endl;
        int n = hens.size();
        if( n == 1 )
            return solve1hen(hens,grains,mxtime);

        int m = grains.size();

        int j = 0; // grain[j] to be picked up next by current hen
        for(int i = 0; i < n; ++i) {
            // cout << "hens[" << i << "] = " << hens[i] << " grains[" << j << "] " << grains[j] << endl;
            // current hen picks up all grains it can
            // starting with the grain at grains[j]

            if( grains[j] >= hens[i] ) {
                // all remaining grains are starting at our position to the right
                j = upper_bound(grains,j,hens[i]+mxtime);
                // cout << "  j " << j << endl;

            } else {
                // there are grains still to the left of our current hen
                // if we cannot reach the grain left to us, we are doomed
                if( hens[i] - grains[j] > mxtime )
                    return false;
                // if all grains are to the left of us we are done
                if( grains[m-1] <= hens[i] )
                    return true;

                // we have a choice:
                //    we could go left first OR go right first
                // left first
                int time_left = mxtime - (hens[i] - grains[j]); // our hen is now at grains[j]
                // cout << "time_left " << time_left << endl;
                int jl = j + 1;
                jl = upper_bound(grains,jl,grains[j]+time_left);
                // cout << "  jl " << jl << endl;

                // right first if there are even any grains to the right of us
                int jr = -1;
                if( grains[m-1] >= hens[i] ) {
                    // we know we have to pick up the grain at grains[j]
                    // so we can only go as far right that still leaves enough time
                    // to pick up the grain at grains[j]
                    // max time we can go to the right is:
                    int time_right = (mxtime - (hens[i] - grains[j])) / 2;
                    // cout << "time_right " << time_right << endl;
                    jr = upper_bound(grains,j,hens[i]+time_right);
                }
                // cout << "  jr " << jr << endl;
                j = max(jl,jr);
            }

            if( j == m )
                return true;
        }

        return false;
    }


    // binary search
    int search(vector<int>& hens, vector<int>& grains, int s, int e) {
        // cout << "search s " << s << " e " << e << endl;
        if( e < s )
            return -1;

        int mid = s + ((e-s)/2);
        bool f = solve(hens,grains,mid);
        if( f ) {
            // can we do better?
            int t = search(hens,grains,s,mid-1);
            return t != -1 ? t : mid;
        }

        return search(hens,grains,mid+1,e);
    }

public:
    int minimumTime(vector<int>& hens, vector<int>& grains) {
        sort(hens.begin(),hens.end());
        sort(grains.begin(),grains.end());

        int s = 0;
        int e = 2000000000;

        return search(hens,grains,s,e);
    }
};
