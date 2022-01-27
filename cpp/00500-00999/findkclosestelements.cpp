
// 658. Find K Closest Elements
// https://leetcode.com/problems/find-k-closest-elements/
// day 2 July 2021 challenge
// https://leetcode.com/explore/challenge/card/july-leetcoding-challenge-2021/608/week-1-july-1st-july-7th/3800/




class Solution {
private:
    // binary search return element equal or 1st element greater
    int search(vector<int> arr, int s, int e, int x) {
        if( s > e )
            return -1;

        int mid = s + ((e-s)/2);
        if( arr[mid] == x ) {
            return mid;
        } else if( arr[mid] > x ) {
            // can we do better?
            int t = search(arr,s,mid-1,x);
            return t != -1 ? t : mid;
        } else {
            return search(arr,mid+1,e,x);
        }
    }

    bool isCloser(int a, int b, int x) {
        if( abs(a - x) < abs(b - x) ) {
            return true;
        } else if( abs(a - x) == abs(b - x) ) {
            if( a < b )
                return true;
        }
        return false;
    }

public:
    vector<int> findClosestElements(vector<int>& arr, int k, int x) {
        int n = arr.size();

        if( k == n )
            return arr;
        if( x <= arr[0] )
            return vector<int>(arr.begin(),arr.begin()+k);
        if( x >= arr[n-1] )
            return vector<int>(arr.begin()+n-k,arr.end());

        int t = search(arr,0,n-1,x);
        // if arr[t] == x we can start our exploration from index t
        // otherwise we need to determine if arr[t] or arr[t-1] is 'closer' to x
        if( arr[t] != x ) {
            if( !isCloser(arr[t],arr[t-1],x) )
                --t;
        }

        vector<int> ans;
        ans.push_back(arr[t]);

        int lidx = t-1,l;
        int ridx = t+1,r;
        while( ans.size() < k && lidx >= 0 && ridx < n ) {
            l = lidx >= 0 ? arr[lidx] : -10001;
            r = ridx <  n ? arr[ridx] :  10001;

            if( isCloser(l,r,x) ) {
                ans.insert(ans.begin(),arr[lidx]);
                --lidx;
            } else {
                ans.push_back(arr[ridx]);
                ++ridx;
            }
        }

        // finish up
        if( ans.size() < k ) {
            while( ans.size() < k && lidx >= 0 ) {
                ans.insert(ans.begin(),arr[lidx]);
                --lidx;
            }
            while( ans.size() < k && ridx < n ) {
                ans.push_back(arr[ridx]);
                ++ridx;
            }
        }

        return ans;;
    }
};
