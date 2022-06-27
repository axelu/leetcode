
// 975. Odd Even Jump
// https://leetcode.com/problems/odd-even-jump/



class Solution {
private:
    int ans;

    int rec(int jump[][2], int n, int i, int k, int can[][2]) {
        // k == 1 odd-numbered jump, k == 0 even-numbered jump

        if( i == n-1 )
            return 1;

        if( jump[i][k] == -1 )
            return 0;

        if( can[i][k] != -1 )
            return can[i][k];

        int t = rec(jump,n,jump[i][k],!k,can);
        if( t && k == 1 && can[i][k] != 1 )
            ++ans;
        return can[i][k] = t;
    }

public:
    int oddEvenJumps(vector<int>& arr) {
        int n = arr.size(); // 1 <= arr.length <= 2 * 10^4
        // cout << "n " << n << endl;

        // let t[i][0] be the jump target when jump is even-numbered
        // let t[i][1] be the jump target when jump is odd-numbered
        // if t[i][0] or t[i][1] is -1, no jump is possible
        int jump[n][2]; // n-1 is irrelevant TODO shorten to jump[n-1][2]

        // we will fill a vector while going through arr from right to left
        // with values encountered in arr in ascending order
        // if the same value encountered multiple times, the smallest index
        // (because we are going right to left it will be the smallest index)
        // will be left most
        // example:     0 1 2 3 4
        //          arr[2,3,1,1,4]
        //          v[[1,2],[1,3],[2,0],[3,1],[4,4]]

        map<int,int> mp;
        mp[arr[n-1]] = n-1;
        for(int i = n-2; i >= 0; --i) {
            // cout << "i " << i << endl;

            // odd-numbered jump:
            //     arr[i] <= arr[j] and arr[j] is the smallest possible value
            //     multiple such indices j, jump to the smallest such index j
            auto lb = mp.lower_bound(arr[i]);
            jump[i][1] = lb == mp.end() ? -1 : lb->second;

            // even-numbered jump:
            //     arr[i] >= arr[j] and arr[j] is the largest possible value
            //     multiple such indices j, jump to the smallest such index j
            if( lb == mp.end() )
                jump[i][0] = mp[prev(lb)->first];
            else if( lb == mp.begin() && lb->first > arr[i] )
                jump[i][0] = -1;
            else if( lb->first > arr[i] )
                jump[i][0] = mp[prev(lb)->first];
            else
                jump[i][0] = mp[lb->first];

            mp[arr[i]] = i;
        }

        /*
        for(auto p : v)
            cout << p[0] << "," << p[1] << " ";
        cout << endl;
        */
        // cout << "s.size() " << s.size() << endl;
        /*
        cout << "odd jump" << endl;
        for(int i = 0; i < n; ++i)
            cout << i << ":" << jump[i][1] << " ";
        cout << endl;
        cout << "even jump" << endl;
        for(int i = 0; i < n; ++i)
            cout << i << ":" << jump[i][0] << " ";
        cout << endl;
        */

        ans = 0;
        int can[n][2];memset(can,-1,sizeof can);
        for(int i = 0; i < n-1; ++i)
            if( can[i][1] == -1 )
                rec(jump,n,i,1,can);

        return ans + 1; // +1 as we can start from n-1 also
    }
};
