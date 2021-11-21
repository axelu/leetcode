
// 1845. Seat Reservation Manager
// https://leetcode.com/problems/seat-reservation-manager/




class SeatManager {
private:
    priority_queue<int,std::vector<int>,std::greater<int>> pq;
public:
    SeatManager(int n) {
        for(int i = 1; i <= n; ++i) pq.push(i);
    }

    int reserve() {
        int t = pq.top();
        pq.pop();
        return t;
    }

    void unreserve(int seatNumber) {
        pq.push(seatNumber);
    }
};

/**
 * Your SeatManager object will be instantiated and called as such:
 * SeatManager* obj = new SeatManager(n);
 * int param_1 = obj->reserve();
 * obj->unreserve(seatNumber);
 */
