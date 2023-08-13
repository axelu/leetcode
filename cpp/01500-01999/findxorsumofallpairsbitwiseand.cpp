
// 1835. Find XOR Sum of All Pairs Bitwise AND
// https://leetcode.com/problems/find-xor-sum-of-all-pairs-bitwise-and/





class Solution {
private:
    // brute force
    int bf(vector<int>& arr1, vector<int>& arr2) {
        int n1 = arr1.size();
        int n2 = arr2.size();

        vector<int> v;
        for(int i = 0; i < n1; ++i)
            for(int j = 0; j < n2; ++j)
                v.push_back(arr1[i] & arr2[j]);

        for(int i = 0; i < v.size(); ++i)
            cout << v[i] << " ";
        cout << endl;

        int ret = v[0];
        for(int i = 1; i < v.size(); ++i)
            ret ^= v[i];

        return ret;
    }

public:
    int getXORSum(vector<int>& arr1, vector<int>& arr2) {
        //return bf(arr1,arr2);

        int n1 = arr1.size();
        int n2 = arr2.size();

        // let arr1 = {a,b};
        // let arr2 = {c,d};
        // (a&c) ^ (a&d) ^ (b&c) ^ (b&d) ->
        // -------------   -------------
        //   a & (c^d)   ^   b & (c^d)   ->
        //   (a ^ b)     &   (c ^ d)

        int arr1xor = arr1[0];
        for(int i = 1; i < n1; ++i)
            arr1xor ^= arr1[i];

        int arr2xor = arr2[0];
        for(int i = 1; i < n2; ++i)
            arr2xor ^= arr2[i];

        return arr1xor & arr2xor;
    }
};
