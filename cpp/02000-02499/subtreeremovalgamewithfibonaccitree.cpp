
// 2005. Subtree Removal Game with Fibonacci Tree
// https://leetcode.com/problems/subtree-removal-game-with-fibonacci-tree/



// from the hints
//     Sprague–Grundy theorem and the Colon Principle
//     The Grundy value of a node is the nim sum of the Grundy values of its children.
// resources
// https://en.wikipedia.org/wiki/Sprague%E2%80%93Grundy_theorem
// https://en.wikipedia.org/wiki/Hackenbush
// https://www.cs.umd.edu/~gasarch/TOPICS/nimnotes.pdf
// https://cp-algorithms.com/game_theory/sprague-grundy-nim.html
// https://www.geeksforgeeks.org/combinatorial-game-theory-set-2-game-nim/
// Nim-Sum: The cumulative XOR value of the number of coins/stones in each piles/heaps
//          at any point of the game is called Nim-Sum at that point
// Colon Principle: when branches come together at a vertex, one may replace the branches
//                  by a non-branching stalk of length equal to their nim sum.
// this is a Hackenbush game


class Solution {
public:
    bool findGameWinner(int n) {
        // 1 <= n <= 100
        // n = 1 -> Alice looses -> false
        // n = 2 -> Alice wins   -> true

        int sprague_grundy[101];
        sprague_grundy[1] = 0; // there are no child nodes, hence XOR is 0
        sprague_grundy[2] = 1; // there is one child node, hence cumulative XOR is 1

        for(int i = 3; i <= 100; ++i)
            sprague_grundy[i] = (sprague_grundy[i-1] + 1) ^ (sprague_grundy[i-2] + 1);

        /*
        for(int i = 1; i <= 100; ++i)
            cout << sprague_grundy[i] << " ";
        cout << endl;
        */

        return sprague_grundy[n] != 0;
    }
};
