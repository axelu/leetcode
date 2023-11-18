
// 1982. Find Array Given Subset Sums
// https://leetcode.com/problems/find-array-given-subset-sums/



class Solution {
private:
    void buildSubsetSum(vector<int>& arr) {
        // per problem description: The sum of an empty array is considered to be 0.

        vector<int> sums{0};
        cout << "round 0: " << sums[0] << endl;
        for(int i = 0; i < arr.size(); ++i) {
            cout << "round " << i+1 << ": ";
            int sums_sz = sums.size();

            for(int k = 0; k < sums_sz; ++k)
                cout << sums[k] << " ";
            for(int k = 0; k < sums_sz; ++k) {
                int t = sums[k] + arr[i];
                cout << t << " ";
                sums.push_back(t);
            }

            /*
            for(int k = 0; k < sums_sz; ++k) {
                int t = sums[k] + arr[i];
                sums.push_back(t);
            }
            */
            cout << endl;
            cout << "         ";
            sort(sums.begin(),sums.end());
            for(int x: sums)
                cout << x << " ";
            cout << endl;
        }
    }

public:
    vector<int> recoverArray(int n, vector<int>& sums) {

        // build subset sums
        // vector<int> arr1{2,5,9}; // some example
        // buildSubsetSum(arr1);
        // vector<int> arr2{1,2,-3}; // example 1
        // buildSubsetSum(arr2);

        // per problem description: The sum of an empty array is considered to be 0.
        // arr              subset sum
        // []               0
        //                  s0
        // [2 ]              0 , 2
        //  e0              s0, s0 + e0,
        //                  s0, s1
        // [2 ,5 ]          0 , 2      , 5      , 7
        //  e0,e1           s0, s1     , s0 + e1, s1 + e1
        //                  s0, s1     , s2     , s3
        // [2 ,5, 9 ]       0 , 2      , 5      , 7       , 9      , 11     , 14     , 16
        //  e0,e1,e2        s0, s1     , s2     , s3      , s0 + e2, s1 + e2, s2 + e2, s3 + e3
        //                  s0, s1     , s2     , s3      , s4     , s5     , s6     , s7
        // at each round the length of our subset sum array double
        // so to recover the original array, we will half the subset sum array at each step

        sort(sums.begin(),sums.end());
        vector<int> ans(n);
        for(int i = 0; i < n; ++i) {
            int diff = sums[1] - sums[0];
            // diff or -diff must be an element in our original array;
            // as an empty array has subset sum 0, we need to keep track
            // of subset sum 0, as that is the half that we want to continue with
            int zero = 0; // 0 goes left

            // split the subset sums array
            vector<int> left;   // s
            vector<int> right;  // s + diff

            left.push_back(sums[0]);
            right.push_back(sums[1]);
            if( sums[1] == 0 )
                zero = 1;

            unordered_multiset<int> plusdiff;
            for(int k = 2; k < sums.size(); ++k) {
                auto f = plusdiff.find(sums[k]);
                if( f != plusdiff.end() ) {
                    right.push_back(sums[k]);
                    if( sums[k] == 0 )
                        zero = 1;
                    plusdiff.erase(f);
                } else {
                    left.push_back(sums[k]);
                    plusdiff.insert(sums[k] + diff);
                }
            }
            sums = zero == 0 ? left : right;
            // based on observation
            // if we continue with the right half, then -diff is in our original array
            ans[i] = zero == 0 ? diff : -diff;
        }

        return ans;
    }
};
