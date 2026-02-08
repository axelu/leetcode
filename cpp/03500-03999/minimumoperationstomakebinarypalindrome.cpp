
// 3766. Minimum Operations to Make Binary Palindrome
// https://leetcode.com/problems/minimum-operations-to-make-binary-palindrome/

// initialize once
int lans[5001];
vector<int> bp; // binary palindromes
bool init = false;

class Solution {
private: 
    string int2binarystring(int x) {
        string ret(13,'0'); // max x = 5000 -> binary 1001110001000 13digits
        for(int i = 0; i < 13; ++i)
            if( (x>>i) & 1 )
                ret[13-1-i] = '1';
        // trim leading 0s, if any
        while(ret.size() > 1 && ret.front() == '0' )
            ret.erase(0,1);
        return ret;
    }



    bool is_binary_palindrome(int x) {
        string s = int2binarystring(x);

        // bool isPalindrome(string& s)
        if( s.size() == 1 ) return true;

        bool p = true;

        auto fi = s.begin();
        auto ri = s.rbegin();
        while( fi <= ri.base() ) {
            if( *fi == *ri ) {
                ++fi;
                ++ri;
            } else {
                p = false;
                break;
            }
        }

        return p;
    }

public:
    vector<int> minOperations(vector<int>& nums) {
        if( !init ) {
            for(int i = 1; i <= 5000; ++i)
                if( is_binary_palindrome(i) )
                    bp.push_back(i);
            memset(lans,-1,sizeof lans);
            init = true;
        }

        int n = nums.size(); // 1 <= n <= 5000; 1 <= nums[i] <= 5000
        vector<int> ans(n);
        for(int i = 0; i < n; ++i) {
            int x = nums[i];
            if( lans[x] != -1 ) {
                ans[i] = lans[x];
                continue;
            }
            auto lb = lower_bound(bp.begin(), bp.end(), x);
            if( lb == bp.end() ) {
                int t = bp.back();
                int d = x - t;
                ans[i] = d;
                lans[x] = d; // lazily populating lans for future
            } else if( *lb == x ) {
                ans[i] = 0;
                lans[x] = 0; // lazily populating lans for future
            } else { // *lb > x
                int d1 = *lb - x;
                int d2 = INT_MAX;
                if( lb != bp.begin() ) {
                    --lb;
                    d2 = x - *lb;
                }
                ans[i] = min(d1, d2);
                lans[x] = min(d1, d2); // lazily populating lans for future
            }
        }

        return ans;
    }
};
