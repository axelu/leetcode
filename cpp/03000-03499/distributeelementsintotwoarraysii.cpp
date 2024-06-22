
// 3072. Distribute Elements Into Two Arrays II
// https://leetcode.com/problems/distribute-elements-into-two-arrays-ii/






class Solution {
private:
    vector<int> bit1; // binary indexed tree bit, 0 indexed
    vector<int> bit2; // binary indexed tree bit, 0 indexed
    int n;

    int sum(vector<int>& bit, int r) {
        int ret = 0;
        for (; r >= 0; r = (r & (r + 1)) - 1)
            ret += bit[r];
        return ret;
    }

    void add(vector<int>& bit, int idx, int delta) {
        for (; idx < n; idx = idx | (idx + 1))
            bit[idx] += delta;
    }

public:
    vector<int> resultArray(vector<int>& nums) {
        int nums_sz = nums.size(); // 3 <= nums.length <= 1e5; 1 <= nums[i] <= 1e9

        set<int> st; // unique vals in nums
        for(int x: nums)
            st.insert(x);

        n = st.size();
        bit1.assign(n, 0);
        bit2.assign(n, 0);

        unordered_map<int,int> um;
        int idx = 0;
        for(int x: st)
            um[x] = idx++;

        vector<int> distribution(nums_sz); // track distribution of nums[i] into arr1 and arr2
        distribution[0] = 1;
        int l1 = 1;                  // number of elements distributed into arr1
        add(bit1, um[nums[0]], 1);
        distribution[1] = 2;
        int l2 = 1;                  // number of elements distributed into arr2
        add(bit2, um[nums[1]], 1);

        for(int i = 2; i < nums_sz; ++i) {
            // cout << "i " << i << endl;
            int r = um[nums[i]];
            // cout << "  r " << r << endl;

            // get number of elements in arr1 that are greater than nums[i]
            int greaterCount1 = l1 - sum(bit1, r); // cout << "  greaterCount1 " << greaterCount1 << endl;

            // get number of elements in arr2 that are greater than nums[i]
            int greaterCount2 = l2 - sum(bit2, r); // cout << "  greaterCount2 " << greaterCount2 << endl;

            if( greaterCount1 > greaterCount2 ) {
                // cout << "  adding to arr1" << endl;
                add(bit1, r, 1);
                ++l1;
                distribution[i] = 1;
            } else if( greaterCount1 < greaterCount2 ) {
                // cout << "  adding to arr2" << endl;
                add(bit2, r, 1);
                ++l2;
                distribution[i] = 2;
            } else { // greaterCount1 == greaterCount2
                if( l1 > l2 ) {
                    // cout << "  adding to arr2" << endl;
                    add(bit2, r, 1);
                    ++l2;
                    distribution[i] = 2;
                } else {
                    // cout << "  adding to arr1" << endl;
                    add(bit1, r, 1);
                    ++l1;
                    distribution[i] = 1;
                }
            }

            // cout << "  l1 " << l1 << endl;
            // cout << "  l2 " << l2 << endl;
        }

        vector<int> ans(nums_sz);
        int i = 0;
        for(int j = 0; j < nums_sz; ++j) {
            if( distribution[j] == 1 ) {
                ans[i] = nums[j];
                ++i;
            }
        }
        for(int j = 0; j < nums_sz; ++j) {
            if( distribution[j] == 2 ) {
                ans[i] = nums[j];
                ++i;
            }
        }

        return ans;
    }
};
