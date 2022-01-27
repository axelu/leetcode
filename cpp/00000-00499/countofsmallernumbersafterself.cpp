
// 315. Count of Smaller Numbers After Self
// https://leetcode.com/problems/count-of-smaller-numbers-after-self/



// segment tree according to leetcode
// https://leetcode.com/articles/a-recursive-approach-to-segment-trees-range-sum-queries-lazy-propagation/

class Solution {
private:

    int merge(int a, int b) {
        return a+b;
    }

    void update(int t[], int treeIndex, int s, int e, int arrIndex, int val) {
        // cout << "update treeIndex " << treeIndex << endl;
        if( s == e ) {              // leaf node.update element.
            t[treeIndex] += val; // increase count by val (val in our case always 1)
            return;
        }

        int index_left_child  = 2 * treeIndex + 1;
        int index_right_child = 2 * treeIndex + 2;

        int mid = s + ((e-s)/2);
        if( arrIndex > mid )    // go right
            update(t,index_right_child,mid+1,e,arrIndex,val);
        else                    // go left
            update(t,index_left_child,s,mid,arrIndex,val);

        // merge updates
        // t[treeIndex] = merge(t[index_left_child],t[index_right_child]);
        t[treeIndex] = t[index_left_child] + t[index_right_child];
    }

    int query(int t[], int treeIndex, int s, int e, int i, int j) {
        // query for segment[i..j] inclusive

        if( s > j || e < i )    // segment completely outside range
            return 0;           // represents a null node

        if( i <= s && j >= e )  // segment completely inside range
            return t[treeIndex];

        // partial overlap of current segment and queried range.
        // we need to recurse deeper.

        int index_left_child  = 2 * treeIndex + 1;
        int index_right_child = 2 * treeIndex + 2;

        int mid = s + ((e-s)/2);
        if( i > mid )           // go right, answer is entirely to the right
            return query(t,index_right_child,mid+1,e,i,j);
        else if( j <= mid )     // go left, answer is entirely to the left
            return query(t,index_left_child,s,mid,i,j);


        int leftQuery = query(t,index_left_child,s,mid,i,mid);
        int rightQuery = query(t,index_right_child,mid+1,e,mid+1,j);

        // merge query results
        // return merge(leftQuery,rightQuery);
        return leftQuery + rightQuery;
    }


public:
    vector<int> countSmaller(vector<int>& nums) {
        auto n = nums.size();
        if( n == 0 )
            return {};
        if( n == 1 )
            return {0};

        // we will use the count of values in nums
        // as 'buckets' in a segment tree.
        // a segment will return us the sum of counts
        // for the given segment.
        // we will update the tree as we traverse nums
        // from right to left i = n-1 ... i = 0.
        // with that, we can issue a query [-∞,nums[i]-1]
        // and get the sum of counts for all elements
        // to the right of i that are smaller than nums[i].


        // segment tree
        // the buckets counts of all possible values in nums
        // are our leaves. as the possible values
        // can be negative, we will apply an offset to
        // only deal with positive values for indexes
        // in our tree
        // -10^4 <= nums[i] <= 10^4 -> offset = 10000
        int o = 10000;
        // number of possible values = 2*10000 + 1
        int number_values = 2*10000+1;
        int t[4 * number_values];
        // build the tree
        // in our case all counts are zero, so we
        // initiallize all nodes in our segment tree
        // to zero
        memset(t,0,sizeof t);

        vector<int> ans(n);

        for(int i = n-1; i >= 0; --i) {
            //int q = query(0,nums[i]+o,t,sz);
            int q = query(t,0,0,number_values-1,0,nums[i]+o-1);
            ans[i] = q;
            update(t,0,0,number_values-1,nums[i]+o,1);
        }

        return ans;
    }
};
