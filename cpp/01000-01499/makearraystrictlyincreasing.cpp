
// 1187. Make Array Strictly Increasing
// https://leetcode.com/problems/make-array-strictly-increasing/



class Solution {
private:
    // remove duplicates
    void removeDuplicates(vector<int>& arr) {
        // input is non-empty sorted vector<int>
        int n = arr.size();
        if( n == 1 )
            return;

        for(auto it = next(arr.begin()); it != arr.end(); )
            if( *prev(it) == *it )
                it = arr.erase(it);
            else
                ++it;
    }

    // binary search
    int search(vector<int>& nums, int target) {
        int n = nums.size();
        // it is guaranteed that target exists in nums
        // nums is sorted and has no duplicates
        int s = 0;
        int e = n; // n = nums.size()
        int mid;
        while(s < e) {
            mid = s + ((e-s)/2);
            if( target <= nums[mid] )
                e = mid;
            else
                s = mid+1;
        }
        if( s < n && nums[s] < target )
            ++s;

        return s;
    }

    // binary search upper bound
    int upper_bound(vector<int>& nums, int target) {
        int n = nums.size();
        // returns 'n' if nums[n-1] <= target
        // returns  0  if nums[0] > target
        int s = 0;
        int e = n; // n = nums.size()
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

    int mem[2000][4000];

    int rec(vector<int>& arr1, vector<int>& arr3, int i, int j, vector<int>& arr2) {
        // i = current index in arr1
        // j = index of prior element in arr3
        // arr2 are the replacements to chose from

        if( i == arr1.size()-1 ) {
            if( arr1[i] > arr3[j] )
                return 0;
            else {
                int t = upper_bound(arr2,arr3[j]);
                return t < arr2.size() ? 1 : 1000000000;
            }
        }

        if( i > 0 && mem[i][j] != -1 ) {
            // cout << "hit" << endl;
            return mem[i][j];
        }

        // we have a choice
        // if the current element > prior element
        //    just continue OR
        //    replace curr element with next greater element than prior element (upper_bound)
        // else
        //    we must actually
        //    replace curr element with next greater element than prior element (upper_bound)

        int a = 1000000000;
        if( i == 0 || arr1[i] > arr3[j] )
            a = rec(arr1,arr3,i+1,search(arr3,arr1[i]),arr2);

        int b = 1000000000;
        if( i == 0 ) {
            // it doesn't make sense to replace the current element with a greater element
            if( arr2[0] < arr1[i] ) {
                // replace with smallest element
                int t = search(arr3,arr2[0]);
                b = rec(arr1,arr3,i+1,t,arr2) + 1;
            }
        } else {
            int t = upper_bound(arr2,arr3[j]);
            if( t < arr2.size() ) {
                t = search(arr3,arr2[t]);
                b = rec(arr1,arr3,i+1,t,arr2) + 1;
            }
        }

        int ret = min(a,b);
        if( i > 0 )
            mem[i][j] = ret;
        return ret;
    }

public:
    int makeArrayIncreasing(vector<int>& arr1, vector<int>& arr2) {
        int arr1_sz = arr1.size();
        if( arr1_sz == 1 )
            return 0;

        // concatenate arr2 and arr1 into arr3
        vector<int> arr3(arr1);
        arr3.insert(arr3.end(),arr2.begin(),arr2.end());
        sort(arr3.begin(),arr3.end());
        removeDuplicates(arr3);

        sort(arr2.begin(),arr2.end());
        removeDuplicates(arr2);

        memset(mem,-1,sizeof mem);
        int ans = rec(arr1,arr3,0,-1,arr2);
        return ans != 1000000000 ? ans : -1;
    }
};
