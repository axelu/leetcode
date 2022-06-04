
// 1562. Find Latest Group of Size M
// https://leetcode.com/problems/find-latest-group-of-size-m/



class Solution {
private:
    bool solve(map<int,int>& mp, int i, int m) {
        // at each invokation we will split a group of 1s at index i
        auto it = mp.lower_bound(i);
        if( it != mp.end() && it->first == i ) {
            int l = it->second;
            if( l == 1 ) {
                mp.erase(it);
                return false;
            } else {
                if( l-1 == m )
                    return true;
                mp.erase(it);
                mp.insert({i+1,l-1});
                return false;
            }
        }

        // we need to split this current group of 1s
        --it;
        int s = it->first;  // start of current group of 1s
        int l = it->second; // length of current group of 1s
        // left
        int ll = i - s;
        if( ll == m )
            return true;
        // right
        int rl = s + l - 1 - i;
        if( rl == m )
            return true;
        // insert update/erase left group and new add right group of 1s
        if( ll == 0 ) {
            mp.erase(it);
        } else {
            it->second = ll;
        }
        // insert right group
        if( rl > 0 )
            mp.insert({i+1,rl});

        return false;
    }

public:
    int findLatestStep(vector<int>& arr, int m) {
        int n = arr.size();
        if( n == m ) // all steps must be executed
            return n;

        // at the end we have one group of ones of length n starting at index 0
        map<int,int> mp{{0,n}}; // index,length
        for(int i = n-1; i >= 0; --i) {
            if( solve(mp,arr[i]-1,m) )
                return i;
        }
        return -1;
    }
};
