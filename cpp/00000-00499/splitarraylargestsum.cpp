
// 410. Split Array Largest Sum
// https://leetcode.com/problems/split-array-largest-sum/



class Solution {
private:
    int n;
    
    int solve(vector<int>& nums, int x, int m) {
        // include as many elements as possible
        // while keeping the sum of elements <= x
        int mx = INT_MIN;
        int sum = 0;
        int people = 1;
        for(int i = 0; i < n; ++i) {
            if( sum + nums[i] <= x ) {
                sum += nums[i];
            } else {
                mx = max(mx,sum);
                sum = nums[i];
                ++people;
            }
        }
        mx = max(mx,sum);
        if( people <= m )
            return mx;            
        else 
            return -1;
    }
  
    // binary search
    int search(vector<int>& nums, int s, int e, int m) {
        //cout << "search s " << s << " e " << e << endl;
        if( s > e )
            return -1;
        
        
        int mid = s + ((e-s)/2);
        //cout << "  mid " << mid << endl;
        int a = solve(nums,mid,m);
        //cout << "  a " << a << endl;
        if( a != -1 ) {
            mid = a;
            // can we do better?
            int t = search(nums,s,mid-1,m);
            return t != -1 ? t : mid;
        } else {
            return search(nums,mid+1,e,m);
        }
    }
    
public:
    int splitArray(vector<int>& nums, int m) {
        n = nums.size();
        int mn = INT_MAX, mx = INT_MIN;
        int sum = 0;
        for(int i = 0; i < n; ++i) {
            mn = min(mn,nums[i]);
            mx = max(mx,nums[i]);
            sum += nums[i];
        }

        if( m == 1 )
            return sum;
        if( m == n || mx == sum )
            return mx;
        
        // our answer is in between mx and sum
        return search(nums,mx,sum,m);
    }
};
