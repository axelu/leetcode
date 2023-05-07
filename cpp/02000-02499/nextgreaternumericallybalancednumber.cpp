
// 2048. Next Greater Numerically Balanced Number
// https://leetcode.com/problems/next-greater-numerically-balanced-number/



class Solution {
private:
    string n;

    // balanced number generator
    bool solve(int k, int cnt[], string& s) {

        if( s.size() == k ) {
            // check if we have a solution aka balanced number
            for(int i = 1; i <= k; ++i) {
                if( cnt[i] > 0 && cnt[i] < i ) {
                    // we don't have a solution
                    return false;;
                }
            }
            // cout << s << endl;
            if( s > n || s.size() > n.size() )
                return true;

            return false;
        }

        for(int i = 1; i <= k; ++i) {
            if( cnt[i] > 0 ) {
                s.push_back(i+'0');
                --cnt[i];
                if( solve(k,cnt,s) )
                    return true;
                // backtrack
                s.pop_back();
                ++cnt[i];
            }
        }

        return false;
    }


public:
    int nextBeautifulNumber(int n) {
        // 0 <= n <= 10^6
        // mn = 1; mx = 7777777, actually 1,224,444

        this->n = to_string(n);

        int cnt[8];
        cnt[1] = 1;
        cnt[2] = 2;
        cnt[3] = 3;
        cnt[4] = 4;
        cnt[5] = 5;
        cnt[6] = 6;
        cnt[7] = 7;

        string s = "";
        for(int i = this->n.size(); i < 8; ++i) { // length of our integer
            if( solve(i,cnt,s) )
                break;
        }

        return stoi(s);
    }
};
