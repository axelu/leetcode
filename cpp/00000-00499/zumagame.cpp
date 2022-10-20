
// 488. Zuma Game
// https://leetcode.com/problems/zuma-game/



class Solution {
private:
    void consolidate(string& s) {
        //cout << "consolidate " << s << endl;
        char pre = '#';
        int cnt = 0;
        int i = 0;
        for(; i < s.size(); ++i) {
            if( s[i] == pre )
                ++cnt;
            else {
                pre = s[i];
                if( cnt >= 3 ) {
                    i -= cnt;
                    s.erase(i,cnt);
                    // re-position i
                    if( i > 0 ) {
                        --i;
                        pre = s[i];
                    }
                    if( i > 0 ) {
                        --i;
                        pre = s[i];
                    }
                }
                cnt = 1;

            }
        }
        // finish up
        if( cnt >= 3 ) {
            i -= cnt;
            s.erase(i,cnt);
        }
        //cout << "consolidate result " << s << endl;
        return;
    }

public:
    int findMinStep(string board, string hand) {

        unordered_map<char,int>  dic{{'R',0},{'Y',1},{'B',2},{'G',3},{'W',4}};
        unordered_map<int,char> rdic{{0,'R'},{1,'Y'},{2,'B'},{3,'G'},{4,'W'}};

        size_t initial_hand_sz = hand.size();
        vector<int> initial_hand(5,0);
        for(char c: hand)
            ++initial_hand[getIndx(c)];

        // board, nbr balls in hand, balls in hand
        struct T {
            string board;
            size_t nbr_balls;
            vector<int> balls;
            T(string b, size_t n, vector<int> balls) : board(b), nbr_balls(n), balls(balls) {}
        };

        // BFS

        auto cmp = [](const T& a, const T& b) {
            if( a.nbr_balls < b.nbr_balls ) {
                return true;
            } else if( a.nbr_balls == b.nbr_balls ) {
                if( a.board.size() > b.board.size() ) {
                    return true;
                }
            }
            return false;
        };
        priority_queue<T,vector<T>,decltype(cmp)> pq(cmp);
        pq.push({board,initial_hand_sz,initial_hand});
        unordered_set<string> seen;
        seen.insert(board);
        while( !pq.empty() ) {
            T t = pq.top();
            pq.pop();

            consolidate(t.board);
            if( t.board.size() == 0 )
                return initial_hand_sz - t.nbr_balls;

            if( t.nbr_balls == 0 )
                continue;

            // we can insert any ball we have at any position
            // but lets insert only around like kind char
            for(int i = 0; i < t.board.size(); ++i) {
                char c = t.board[i];
                int k = dic[c];
                if( i == 0 || t.board[i-1] != t.board[i] ) {
                    if( t.balls[k] != 0 ) {
                        --t.balls[k];
                        t.board.insert(i,1,c);
                        if( seen.insert(t.board).second )
                            pq.push({t.board,t.nbr_balls-1,t.balls});

                        // backtrack
                        t.board.erase(i,1);
                        ++t.balls[k];
                    }

                } else { // t.board[i-1] == t.board[i]
                    // let's break up a group of two
                    for(int j = 0; j < 5; ++j) {
                        if( j == k )
                            continue;
                        if( t.balls[j] != 0 ) {
                            --t.balls[j];
                            t.board.insert(i,1,rdic[j]);
                            if( seen.insert(t.board).second )
                                pq.push({t.board,t.nbr_balls-1,t.balls});

                            // backtrack
                            t.board.erase(i,1);
                            ++t.balls[j];
                        }
                    }
                }
            }

        }

        return -1;
    }
};
