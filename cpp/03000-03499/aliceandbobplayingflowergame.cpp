
// 3021. Alice and Bob Playing Flower Game
// https://leetcode.com/problems/alice-and-bob-playing-flower-game/






class Solution {
private:
    //int mem[100001][100001][2]; // out of memory

    enum players {Alice, Bob};

    players play(int x, int y, int player) {
        // we have a choice
        //     take from x OR
        //     take from y

        players winner;

        if( player == Alice ) { // ALice's turn
            winner = Bob;
            if( x > 0 )
                winner = play(x-1, y, 1);
            if( winner == Bob && y > 0 )
                winner = play(x, y-1, 1);
        } else { // Bob's turn
            winner = Alice;
            if( x > 0 )
                winner = play(x-1, y, 0);
            if( winner == Alice && y > 0)
                winner = play(x, y-1, 0);
        }

        return winner;
    }

public:
    long long flowerGame(int n, int m) {

        // brute force
        /*
        long long ans = 0LL;
        for(int x = 1; x <= n; ++x) {
            for(int y = 1; y <= m; ++y) {
                players winner = play(x,y,Alice); // Alice starts
                if( winner == Alice ) {
                    cout << "x " << x << " y " << y << " Alice wins" << endl;
                    ++ans;
                } else {
                    cout << "x " << x << " y " << y << " Bob wins" << endl;
                }
            }
        }
        return ans;
        */
        // observation from Brute Force approach
        //    if x == y -> Bob wins (note: same as abs(x - y) % 2 == 0 )
        //    if( abs(x - y) % 2 == 0 ) -> Bob wins
        //    else Alice wins
        // so can we calculate for a given n and m how many pairs of each we have?
        // n    | m
        // -----|-----
        // odd  | odd
        // odd  | even
        // even | odd
        // even | even
        // if n is odd
        //     we have n/2 ceiling odd x
        //     we have n/2 even x
        //     if m is odd
        //        we have m/2 ceiling odd y
        //        -> odd x * odd y pairs with even difference -> Bob wins
        //        we have m/2 even y's
        //        -> odd x * even y pairs with odd difference -> Alice wins
        //     if m is even
        //        we have m/2 odd y
        //        -> odd x * odd y pairs with even difference -> Bob wins
        //        we have m/2 even y
        //        -> odd x * even y pairs with odd difference -> Alice wins
        // if n is even
        //     we have n/2 odd x's
        //     we have n/2 even x's
        //     ...

        long long odd_x = ceil(n/2.0);
        long long even_x = n/2;

        long long odd_y = ceil(m/2.0);
        long long even_y = m/2;

        return odd_x * even_y + even_x * odd_y;    
    }
};
