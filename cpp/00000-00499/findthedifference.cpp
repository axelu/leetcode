
// 389. Find the Difference
// https://leetcode.com/explore/challenge/card/september-leetcoding-challenge/557/week-4-september-22nd-september-28th/3471/
// https://leetcode.com/problems/find-the-difference/




#include <iostream>
#include <cassert>
#include <chrono>
#include <bitset>

#include <string>
#include <unordered_map>
#include <unordered_set>
#include <iterator>
#include <utility>
#include <climits>

using namespace std;
//234567890123456789012345678901234567890123456789012345678901234567890123456789

class Solution {
public:
    char findTheDifference(string s, string t) {
        if( s.empty() ) return t[0];

        unordered_set<char> st;
        pair<unordered_set<char>::iterator,bool> p;
        auto itt = t.begin();
        for(auto its = s.begin(); its != s.end(); ++its) {
            // from string s
            p = st.insert(*its);
            if( !p.second )
                st.erase(p.first);
            // from string t
            p = st.insert(*itt);
            if( !p.second )
                st.erase(p.first);
            ++itt;
        }
        // process extra char from string t
        p = st.insert(*itt);
        if( !p.second )
            st.erase(p.first);

        return *st.begin();
    }
};

int main() {

    chrono::time_point<chrono::system_clock> start;
    chrono::time_point<chrono::system_clock> end;
    chrono::duration<double> elapsed_seconds;

    // start = chrono::system_clock::now();
    // do something
    // end = chrono::system_clock::now();
    // elapsed_seconds = end - start;
    // cout << "elapsed_seconds " << elapsed_seconds.count() << endl;

    Solution s;
    string s1;
    string s2;

    s1 = "";
    s2 = "d";
    assert(s.findTheDifference(s1,s2) == 'd');

    s1 = "abcd";
    s2 = "abcde"; // extra letter in the end (different letter)
    assert(s.findTheDifference(s1,s2) == 'e');

    s1 = "abcd";
    s2 = "bcade"; // extra letter in the end (different letter)
    assert(s.findTheDifference(s1,s2) == 'e');

    s1 = "abcd";
    s2 = "ecbda"; // extra letter in the front (different letter)
    assert(s.findTheDifference(s1,s2) == 'e');

    s1 = "abcd";
    s2 = "decab"; // extra letter in the middle (different letter)
    assert(s.findTheDifference(s1,s2) == 'e');

    s1 = "abcd";
    s2 = "bcadb"; // extra letter in the end (same letter)
    assert(s.findTheDifference(s1,s2) == 'b');

    s1 = "abcd";
    s2 = "bbcad"; // extra letter in the front (same letter)
    assert(s.findTheDifference(s1,s2) == 'b');

    s1 = "abcd";
    s2 = "bcbda"; // extra letter in the middle (same letter)
    assert(s.findTheDifference(s1,s2) == 'b');

    // case 11 of 54
    s1 = "ymbgaraibkfmvocpizdydugvalagaivdbfsfbepeyccqfepzvtpyxtbadkhmwmoswrcxnargtlswqemafandgkmydtimuzvjwxvlfwlhvkrgcsithaqlcvrihrwqkpjdhgfgreqoxzfvhjzojhghfwbvpfzectwwhexthbsndovxejsntmjihchaotbgcysfdaojkjldprwyrnischrgmtvjcorypvopfmegizfkvudubnejzfqffvgdoxohuinkyygbdzmshvyqyhsozwvlhevfepdvafgkqpkmcsikfyxczcovrmwqxxbnhfzcjjcpgzjjfateajnnvlbwhyppdleahgaypxidkpwmfqwqyofwdqgxhjaxvyrzupfwesmxbjszolgwqvfiozofncbohduqgiswuiyddmwlwubetyaummenkdfptjczxemryuotrrymrfdxtrebpbjtpnuhsbnovhectpjhfhahbqrfbyxggobsweefcwxpqsspyssrmdhuelkkvyjxswjwofngpwfxvknkjviiavorwyfzlnktmfwxkvwkrwdcxjfzikdyswsuxegmhtnxjraqrdchaauazfhtklxsksbhwgjphgbasfnlwqwukprgvihntsyymdrfovaszjywuqygpvjtvlsvvqbvzsmgweiayhlubnbsitvfxawhfmfiatxvqrcwjshvovxknnxnyyfexqycrlyksderlqarqhkxyaqwlwoqcribumrqjtelhwdvaiysgjlvksrfvjlcaiwrirtkkxbwgicyhvakxgdjwnwmubkiazdjkfmotglclqndqjxethoutvjchjbkoasnnfbgrnycucfpeovruguzumgmgddqwjgdvaujhyqsqtoexmnfuluaqbxoofvotvfoiexbnprrxptchmlctzgqtkivsilwgwgvpidpvasurraqfkcmxhdapjrlrnkbklwkrvoaziznlpor";
    s2 = "qhxepbshlrhoecdaodgpousbzfcqjxulatciapuftffahhlmxbufgjuxstfjvljybfxnenlacmjqoymvamphpxnolwijwcecgwbcjhgdybfffwoygikvoecdggplfohemfypxfsvdrseyhmvkoovxhdvoavsqqbrsqrkqhbtmgwaurgisloqjixfwfvwtszcxwktkwesaxsmhsvlitegrlzkvfqoiiwxbzskzoewbkxtphapavbyvhzvgrrfriddnsrftfowhdanvhjvurhljmpxvpddxmzfgwwpkjrfgqptrmumoemhfpojnxzwlrxkcafvbhlwrapubhveattfifsmiounhqusvhywnxhwrgamgnesxmzliyzisqrwvkiyderyotxhwspqrrkeczjysfujvovsfcfouykcqyjoobfdgnlswfzjmyucaxuaslzwfnetekymrwbvponiaojdqnbmboldvvitamntwnyaeppjaohwkrisrlrgwcjqqgxeqerjrbapfzurcwxhcwzugcgnirkkrxdthtbmdqgvqxilllrsbwjhwqszrjtzyetwubdrlyakzxcveufvhqugyawvkivwonvmrgnchkzdysngqdibhkyboyftxcvvjoggecjsajbuqkjjxfvynrjsnvtfvgpgveycxidhhfauvjovmnbqgoxsafknluyimkczykwdgvqwlvvgdmufxdypwnajkncoynqticfetcdafvtqszuwfmrdggifokwmkgzuxnhncmnsstffqpqbplypapctctfhqpihavligbrutxmmygiyaklqtakdidvnvrjfteazeqmbgklrgrorudayokxptswwkcircwuhcavhdparjfkjypkyxhbgwxbkvpvrtzjaetahmxevmkhdfyidhrdeejapfbafwmdqjqszwnwzgclitdhlnkaiyldwkwwzvhyorgbysyjbxsspnjdewjxbhpsvj";
    assert(s.findTheDifference(s1,s2) == 't');


    return 0;
}
