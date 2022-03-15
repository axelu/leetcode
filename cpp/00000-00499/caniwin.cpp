
// 464. Can I Win
// https://leetcode.com/problems/can-i-win/

class Solution {
private:
    int n,mx;
    
    // bool play(int score, int state, int player, int mem[][2]) {
    bool play(int score, int state, int player, int mem[]) {    
        // cout << "player " << player << " score " << score << endl;
        // state is bit mask of available integers
        // player 0 is the player starting, return true if 0 wins
        // player 1 is the other player, return false if 1 wins
        
        // play optimally:
        // if there is one move the current player can make that
        // gets her the win, she will make that move
        
        if( score >= mx ) // current player looses
            return player;
        
        // if( mem[state][player] != -1 )
        //    return mem[state][player];        
        if( mem[state] != -1 )
            return mem[state];

        
        // if( state == 0 ) // player 0 does not win, in fact really no one wins
        //   return false;
        
        if( player == 1 ) {
            for(int i = 0; i < n; ++i) {
                if( (state >> i) & 1 ) {
                    state &= ~(1 << i);
                    bool f = play(score+i+1,state,0,mem);
                    if( !f )
                        // return mem[state][player] = false;
                        return mem[state] = false;
                    // backtrack
                    state |= 1 << i;
                }
            }
            // return mem[state][player] = true;
            return mem[state] = true;
        } else {
             for(int i = 0; i < n; ++i) {
                if( (state >> i) & 1 ) {
                    state &= ~(1 << i);
                    bool f = play(score+i+1,state,1,mem);
                    if( f )
                        // return mem[state][player] = true;
                        return mem[state] = true;
                    // backtrack
                    state |= 1 << i;
                }
            }
            // return mem[state][player] = false;
            return mem[state]= false;
        }
        
    }
        
public:
    bool canIWin(int maxChoosableInteger, int desiredTotal) {
        // 1 <= maxChoosableInteger <= 20
        if( desiredTotal == 0 )
            return true;
        
        
        n  = maxChoosableInteger;
        mx = desiredTotal;
                
        int state = pow(2,maxChoosableInteger) - 1;
        // int mem[state+1][2];memset(mem,-1,sizeof mem);
        int mem[state+1];memset(mem,-1,sizeof mem);
        // mem[0][0] = 0;
        // mem[0][1] = 0;
        mem[0] = 0;
        return play(0,state,0,mem); // player 0 starts
    }
};
