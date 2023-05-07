
// 1053. Previous Permutation With One Swap
// https://leetcode.com/problems/previous-permutation-with-one-swap/




class Solution {
private:
    // binary search
    // return the rightmost element less than target
    int search(vector<vector<int>>& q, int s, int e, int target) {
        if( s > e )
            return -1;

        int mid = s + ((e-s)/2);
        if( q[mid][0] < target ) {
            // can we do better?
            int t = search(q,mid+1,e,target);
            return t != -1 ? t : mid;
        }

        return search(q,s,mid-1,target);
    }

public:
    vector<int> prevPermOpt1(vector<int>& arr) {
        int n = arr.size();
        if( n == 1 )
            return arr;

        // we need to bring a smaller value to the left
        // from the right
        // find the 1st larger value
        // said differently:
        // the right most element smaller than the current element we need to swap

        vector<vector<int>> q;
        q.push_back({arr[n-1],n-1});
        for(int i = n-2; i >= 0; --i) {
            // get the rightmost element less than current element
            int j = search(q,0,q.size()-1,arr[i]);
            if( j != -1 ) {
                // swap current position value with j

                // edge case
                // [3,1,1,3] -> [1,3,1,3]
                if( q[0][0] == q[j][0] )
                    j = 0;

                int t = arr[i];
                arr[i] = q[j][0]; // equivalent to arr[i] = arr[q[j][q]];
                arr[q[j][1]] = t;
                break;
            }
            q.push_back({arr[i],i});
            sort(q.begin(),q.end());
        }

        return arr;
    }
};
