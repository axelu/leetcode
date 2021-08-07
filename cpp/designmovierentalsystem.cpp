
// 1912. Design Movie Rental System
// https://leetcode.com/problems/design-movie-rental-system/





class MovieRentingSystem {
private:
    struct ShopPrice { int shop,price; };

    struct ShopPriceCmp {
        bool operator()(const ShopPrice& a, const ShopPrice& b) const {
            if( a.price < b.price ) {
                return true;
            } else if( a.price == b.price ) {
                if( a.shop < b.shop )
                    return true;
            }
            return false;
        }
    };

    unordered_map<int,set<ShopPrice,ShopPriceCmp>> unrented; // key: movie

    struct ShopMoviePrice { int shop,movie,price; };

    struct ShopMoviePriceCmp {
        bool operator()(const ShopMoviePrice& a, const ShopMoviePrice& b) const {
            if( a.price < b.price ) {
                return true;
            } else if( a.price == b.price ) {
                if( a.shop < b.shop ) {
                    return true;
                } else if( a.shop == b.shop) {
                    if( a.movie < b.movie)
                        return true;
                }
            }
            return false;
        }
    };

    set<ShopMoviePrice,ShopMoviePriceCmp> rented;

    map<array<int,2>,int> MovieShopPrice; // key:movie,shop value:price


public:
    MovieRentingSystem(int n, vector<vector<int>>& entries) {
        int shop,movie,price;
        for(int i = 0; i < entries.size(); ++i) {
            shop  = entries[i][0];
            movie = entries[i][1];
            price = entries[i][2];

            MovieShopPrice[{movie,shop}] = price;
            unrented[movie].insert({shop,price});
       }
    }

    vector<int> search(int movie) {
        // unrented movies

        vector<int> ans;

        auto f = unrented.find(movie);
        if( f == unrented.end() )
            return ans;


        int i = 0;
        for(auto it = f->second.begin(); it != f->second.end(); ++it) {
            ans.push_back((*it).shop);
            if( ++i == 5 )
                break;
        }
        return ans;
    }

    void rent(int shop, int movie) {
        int price = MovieShopPrice[{movie,shop}];

        auto f = unrented.find(movie);
        f->second.erase({shop,price});

        rented.insert({shop,movie,price});
    }

    void drop(int shop, int movie) {
        int price = MovieShopPrice[{movie,shop}];

        MovieShopPrice[{movie,shop}] = price;
        unrented[movie].insert({shop,price});

        rented.erase({shop,movie,price});
    }

    vector<vector<int>> report() {
        // rented movies

        vector<vector<int>> ans;

        int i = 0;
        for(auto it = rented.begin(); it != rented.end(); ++it) {
            ans.push_back({(*it).shop,(*it).movie});
            if( ++i == 5 )
                break;
        }

        return ans;
    }
};

/**
 * Your MovieRentingSystem object will be instantiated and called as such:
 * MovieRentingSystem* obj = new MovieRentingSystem(n, entries);
 * vector<int> param_1 = obj->search(movie);
 * obj->rent(shop,movie);
 * obj->drop(shop,movie);
 * vector<vector<int>> param_4 = obj->report();
 */
