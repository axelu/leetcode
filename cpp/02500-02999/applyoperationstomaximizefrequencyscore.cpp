
// 2968. Apply Operations to Maximize Frequency Score
// https://leetcode.com/problems/apply-operations-to-maximize-frequency-score/

// both solutions pass, recursive binary search and while loop binary search

class Solution {
private:
    bool solve(int l, vector<int>& nums, long long k, long long prefixSum[]) {
        if( l == 1 )
            return true;
        
        int n = nums.size();
        
        if( l % 2 ) {   // odd window length
            for(int i  = 0; i <= n-l; ++i) {
                int median_idx = i + l/2;
                // sum left of median idx
                long long sum_i_to_median_idx_minus_one = prefixSum[median_idx] - prefixSum[i];
                
                // sum right of median idx
                int j = i + l - 1;
                long long sum_i_plus_one_to_j = prefixSum[j+1] - prefixSum[median_idx+1];
                
                long long median = nums[median_idx];
                long long t = ((l/2 * median) - sum_i_to_median_idx_minus_one) + (sum_i_plus_one_to_j - (l/2 * median));
                if( t <= k )
                    return true;
            }
            
        } else {    // even window length
            for(int i  = 0; i <= n-l; ++i) {
                int upper_median_idx = i + l/2;
                int lower_median_idx = upper_median_idx - 1;
                
                long long median = (nums[lower_median_idx] + nums[upper_median_idx]) / 2LL;
                // sum left of upper median idx
                long long sum_i_to_lower_median_idx = prefixSum[lower_median_idx + 1] - prefixSum[i];

                // sum right of lower median idx
                int j = i + l - 1;
                long long sum_upper_median_idx_to_j = prefixSum[j+1] - prefixSum[upper_median_idx];

                long long t = ((l/2 * median) - sum_i_to_lower_median_idx) + (sum_upper_median_idx_to_j - (l/2 * median)); 
                if( t <= k )
                    return true;

                if( median % 2LL ) {
                    t = ((l/2 * (median+1)) - sum_i_to_lower_median_idx) + (sum_upper_median_idx_to_j - (l/2 * (median+1)));
                    if( t <= k )
                        return true;
                }
                    
            }
        }
        
        return false;
    }
    
    // binary search recursive
    int search(int s, int e, vector<int>& nums, long long k, long long prefixSum[]) {
        if( s > e )
            return -1;
        
        int mid = s + ((e-s)/2);
        bool f = solve(mid,nums,k,prefixSum);
        if( f ) {
            // can we do better?
            int t = search(mid+1,e,nums,k,prefixSum);
            return t != -1 ? t : mid;
        }
        
        return search(s,mid-1,nums,k,prefixSum);
    }
    
public:
    int maxFrequencyScore(vector<int>& nums, long long k) {
        int n = nums.size();
        if( n == 1 )
            return 1;
        
        sort(nums.begin(),nums.end());

        long long prefixSum[n+1];
        prefixSum[0] = 0LL;
        for(int i = 1; i <= n; ++i)
            prefixSum[i] = prefixSum[i-1] + nums[i-1];
        
        // return search(1,n,nums,k,prefixSum);
        
        // binary search while loop
        int s = 1;
        int e = n+1;
        while(s < e) {
            int mid = s + ((e-s)/2);
            bool f = solve(mid,nums,k,prefixSum);
            if( f )
                s = mid + 1;
            else
                e = mid;
        }
        if( s < n+1 && !solve(s,nums,k,prefixSum) )
            --s;
        
        return min(n,s);
    }
};



// passes 767/774 test cases as of 12/27/2023, 768th case TLE

class Solution {
private:
    int get_left(long long x, long long prefixSum[], int s, int e, long long k) {
        // cout << "get_left s " << s << " e " << e << " x " << x << " k " << k << endl;

        // e is i
        // s is 0

        int left = s;
        for( ; left < e; ++left) {
            long long _prefixSum = prefixSum[e] - prefixSum[left];
            long long l = e - left;
            long long sum = x * l;
            if( sum - _prefixSum <= k )
                break;
        }

        return left;
    }

    /*
    // binary search recursive
    int search_left(int s, int e, long long value_at_i, int i, long long prefixSum[], long long k) {
        if( s > e )
            return -1;

        int mid = s + ((e-s)/2);

        long long sum_mid_to_iminusone = prefixSum[i] - prefixSum[mid];
        long long l = i - mid;
        long long diff = (l * value_at_i) - sum_mid_to_iminusone;

        if( diff <= k ) {
            // can we do better?
            int t = search_left(s,mid-1,value_at_i,i,prefixSum,k);
            return t != -1 ? t : mid;
        }

        return search_left(mid+1,e,value_at_i,i,prefixSum,k);
    }
    */

    // binary search while loop
    int search_left(int s, int e, long long value_at_i, int i, long long prefixSum[], long long k) {

        int n = e+1;
        int mid;
        while(s < e) {
            mid = s + ((e-s)/2);

            long long sum_mid_to_iminusone = prefixSum[i] - prefixSum[mid];
            long long l = i - mid;
            long long diff = (l * value_at_i) - sum_mid_to_iminusone;
            if( diff <= k )
                e = mid;
            else
                s = mid + 1;
        }
        if( s < n ) {
            long long sum_s_to_iminusone = prefixSum[i] - prefixSum[s];
            long long l = i - s;
            long long diff = (l * value_at_i) - sum_s_to_iminusone;
            if( diff > k )
                ++s;
        }

        return s;
    }

    int get_right(long long x, long long prefixSum[], int s, int e, long long k) {
        // prefixSum size is n+1
        // s is i


        int right = e;
        for( ; right > s; --right) {
            long long suffixSum = prefixSum[right+1] - prefixSum[s+1];
            long long l = right - s;
            long long sum = x * l;
            if( suffixSum - sum <= k )
                break;
        }

        return right;
    }

    /*
    // binary search recursive
    int search_right(int s, int e, long long value_at_i, int i, long long prefixSum[], long long k) {
        if( s > e )
            return -1;

        int mid = s + ((e-s)/2);

        long long sum_iplusone_to_mid = prefixSum[mid+1] - prefixSum[i+1];
        long long l = mid - i;
        long long diff = sum_iplusone_to_mid - (value_at_i * l);

        if( diff <= k ) {
            // can we do better?
            int t = search_right(mid + 1,e,value_at_i,i,prefixSum,k);
            return t != -1 ? t : mid;
        }

        return search_right(s,mid-1,value_at_i,i,prefixSum,k);
    }
    */

    // binary search while loop
    int search_right(int s, int e, long long value_at_i, int i, long long prefixSum[], long long k) {

        s = s-1;
        int n = e + 1;
        e = e + 1;
        int mid;
        while(s < e) {
            mid = s + ((e-s)/2);

            long long sum_iplusone_to_mid = prefixSum[mid+1] - prefixSum[i+1];
            long long l = mid - i;
            long long diff = sum_iplusone_to_mid - (value_at_i * l);

            if( diff > k )
                e = mid;
            else
                s = mid + 1;
        }
        if( s < n ) {
            long long sum_iplusone_to_s = prefixSum[s+1] - prefixSum[i+1];
            long long l = s - i;
            long long diff = sum_iplusone_to_s - (value_at_i * l);
            if( diff > k )
                --s;
        }

        if( s == n )
            --s;

        return s;
    }

public:
    int maxFrequencyScore(vector<int>& nums, long long k) {
        int n = nums.size();
        if( n == 1 )
            return 1;

        sort(nums.begin(),nums.end());
        /*
        for(int x: nums)
            cout << x << " ";
        cout << endl;
        */

        long long prefixSum[n+1];
        prefixSum[0] = 0LL;
        for(int i = 1; i <= n; ++i)
            prefixSum[i] = prefixSum[i-1] + nums[i-1];
        /*
        cout << "prefixSum ";
        for(int i = 0; i <= n; ++i)
            cout << i << ":" << prefixSum[i] << " ";
        cout << endl;
        */

        int ans = -1;

        for(int i = 0; i < n; ++i) {
            // we want to attempt to make nums[i] THE value

            // find the leftmost index left, where 0 <= left <= i,
            // where (nums[i] * (i - left)) - sum[left,i-1] <= k

            // if we have something left over, respectively
            // rem = k - ((nums[i] * (i - left)) - sum[left,i-1])
            // we find the rightmost index right, where i <= right <= n-1
            // where sum[i+1,right] - nums[i] * (right - i) <= rem

            if( i == 0 ) {
                // find the rightmost index
                // int right = get_right(nums[i],prefixSum,i,n-1,k);
                int right = search_right(i+1,n-1,nums[i],i,prefixSum,k);
                // if( right == -1 ) // use for rec search
                //    right = i;
                // cout << "i " << i << " right " << right << endl;
                ans = max(ans, right + 1);
                // cout << "ans " << ans << endl;

            } else if( i > 0 && i < n-1 ) {
                // sliding window
                // int left = get_left(nums[i],prefixSum,0,i,k);
                int left = search_left(0,i-1,nums[i],i,prefixSum,k);
                // if( left == -1 ) // use for rec search
                //    left = i;
                long long sum_to_the_left = prefixSum[i] - prefixSum[left];
                long long l = i - left;
                long long diff = (l * nums[i]) - sum_to_the_left;
                int right = i;
                for(; left <= i; ++left) {
                    // cout << "i " << i << " left " << left << endl;
                    // cout << "remainder " << k-diff << endl;
                    // int right = get_right(nums[i],prefixSum,i,n-1,k-diff);
                    right = search_right(right+1,n-1,nums[i],i,prefixSum,k-diff);
                    // if( right == -1 ) // use for rec search
                    //     right = i;
                    // cout << "i " << i << " right " << right << endl;
                    ans = max(ans, right - left + 1);
                    // cout << "ans " << ans << endl;

                    // right cannot be better than n-1
                    if( right == n-1 )
                        break;

                    diff -= (nums[i] - nums[left]);
                }

            } else { // i == n-1
                // find the leftmost index
                // int left = get_left(nums[i],prefixSum,0,i,k);
                int left = search_left(0,i-1,nums[i],i,prefixSum,k);
                // if( left == -1 ) // use for rec search
                //    left = i;
                // cout << "i " << i << " left " << left << endl;
                ans = max(ans, n - left);
                // cout << "ans " << ans << endl;
            }

            // we cannot do better than n
            if( ans == n )
                break;
        }

        return ans;
    }
};
