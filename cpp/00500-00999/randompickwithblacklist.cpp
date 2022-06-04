
// 710. Random Pick with Blacklist
// https://leetcode.com/problems/random-pick-with-blacklist/



class Solution {
private:
    vector<array<int,2>> offsets;
    int mod;

    // binary search greatest element less than target or equal target
    int search(int target) {
        int n = offsets.size();
        // returns n-1 if nums[n-1] < target
        // returns  -1 if nums[0] > target
        int s = 0;
        int e = n;
        int mid;
        while(s < e) {
            mid = s + ((e-s)/2);
            if( offsets[mid][0] > target )
                e = mid;
            else
                s = mid+1;
        }
        if( (s < n && offsets[s][0] > target) || s == n )
            --s;

        return s;
    }

public:
    Solution(int n, vector<int>& blacklist) {
        int m = blacklist.size();

        if( m > 0 ) {
            sort(blacklist.begin(),blacklist.end());
            int offset = 1;
            int key = blacklist[0];
            for(int i = 1; i < m; ++i) {
                if( blacklist[i] - 1 != blacklist[i-1] ) {
                    // cout << "inserting key:offset " << key << ":" << offset << endl;
                    offsets.push_back({key,offset});
                    key = key + blacklist[i] - blacklist[i-1] - 1;
                }
                ++offset;
            }
            // finish up
            // cout << "inserting key:offset " << key << ":" << offset << endl;
            offsets.push_back({key,offset});
        }

        mod = n - m;
        srand(time(nullptr)); // use current time as seed for random generator
    }

    int pick() {
        int rdm = rand() % mod;
        int t = search(rdm);
        return t == -1 ? rdm : rdm + offsets[t][1];
    }
};

/**
 * Your Solution object will be instantiated and called as such:
 * Solution* obj = new Solution(n, blacklist);
 * int param_1 = obj->pick();
 */
