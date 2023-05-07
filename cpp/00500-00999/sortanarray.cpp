
// 912. Sort an Array
// https://leetcode.com/problems/sort-an-array/



class Solution {
private:
    void mergesort(vector<int>& v, int p, int r) {
        if(p < r) {
            // divide
            // cout << "divide " << p << " " << r << endl;
            int q = p + ((r - p)/2);
            mergesort(v,p,q);
            mergesort(v,q+1,r);

            // combine aka merge
            // cout << "merge  " << p << " " << r << endl;
            int n1 = q-p+1;
            int n2 = r-q;
            vector<long> L(n1+1);
            vector<long> R(n2+1);
            for(int i = 0; i < n1; ++i)
                L[i] = v[p+i];
            for(int i = 0; i < n2; ++i)
                R[i] = v[q+1+i];
            L[n1] = (long)INT_MAX+1;
            R[n2] = (long)INT_MAX+1;
            int i = 0;
            int j = 0;
            for(int k = p; k <= r; ++k) {
                if( L[i] <= R[j] ) {
                    v[k] = L[i];
                    ++i;
                } else {
                    v[k] = R[j];
                    ++j;
                }
            }
        }
    }
    
    vector<int> countingsort(vector<int>& nums) {
        int n = nums.size();
        auto itb = nums.begin();
        auto ite = nums.end();
        
        // counting sort
        int max = *max_element(itb,ite);
        int min = *min_element(itb,ite);
        int range = max - min + 1;

        vector<int> count(range);
        vector<int> output(n);
        for (int i = 0; i < n; i++)
            count[nums[i] - min]++;

        for (int i = 1; i < range; i++)
            count[i] += count[i - 1];

        for (int i = n - 1; i >= 0; i--) {
            output[count[nums[i] - min] - 1] = nums[i];
            count[nums[i] - min]--;
        }
        
        return output;
    }

public:
    vector<int> sortArray(vector<int>& nums) {
        // sort(nums.begin(),nums.end()); // built-in functions
        
        // mergesort(nums,0,nums.size()-1);
        // return nums;
        
        return countingsort(nums);
    }
};
