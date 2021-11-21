
// 1227. Airplane Seat Assignment Probability
// https://leetcode.com/problems/airplane-seat-assignment-probability/





/*
 * n = 1 -> ans = 1.0
 * the first person can only get the first seat
 *
 * n = 2 -> ans = 0.5
 * the first person can get seat 1 or seat 2.
 * case: first person takes seat 1, then second person gets her seat: probability = 1
 * case: first person takes seat 2, then second person's chance to get her seat is zero: probability = 0
 * answer for total probability: (1+0)/2 = .5
 *
 * n = 3 -> ans = 0.5
 * the first person can get seat 1, 2 or 3.
 * case: first person takes seat 1, then second person takes her seat and third person takes her seat: probability = 1
 * case: first person takes seat 2, then second person will take either seat 1 or seat 3,
 *       so the probability for third person to get her seat is 0.5.
 * case: first person takes seat 3, then second person takes her assigned seat, which is seat 2, and
 *       the third person has to take seat 1, so the probability for third person to get her seat is 0.
 * answer for total probability: (1 + 0.5 + 0)/3

 * This repeats for all n > 1.
 */
class Solution {
public:
    double nthPersonGetsNthSeat(int n) {
        return n == 1 ? 1.0 : 0.5;
    }
};
