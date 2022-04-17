
// 1352. Product of the Last K Numbers
// https://leetcode.com/problems/product-of-the-last-k-numbers/



class ProductOfNumbers {
private:
    int n;
    int a[40001]; // prefix product

public:
    ProductOfNumbers() {
        n = 0;
        a[0] = 1;
    }

    void add(int num) {
        // we multiply the last 'product' with our num
        // if num == 0 all prefix products would become 0,
        // so we can wipe all of them
        if( num == 0 )
            n = 0;
        else {
            a[n+1] = a[n] * num;
            ++n;
        }
    }

    int getProduct(int k) {
        // k will only be as large as numbers have been added to our stream,
        // but if 0 appeared in the stream, we cleard the prefix products
        if( n < k )
            return 0;

        // example        2,  5,  4,   8
        // prefixProduct  1,  2, 10,  40, 320
        // k = 1 -> ans = 320/40
        // k = 2 -> ans = 320/10
        // k = 3 -> ans = 320/2
        // k = 4 -> ans = 320/1

        return a[n]/a[n-k];
    }
};

/**
 * Your ProductOfNumbers object will be instantiated and called as such:
 * ProductOfNumbers* obj = new ProductOfNumbers();
 * obj->add(num);
 * int param_2 = obj->getProduct(k);
 */
