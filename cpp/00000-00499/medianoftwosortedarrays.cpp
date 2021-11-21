#include <iostream>
#include <cassert>

#include <vector>

using namespace std;

// 4. Median of Two Sorted Arrays
// https://leetcode.com/problems/median-of-two-sorted-arrays/

class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {

        if ( nums1.empty() || nums2.empty() ) {

            vector<int>* v = ( nums1.empty() ) ? &nums2 : &nums1;
        
            if ( v->size() == 1 ) {
                return v->at(0);
            } else {
                size_t h = v->size() / 2;
                if ( v->size() % 2 == 0 ) {
                    return ( (v->at(h - 1) + v->at(h)) / 2.0 );
                } else {
                    return v->at(h);
                }
            }
        
        } else {

            size_t h = (nums1.size() + nums2.size()) / 2;

            if ( nums1.back() <= nums2.front() || nums2.back() <= nums1.front() ) {

                vector<int>* v1;
                vector<int>* v2;

                if ( nums1.back() <= nums2.front() ) {
                    v1 = &nums1;
                    v2 = &nums2;
                } else {
                    v1 = &nums2;
                    v2 = &nums1;
                }

               if ( (nums1.size() + nums2.size()) % 2 == 0 ) {
                   
                   int a; // at pos h-1 of 'combined' vector
                   int b; // at pos h of 'combined' vector

                    if ( h == v1->size() ) {
                        a = v1->back();
                        b = v2->front();
                    } else {

                        // a
                        // if ( v1->size() - 1 < h - 1 ) {
                        if ( v1->size() < h ) {
                            a = v2->at(h - v1->size() - 1);
                        } else {
                            a = v1->at(h - 1);
                        }

                        // b
                        if ( v1->size() - 1 < h ) {
                            b = v2->at(h - v1->size());
                        } else {
                            b = v1->at(h);
                        }
                    
                   }
                   
                   return (a + b) / 2.0;

               } else {
                    if ( h <= v1->size() - 1 ) {
                        return v1->at(h);
                    } else {
                        return v2->at(h - v1->size());
                    }
               }

           } else {

                auto it1 = nums1.begin();
                auto it2 = nums2.begin();
                size_t s = 0;
                int a;
                int b;

                while ( it1 != nums1.end() && it2 != nums2.end() ) {

                    if ( *it1 < *it2 ) {
                        if ( s == h - 1 ) a = *it1;
                        if ( s == h ) {
                            b = *it1;
                            break;
                        }
                        it1++;
                        s++;
                    } else {
                        if ( s == h - 1 ) a = *it2;
                        if ( s == h ) {
                            b = *it2;
                            break;
                        }
                        it2++;
                        s++;
                    }
                }

                if ( s < h ) {
                    if ( it1 == nums1.end() ) {
                        // it2 += s - 1; b = *it2;
                        it2 += h - s; b = *it2;
                        it2--; a = *it2;
                    } else {
                        // it1 += s - 1; b = *it1;
                        it1 += h - s; b = *it1;
                        it1--; a = *it1;
                    }
                } else if ( s == h && ( it1 == nums1.end() || it2 == nums2.end() ) ) {
                    // edge case
                    if ( it1 == nums1.end() ) {
                        b = *it2;
                        a = nums1.back();
                    } else {
                        b = *it1;
                        a = nums2.back();
                    }
                }

                return ( (nums1.size() + nums2.size()) % 2 == 0 ) ? (a + b) / 2.0 : b;

           }

        }
    }
};

int main() {

    Solution s;

    vector<int> v1;
    vector<int> v2;


    v1 = {};
    v2 = {1,2,3};
    assert(s.findMedianSortedArrays(v1, v2) == 2.0);

    v1 = {1,2,3};
    v2 = {};
    assert(s.findMedianSortedArrays(v1, v2) == 2.0);

    v1 = {};
    v2 = {2};
    assert(s.findMedianSortedArrays(v1, v2) == 2.0);

    v1 = {2};
    v2 = {};
    assert(s.findMedianSortedArrays(v1, v2) == 2.0);

    v1 = {1,2};
    v2 = {};
    assert(s.findMedianSortedArrays(v1, v2) == 1.5);

    v1 = {1};
    v2 = {3};
    assert(s.findMedianSortedArrays(v1, v2) == 2.0);

    v1 = {1};
    v2 = {1};
    assert(s.findMedianSortedArrays(v1, v2) == 1.0);

    v1 = {1,2};
    v2 = {3,4};
    assert(s.findMedianSortedArrays(v1, v2) == 2.5);

    v1 = {3,4};
    v2 = {1,2};
    assert(s.findMedianSortedArrays(v1, v2) == 2.5);

    v1 = {1,3};
    v2 = {2};
    assert(s.findMedianSortedArrays(v1, v2) == 2.0);

    v1 = {-1,2,3};
    v2 = {2,3,4};
    assert(s.findMedianSortedArrays(v1, v2) == 2.5);

    v1 = {2,3,4,5};
    v2 = {1,6,7,8};
    assert(s.findMedianSortedArrays(v1, v2) == 4.5);

    v1 = {2,3,4};
    v2 = {1,5,6,7};
    assert(s.findMedianSortedArrays(v1, v2) == 4.0);

    v1 = {1,4,5,6,7,8,9,10};
    v2 = {2,3};
    assert(s.findMedianSortedArrays(v1, v2) == 5.5);

    v1 = {2,3};
    v2 = {1,4,5,6,7,8,9,10};
    assert(s.findMedianSortedArrays(v1, v2) == 5.5);

    v1 = {1};
    v2 = {2,3,4};
    assert(s.findMedianSortedArrays(v1, v2) == 2.5);

    v1 = {2,3,4};
    v2 = {1};
    assert(s.findMedianSortedArrays(v1, v2) == 2.5);

    v1 = {1,2};
    v2 = {2,3,4,5};
    assert(s.findMedianSortedArrays(v1, v2) == 2.5);

    v1 = {1,2,3,4,5,6,8};
    v2 = {7};
    assert(s.findMedianSortedArrays(v1, v2) == 4.5);

    v1 = {2};
    v2 = {1,3,4};
    assert(s.findMedianSortedArrays(v1, v2) == 2.5);

    v1 = {2};
    v2 = {1,3,4,5,6,7,8};
    assert(s.findMedianSortedArrays(v1, v2) == 4.5);

    v1 = {1,3,4,5,6,7,8};
    v2 = {2};
    assert(s.findMedianSortedArrays(v1, v2) == 4.5);



    return 0;
}
