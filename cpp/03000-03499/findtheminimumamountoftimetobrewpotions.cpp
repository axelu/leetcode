
// 3494. Find the Minimum Amount of Time to Brew Potions
// https://leetcode.com/problems/find-the-minimum-amount-of-time-to-brew-potions/





class Solution {
public:
    long long minTime(vector<int>& skill, vector<int>& mana) {
        int n = skill.size();   // number wizards
        int m = mana.size();    // number potions
        // 1 <= n, m <= 5000; 1 <= mana[i], skill[i] <= 5000
        // time take by the ith wizard on the jth potion is timeij = skill[i] * mana[j]

        // edge case: only one wizard
        if( n == 1 ) {
            long long t = 0LL;
            for(int potion = 0; potion < m; ++potion)
                t += (long long)(skill[0] * mana[potion]);
            return t;
        }

        vector<long long> pre(n, 0LL); // start times
        vector<long long> * ptr_pre = &pre;
        // the 1st wizard (wizard 0) always starts to 1st potion (potion 0) at time 0
        // potion 0
        for(int wizard = 0; wizard < n-1; ++wizard) {
            // when is the current wizard done by? that is when the next wizard can start.
            long long t = pre[wizard] + (long long)(skill[wizard] * mana[0]);
            pre[wizard+1] = t;
        }

        // debug
        /*
        cout << "potion 0 " << endl;
        for(int i = 0; i < n; ++i) {
            cout << "wizard " << i << " start " << ptr_pre->at(i) << " ";
            long long  d = (long long)(skill[i] * mana[0]);
            cout << "done by " << ptr_pre->at(i) + d << "; ";
        }
        cout << endl;
        */

        // edge case: only one potion
        if( m == 1 )
            return pre[n-1] + (long long)(skill[n-1] * mana[0]);


        vector<long long> cur(n, 0LL);
        vector<long long> * ptr_cur = &cur;
        for(int potion = 1; potion < m; ++potion) {
            long long delay = 0;
            for(int wizard = 0; wizard < n; ++wizard) {
                // our current wizard could start the earliest with the current potion
                //   when either she is done with the prior potion OR
                //   when the wizard in front of us is done with the current potion
                // whichever is later
                long long start1 = ptr_pre->at(wizard) + (long long)(skill[wizard] * mana[potion-1]);
                if( wizard == 0 ) {
                    ptr_cur->at(0) = start1;
                    continue;
                }
                long long start2 = ptr_cur->at(wizard-1) + (long long)(skill[wizard-1] * mana[potion]);
                ptr_cur->at(wizard) = max(start1, start2);
            }
            // adjust start times cur
            // we know that ptr_cur->at(n-1) is the best possible start time for wizard n-1
            // we need to go backwards and close all gaps
            for(int wizard = n-2; wizard >= 0; --wizard) {
                long long t = (long long)(skill[wizard] * mana[potion]);
                ptr_cur->at(wizard) = ptr_cur->at(wizard+1) - t;
            }

            // debug
            /*
            cout << "potion " << potion << endl;
            for(int i = 0; i < n; ++i) {
                cout << "wizard " << i << " start " << ptr_cur->at(i) << " ";
                long long  d = (long long)(skill[i] * mana[potion]);
                cout << "done by " << ptr_cur->at(i) + d << "; ";
            }
            cout << endl;
            */

            swap(ptr_pre, ptr_cur);
        }

        return ptr_pre->at(n-1) + (long long)(skill[n-1] * mana[m-1]);
    }
};
