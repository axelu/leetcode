
// 1720. Decode XORed Array
// https://leetcode.com/problems/decode-xored-array/


class Solution {
public:
    vector<int> decode(vector<int>& encoded, int first) {
        size_t n = encoded.size();
        vector<int> arr(n+1);
        arr[0] = first;

        // encoded[i] = arr[i] XOR arr[i + 1]
        // can be transformed to
        // arr[i+1] = encoded[i] XOR arr[i]
        // becaouse the inverse of XOR is XOR!

        for(int i = 0; i < n; ++i)
            arr[i+1] = encoded[i]^arr[i];

        return arr;
    }
};
