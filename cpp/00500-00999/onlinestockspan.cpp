
// 901. Online Stock Span
// https://leetcode.com/problems/online-stock-span/



class StockSpanner {
private:
    int i;
    stack<array<int,2>> stck; // monotonic stack
public:
    StockSpanner() {
        i = 0;
    }

    int next(int price) {
        while( !stck.empty() && stck.top()[0] <= price )
            stck.pop();
        int t = stck.empty() ? i + 1 : i - stck.top()[1];

        stck.push({price,i});
        ++i;

        return t;
    }
};

/**
 * Your StockSpanner object will be instantiated and called as such:
 * StockSpanner* obj = new StockSpanner();
 * int param_1 = obj->next(price);
 */
