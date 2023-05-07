
// 481. Magical String
// https://leetcode.com/problems/magical-string/



class Solution {
public:
    int magicalString(int n) {
        // example
        // "1221121221221121122……""
        // grouped "1 22 11 2 1 22 1 22 11 2 11 22 ......"
        //         "1 2  2  1 1 2  1 2  2  1 2  2 ......"

        if( n <= 3 )
            return 1;

        int ans = 1; // 1 because t[0] is our 1st 1

        vector<int> t(n+2);
        t[0] = 1;
        t[1] = 2;
        t[2] = 2;

        int i = 3; // index at which we write the current group
        int j = 2; // index that gives us the count of elements in the current group

        while(i<n) {
            // get if current group is group of 1s or 2s from prior group
            int c = t[i-1] == 1 ? 2 : 1;
            t[i] = c;
            if( c == 1 ) ++ans;
            ++i;
            if( t[j] == 2 ) {
                t[i] = c;
                if( c == 1 && i < n ) ++ans;
                ++i;
            }
            ++j;
        }

        /*
        for(int i = 0; i < n; ++i) {
            cout << t[i];
        }
        cout << endl;
        */



        return ans;
    }
};
