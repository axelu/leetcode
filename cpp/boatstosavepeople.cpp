
// 881. Boats to Save People
// https://leetcode.com/problems/boats-to-save-people/
// day 13 January 2021 challenge
// https://leetcode.com/explore/challenge/card/january-leetcoding-challenge-2021/580/week-2-january-8th-january-14th/3602/


class Solution {
public:
    int numRescueBoats(vector<int>& people, int limit) {
        size_t n = people.size();
        if( 1 == n ) return 1;

        map<int,int> m; // weight of person, number of people with that weight
        pair<map<int,int>::iterator,bool> p;
        for(int i = 0; i < n; ++i) {
            p = m.insert({people[i],1});
            if( !p.second ) ++p.first->second;
        }

        int ans = 0;
        int peopleRescued = 0;
        int remainingCapacity; // per boat
        map<int,int>::reverse_iterator itf;
        map<int,int>::iterator f;
        // greedy
        for(auto it = m.rbegin(); it != m.rend(); ++it) {
            remainingCapacity = limit - it->first;
            while( it->second > 0 ) { // there are people of this weight to be rescued
                ++ans;
                ++peopleRescued;
                if( peopleRescued == n ) break; // all people rescued?
                --it->second;
                if( remainingCapacity > 0 ) {
                    // find the heaviest person who fits in this boat
                    if( remainingCapacity <= it->first ) {
                        f = m.lower_bound(remainingCapacity);
                        if( f->first > remainingCapacity ) {
                            if( f == begin(m) ) {
                                itf = m.rend();
                            } else {
                                // convert to reverse iterator
                                f = prev(f);
                                itf = map<int,int>::reverse_iterator(next(f));
                            }
                        } else {
                            // convert to reverse iterator
                            itf = map<int,int>::reverse_iterator(next(f));
                        }
                    } else {
                        itf = it;
                    }
                    for(;itf != m.rend(); ++itf)
                        if( itf->second > 0 ) break;
                    // itf now points to a person who fits in this boat
                    if( itf != m.rend() ) {
                        --itf->second;
                        ++peopleRescued;
                    }
                }
            }
            if( peopleRescued == n ) break; // all people rescued?
        }

        return ans;
    }
};
