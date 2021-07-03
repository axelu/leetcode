#include <vector>
#include <climits>
#include <iostream>
#include <cassert>

using namespace std;


vector<int> find_max_crossing_subarray(vector<int> A, int low, int mid, int high) {
    cout << "find_max_crossing_subarray low " << low << " mid " << mid << " high " << high << endl;
    // returns a tuple cointaining the indices demarcating
    // a maximum subarray that crosses the midpoint, along with
    // sum of the values in a maximum subarray

    int max_left = mid;
    int left_sum = INT_MIN;
    int sum = 0;
    for(int i = mid; i >= low; --i) {
        sum += A[i];
        if( sum > left_sum ) {
            left_sum = sum;
            max_left = i;
        }
    }

    int max_right = mid+1;
    int right_sum = INT_MIN;
    sum = 0;
    for(int j = mid+1; j <= high; ++j) {
        sum += A[j];
        if( sum > right_sum ) {
            right_sum = sum;
            max_right = j;
        }
    }

    return {max_left,max_right,left_sum + right_sum};
}

vector<int> find_max_subarray(vector<int> A, int low, int high) {
    cout << "find_max_subarray low " << low << " high " << high << endl;
    // returns a tuple cointaining the indices demarcating
    // a maximum subarray, along with
    // sum of the values in a maximum subarray

    if( high == low ) {
        return {low,high,A[low]};
    } else {
        int mid = (low+high)/2;

        // left
        vector<int> left  = find_max_subarray(A,low,mid);
        int left_low  = left[0];
        int left_high = left[1];
        int left_sum  = left[2];

        // right
        vector<int> right = find_max_subarray(A,mid+1,high);
        int right_low  = right[0];
        int right_high = right[1];
        int right_sum  = right[2];

        // cross
        vector<int> cross = find_max_crossing_subarray(A,low,mid,high);
        int cross_low  = cross[0];
        int cross_high = cross[1];
        int cross_sum  = cross[2];

        if( left_sum >= right_sum && left_sum >= cross_sum ) {
            return {left_low,left_high,left_sum};
        } else if( right_sum >= left_sum && right_sum >= cross_sum ) {
            return {right_low,right_high,right_sum};
        } else {
            return {cross_low,cross_high,cross_sum};
        }
    }
}

int main() {
    vector<int> a{13,-3,-25,20,-3,-16,-23,18,20,-7,12,-5,-22,15,-4,7};

    // expected
    vector<int> b{7,10,43};

    vector<int> r = find_max_subarray(a,0,a.size()-1);
    cout << r[0] << " " << r[1] << " " << r[2] << endl;
    assert(r == b);


    return 0;
}
