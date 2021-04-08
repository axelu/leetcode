
// 1346. Check If N and Its Double Exist
// https://leetcode.com/problems/check-if-n-and-its-double-exist/


class Solution {
public:
    bool checkIfExist(vector<int>& arr) {
        auto n = arr.size();

        int ht[2001]; memset(ht,0,sizeof ht);

        int c,d,idx,h;
        for(int i = 0; i < n; ++i) {
            c = arr[i];

            // have we seen 2 * arr[i] ?
            d = 2 * c;
            idx = d + 1000;
            if(idx >= 0 && idx <= 2000 && ht[idx]) return true;

            // have we seen arr[i] / 2 ?
            if( c % 2 == 0 ) {
                h = c / 2;
                idx = h + 1000;
                if(ht[idx]) return true;
            }

            idx = c + 1000;
            ht[idx] = 1;
        }
        return false;
    }
};
