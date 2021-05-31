
// 702. Search in a Sorted Array of Unknown Size
// https://leetcode.com/problems/search-in-a-sorted-array-of-unknown-size/




/**
 * // This is the ArrayReader's API interface.
 * // You should not implement it, or speculate about its implementation
 * class ArrayReader {
 *   public:
 *     int get(int index);
 * };
 */

class Solution {
private:
    // binary search
    int search(const ArrayReader& reader, int s, int e, int target) {
        if( s > e ) return -1;        
        
        int mid = s + ((e-s)/2);
        int val = reader.get(mid);
        if( val == target ) {
            return mid;
        } else if( val != 2147483647 ) {
            if( val < target ) {
                return search(reader,mid+1,e,target);
            } else {
                return search(reader,s,mid-1,target);
            }
        } else {
            return search(reader,s,mid-1,target);
        }
    }
public:
    int search(const ArrayReader& reader, int target) {
        return search(reader,0,9999,target);
    }
};
