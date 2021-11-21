
// 1533. Find the Index of the Large Integer
// https://leetcode.com/problems/find-the-index-of-the-large-integer/




/**
 * // This is the ArrayReader's API interface.
 * // You should not implement it, or speculate about its implementation
 * class ArrayReader {
 *   public:
 *     // Compares the sum of arr[l..r] with the sum of arr[x..y]
 *     // return 1 if sum(arr[l..r]) > sum(arr[x..y])
 *     // return 0 if sum(arr[l..r]) == sum(arr[x..y])
 *     // return -1 if sum(arr[l..r]) < sum(arr[x..y])
 *     int compareSub(int l, int r, int x, int y);
 *
 *     // Returns the length of the array
 *     int length();
 * };
 */

class Solution {
private:
    // binary search
    int search(ArrayReader &reader, int s, int e) {
        // cout << "s " << s << " e " << e << endl;

        if( e - s == 1 )
            return reader.compareSub(s,s,e,e) == 1 ? s : e;
        if( e - s == 2 ) {
            int res = reader.compareSub(s,s,s+1,s+1);
            if( res == 0 ) {
                return e;
            } else if( res == 1 ) {
                return s;
            } else {
                return s+1;
            }
        }


        int mid = s+((e-s)/2);
        // cout << "mid " << mid << endl;
        if( (e-s)%2 == 0 ) {
            int res = reader.compareSub(s,mid,mid,e);
            if( res == 0 ) {
                return mid;
            } else if( res == 1 ) {
                return search(reader,s,mid-1);
            } else {
                return search(reader,mid+1,e);
            }
        } else {
            int res = reader.compareSub(s,mid,mid+1,e);
            if( res == 1 )
                return search(reader,s,mid);
            else
                return search(reader,mid+1,e);
        }
    }

public:
    int getIndex(ArrayReader &reader) {
        int n = reader.length(); // 2 <= arr.length <= 5 * 10^5
        return search(reader,0,n-1);
    }
};
