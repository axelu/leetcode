
// 2459. Sort Array by Moving Items to Empty Space
// https://leetcode.com/problems/sort-array-by-moving-items-to-empty-space/





class Solution {
private:
    // brute force swap till done

    int casea(vector<int>& nums) {
        int n = nums.size();
        int pos0;
        int cntA = 0;
        vector<int> v(n);
        for(int i = 0; i < n; ++i) {
            if( nums[i] != i )
                ++cntA;
            if( nums[i] == 0 )
                pos0 = i;
            v[nums[i]] = i;
        }

        int ret = 0;
        int seen[n];memset(seen,0,sizeof seen);
        while( cntA > 1 ) {
            // cout << "pos0 " << pos0 << " cntA " << cntA << " moves " << ret << endl;
            if( pos0 == 0 ) {
                // cout << "we are stuck" << endl;
                // we are stuck

                int i = 1;
                for(; i < n; ++i) {
                    if( seen[i] || nums[i] == i )
                        continue;
                    break;
                }
                pos0 = i;
                if( pos0 == n )
                    break;
                // cout << "new pos0 " << pos0 << endl;
                if( ret == 0 )
                    ++cntA;
                ++ret;
                v[nums[i]] = 0;
                continue;

            }
            if( pos0 == n )
                break;

            seen[pos0] = 1;
            pos0 = v[pos0];
            ++ret;
            --cntA;
        }

        return ret;
    }

    int caseb(vector<int>& nums) {
        int n = nums.size();
        int pos0;
        int cntB = 0;
        vector<int> v(n);
        for(int i = 0; i < n; ++i) {
            if( (i == n-1 && nums[i] != 0) || nums[i] != i+1 )
                ++cntB;
            if( nums[i] == 0 )
                pos0 = i;
            v[nums[i]] = i;
        }

        int ret = 0;
        int seen[n];memset(seen,0,sizeof seen);
        while( cntB > 1 ) {
            // cout << "pos0 " << pos0 << " cntB " << cntB << " moves " << ret << endl;
            if( pos0 == n-1 ) {
                // cout << "we are stuck" << endl;
                // we are stuck

                int i = 0;
                for(; i < n-1; ++i) {
                    if( seen[i] || nums[i] == i+1 )
                        continue;
                    break;
                }
                pos0 = i;
                if( pos0 == n-1 )
                    break;
                // cout << "new pos0 " << pos0 << endl;
                if( ret == 0 )
                    ++cntB;
                ++ret;
                v[nums[i]] = n-1;
                continue;

            }
            if( pos0 == n-1 )
                break;

            seen[pos0] = 1;
            pos0 = v[pos0+1];
            ++ret;
            --cntB;
        }

        return ret;
    }

public:
    int sortArray(vector<int>& nums) {
        int n = nums.size();
        // cout << "n " << n << endl;

        int a = casea(nums);
        // cout << "a " << a << endl;
        int b = caseb(nums);
        // cout << "b " << b << endl;

        return min(a,b);
    }
};
