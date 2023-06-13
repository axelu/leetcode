

// 2353. Design a Food Rating System
// https://leetcode.com/problems/design-a-food-rating-system/




class FoodRatings {

    unordered_map<string,array<int,2>> _foods;  // food: cuisine_id, rating
    unordered_map<string,int> _cuisines;        // cuisine: cuisine_id

    vector<map<int,set<string>>> _rated_foods;  // index is cuisine_id: rating: foods

public:
    FoodRatings(vector<string>& foods, vector<string>& cuisines, vector<int>& ratings) {
        int n = foods.size(); // foods.size == cuisines.size == ratings.size

        int cuisine_id = 0;
        for(int i = 0; i < n; ++i) {
            int cid;
            auto p = _cuisines.insert({cuisines[i],cuisine_id});
            if( !p.second ) {
                // food is in an existing cuisine
                cid = p.first->second;
                _rated_foods[cid][ratings[i]].insert(foods[i]);

            } else {
                // food is in a new cuisine
                cid = cuisine_id++;
                _rated_foods.push_back({{ratings[i],{foods[i]}}});
            }

            _foods[foods[i]] = {cid,ratings[i]};
        }

    }

    void changeRating(string food, int newRating) {
        auto f = _foods.find(food);
        int old_rating = f->second[1];
        int cid = f->second[0];

        auto itrf = _rated_foods.begin();
        advance(itrf,cid); // itrf pointer to cuisine map in _rated_foods

        // remove food from current rating
        itrf->at(old_rating).erase(food);
        if( itrf->at(old_rating).empty() )
            itrf->erase(old_rating);

        // add food to new rating
        auto p = itrf->insert({newRating,{food}});
        if( !p.second )
            p.first->second.insert(food);

        // update food
        f->second[1] = newRating;
    }

    string highestRated(string cuisine) {
        int cid = _cuisines.find(cuisine)->second;
        auto itrf = _rated_foods.begin();
        advance(itrf,cid); // itrf pointer to cuisine map in _rated_foods

        return *itrf->rbegin()->second.begin();
    }
};

/**
 * Your FoodRatings object will be instantiated and called as such:
 * FoodRatings* obj = new FoodRatings(foods, cuisines, ratings);
 * obj->changeRating(food,newRating);
 * string param_2 = obj->highestRated(cuisine);
 */
