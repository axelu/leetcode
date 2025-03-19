
// 3149. Find the Minimum Cost Array Permutation
// https://leetcode.com/problems/find-the-minimum-cost-array-permutation/






class Solution {
private:
    void printBinary(int x, int m) {
        for(int i = m; i >= 0; --i) {
            if( x & (1 << i) ) cout << 1;
            else cout << 0;
        }
        // cout << endl;
    }

    const int INF = 100000;

    int countSetBits(int i) {
        unsigned int count = 0;
        while (i) {
            count += i & 1;
            i >>= 1;
        }
        return count;
    }

    int mem[15][16384];  // min score
    int memP[15][16384]; // int used, to reconstruct path later
    int pre0;

    int rec(vector<int>& nums, int pre, int mask) {
        // we start with one bit set

        int n = nums.size();
        int setBits = countSetBits(mask);

        // cout << "search pre " << pre << " ";printBinary(mask, n-1);cout << " setBits " << setBits << endl;


        if( setBits == n )
            return abs(pre - nums[pre0]);

        if( mem[pre][mask] != -1 )
            return mem[pre][mask];

        // setBits tells which position we are at
        // mask tells us which integers between 0..n-1 inclusive have been used
        // pre tells us the integer used before us

        int score = INF;

        for(int i = 0; i < n; ++i) {
            if( !(mask & (1<<i)) ) {

                int cost = abs(pre - nums[i]);
                /*
                if( setBits == 0 ) {
                    cost = 0;
                    pre0 = i;
                }
                */
                int local_score = cost + rec(nums, i, mask|(1<<i));
                if( local_score < score ) {
                    score = local_score;
                    memP[pre][mask] = i;
                }
            }
        }
        // cout << "search pre " << pre << " ";printBinary(mask, n-1);cout << " result " << score << endl;
        return mem[pre][mask] = score;
    }

    vector<int> ans;

    void get_path(int pre, int mask, int n) {

        int i = memP[pre][mask];
        ans.push_back(i);
        if( (mask|(1<<i)) == pow(2,n)-1 )
            return;

        get_path(i, mask|(1<<i), n);
        return;
    }


public:
    vector<int> findPermutation(vector<int>& nums) {
        int n = nums.size(); // 2 <= n == nums.length <= 14

        int min_score = INF;
        for(int i = 0; i < n; ++i) {
            memset(mem,-1,sizeof mem);

            // we use i for pos 0 in our perm
            pre0 = i;
            int mask = (1<<i);
            int score = rec(nums, i, mask);

            if( score < min_score ) {
                min_score = score;
                ans.clear();
                ans.push_back(i);
                get_path(i, mask, n);
            }
        }

        // cout << "min_score " << min_score << endl;
        return ans;
    }
};
