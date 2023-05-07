

// 1535. Find the Winner of an Array Game
// https://leetcode.com/problems/find-the-winner-of-an-array-game/



class Solution {
public:
    int getWinner(vector<int>& arr, int k) {

        unordered_map<int,int> wins;

        int mx = 0;

        // turn array into deque
        deque<int> dq;
        for(int x: arr) {
            dq.push_back(x);
            mx = max(mx,x);
        }


        // for(auto it = dq.begin(); it != dq.end(); ++it)
        //    cout << *it << " ";
        // cout << endl;


        while( true ) {

            int a = dq.front();
            // if the mx made it to the front, it will win
            if( a == mx )
                return a;

            dq.pop_front();

            int b = dq.front();
            dq.pop_front();

            if( a > b ) {
                ++wins[a];
                if( wins[a] == k )
                    return a;

                dq.push_front(a);
                dq.push_back(b);
            } else {
                ++wins[b];
                if( wins[b] == k )
                    return b;

                dq.push_front(b);
                dq.push_back(a);
            }
        }

        return -1; // satisfy compiler
    }
};
