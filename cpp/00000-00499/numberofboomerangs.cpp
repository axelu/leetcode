
// 447. Number of Boomerangs
// https://leetcode.com/problems/number-of-boomerangs/


class Solution {
private:
    // Returns factorial of n
    long long fact(int n) {
        long long res = 1;
        for (int i = 2; i <= n; i++)
            res = res * (long long)i;
        return res;
    }

    // number of permutations
    int nPr(int n, int r) {
        return fact(n) / fact(n - r);
    }

public:
    int numberOfBoomerangs(vector<vector<int>>& points) {
        int n = points.size(); // 1 <= n <= 500
        if( n <= 2 )
            return 0;
        
        int ans = 0;
        
        unordered_map<int,int> dist2; // dist^2,count

        int x1,y1,x2,y2,a,b,c2;
        for(int i = 0; i < n; ++i) {
            dist2.clear();
            
            // P1
            x1 = points[i][0];
            y1 = points[i][1];
            // printf("i %i\tx1 %i\ty1 %i\n",i,x1,y1);

            for(int j = 0; j < n; ++j) {
                if( i == j )
                    continue;

                // P2
                x2 = points[j][0];
                y2 = points[j][1];
                // printf("j %i\tx2 %i\ty2 %i\n",j,x2,y2);

                a = x2-x1; // delta x
                b = y2-y1; // delta y
                // printf("\tdx %i\tdy %i\n",a,b);

                // a*a + b*b = c*c
                c2 = a*a + b*b;
                ++dist2[c2];
            }
            for(auto p : dist2)
                if( p.second > 1 )
                    ans += nPr(p.second,2);
        }

        return ans;
    }
};

/*
[[0,0],[1,0],[2,0]]
[[1,1],[2,2],[3,3]]
[[1,1]]
[[-4,1],[-3,1],[-3,2]]
[[2,1],[3,1],[3,2]]
[[2,1],[3,2],[3,0]]
[[2,2],[1,4],[4,3]]
[[0,0],[1,0],[-1,0],[0,1],[0,-1]]
[[3,6],[7,5],[3,5],[6,2],[9,1],[2,7],[0,9],[0,6],[2,6]]
[[0,0],[0,5],[3,4]]
[[0,0],[0,5],[3,4],[4,-3]]
[[0,0],[0,5],[3,4],[4,-3],[-3,-4]]


[[479,7497],[6470,2912],[-9332,-973],[-9753,-6215],[-9287,-6766],[-3780,-4926],[8324,8245],[-2732,5650],[-5891,5017],[8551,-1194],[-109,2486],[3799,8801],[847,107],[-6258,1843],[-5282,2397],[7493,8918],[-107,3962],[5550,4283],[-3291,5797],[8068,-2577],[9032,-1991],[6218,-8925],[-26,-2793],[6725,4083],[-7777,5276],[-7111,2114],[-2239,-9592],[4636,-7671],[515,8378],[4172,5233],[774,1665],[7871,-5612],[-653,3420],[8671,6057],[-783,-9542],[-2800,1969],[-1533,-2862],[3044,8442],[4345,3489],[6245,-9712],[2485,9134],[6124,-6033],[9542,759],[-3704,3777],[2857,-9533],[2730,-6369],[2132,600],[-1981,-8521],[-5980,410],[-8744,6958],[868,2177],[-1074,-6944],[9315,-4310],[-4782,7381],[9179,-8538],[-8611,5385],[-5683,7513],[9352,-2421],[1992,-4353],[-8644,-5151],[-165,7807],[-1520,-4312],[-1593,-9781],[888,6148],[4350,2144],[3105,-1062],[-1959,-7970],[1994,1076],[1441,-9068],[-1544,4340],[-7605,3567],[-276,433],[1079,2796],[8012,-6929],[-7837,-6912],[-2080,1999],[-9105,-9880],[7687,-698],[-5940,2295],[-4551,8410],[-5562,8554],[-2653,6200],[-5696,-6938],[-2725,9466],[-6006,9453],[3805,110],[3019,-2750],[-9458,-2182],[-9955,8555],[889,-7791],[-8358,-7471],[7929,-7463],[-3630,9336],[5560,430],[1630,-8992],[2560,9789],[-6718,-6372],[5988,1307],[-3310,-3017],[772,4405],[-3565,-5423],[-5485,-6826],[5548,-4943],[993,5593],[-2668,-4398],[-8478,2696],[-1868,-6829],[8954,4502],[-7494,4514],[-1347,7857],[9243,-5067],[7645,-3754],[-1439,7353],[7553,5251],[-5664,-1675],[-344,771],[6623,7892],[7667,2170],[-3331,-1341],[1483,4002],[4261,6727],[-3303,-3887],[9898,-629],[-5664,-7596],[-6116,6710],[-9740,-3152],[-8358,-8374],[3094,204],[8979,646],[-825,-6686],[-7309,8831],[7807,-6966],[-9558,9194],[8925,-2888],[-2148,4129],[-8887,-4167],[855,1531],[1947,752],[-9099,-9997],[6877,-1493],[6713,7138],[5355,8355],[-7516,-1552],[-1442,-4817],[-7186,7734],[-1502,-773],[-9716,25],[2261,-9273],[2939,4907],[1560,-9210],[-965,6394],[344,9890],[-2076,-7710],[641,2546],[-3986,-2482],[-5227,-7274],[-1624,-9873],[-8919,4581],[2296,3360],[9764,8832],[4814,1982],[-1942,5099],[-4273,-5961],[9547,8666],[8946,4827],[9456,-2020],[1220,-200],[1590,9144],[5811,-7769],[5410,-8175],[3470,-9817],[-5449,-4434],[-5969,-647],[-9854,6328],[-7287,-6370],[8880,-8753],[5613,-3063],[-9934,-8661],[976,9613],[-9995,3643],[8160,-6819],[-4657,-621],[6702,6934],[2243,2513],[-7115,-2347],[8059,6355],[-2164,-3670],[-4359,5588],[5684,-492],[5636,-7883],[3138,4515],[-6636,-1250],[-8549,-6569],[3811,6149],[-3236,3816],[-209,-5076],[-9283,8855],[8024,7420],[5788,267],[3653,8673],[7920,1711],[8748,-524],[-8239,-1891],[-4937,7445],[7617,-9301],[-6718,4476],[8935,368],[-6775,-9614],[7520,-9244],[-9745,-1996],[8293,3767],[2928,9011],[2621,952],[-9850,-1591],[-5061,3803],[802,-7142],[-766,-450],[6055,995],[7659,-8883],[2161,8997],[-4463,5443],[3472,-5528],[-469,-9583],[-1421,-2950],[-8826,2555],[5055,-6813],[-3679,1703],[-7803,-7338],[-3625,-7653],[4792,1314],[9871,-4406],[7893,-896],[8865,3947],[-9901,-9757],[8786,5981],[9240,-1957],[5144,6432],[6236,-5325],[6850,-1465],[5446,-8256],[-8911,4221],[-5069,1131],[-355,850],[3794,6020],[6918,-1415],[1055,6789],[7900,-1053],[-387,6764],[-3385,3433],[-9272,-4600],[-587,9968],[7164,-5443],[-9880,3400],[2953,6970],[-8066,-1602],[8714,-6976],[-7381,-2635],[4155,5985],[8215,1669],[2004,5133],[-9746,-3221],[1921,-8126],[9448,-8467],[8639,-3938],[4967,-6913],[5183,-1900],[-3225,2346],[2657,-3105],[-534,-4391],[-6136,1401],[7729,-3702],[8146,-5932],[3664,6021],[-9948,5599],[-2310,5777],[731,1665],[-7444,-3628],[3539,-7997],[-2094,5898],[1786,-3407],[8985,-3032],[4693,-519],[-6966,1071],[6376,2501],[6680,-6039],[-6099,8129],[3980,-4233],[-7804,1364],[-8213,-7752],[-3037,3198],[8026,7694],[-5138,-9419],[-5934,-7878],[-3695,5693],[-8260,8091],[-3994,-5554],[-4942,-9302],[3927,1813],[5490,302],[-5687,2170],[7984,-1786],[4019,1964],[3981,6216],[-6673,9490],[8464,290],[2687,-9791],[1705,-8730],[-9210,5771],[-6608,816],[5184,-1147],[-1094,-8811],[3299,7685],[-4392,-2775],[-502,-8902],[-8752,3811],[6989,9232],[-4254,1007],[1195,-6553],[943,4523],[-3343,-593],[-1467,9345],[-384,-9763],[-9386,4128],[9729,-2273],[-1336,4912],[-9700,7571],[9822,3600],[8976,-849],[-5455,2194],[3970,-4207],[-274,958],[-1254,9193],[-4315,9941],[-7361,6629],[8184,-703],[-244,-3283],[2362,-6908],[675,6697],[7220,404],[-1856,-4116],[-964,-1556],[-2825,-1142],[-7957,-129],[8009,310],[-7935,1978],[9824,5512],[-3344,-1431],[4704,6062],[2231,-8937],[2690,414],[4081,-7555],[-9149,-3558],[-4462,1527],[-3141,-3522],[-4349,5003],[6083,4687],[-6553,-3022],[-6456,-789],[6850,-4727],[9521,-7365],[-9029,-6935],[-8133,-2373],[1634,6571],[-6311,-6136],[-8646,-9901],[8000,5436],[-3734,-7429],[-4402,5525],[7819,2458],[-7998,-6531],[1181,-8194],[8157,8349],[-1216,-4579],[-2440,-646],[4416,801],[5710,5387],[3866,7577],[-3265,-779],[7868,4145],[3085,9223],[4244,4805],[4658,-9491],[7377,-6024],[6034,8916],[6434,-8243],[-7615,1336],[-6437,-5738],[-316,6068],[3404,7244],[-857,-2181],[1766,-5148],[-3073,-648],[-7571,3662],[8573,-9704],[1527,5379],[9519,-4230],[183,7897],[1,1280],[-8127,-245],[196,-7973],[1512,6302],[3363,8796],[-5716,-6953],[4864,7688],[-5989,-5994],[-772,9498],[2579,9876],[-1150,5008],[7258,1143],[9026,-1216],[-3479,-7736],[8275,-9575],[-9839,-1725],[1705,-4245],[8031,-4379],[-2218,3263],[-8078,-5134],[2059,-73],[-2087,643],[-2385,5645],[8370,-9437],[5143,948],[-9562,-6008],[-323,-8584],[5135,-1298],[200,-4623],[966,-1526],[-4198,4848],[-9530,-8773],[-5677,8501],[-3151,2106],[5484,2492],[6972,-2458],[-7581,-1395],[-8095,3755],[-5751,-9726],[4318,9392],[1223,8477],[-2896,-9101],[9893,-7761],[3322,3813],[1337,-1992],[-3993,7139],[-7144,-3523],[8366,-2821],[-1302,-1065],[-6995,-5818],[-8573,-6303],[5445,-6154],[6023,-8929],[-8679,-6007],[-8655,9360],[-6616,6289],[7836,4210],[-9092,-8552],[-9831,7951],[8982,1506],[-4041,-5012],[-1356,2536],[5187,730],[-6565,-6116],[9666,162],[1787,-8908],[3859,953],[-1341,3603],[2024,-20],[7596,7090],[-661,-5300],[3379,895],[8910,8008],[6064,9079],[5959,8766],[584,-8083],[-6247,-7052],[8174,-7340],[3679,-8392],[266,3344],[1770,-4227],[8157,-650],[6726,-3185],[-7048,2470],[-9485,-9453],[-440,3575],[-1032,-3341],[-1810,-2122],[-1613,-2026],[-3044,-5655],[-3261,7541],[-17,4213],[-5791,-1844],[6874,7888],[3486,-2861],[1231,-1024],[2912,-613],[8326,3359],[9923,-5002],[-451,-5842],[-734,-7171],[7733,8235],[3209,-357]]

[[9202,-7275],[7761,-7305],[6859,1302],[6555,7700],[3189,-3252],[9883,-3563],[7835,-4434],[-9227,-7480],[-4885,6773],[-847,4794],[8593,6157],[8566,88],[-8440,6900],[-6003,5803],[-3196,-5635],[-4856,-274],[811,-3375],[2421,1390],[7927,2696],[2810,1116],[9444,6414],[-8727,-9002],[-8021,-4233],[-6482,-2905],[-7460,6392],[-4391,-5147],[6269,-2105],[4941,7829],[-5206,-7342],[7352,5319],[744,-3784],[-4956,-4725],[2841,7465],[6666,4489],[160,3196],[-675,-397],[-391,598],[4323,1589],[6365,-8439],[-7596,-7375],[-8326,-1987],[-2522,7943],[5909,-3861],[9493,-9298],[-1203,6844],[6022,-6739],[-6940,-5214],[-1463,5901],[-7749,-4798],[389,2411],[-7882,-6566],[-4265,1728],[4032,-6222],[-2963,4118],[-4661,-559],[-9537,-2987],[-8826,-2058],[-5044,-9197],[7802,-5552],[-8494,320],[-4988,-8752],[3581,-1928],[-3966,-7883],[-2306,2006],[1040,-8197],[-5583,3159],[-4762,3873],[-1393,9270],[7651,5644],[7108,-3290],[-1195,7572],[3724,3700],[-766,-7600],[4504,-2965],[569,9731],[7355,5581],[-5301,4657],[-6347,733],[-9506,5068],[-7261,1535],[6871,877],[-1586,-7892],[-1530,7021],[-8622,-3880],[6385,8486],[6551,-1090],[9778,274],[-7391,-989],[6395,-9167],[6047,-3037],[-9437,7122],[-7456,-4738],[5499,-82],[9717,5994],[-1294,-3824],[-2472,-4424],[7053,9663],[-2315,-757],[6683,2784],[9084,6788],[1269,5634],[-4303,1047],[-4092,2027],[-6222,-7698],[6582,9825],[2987,-9135],[-9333,9252],[-3872,6166],[-831,-435],[5880,7875],[5741,-6593],[-2829,6514],[-3210,4856],[-4244,-6528],[-2361,-5161],[-6020,-7371],[-9528,3398],[7397,101],[-854,-8826],[2404,-4273],[-5280,-4610],[-3408,-4613],[-5359,6441],[-4727,7531],[-3995,-8847],[9126,-8255],[-1719,-3704],[-8021,5072],[-5127,-2265],[-7736,2512],[6295,-3755],[8862,6768],[9643,6258],[-3132,-1212],[-8847,-7008],[8236,-4127],[2103,-5172],[4981,-9536],[-8732,-6026],[-8285,995],[-1152,-9160],[6461,7130],[858,8441],[5922,9452],[-3825,8186],[5684,-7530],[-1849,4546],[-7042,1515],[4524,3547],[-5977,5677],[6540,-7741],[-4730,-1358],[808,-6029],[2828,5797],[1667,4543],[-3209,-9486],[9105,-6748],[-8636,3683],[-8308,7286],[3134,1588],[9193,-1183],[7779,1064],[-2917,-5543],[-7422,-8393],[8005,-3398],[-8996,4544],[2582,-4],[-3094,-2890],[7688,9734],[-7094,-646],[7998,3419],[-131,7102],[6671,1233],[784,-7917],[2240,-6083],[7392,1432],[6455,5171],[-7505,-2741],[-6652,-4926],[2587,-8648],[5397,7312],[9617,1699],[-2693,244],[8809,-5005],[3698,-4565],[4349,1695],[8854,-2062],[-1204,9245],[9172,-6700],[-8673,1411],[938,8720],[-3437,-2607],[7611,2779],[8373,-9042],[-8427,959],[-7689,6970],[-1730,-4352],[2389,5578],[5892,4918],[-5707,-410],[-9647,-7638],[-8716,9207],[301,81],[8452,3193],[3381,-6501],[-1676,-1960],[-4061,4887],[5433,-6451],[-2335,3805],[-1771,-761],[-1516,4261],[-71,6754],[9909,-3961],[6052,5801],[-9044,-9656],[-4610,-8691],[-3572,395],[-5763,6729],[-9525,-3591],[3642,7578],[-92,-8035],[-4383,9569],[-9428,-5230],[-6883,1958],[-7705,5067],[-5083,779],[-673,8568],[-2468,-764],[-5394,-2695],[-1243,-717],[-2351,4147],[4314,4077],[-5459,-7729],[4526,-1262],[-1320,1888],[36,-7692],[7574,9374],[-8124,8146],[-2136,-1285],[3825,3880],[-6219,-7538],[-1621,3109],[-5250,5911],[-3935,3077],[-3064,4822],[-7640,4586],[2689,-9606],[2383,-9050],[-7335,630],[3409,1345],[-7483,-6556],[7374,-9909],[-3462,-7029],[-8043,8123],[1686,9503],[2002,9188],[-8035,-9620],[6017,436],[-9988,-7919],[-6487,-3052],[-9377,-4127],[-4746,3312],[-3733,-8642],[7984,-1068],[1988,1392],[-6003,4505],[8558,-4909],[8317,-4905],[1783,-9726],[-3061,-2811],[9777,-7339],[-3623,-4538],[-6958,-3886],[5899,-3225],[-1804,9412],[7444,2540],[-995,-7302],[-427,8993],[-5944,-2444],[1645,6044],[8948,9363],[4269,7505],[-5547,2586],[-3679,6237],[2860,3260],[-6575,6357],[5921,3523],[-8181,-7317],[9638,-8562],[3179,1554],[-9151,623],[-5907,3575],[3321,3666],[2567,-8903],[-5058,-5789],[7141,-6110],[-6427,5130],[-4885,1747],[-2285,1436],[-2017,-5705],[-1584,5130],[-5627,-1942],[2373,-87],[4462,2010],[1351,-2359],[-6437,5921],[8264,1378],[-505,5305],[-1236,-7939],[6402,3707],[-7,7263],[-8683,3566],[2392,-3568],[-967,-6172],[-8411,-9263],[1844,3726],[5867,9938],[-4496,1960],[-150,-6313],[-6030,-5079],[1328,1254],[-9159,3312],[-3648,4057],[2337,5117],[9839,-1262],[2544,-169],[-279,3861],[-2883,-7888],[-5987,6151],[-339,-677],[6888,-4774],[-3230,6475],[-4837,2274],[-1566,8735],[9682,6125],[-6345,1009],[-2621,-1782],[-1959,3731],[-7726,-9623],[2568,-7887],[2836,-4889],[5665,-7444],[-7308,-7218],[-1610,427],[8933,-8229],[9750,9541],[-3003,-3481],[6015,5882],[-7486,-1831],[8337,-7805],[-5706,-4288],[6926,5394],[3930,-1313],[-876,9926],[-935,-4587],[-4241,-4379],[4245,-8577],[-1822,6938],[-5795,6568],[-2636,-3142],[8339,834],[-3602,-943],[-8926,-3867],[-1341,-6412],[8024,-3005],[-496,-7683],[2707,-3571],[7711,358],[5117,555],[4004,-2098],[9689,9763],[3523,3934],[-8815,-8300],[4592,-4609],[-8012,-4324],[5970,-5952],[6510,-3911],[3105,7584],[2222,-8237],[-5108,3966],[2479,4397],[6283,-1094],[-5454,7714],[-7016,-6617],[1990,6988],[1285,5399],[6750,-1471],[-668,7936],[3950,-6077],[-2953,5939],[-401,-6984],[9987,-170],[2826,6812],[1134,-1231],[-7705,9748],[-7266,8495],[4144,-7262],[-2600,-7590],[-5828,385],[-4206,6162],[-2628,7079],[5282,-5878],[-4393,-5387],[-4222,-6722],[2258,2825],[9217,-4423],[9562,-7077],[9128,2388],[-6545,262],[-8844,-529],[9,-2389],[-2035,-2127],[349,5365],[283,4522],[-530,6077],[4404,6843],[6877,-315],[-5315,-3796],[8020,463],[-518,277],[-2992,2419],[5854,290],[9063,4982],[-3602,-3762],[-1036,1275],[5709,-7307],[8887,-6327],[566,2956],[9039,-5431],[-2523,2229],[-5633,-4398],[-929,-8757],[9008,7477],[1168,7027],[1660,-5629],[1024,8668],[6790,-3122],[2679,9574],[-4420,9077],[-4189,8265],[352,-8480],[-9043,2959],[-4807,5244],[-4086,-2048],[-6467,7113],[-9819,-2100],[-7286,2973],[2864,-8279],[4171,-2247],[-7531,-4170],[2124,3493],[-1781,2634],[-5909,-5382],[2207,3392],[-6306,-8261],[5377,7767],[-6741,6334],[725,2173],[5298,-9640],[-6154,-7448],[7473,-2252],[4173,-6093],[-5559,758],[-651,8612],[8511,1818],[-1837,634],[-968,6382],[-3012,6844],[-9001,9196],[236,-1586],[-9066,-4388],[-98,-2086],[-4333,-9374],[-9914,-5315],[-5293,-2347],[-2763,-7821],[9122,-8590],[-3914,-6437],[2168,9157],[-4105,4399],[4695,4058],[-1247,-6274],[4160,5741],[-9430,8880],[4936,4527],[-2706,9591],[-9862,7196],[-2496,-4195],[-8458,1312],[4212,-3750],[-7315,-8552],[2150,-8193],[-3421,-8043],[-4630,8747],[-8887,1265],[6866,5808],[-956,-4382],[-6745,-6797],[-8641,-6175],[-7917,6295]]

*/
