
// 936. Stamping the Sequence
// https://leetcode.com/problems/stamping-the-sequence/
// day 31 March 2021 challenge
// https://leetcode.com/explore/challenge/card/march-leetcoding-challenge-2021/592/week-5-march-29th-march-31st/3691/






class Solution {
public:
    vector<int> movesToStamp(string stamp, string target) {
        int ns = stamp.size();  // stamp length
        int nt = target.size(); // target length
        // 1 <= stamp.length <= target.length <= 1000

        // base case
        if( ns == nt ) {
            if( stamp != target ) return {};
            else return {0};
        }

        // we will think of the target as having been created in layers
        // whereas the creation occured from the bottom to the top.
        // each round of our while loop will attempt to peel away a layer
        // we start peeling away from the top (last layer that was applied)
        // to the bottom (first layer that was applied)
        // in each round we will try for the stamp to be placed at each index
        // and wipe out something (replace char at index with question mark)
        // till we have a round in which no changes were made,
        // meaning the stamp could not be applied anywhere, then we are done
        // if the stamp wiped out everything, we have an answer, otherwise
        // it is not possible and we return an empty answer.

        vector<int> ans;
        bool targetChanged;
        bool stampMatched;
        while(true) {
            targetChanged = false;
            for(int i = 0; i <= nt-ns; ++i) { // last index we can place the stamp is nt-ns
                stampMatched = false;
                int j;
                for(j = 0; j < ns; ++j) {
                    if( target[i+j] == '?' ) continue;
                    else if( target[i+j] != stamp[j] ) break;
                    else stampMatched = true;
                }
                // were we able to apply the entire stamp at index i?
                if(j == ns && stampMatched) {
                    targetChanged = true;
                    for(int l = i; l < ns + i; ++l)
                        target[l] = '?';
                    ans.insert(ans.begin(),i);
                }
            }
            if( !targetChanged ) break;  // we had a round with no changes, so we are done
        }

        // did our stamp replace everything?
        for(int i = 0; i < nt; ++i)
            if (target[i] != '?') return {};

        return ans;
    }
};
