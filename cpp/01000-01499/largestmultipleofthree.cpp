
// 1363. Largest Multiple of Three
// https://leetcode.com/problems/largest-multiple-of-three/





class Solution {
private:
    vector<vector<string>> mem;

    string rec(vector<int>& digits, int pos, int rem, map<int,int>& mp) {
        // TODO instead of digits and pos, just use a vector representing count of each digit, and which digit we are at
        int n = digits.size();

        // cout << "rec pos " << pos << " rem " << rem << endl;
        if( pos == n )
            return "";

        if( mem[pos][rem] != "#" )
            return mem[pos][rem];

        // add all of our kind to answer (greedy)
        // go to next pos
        // if after return the ans is not longer back up one
        //    if there is only one of us, we are done
        //    go to next pos
        // if after return the ans is not longer back up one more
        //    if there are only two of us, we are done
        //    go to next pos
        // if after return the ans is not longer back up one more
        //    if there are only three of us, we are done
        //    go to next pos
        // after that the remainder will repeat, so no point to go further back

        int j; // (index of next smaller value or n if we are the smallest value) - 3
        int val = digits[pos];
        auto it = mp.find(val);
        if( it == mp.begin() ) {
            // there is no smaller number behind us
            j = max(pos, n - 3);
        } else {
            j = max(pos, prev(it)->second - 3);
        }
        // cout << "  j " << j << endl;

        string t = "";
        int rem_new = rem;
        int i = pos;
        vector<int> remainders;
        for(; i < n; ++i) {
            if( digits[i] != val )
                break;
            t = t + to_string(digits[i]);
            rem_new = ((10 * rem_new) + val) % 3;
            if( i >= j )
                remainders.push_back(rem_new);
        }

        if( it == mp.begin() ) {
            // there is no smaller number behind us
            if( remainders.back() == 0 )
                return mem[pos][rem] = t;

            // back up 1
            t.pop_back();
            remainders.pop_back();
            if( t.empty() || remainders.back() == 0 )
                return mem[pos][rem] = t;

            // back up 2
            t.pop_back();
            remainders.pop_back();
            if( t.empty() || remainders.back() == 0 )
                return mem[pos][rem] = t;
            else
                return mem[pos][rem] = "";
        }

        --it;

        string ret = "";
        if( remainders.back() == 0 )
            ret = t;

        auto it_new = it;
        while( true ) {
            string a = rec(digits, it_new->second, remainders.back(), mp);
            if( !a.empty() )
                if( t.size() + a.size() > ret.size() )
                    ret = t + a;
            if( it_new == mp.begin() )
                break;
            --it_new;
        }

        // back up 1
        t.pop_back();
        remainders.pop_back();
        if( !t.empty() && remainders.back() == 0 )
            if( t.size() > ret.size() )
                ret = t;
        if( !t.empty() ) {
            it_new = it;
            while( true ) {
                string a = rec(digits, it_new->second, remainders.back(), mp);
                if( !a.empty() )
                    if( t.size() + a.size() > ret.size() )
                        ret = t + a;
                if( it_new == mp.begin() )
                    break;
                --it_new;
            }
        }

        // back up 2
        if( !t.empty() ) {
            t.pop_back();
            remainders.pop_back();
            if( !t.empty() && remainders.back() == 0 )
                if( t.size() > ret.size() )
                    ret = t;
            if( !t.empty() ) {
                it_new = it;
                while( true ) {
                    string a = rec(digits, it_new->second, remainders.back(), mp);
                    if( !a.empty() )
                        if( t.size() + a.size() > ret.size() )
                            ret = t + a;
                    if( it_new == mp.begin() )
                        break;
                    --it_new;
                }
            }
        }

        return mem[pos][rem] = ret;
    }

public:
    string largestMultipleOfThree(vector<int>& digits) {
        int n = digits.size();
        // observation (not proof)
        // the largest multiple of three, the digits are always non-increasing
        // so if we don't use all of the available of a given digits and proceed to a smaller one,
        // we don't go back and use one or more of the remaining higher ones, BUT
        // digits = {1,1,1,2} -> ans = "111" Note: 21 is also an answer, but not the best answer

        sort(digits.begin(),digits.end(),greater<int>());
        if( digits[0] == 0 )
            return "0";

        map<int,int> mp;
        int digit = 10;
        for(int i = 0; i < n; ++i) {
            if( digits[i] != digit ) {
                mp.insert({digits[i],i});
                digit = digits[i];
            }
        }

        mem = vector<vector<string>>(n,vector<string>(3,"#"));
        string ans = "";
        for(auto rit = mp.rbegin(); rit != mp.rend(); ++rit) {
            string ret = rec(digits, rit->second, 0, mp);
            if( ret.size() > ans.size() )
                ans = ret;
        }

        // trim leading zeros
        while( ans.size() > 1 && ans[0] == '0' )
            ans.erase(ans.begin());

        return ans;
    }
};
