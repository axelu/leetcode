
// 1244. Design A Leaderboard
// https://leetcode.com/problems/design-a-leaderboard/


class Leaderboard {
private:
    unordered_map<int,int> players; // playerId,score
    multiset<int> scores;
public:
    Leaderboard() {

    }

    void addScore(int playerId, int score) {
        auto f = players.find(playerId);
        if( f == players.end() ) {
            players.insert({playerId,score});
            scores.insert(score);
        } else {
            scores.erase(scores.find(f->second));
            f->second += score;
            scores.insert(f->second);
        }
    }

    int top(int K) {
        // it's guaranteed that K is less than or equal
        // to the current number of players
        int ans = 0;
        auto it = scores.rbegin();
        for(int i = 0; i < K; ++i) {
            ans += *it;
            ++it;
        }
        return ans;
    }

    void reset(int playerId) {
        // it is guaranteed that the player was added
        // to the leaderboard before calling this function
        auto f = players.find(playerId);
        scores.erase(scores.find(f->second));
        players.erase(playerId);
    }
};

/**
 * Your Leaderboard object will be instantiated and called as such:
 * Leaderboard* obj = new Leaderboard();
 * obj->addScore(playerId,score);
 * int param_2 = obj->top(K);
 * obj->reset(playerId);
 */
