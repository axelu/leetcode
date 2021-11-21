
// 1996. The Number of Weak Characters in the Game
// https://leetcode.com/problems/the-number-of-weak-characters-in-the-game/






class Solution {
public:
    int numberOfWeakCharacters(vector<vector<int>>& properties) {
        int n = properties.size();

        // group by attack
        map<int,int> byAttackMp; // attack,maxdefense
        pair<map<int,int>::iterator,bool> p;
        for(int i = 0; i < n; ++i) {
            p = byAttackMp.insert({properties[i][0],properties[i][1]});
            if( !p.second )
                p.first->second = max(p.first->second,properties[i][1]);
        }


        int k = byAttackMp.size();
        if( k == 1 ) // all characters have the same attack strength
            return 0;


        for(auto it = ++byAttackMp.rbegin(); it != byAttackMp.rend(); ++it)
            it->second = max(it->second,prev(it)->second);


        int ans = 0;
        map<int,int>::iterator it;
        map<int,int>::iterator itl = prev(end(byAttackMp));
        for(int i = 0; i < n; ++i) {
            it = byAttackMp.find(properties[i][0]);

            if( it == itl )
                continue;

            if( properties[i][1] < next(it)->second )
                ++ans;
        }

        return ans;
    }
};
