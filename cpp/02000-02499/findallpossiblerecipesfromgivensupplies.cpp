
// 2115. Find All Possible Recipes from Given Supplies
// https://leetcode.com/problems/find-all-possible-recipes-from-given-supplies/




// see 802. Find Eventual Safe States https://leetcode.com/problems/find-eventual-safe-states/

class Solution {
private:
    int dfs(vector<int> g[], int u, int seen[], int canmake[]) {
        // dfs on graph starting at u
        // returns 0 if u is canmake, 1 if u is canmake

        // have we seen u already during a different exploration?
        if( canmake[u] != -1 )
            return canmake[u];

        // if we have seen u already in our current path,
        // then we have a cycle and with that,
        // any node in the path that got us here we cannot make
        if( seen[u] )
            return 0;

        seen[u] = 1;

        int ret = 1;
        for(int i = 0; i < g[u].size(); ++i) {
            int v = g[u][i];
            int t = dfs(g,v,seen,canmake);
            if( t == 0 )
                ret = 0;
        }

        return canmake[u] = ret;
    }

public:
    vector<string> findAllRecipes(vector<string>& recipes, vector<vector<string>>& ingredients, vector<string>& supplies) {
        // values of recipes and supplies combined are unique
        // lets assume those form the nodes in a graph
        // supplies are terminal nodes aka leaf nodes

        // -1 unseen, 0 cannot make, 1 can make
        int n = recipes.size() + supplies.size();
        int canmake[n];memset(canmake,-1,sizeof canmake);

        unordered_map<string,int> dic;

        // add recipes to dictionary
        int i = 0;
        for(; i < recipes.size(); ++i)
            dic.insert({recipes[i],i});
        // add supplies to dictionary
        for(int j = 0; j < supplies.size(); ++j) {
            dic.insert({supplies[j],i});
            canmake[i] = 1;
        }

        // directed graph
        vector<int> g[n];
        for(int u = 0; u < ingredients.size(); ++u)
            for(auto& ingredient : ingredients[u]) {
                // the ingredient can be a supply or a recipe
                // or may not be either, in which case we cannot make the recipe
                auto f = dic.find(ingredient);
                if( f != dic.end() ) {
                    int v = f->second;
                    g[u].push_back(v);
                } else {
                    canmake[u] = 0;
                }
            }

        vector<string> ans;

        // our graph can have cycles -> those recipes we cannot make
        int seen[n];
        for(int u = 0; u < recipes.size(); ++u)
            if( canmake[u] == -1 ) {
                memset(seen,0,sizeof seen);
                if( dfs(g,u,seen,canmake) )
                    ans.push_back(recipes[u]);
            } else if( canmake[u] == 1 ) {
                ans.push_back(recipes[u]);
            }

        return ans;
    }
};
