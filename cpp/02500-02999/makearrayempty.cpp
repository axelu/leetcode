
// 2659. Make Array Empty
// https://leetcode.com/problems/make-array-empty/





class Solution {
private:
    vector<int> bit;  // binary indexed tree, 0-indexed, (BIT) Fenwick Tree
    int n;

    bool is_sorted(vector<int>& nums, vector<pair<int,int>>& _nums) {
        for(int i = 0; i < n; ++i)
            if( nums[i] != _nums[i].first )
                return false;
        return true;
    }

    void init() {
        for (int i = 0; i < n; i++) {
            bit[i] += 1; // initially each index is present
            int r = i | (i + 1);
            if (r < n) bit[r] += bit[i];
        }
    }

    int sum(int r) {
        int ret = 0;
        for (; r >= 0; r = (r & (r + 1)) - 1)
            ret += bit[r];
        return ret;
    }

    int sum(int l, int r) {
        return sum(r) - sum(l - 1);
    }

    void add(int idx, int delta) {
        for (; idx < n; idx = idx | (idx + 1))
            bit[idx] += delta;
    }

public:
    long long countOperationsToEmptyArray(vector<int>& nums) {
        // it is guaranteed that all values in nums are distinct
        n = nums.size();
        if( n == 1 )
            return 1;

        // brute force passes 505/514 test cases as of 3/12/2024, then TLE
        /*
        struct T {
            int val;
            T * next;
            T(int val) : val(val), next(nullptr) {}
        };

        set<int> st;
        st.insert(nums[0]);
        T * head = new T(nums[0]);
        T * pre = head;
        for(int i = 1; i < n; ++i) {
            st.insert(nums[i]);
            T * ln = new T(nums[i]);
            pre->next = ln;
            pre = ln;
        }
        pre->next = head;

        long long cnt = (long long)n;
        for(auto x: st) {

            while( head->val != x ) {
                ++cnt;
                pre = head;
                head = head->next;
            }

            // delete
            T * t = head;
            head = head->next;
            delete t;
            if( pre != t )
                pre->next = head;
        }

        return cnt;
        */

        // idea
        // we can sort the values in nums while maintaining at which index a given element is
        // with that we get the order in which the indicies get deleted
        // lets say we are about to delete index i (that we got to position 0) and after that would be index j
        // 0 1 2 3 4 5 6 7 8 9
        // i         j
        // then including the delete operation, we would need 5 operations
        // 0 1 2 3 4 5 6 7 8 9
        //         j            1 operation, deleting i ,  j moves from pos 5 to pos 4
        //       j              1 operation, rotate by 1,  j moves from pos 4 to 3
        //     j                1 operation, rotate by 1,  j moves from pos 3 to 2
        //   j                  1 operation, rotate by 1,  j moves from pos 2 to 1
        // j                    1 operation, rotate by 1,  j moves from pos 1 to 0
        // this is the same as 'measuring' the distance between the index following the index we just deleted and
        // the index we are deleting next + the delete operation.  j = 5, i = 0, dist = j - (i+1) + 1 = 5 - (0+1) + 1
        // if we keep track of the indexes [i+1,j] that we already delete, then we know the answer
        // we can use a range sum data structure, initally all leaves (representing our indicies) are 1, when we delete an index
        // we update it to 0
        // note that we will need to wrap around if our next index to be deleted is in front of us.
        // 0 1 2 3 4 5 6 7 8 9
        //     j     i
        // example
        // 0 1 2 3 4 5 index
        // 5 3 1 4 2 6 nums
        // first index to delete: 2, takes 3 operations (2 rotations, 1 deletion)
        //

        vector<pair<int,int>> _nums(n);
        for(int i = 0; i < n; ++i)
            _nums[i] = {nums[i],i};

        sort(_nums.begin(),_nums.end(),[](const pair<int,int>& a, const pair<int,int>& b){
           return a.first < b.first;
        });

        // if( is_sorted(nums, _nums) )
        //     return n;

        bit.assign(n,0);
        init();

        long long ans = 1LL; // deletion of 1st element

        int pre = 0;
        int i = 0;
        if( _nums[0].second == 0 ) { // handle where smallest value is at index 0;
            i = 1;
            // 'delete'
            add(0, -1);
        }
        for(; i < n; ++i) {
            int cur = _nums[i].second;

            // calculate 'distance'
            long long d = 0LL;;
            if( pre < cur) {
                d = sum(pre + 1, cur);
            } else {
                // we need to wrap around
                if( pre + 1 < n )
                    d = sum(pre + 1, n - 1);
                d += sum(0, cur);
            }

            // 'delete'
            add(cur, -1);

            // cout << "index pre " << pre << " cur " << cur << " operations " << d << endl;
            ans += d;
            pre = cur;
        }

        return ans;
    }
};
