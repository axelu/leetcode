
// 321. Create Maximum Number
// https://leetcode.com/problems/create-maximum-number/





class Solution {
private:
    vector<int> merge(vector<int>& nums1, int n1, vector<int>& nums2, int n2, int k) {
        vector<int> ret(k); // n1 + n2 == k
        int i = 0; // index in nums1
        int j = 0; // index in nums2
        int o = 0; // index in ret
        while( i < n1 && j < n2 ) {
            if( nums1[i] > nums2[j] ) {
                ret[o] = nums1[i];
                ++i;
                ++o;
            } else if( nums1[i] < nums2[j] ) {
                ret[o] = nums2[j];
                ++j;
                ++o;
            } else { // nums1[i] == nums2[j]
                // we have to break the tie
                // lets peek ahead
                int i_new = i;
                int j_new = j;
                // advance as long as nums1 and nums2 are equal or we run out
                while( i_new < n1 && j_new < n2 && nums1[i_new] == nums2[j_new] ) {
                    ++i_new;
                    ++j_new;
                }
                // we must check if we ran out?
                if( i_new < n1 && j_new < n2 ) {
                    if( nums1[i_new] > nums2[j_new] ) {
                        ret[o] = nums1[i];
                        ++i;
                        ++o;
                    } else {
                        ret[o] = nums2[j];
                        ++j;
                        ++o;
                    }
                } else if( i_new == n1 ) {
                    ret[o] = nums2[j];
                    ++j;
                    ++o;
                } else {
                    ret[o] = nums1[i];
                    ++i;
                    ++o;
                }
            }
        }
        // finish up
        while( i < n1 ) {
            ret[o] = nums1[i];
            ++i;
            ++o;
        }
        while( j < n2 ) {
            ret[o] = nums2[j];
            ++j;
            ++o;
        }

        return ret;
    }

    vector<int> get_mx(vector<int>& nums, int k) {
        // k <= nums.size()
        int n = nums.size();
        // we need to extract k elements by preserving the order out of nums
        if( k == 0 )
            return {};
        if( k == nums.size() )
            return nums;

        stack<int> stck;
        for(int i = 0; i < n; ++i) {

            //  including the current element at i, there are rem = n - i elements left
            //  with the number of elements in the stack.size() + rem, we need to be able to get out with k elements in the stack
            int rem = n - i;
            while( !stck.empty() && stck.size() - 1 + rem >= k && stck.top() < nums[i] )
                stck.pop();

            if( stck.size() < k )
                stck.push(nums[i]);
        }

        // extract from stack and reverse
        vector<int> ret;
        while( !stck.empty() ) {
            ret.push_back(stck.top());
            stck.pop();
        }
        reverse(ret.begin(),ret.end());

        return ret;
    }

    bool cmp(vector<int>& a, vector<int>& b, int n) {
        // returns true if vector<int> a is lexicographically greater than vector<int> b
        // n == a.size() == b.size()
        for(int i = 0; i < n; ++i)
            if( a[i] != b[i] )
                return a[i] > b[i];

        return false;
    }

public:
    vector<int> maxNumber(vector<int>& nums1, vector<int>& nums2, int k) {
        int n1 = nums1.size();
        int n2 = nums2.size();

        // if n1 + n2 == k, then we have to select all elements from nums1 and all element from nums2
        if( n1 + n2 == k ) {
            return merge(nums1, n1, nums2, n2, k);
        }

        // similar to above, we need to take k elements our of nums1 and nums2 combined
        // so we cold take  nums1 nums2
        //                    0     k
        //                    1     k-1
        //                    2     k-2
        //                    ...
        //                    k-2   2
        //                    k-1   1
        //                    k     0
        // NOTE: whatever we take out of either obviously can only be as many elements as there are in nums1, nums2 respectively

        // TODO we could work with 2 preallocated vectors to increase performance

        vector<int> ans(k,0);

        for(int i = 0; i <= k; ++i) {
            // can we take k-i elements out of nums2?
            if( k-i > n2 )
                continue;

            if( i <= n1 ) {
                auto v1 = get_mx(nums1, i);
                auto v2 = get_mx(nums2, k-i);
                // merge
                auto v = merge(v1, i, v2, k-i, k);
                if( cmp(v,ans,k) )
                    ans = v;
            }
        }

        return ans;
    }
};
