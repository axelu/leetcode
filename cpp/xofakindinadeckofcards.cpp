
// 914. X of a Kind in a Deck of Cards
// https://leetcode.com/problems/x-of-a-kind-in-a-deck-of-cards/




class Solution {
private:
    // greatest common denominator
    int gcd(int a, int b) {
        if (a == 0)
            return b;
        return gcd(b % a, a);
    }

public:
    bool hasGroupsSizeX(vector<int>& deck) {
        int n = deck.size();

        // can we choose an X >= 2 such that
        // deck is split int 1 or groups
        // - each group has exactly x cards
        // - all the cards in the group have the same integer

        if( n == 1 ) return false;

        int cnt[10000]; memset(cnt,0,sizeof cnt);
        int i, j, mn = INT_MAX, mx = 0;
        for(i = 0; i < n; ++i)
            ++cnt[deck[i]];

        unordered_set<int> counts;
        for(i = 0; i < 10000; ++i) {
            if( cnt[i] == 1 ) return false;
            counts.insert(cnt[i]);
        }

        if( counts.size() == 1 ) return true;

        // list of common divisors of counts
        unordered_set<int> divisors;
        int g = *counts.begin(); // GCD of counts
        for(auto it = next(counts.begin()); it != counts.end(); ++it)
            g = gcd(*it, g);

        for(i = 1; i * i <= g; ++i)
            if( g % i == 0 ) {
                divisors.insert(i);
                if( g/i != i )
                    divisors.insert(g/i);
            }

        // 1 is always a divisor, but we are looking for a divisor >= 2
        return divisors.size() != 1;
    }
};
