
// 3477. Fruits Into Baskets II
// https://leetcode.com/problems/fruits-into-baskets-ii/





class Solution {
public:
    int numOfUnplacedFruits(vector<int>& fruits, vector<int>& baskets) {
        int n = fruits.size(); // fruits.size() == baskets.size(); 1 <= n <= 100

        // brute force due to small constraints
        for(int i = 0; i < n; ++i) {
            int required_capacity = fruits[i];

            auto it = baskets.begin();
            for(; it != baskets.end(); ++it)
                if( *it >= required_capacity )
                    break;
            if( it != baskets.end() )
                baskets.erase(it);
        }

        return baskets.size();
    }
};
