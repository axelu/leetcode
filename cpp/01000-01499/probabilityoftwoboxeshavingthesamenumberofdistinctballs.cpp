

// 1467. Probability of a Two Boxes Having The Same Number of Distinct Balls
// https://leetcode.com/problems/probability-of-a-two-boxes-having-the-same-number-of-distinct-balls/






class Solution {
private:
    // number of combinations
    // Returns factorial of n
    double fact(int n) {
        double res = 1;
        for (int i = 2; i <= n; i++)
            res = res * i;
        return res;
    }

    double nCr(int n, int r) {
        return fact(n) / (fact(r) * fact(n - r));
    }

    int nbr_colors;
    int nbr_balls;
    int * _balls;

    double same,diff;

    double perms(vector<int>& box) {
        double ret = 1;
        int n = nbr_balls / 2;
        for(int i = 0; i < nbr_colors - 1; ++i) {
            ret *= nCr(n,box[i]);
            n -= box[i];
        }
        return ret;
    }

    void rec(int idx_colors, vector<int>& box1, int nbr_balls_box1) {
        //  cout << "rec idx_colors " << idx_colors << endl;

        if( nbr_balls_box1 == nbr_balls / 2 ) {
            // construct box2 from balls and box1
            vector<int> box2(nbr_colors,0);
            for(int i = 0; i < nbr_colors; ++i)
                box2[i] = _balls[i] - box1[i];

            // calculate the nbr of distinct colors
            int c1 = 0; // nbr of distinct colors in box1
            int c2 = 0; // nbr of distinct colors in box2
            for(int i = 0; i < nbr_colors; ++i) {
                if( box1[i] > 0 )
                    ++c1;
                if( box2[i] > 0)
                    ++c2;
            }

            // as our balls will be shuffled, we need to figure out
            // the number of possible arrangements between box1 and box2
            double a = perms(box1);
            double b = perms(box2);

            if( c1 == c2 )
                same += a * b;
            else
                diff += a * b;

            return;
        }

        if( idx_colors == nbr_colors )
            return;

        // put between 0 and balls[idx_colors] balls into box1
        for(int i = 0; i <= _balls[idx_colors]; ++i) {
            // no point putting more than half the balls into box1
            if( nbr_balls_box1 + i > nbr_balls / 2 )
                break;

            box1[idx_colors] = i;
            rec(idx_colors + 1,box1,nbr_balls_box1+i);
            // backtrack
            box1[idx_colors] = 0;
        }
    }

public:
    double getProbability(vector<int>& balls) {
        nbr_colors = balls.size();

        nbr_balls = 0;
        for(int& x: balls)
            nbr_balls += x;

        // we have a valid split of balls in box1 and box2 if:
        //     nbr balls box1  =  nbr balls box 2  =  nbr balls total / 2  AND
        //     nbr of distinct colors in box 1  =  nbr of distinct colors in box 2

        same = 0;
        diff = 0;

        _balls = balls.data();
        vector<int> box1(nbr_colors,0); // no need to keep track of box2
        rec(0,box1,0);

        return same / (same+diff);
    }
};
