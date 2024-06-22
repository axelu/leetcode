

// 402. Remove K Digits
// https://leetcode.com/problems/remove-k-digits/








class Solution {
public:
    string removeKdigits(string& num, int k) {
        size_t n = num.size();
        if( n == k ) return "0";

        string stck;
        stck.push_back(num[0]);
        int i = 1;
        for(; i < n; ++i) {
            while( !stck.empty() ) {
                if( num[i] < stck.back() ) {
                    stck.pop_back();
                    --k;
                    if( k == 0 ) break;
                } else {
                    break;
                }
            }

            if( k == 0 ) break;

            if( num[i] != '0' ) {
                stck.push_back(num[i]);
            } else {
                while(i < n-1) {
                    if( num[i+1] != '0' ) break;
                    ++i;
                }
            }
        }

        // cout << "before finish i=" << i << " k=" << k << endl;

        // finish up
        for(; k > 0; --k) {
            if( stck.empty() ) break;
            stck.pop_back();
        }

        // cout << "after finish k=" << k << endl;
        // cout << "stck.size() " << stck.size() << " i " << i << " n " << n << endl;

        string ans = "";
        // if stck is not empty, stck to string + num.substr(i);
        if( !stck.empty() ) {
            /*
            while( !stck.empty() ) {
                ans = stck.back() + ans;
                stck.pop_back();
            }
            */
            ans = stck;
            ans += num.substr(i);
        } else {
            // if stck is empty and current is a non-0 return num.substr(i)
            if( i == n ) {
                ans = "0";
            } else if( num[i] != '0' ) {
                ans = num.substr(i);
            } else {
            // if stck is empty and current is a 0, advance to next non-0 and return from there
            //     if end, then return "0"
                ++i;
                while(i < n) {
                    if(num[i] != '0' ) break;
                    ++i;
                }
                ans = i != n ? num.substr(i) : "0";
            }
        }

        return ans;
    }
};
