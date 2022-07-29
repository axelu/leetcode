
// 913. Cat and Mouse
// https://leetcode.com/problems/cat-and-mouse/

class Solution {
private:
    int mem[401][50][50];
    
    // DFS
    int play(vector<vector<int>> &g , int n, int mousePos, int catPos, int player, int turn) {
        // return 0 draw, 1 mouse win, 2 cat win
        // player 0 mouse, player 1 cat
        
        // using number of turns as circuit breaker to detect draw
        if( turn >= 8*n )        return mem[turn][mousePos][catPos]  = 0; // draw
        if( mousePos == 0 )      return mem[turn][mousePos][catPos]  = 1; // mouse win
        if( mousePos == catPos ) return mem[turn][mousePos][catPos]  = 2; // cat win

        if( mem[turn][mousePos][catPos] != -1) 
            return mem[turn][mousePos][catPos];

        int res,newMousePos,newCatPos;
        bool draw = false;
        if( player == 0 ) { 
            // mouse turn
            // where can the mouse go from its current position
            for(int i = 0; i < g[mousePos].size(); ++i) {
                newMousePos = g[mousePos][i];
                res = play(g,n,newMousePos,catPos,1,turn+1);
                if( res == 1 )                              // mouse win
                    return mem[turn][mousePos][catPos] = 1; // play optimally
                if( res == 0 ) 
                    draw = true;
            }
            if( !draw ) 
                return mem[turn][mousePos][catPos] = 2;
            else
                return mem[turn][mousePos][catPos] = 0;
        
        } else { 
            // cat turn
            // where can the cat go from its current position
            for(int i = 0; i < g[catPos].size(); ++i) {
                newCatPos = g[catPos][i];
                if( newCatPos == 0 ) continue; // cat cannot go to hole
                res = play(g,n,mousePos,newCatPos,0,turn+1);
                if( res == 2 )                                // cat win
                    return mem[turn][mousePos][catPos] = 2;  // play optimally
                if( res == 0 ) 
                    draw = true;
            }
            if( !draw ) 
                return mem[turn][mousePos][catPos] = 1;
            else
                return mem[turn][mousePos][catPos] = 0;
        }
    }
    
public:
    int catMouseGame(vector<vector<int>>& g) {
        // 3 <= graph.length <= 50
        int n = g.size();
        memset(mem,-1,sizeof mem);
        return play(g,n,1,2,0,0);
    }
};
