
// 898. Bitwise ORs of Subarrays
// https://leetcode.com/problems/bitwise-ors-of-subarrays/



class Solution {
public:
    int subarrayBitwiseORs(vector<int>& arr) {
        size_t n = arr.size();
        unordered_set<int> s;

        // "optimized" brute force

        // [[arr[0]],[arr[0],arr[1]],...,[arr[0],arr[1],...arr[n-1]]]
        s.insert(arr[0]);
        int m = arr[0];
        for(int i = 1; i < n; ++i) {
            m = m | arr[i];
            s.insert(m);
        }

        for(int i = 1; i < n; ++i) {
            // if arr[i] has all the same bits set as arr[i-1], basically
            // arr[i] & arr[i-1] == arr[i-1], then we can skip arr[i], because
            // subarray[arr[i],arr[i]], subarray[arr[i],arr[i + 1]],..., subarray[arr[i],arr[n - 1]]
            // has already been covered by
            // subarray[arr[i-1],arr[i-1]], subarray[arr[i-1],arr[i]],..., subarray[arr[i-1],arr[n - 1]]
            if( (arr[i] & arr[i - 1]) != arr[i - 1] ) {
                int m = 0;
                for(int j = i; j < n; ++j) {
                    m = m | arr[j];
                    s.insert(m);
                    if( (m & arr[i-1]) == arr[i-1] )
                        break;
                }
            }
        }
        return s.size();
    }
};
