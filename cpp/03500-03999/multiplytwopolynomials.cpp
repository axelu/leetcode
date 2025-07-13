
// 3549. Multiply Two Polynomials
// https://leetcode.com/problems/multiply-two-polynomials/





/* Fast Fourier transform (FFT)
 * https://cp-algorithms.com/algebra/fft.html
 * fast multiplication of polynomials
 * can also be adapted to multiply two long numbers aka multiply large integers
 *
 * the solution below is taken straight from the above link, so that is where credits go
 */
class Solution {
private:
    using cd = complex<double>;
    const double PI = acos(-1);

    void fft(vector<cd> & a, bool invert) {
        int n = a.size();
        if (n == 1)
            return;

        vector<cd> a0(n / 2);
        vector<cd> a1(n / 2);
        for (int i = 0; 2 * i < n; i++) {
            a0[i] = a[2*i];
            a1[i] = a[2*i+1];
        }
        fft(a0, invert);
        fft(a1, invert);

        double ang = 2 * PI / n * (invert ? -1 : 1);
        cd w(1), wn(cos(ang), sin(ang));
        for (int i = 0; 2 * i < n; i++) {
            a[i] = a0[i] + w * a1[i];
            a[i + n/2] = a0[i] - w * a1[i];
            if (invert) {
                a[i] /= 2;
                a[i + n/2] /= 2;
            }
            w *= wn;
        }
    }

public:
    vector<long long> multiply(vector<int>& poly1, vector<int>& poly2) {

        vector<cd> fa(poly1.begin(), poly1.end());
        vector<cd> fb(poly2.begin(), poly2.end());
        int n = 1;
        while (n < poly1.size() + poly2.size())
            n <<= 1;
        fa.resize(n);
        fb.resize(n);

        fft(fa, false);
        fft(fb, false);
        for (int i = 0; i < n; i++)
            fa[i] *= fb[i];
        fft(fa, true);

        vector<long long> result(n);
        for (int i = 0; i < n; i++)
            result[i] = round(fa[i].real());

        int n_target = poly1.size() + poly2.size() - 1;
        while( result.back() == 0 && result.size() > n_target )
            result.pop_back();

        return result;
    }
};
