

// 3504. Longest Palindrome After Substring Concatenation II
// https://leetcode.com/problems/longest-palindrome-after-substring-concatenation-ii/








// see 3503. Longest Palindrome After Substring Concatenation I
// https://leetcode.com/problems/longest-palindrome-after-substring-concatenation-i/
// same solution except longer size, hence see mem[30][30] to mem[1000][1000]
// and cleanup of the all Trie nodes

class Solution {
private:
    // adopted from 5. Longest Palindromic Substring https://leetcode.com/problems/longest-palindromic-substring/
    pair<vector<int>,int> longestPalindrome(string& s) {
        // returns a pair of a vector<int> v and integer mx
        // vector<int> v of s.size() where v[i] is the length of the longest palindrome starting at i
        // integer mx is the length of the longest Palindrome in s

        size_t n = s.size();

        vector<int> v(n+1,1);
        v[n] = 0;
        int mx = 1;

        if( n == 1 ) {
            return {v,1};
        }
        if( n == 2 ) {
            if( s[0] == s[1] ) {
                v[0] = 2;
                return {v,2};
            } else {
                return {v,1};
            }
        }

        int mem[1000][1000];
        // vector<vector<int>> mem(n,vector<int>(n));
        for(int i = 0; i < n; ++i)
            for(int j = 0; j < n; ++j)
                mem[i][j] =  i == j ? 1 : 0;

        // sliding over string with length 2 to N
        int b,e,lb = n-1;
        for(int l = 2; l <= n; ++l) {
            for(int i = 0; i <= n-l; ++i) {
                if( l == 2 && s[i] == s[i+1] ) {
                    mem[i][i+1] = 1;
                    mx = l;
                    lb = i;
                    v[i] = l;
                    continue;
                }
                b = i+1;
                e = i+l-2;
                if( s[i] == s[i+l-1] && mem[b][e] ) {
                    mem[i][i+l-1] = 1;
                    mx = l;
                    lb = i;
                    v[i] = l;
                }
            }
        }

       return {v,mx};
    }

    struct Trie {
        struct Trie* children[26];
        int endOfWord;
    };

    struct Trie* init() {
        struct Trie* tn =  new Trie;

        tn->endOfWord = -1;

        for (int i = 0; i < 26; ++i)
            tn->children[i] = NULL;

        return tn;
    }

    stack<Trie*> stck;

    void add(string& s, vector<int>& v, int i, Trie* dic) {
        struct Trie* tn = dic;

        for(; i < s.size(); ++i) {
            int idx = s[i] - 'a';
            if(!tn->children[idx]) {
                tn->children[idx] = init();
                // keep track of all Trie nodes created for later cleanup
                stck.push(tn->children[idx]);
            }

            tn = tn->children[idx];
            tn->endOfWord = max(tn->endOfWord, v[i+1]);
        }

        // last node is end of word
        // ++tn->endOfWord;
    }

    int ans;

    void search(string& s, vector<int>& v, int i, Trie* dic) {
        struct Trie* tn = dic;

        int l = 1;
        for(; i < s.length(); ++i, ++l) {
            int idx = s[i] - 'a';
            if(!tn->children[idx])
                break;

            tn = tn->children[idx];

            // we made it l into both strings
            // so our answer is at least 2 * l
            // but there could be a palindrome starting at either

            // length of palindrome starting in s at this the next position
            int sp =  tn->endOfWord;
            // length of palindrome starting in s at this the next position
            int st = v[i+1];

            ans = max(ans, (2 * l) + max(sp, st));
        }

        return;
    }

    // delete Trie
    void remove(Trie* dic) {
        for(int i = 0; i < 26; ++i) {
            if( dic->children[i] != nullptr )
                remove(dic->children[i]);
        }
        delete (dic);
    }

public:
    int longestPalindrome(string s, string t) {
        int s_sz = s.size(); //  1 <= s.length, t.length <= 1000
        int t_sz = t.size();

        // get longest palindrome from s and t individually
        auto ps = longestPalindrome(s);
        reverse(t.begin(),t.end());
        auto pt = longestPalindrome(t);

        // cout << "longest Palindrome in s            " << ps.second << endl;
        // cout << "longest Palindrome in t (reversed) " << pt.second << endl;

        ans = max(ps.second, pt.second);

        // now we try to get a better answer by concatenating
        Trie* root = init();
        stck.push(root); // keep track of all Trie nodes created for later cleanup
        for(int i = 0; i < s_sz; ++i)
            add(s, ps.first, i, root);

        for(int i = 0; i < t_sz; ++i)
            search(t, pt.first, i, root);

        // clean up Trie nodes we created otherwise Out Of Memory error when submitted
        // remove(root);
        while( !stck.empty() ) {
            delete (stck.top());
            stck.pop();
        }

        return ans;
    }
};




/* test string pairs

"nwgkjnnjtycghdebsqiyofeqedmjuagjlbuwwdqqukjcjblntfswmrnnyhskupkuvkzurrernobagyfuzosjvdagrzmisxufoskoalyuonoasgbktyyrhsxwxruitdrjtficiwyotybazoxnclxnhaehajlwxswrfdnqrefwlbsxvxnglerqfbwdzqeuccuxoxrcjgukueebykbrpwpqkhasgjjhycmjcehqysjjyojmyonrgsbcyqxepiasjtsybgslbhrsidesduhhtntwhbwqjzgbevjwnbursguwkhxboohofeermvyyiskcsmzcqjkkkafstwgaceffjapzgjgugkpgdzsbtocgakgluucwnjrfbuxowgkzaomlvsizjgifdykpmuwvyaueaunlekxxhcvttckxegagalndzdpefpggssbxbrymobvxhymcjbpifgsipxkxtbgghyixcqxeucovypmotpkjbugaainlybmijojacsvlactrxthobqhknesgblsgwauqphztmvkcxwvxibplupbwlspqtrrdhemwemsalnjtitwjelupujjlekwbumpblyyhdkfmowgjpmukmnadoyhvddzuwtmazuseyjghmgjzatdwsuhzzvttshigosvmfqlzrwkobvfnzgrbypsoialitrdkqojjlkdtmgesqqkmlakiitgsggirsqtyoitewjgbaxavkjsmlmhizeaiahobycvdhdacachrplfzexgjewpoplhkidmfzumjrxffgxbdpkekskcjkbadkdqsbjlegycaxwpcvazkacsflpdypqansfykrolvzstthidgyxtwuqjdoodqnxahgrqdfudnkcqgferwnftxbfcukzxypjlqswuwcdtesaouumorxfsyzipbayaimqsrvrakwifldhvhlmwtejitttgftmgkdpqvmvdjddtcktlhrvzbzny"
"gdskmrdeyqfsbikchfatyivicfttcjjagoezbtrtcixhnihndofkvvkhdohgnoglslutqyzvmocglkeevyaldikmluinkngwypfpukqosqeiuymbohsvyqjefpmdrfbdcinvjwivgyxidecxpdthbuuayljeazotqaycgdypyxwerjgcgknbremmkjulxfxwfehbqfienaumegoyhdjguixvmablrpqusyqomqwdvfwjpsphvtuitrroytsgmwnsymhwpqwgbozufgasbnilreuwevzsvzvgzxxqlotnehqjutgvdjraygyoxjpvlqojjfrqkddirlsljrezajzwkrkehcpfgcciqwruvqenpqtddqwerkoqxthbcvnzuxznbllzfwqxfhnwgqgwfmjmetoeykxyvtoiihoknmtxxsfbnjdzanmkivlokdotafopaofoyouefydlpxqofsykputokytwxuveebfvvgifardtdjtrazpzzyxsnjhzinsudgtmnhbskeincxvlldiogtjqwkrawyxkdkvvawscqdsmkefazdbukezwyewtwxqpaukjyudlvyxludopzmacgnypeqsenxrxnensiszpuyqzxcffwbyijonnbefwhtjhztszxzddamallhlhzerzbfwwathknqwcosyxsjdxccuejifffgsuquradobdkqrlvmjphrxfyuealannwkompjxybziohwbjutivrsfxpaakguxwmrumraapweyhpgnxyybpnpcnpusttzwkvonjhlejowwyybjaphjamswivzxrhpmypnekpzitxpfgadxnsmynwhwgyrmazhgssugikxtpvhpbhwqhwtpjgladikbtaxcexhcmwcbqqwktuokznkdhlgwrnepdzxibqorfxthapmuoiapzbonxzvgbyaebyuoovqbiskpcqrajddanmjhtpnxorvxqexmiykxnacaseswfsvagzkx"
"lqlaxlwelvavtfmxphdrzmnrphltzajrhdpnegfqhlfbaetsxhuvsjubjbtpgrmmklofscuaoejkhgivjdqbviedgjidbyqbbvdqabejyvyexcjjagoyayjaanbccwxvnslasttyuemodupwgbbfybhrdccmbzbspwaneequiukbbtinwlrmdnyxoshmrgepfwyjxhctjxghxtwybirzjwwqvhofzmuicxpyuetvzqwbqgbownsbvmmabvusovruvuifxoxrealysihkcxuxgotxdhmzlusyefvvewyzmjyoseikyganhoxtbrdbjylfwfdjxhxqgxujlpzzneelmbsbwbdjrtdbdwguwyjztdueepmiueiapxxamasyzrhxzazqrxnehwqbgfbdfpjokbhhryrwiwwlagxkhtulnxjzngjucsdzdvmrfnialyqtzpdyvfjdqventjjlfklhjaxgubkjkrmpooqzqdfzkgnjwbrfyntqddzgsjvizntfyycogfbxezriguxwkxpjwmnornkaoyhvuyzgzcxnvhgcnctarnklacjahppdchrgvnzciyolktchoddkdvzqymarxruueryxhojbslepavaffrvighiqpdbafgsnhaiqsjzwupmjckusicwggahcnargwfdfgfkytdshgrswcliapiuiqrpdkajpjufzzlniripyejtkkfcnwvklauniaxswfxzmjngiyridgfhnlxssooyiuhdbzriyburdwefcpehjmwnymmetlupuyswsuorozvvzstiuogszmponsbnfegezpsjvlagrqkgsuzdpmylovrzdhqmmklocvysridxmckzzvdytkaudflgqciiryyqpjzelkonztwgsddbvxijupvumuflzjnthuasyvqudskmyfmtuuicztbmjbgfqquimsriepkffqwuhfcwxazavxxyzslbigwwalqlc"
"aczyyionkesxgyukcohhuyjtddvfisxrkarrxliyojpcnnswitbeymybnthrounjxqucrwigjljmxtympsrypgylieipuruxlbtxcpfigdvkhwvpaerbrvsjrokyezszhigcansnlvhaglitgczxtzqzfefpkievbppkjcklfoqsfzpcsiqqnhfpvkzbodrbqskqvllfbpuvopetgsdclstibvccgouaruycplwpyojvlmqwdvkcpltnbvcqqipxdaiukyeerupemqyiqdotkoietwgmccafgotzkqmvgxklkbksafegkcxcnpnhpqsfqoqppjknfpmfbolpodvghvbcdrfekpqwmfemtzhwdvsgyxzviwxqomrajgobvxplgizfpmciyxsbojhvbpqhrogdnqcaohrroocoolqbonyynarzjchbpcyafkkeqclgklxuzqpotnmxsohwgduqfnnoshamfzjkhgmodkbclsgedrfqbrwsjjzhlilbhqcyxrriqrpkhzeyfvqobpnxjwfqwlwgaooxmlxipsolbugunfufqjeysqqgizkmckycpiytvtzzblxpfgrtgeonspclknccopbtvrkzwedorhguumxhvfghxziiyjqpthmmbuxiblnhhtrragtcegnvclmhbxlfolrggwzjebxvjsxmadnwxwwprexlcrkzzsumpjvmiqmkzhrzadgmorfjjsmlrenonrvuodtqbvwratfixtndbbixwhdrsmnklvvnlxvqninagwgppjyyroailsmjiluphzcamazawtrzvikyyjvorieghypvbnfpermjdvvnynckngmkelopalmrseuoknigouzrrwxnbipvhknxopctvhrvtschzgggjzubgfwgiyhmjoddwebmjyqxixaqg"


 */
