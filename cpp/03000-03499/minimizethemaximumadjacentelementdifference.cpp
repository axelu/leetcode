
// 3357. Minimize the Maximum Adjacent Element Difference
// https://leetcode.com/problems/minimize-the-maximum-adjacent-element-difference/





class Solution {
private:
    bool solve(vector<int>&nums, int n, int x, int y, int d) {
        // cout << "solve x " << x << " y " << y << " d " << d << endl;

        int pre = nums[0]; // guaranteed not -1
        for(int i = 1; i < n-1; ++i) {

            if( nums[i] == -1 && nums[i+1] != -1 ) {
                if( nums[i-1] != -1 ) {
                    // we either use x or y
                    int d1 = max(abs(nums[i-1]-x), abs(nums[i+1]-x)); // use x
                    int d2 = max(abs(nums[i-1]-y), abs(nums[i+1]-y)); // use y
                    int mn_d = min(d1, d2);
                    if( mn_d > d )
                        return false;

                } else { // nums[i-1] =! -1, meaning more than one -1
                    // edge case where we could do
                    // a, x, y, b

                    // we try to use either x or y
                    int d1 = max(abs(pre-x), abs(nums[i+1]-x)); // use x
                    int d2 = max(abs(pre-y), abs(nums[i+1]-y)); // use y
                    int mn_d = min(d1, d2);
                    if( mn_d > d ) {
                        // let us try a, x, y, b
                        int xy_diff = abs(x-y);
                        if( xy_diff > d )
                            return false;
                    }
                }
            }
            if( nums[i] != -1 )
                pre = nums[i];
        }

        return true;
    }

public:
    int minDifference(vector<int>& nums) {
        int n = nums.size(); // 2 <= nums.length <= 1e5
        if( n == 2 ) {
            // something something
            // -1        something
            // something -1
            // -1        -1
            if( nums[0] == -1 || nums[1] == -1 )
                return 0;
            else
                return abs(nums[0] - nums[1]);
        }

        // note that the answer maximum absolute difference between adjacent elements
        // can be in the end between existing elements, as we cannot do anything about those difference
        // example: [1,2,-1,10,20]
        //     we replace -1 with 6, which gives us 4 as the difference to the adjacent elements
        //     but have also the diff between 10 and 20, which is in fact our answer
        // also should the -1 be at the very begin or at the very end
        // we can just add the 1st non -1 at the begin respectively the last non -1 at the end
        // also, there could be consecutive -1s
        // which makes an interesting edge case, because we could do
        // a,-1,-1, b (or more -1s in between)
        // a, x, y, b; where x-a <= d and b-y <=b, BUT also y-x <= d

        // track the maximim diff between existing adjacent numbers and
        // between numbers on either side of one or more -1s

        int mx_diff_existing = 0;
        int mn_element = INT_MAX; // mn element next to -1
        int mx_element = INT_MIN; // mx element next to -1
        int fst = -1;
        int lst = -1;
        for(int i = 0; i < n; ++i) {
            int val = nums[i];
            if( val != -1 ) {

                if( fst == -1 )
                    fst = val;
                lst = val;

                if( i > 0 && nums[i-1] != -1 )
                    mx_diff_existing = max(mx_diff_existing, abs(nums[i-1] - val));
                if( i < n-1 && nums[i+1] != -1 )
                    mx_diff_existing = max(mx_diff_existing, abs(val - nums[i+1]));

            } else {

                if( i > 0 && nums[i-1] != -1 ) {
                    mn_element = min(mn_element, nums[i-1]);
                    mx_element = max(mx_element, nums[i-1]);
                }
                if( i < n-1 && nums[i+1] != -1 ) {
                    mn_element = min(mn_element, nums[i+1]);
                    mx_element = max(mx_element, nums[i+1]);
                }
            }
        }

        if( fst == -1 ) // we only have -1s
            return 0;
        if( mn_element == mx_element ) // all adjacent elements to -1(s) are the same
            return mx_diff_existing;
        if( mn_element == INT_MAX && mx_element == INT_MIN ) // no -1 at all
            return mx_diff_existing;


        // to simplify
        if( nums[0] == -1 ) {
            nums.insert(nums.begin(), fst);
            ++n;
        }
         if( nums[n-1] == -1 ) {
            nums.push_back(lst);
            ++n;
        }

        // cout << "mn_element " << mn_element << " mx_element " << mx_element << " mx_diff_existing " << mx_diff_existing << endl;

        // our answer is somewhere between the existing largest diff of adjacent elements and
        // half the difference between the min and max element of elements adjacent to one or more -1
        // we would add d to the smallest element adjacent to -1, so x = mn_element + d
        // we would subtract d from the largest element adjacent to -1, so y = mx_element - d
        // then we can see if with those x and y we can solve it
        // binary search while loop
        int s = mx_diff_existing;
        int e = (mx_element - mn_element + 1) / 2; // +1 because of int conversion (rounding down)
        // cout << "e " << e << endl;
        while( s < e ) {
            int mid = s + ((e-s)/2); // this is our minimum difference candidate
            int x = mn_element + mid;
            int y = mx_element - mid;
            if( solve(nums, n, x, y, mid) )
                e = mid;
            else
                s = mid+1;
        }

        return s;
    }
};
