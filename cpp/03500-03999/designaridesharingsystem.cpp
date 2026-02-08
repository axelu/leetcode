
// 3829. Design Ride Sharing System
// https://leetcode.com/problems/design-ride-sharing-system/




class RideSharingSystem {
private:
    // doubly-linked list
    struct Node {
        int riderId;
        Node* prev;
        Node* next;
        Node(int riderId) : riderId(riderId), next(nullptr), prev(nullptr) {}
        Node(int riderId, Node *prev, Node *next) : riderId(riderId), next(next), prev(prev) {}
    };
    Node * head;
    Node * tail;
    unordered_map<int,Node*> riders; // key: riderId value: ptr to rider node
    queue<int> drivers;

    void insertRider(int riderId) {
        if( riders.find(riderId) != riders.end() )
            return; // should never happen

        Node * riderNd = new Node(riderId);
        if( tail == nullptr ) {
            head = riderNd;
            tail = riderNd;
        } else {
            riderNd->next = tail;
            tail->prev = riderNd;
            tail = riderNd;
        }
        riders.insert({riderId, riderNd});
        return;
    }

    void eraseRider(int riderId) {
        auto it = riders.find(riderId);
        if( it == riders.end() )
            return;

        Node * riderNd = it->second;
        riders.erase(it);

        // our node could be the head, the tail, or both,
        // or somewhere in our list
        if( riderNd == tail && riderNd == head ) {
            head = nullptr;
            tail = nullptr;
        } else if( riderNd == tail ) {
            tail = riderNd->next;
            riderNd->next->prev = nullptr;
        } else if( riderNd == head ) {
            head = riderNd->prev;
            riderNd->prev->next = nullptr;
        } else {
            riderNd->next->prev = riderNd->prev;
            riderNd->prev->next = riderNd->next;
        }
        delete riderNd;
        riderNd = nullptr;

        return;
    }


public:
    RideSharingSystem() {
        head = nullptr;
        tail = nullptr;
    }

    void addRider(int riderId) {
        insertRider(riderId);
        return;
    }

    void addDriver(int driverId) {
        drivers.push(driverId);
        return;
    }

    vector<int> matchDriverWithRider() {
        if( head == nullptr || drivers.empty() )
            return {-1,-1};

        // get driver
        int driverId = drivers.front();
        drivers.pop();

        // get rider
        int riderId = head->riderId;
        eraseRider(riderId);

        return {driverId, riderId};
    }

    void cancelRider(int riderId) {
        eraseRider(riderId);
        return;
    }
};

/**
 * Your RideSharingSystem object will be instantiated and called as such:
 * RideSharingSystem* obj = new RideSharingSystem();
 * obj->addRider(riderId);
 * obj->addDriver(driverId);
 * vector<int> param_3 = obj->matchDriverWithRider();
 * obj->cancelRider(riderId);
 */
