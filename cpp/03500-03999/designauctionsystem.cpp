
// 3815. Design Auction System
// https://leetcode.com/problems/design-auction-system/




class AuctionSystem {
private:
    // [item][amount][user]
    unordered_map<int,map<int,set<int>>> iau;
    unordered_map<unsigned int,int> uia; // key: user<<16 + item, value: amount

    void removeBid(int userId, int itemId, int bidAmount) {
        // it is guaranteed that this bid exists
        auto fi = iau.find(itemId); // ptr to map key: amount value: set of userId's
        auto fa = fi->second.find(bidAmount); // ptr to set of userId's
        fa->second.erase(userId);
        if( fa->second.empty() ) {
            // there is no user who has a bid in itemId with bidAmount left
            fi->second.erase(fa);
            if( fi->second.empty() ) {
                // there is no bid on this item left
                iau.erase(fi);
            }
        }
        return;
    }

    void insertBid(int userId, int itemId, int bidAmount) {
        // it is guaranteed that this bid does not exists
        iau[itemId][bidAmount].insert(userId);
        return;
    }

public:
    AuctionSystem() {
    }

    void addBid(int userId, int itemId, int bidAmount) {
        // this bid may or may not exist

        // get amount of this users bid for itemId
        unsigned int key = (userId<<16) + itemId;
        auto p = uia.insert({key, bidAmount});
        if( p.second ) {
            // insert a new bid
            insertBid(userId, itemId, bidAmount);

        } else {
            // a bid already exists
            int oldAmount = p.first->second;
            removeBid(userId, itemId, oldAmount);
            insertBid(userId, itemId, bidAmount);
            p.first->second = bidAmount; // uia[key] = bidAmount;
        }
        return;
    }

    void updateBid(int userId, int itemId, int newAmount) {
        // it is guaranteed that this bid exists

        // get amount of this users bid for itemId
        unsigned int key = (userId<<16) + itemId;
        int bidAmount = uia[key];

        if( bidAmount == newAmount )
            return;

        removeBid(userId, itemId, bidAmount);
        insertBid(userId, itemId, newAmount);
        uia[key] = newAmount;

        return;
    }

    void removeBid(int userId, int itemId) {
        // it is guaranteed that this bid exists

        // get amount of this users bid for itemId
        unsigned int key = (userId<<16) + itemId;
        int bidAmount = uia[key];

        removeBid(userId, itemId, bidAmount);
        uia.erase(key);

        return;
    }

    int getHighestBidder(int itemId) {
        auto fb = iau.find(itemId);
        if( fb == iau.end() )
            return -1;

        return *(fb->second.rbegin()->second.rbegin());
    }
};

/**
 * Your AuctionSystem object will be instantiated and called as such:
 * AuctionSystem* obj = new AuctionSystem();
 * obj->addBid(userId,itemId,bidAmount);
 * obj->updateBid(userId,itemId,newAmount);
 * obj->removeBid(userId,itemId);
 * int param_4 = obj->getHighestBidder(itemId);
 */
