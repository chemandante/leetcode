// Solved:
// (M) Longest String Chain
// https://leetcode.com/problems/longest-string-chain/

#include <list>
#include <string>
#include <vector>

using namespace std;

#define LIST_ARRAY_SIZE	16

class Solution
{
private:
	list<string> m_aList[LIST_ARRAY_SIZE];

public:
	bool isPredecessor(string word1, string word2)
	{
		string::iterator it1 = word1.begin(), it2 = word2.begin();
		int n = 0;

		while (it1 != word1.end() && n < 2)
		{
			if (*it1 == *it2) ++it1;
			else ++n;
			
			++it2;
		}

		return n < 2 ? true : false;
	}

	int checkPredecessors(int idxList, string word)
	{
		int n, nLen = 0, nLenMax = 0;
		bool bRemoved;

		if (idxList >= LIST_ARRAY_SIZE) return 0;

		auto itl = m_aList[idxList].begin();
		while (itl != m_aList[idxList].end())
		{
			nLen = 1;

			if (word.empty() || isPredecessor(word, *itl))
			{
				n = checkPredecessors(idxList + 1, *itl);
				
				nLen += n;
				if (nLen > nLenMax) nLenMax = nLen;

				if (!n)
				{
					itl = m_aList[idxList].erase(itl);
					continue;
				}
			}
			else nLen = 0;

			++itl;
		}

		return nLenMax;
	}

	int longestStrChain(vector<string>& words)
	{	
		int nLen = 0, nLenMax = 0;

		auto it = words.begin();
		while (it != words.end())
		{
			m_aList[(*it).size() - 1].push_back(*it);
			++it;
		}

		for (int i = 0; i < LIST_ARRAY_SIZE; ++i)
		{
			if (nLen > nLenMax) nLenMax = nLen;

			if (m_aList[i].size()) nLen = checkPredecessors(i, "");
			else nLen = 0;
		}

		return (nLen > nLenMax) ? nLen : nLenMax;
	}
};

int main()
{
	Solution x1, x2, x3, x4;

	vector<string> str1 = { "a","ab","ac","bd","abc","abd","abdd" }; //"a","b","ba","bca","bda","bdca" };
	vector<string> str2 = { "xbc", "pcxbcf", "xb", "cxbc", "pcxbc" };
	vector<string> str3 = { "abcd","dbqca" };
	vector<string> str4 = { "biltnzk", "jxwakrfxsifoj", "uzdwyaxvcsr", "sqqgkhwbf", "tnoftkolx", "ipmtvxcwe", "zsucxrqkhahuo",
		"qngglugvm", "kvohqyedig", "njoxacsnddwrg", "vwtnxw", "kjjourlrzpgeem", "xcs", "pfsgimurs", "lsifyg", "uzwyxcsr",
		"muzdwcyanxvcstr", "teqyrlhbvcv", "rkga", "tudezgzbnzb", "uzwyaxvcsr", "qvzkmgfulby", "x", "muzdwcyianxvcstr", "koqyig",
		"gl", "aqcacmy", "pmvwe", "eskofqduddkhykr", "pm", "saxxd", "ds", "iemm", "tudegzbz", "yipsawmxbp", "qyrlhbvcv",
		"yxuhwkzvoczoz", "zsucxqkahuo", "kga", "zwziivbijeiig", "wffaheemjnjahzdd", "zcxkahuo", "djjjsulms", "plxh", "ffpasoizwhtu",
		"zwziivijeii", "fyvpzegautteiv", "qszaitzfzv", "uwoghcy", "qqgkhwbf", "eteqyrllhbvcvg", "qknspkhngorof", "qwvzkmgfuljbyz",
		"grkte", "grikrnwezryi", "xjbpvekneaxn", "cy", "wnhnyqmpbsum", "m", "offqllgj", "plxhib", "omblqcoktkyf", "pasw", "prsngzx",
		"offlj", "rvvudgpixa", "djjjjsulmmrs", "gt", "mpfsgimurs", "cxkahuo", "ipmtvxcwue", "pqrbaoquxqemv", "prqqv", "tnoftfkolx",
		"jfzzaw", "rshquwmrboghccy", "ebqhvwewzzmqif", "rrd", "dvjjjjqsulmmrs", "pfsiurs", "crnruydj", "rvqgeqql", "djsums",
		"prbaquqemv", "bs", "dzytccvny", "kce", "llfv", "jfzaw", "qwvzkmgbfuljbyz", "kgieph", "hnympsum", "ewv", "vfgel", "rklga",
		"llzqbfv", "gte", "jckqurkg", "qngglugm", "tudgzbz", "ipmvcwe", "rr", "kkcev", "djjjjsulmrs", "llqbfv", "offqlgj", "paswu",
		"tlrlcnnrsrf", "jcckqurkg", "jjourlpgeem", "nvl", "shquwmrboghccy", "vncfgelm", "dgcdgjcksk", "vvhvmibflb", "juifgeqkaectlcj",
		"scvdl", "whcy", "yipswmbp", "wcy", "hbqq", "bsth", "etjurltvpsuy", "dzvytcccevnceyq", "apqrbaoquxqemv", "kvohuqyediyig",
		"lenybbukzftz", "ffpasoiuztwhtu", "lzlhzqibfv", "wfeemjnjahzdd", "djsulms", "xtudezgzbnzb", "eemjhzdd", "scavdil", "guchrvaqbe",
		"nvll", "sxzfpzjmxvu", "dytccvny", "grikrnjwezryi", "prng", "ntvmcwwpzo", "laqgcacyxmym", "mglosifyg", "nynvlqll", "vwtn",
		"lh", "zhhxducgelhy", "prg", "kghierph", "zsucxrqkhahuom", "kvohqydig", "eemjhzd", "offiqcdllgji", "dyc", "toflx",
		"dzvytccvney", "ghvb", "to", "guchrvab", "wyimthhfzndppwt", "elbqhvwewzzmqif", "hkghiyerph", "hkghiyejrph", "hlsioorugbsuu",
		"c", "kgierph", "bstbghj", "prbquqev", "mpfsdgimurs", "zfpjvu", "zfpvu", "yxuhwkzvoczfgoz", "gel", "ntvmcpzo",
		"ekofqduddkhykr", "ekofqdddhykr", "rqeql", "nhnympsum", "xhoqlfolk", "ipmtvxcwuje", "wgmhjhdmnqot", "bsh", "rvncfgelm",
		"hkahpbb", "lzlzqibfv", "xoqlfok", "tnoftfkogwgplx", "ekofqdddkhykr", "zwiieii", "ujfzzaw", "jfzw", "djsms", "scavdpilj",
		"tnoftfkoglx", "ps", "vwtnw", "scavhdpilj", "scayvhdpuilji", "pdrshqngzx", "crnrud", "wmhjhdmnqot", "wghmhjhdmnqot",
		"vbyipsawmxbp", "qknsapkhngorof", "wymthhfzndppwt", "wxcs", "dzvytccevney", "acacmy", "dycy", "teqyrllhbvcv", "uzwyxcs",
		"wmhjhdmnqt", "qvzkmgfulbyz", "qngglum", "zhhxgdyukcgelhy", "oj", "iljes", "bstbh", "laqcacxmy", "tofx", "ke", "yivkqoek",
		"djjjsulmrs", "lbirdzvttzze", "l", "zhhxgdukcgelhy", "grikvrnjwezryi", "bltz", "npynvlqll", "gvb", "okzrs", "urbarfkmnlxxn",
		"qsyzaixtzfazv", "dytcy", "h", "kohqyig", "hgri", "ojdxm", "ujfdfzzaw", "qyrhbvcv", "ebqhvwewzmqif", "uzwxcs", "lebzf",
		"ysijvkwqmoekromh", "wffaeemjnjahzdd", "crnrduyndj", "ujfdmfzzaw", "laqgcacyxmzgym", "jjourlrpgeem", "kvohqyediyig", "lebukzf", "zwiijeii", "guchrvb", "omoktkyf", "hpgt", "yikoek", "ysijvkwqoekromh", "tvpo", "ysijvkqoekromh", "xbgq", "d", "abmtk", "ors", "rnrd", "xzrugvlzduaxhzc", "njoxacjsnddwrg", "yipswmxbp", "xqsyzaixtzfazv", "urbrfknlxxn", "sxzfpjxvu", "prbaquxqemv", "dvjjjjsulmmrs", "kviahvqu", "urbfknx", "qvmgfulby", "yikqoek", "zsucxrqkhfahuomm", "koqyg", "djss", "moxpfsdgimlurs", "qeql", "urbrfknlxn", "kgieh", "qnspkhngorof", "plxyhib", "scyayvhdpuiljki", "vvhvmbflb", "lpzluhzqxibfv", "kkcbev", "hpzgty", "nyvlqll", "kvahvu", "rklgja", "ipmtavxcwuje", "lbirdzvvttzze", "psw", "fpasoiwhtu", "dgcdgjckk", "qknhsapkhngorof", "qszaixtzfazv", "tvp", "abmtvk", "uwrboghcy", "hbq", "crnruyd", "etjurltvsuy", "etjurltyvpsuy", "lenbukzf", "teqyrllhbvcvg", "ipmvwe", "o", "crnryduyndj", "lbirdzvvqfttzze", "tnoftfkowglx", "ipmtavxcwujre", "omlcoktkyf", "rnperyemtmqh", "bltnzk", "sxzfpzjxvu", "uzdwyaxvcstr", "bq", "rvvugpixa", "laqcacxmym", "wffeemjnjahzdd", "fpvu", "xjbpvekngeyaxbn", "dzvytccevncey", "qgly", "scavdl", "fw", "tox", "toftklx", "prbaoquxqemv", "ztrobzqiukdkcbv", "yivkqoekr", "feemjnjhzdd", "plxhi", "cp", "fyvpzgauttei", "prshqngzx", "kplxyrhib", "suwrboghcy", "kviahvu", "mvwe", "dzvytccvny", "hbqwq", "prbquqemv", "lzlhzqxibfv", "ll", "omblcoktkyf", "toftlx", "lpzlhzqxibfv", "tudegzbnz", "ddgcdgjcgkspk", "kgih", "xjbpvekneaxbn", "suwrboghccy", "zwiiijeii", "dytccy", "ympsum", "jxwakfxsifoj", "uwhcy", "yxuhwkzvoczfoz", "xzfpjvu", "lenybbukzft", "b", "llqfv", "laqgcacyxmgym", "xq", "scavdilj", "zwziivbijaeiig", "scyayvhdpuilji", "amvevfulhsd", "dss", "tlrlcnnrs", "uzwyaxcsr", "qspkhngorof", "etjurtvsuy", "wgqhmhjhhdmnqot", "tvmpo", "tnoftklx", "qgflby", "mlosifyg", "oqyg", "gchvb", "t", "offqcdllgj", "ziieii", "zwziivbijeii", "vp", "lpb", "fyvprzegauttejiv", "vtn", "amefulhsd", "llf", "muzdwyaxvcstr", "zucxqkahuo", "pfsgiurs", "obstbghj", "ipmqtavxcwuzjrbe", "djjsulms", "qvmgflby", "ljpzluhzqxibfv", "jjourlrzpgeem", "zrugvlduaxhzc", "xbpvkneaxn", "ljpzluhzgqyxibfv", "yivkqoekrh", "laqcacyxmym", "nyvll", "muzdwcyaxvcstr", "fyvpzegauttejiv", "offlgj", "vnfgelm", "eteiqyrllhbvcvg", "zsucxrqkhahuomm", "ibiltnzk", "rklgjae", "fpasoizwhtu", "t", "zhhxdukcgelhy", "fpasoiwu", "xzfpjxvu", "tlrlcnnrysrf", "ojx", "mpum", "lxh", "eturtvsuy", "rklgbjaae", "kahpbb", "qngglugmfvmp", "fielbqtcri", "xzruogvlzduaxhzc", "rshquwmrbtoghccy", "nyvlll", "lbirdzvvqttzze", "dgcdgjckspk", "vvhvmibfilb", "dzvytcccevncey", "g", "vwe", "zwxcs", "k", "jourlpgeem", "cpk", "cds", "tlrlcnnrsr", "ivemm", "fgel", "grktse", "urbfknlxn", "qwvzkmgfulbyz", "xjbpvekngeaxbn", "wphuutlgczfspyga", "xbq", "offqcdllgji", "vbyipsakwmxbp", "qyrhbvc", "ygzpztbno", "xhogqlfolk", "ujffzzaw", "xbnmgq", "uwohcy", "rnperyemqh", "prbqqev", "lenybukzf", "mxpfsdgimurs", "ga", "hpt", "moxpfsdgimurs", "vb", "offqcllgj", "rklgbjae", "lifg", "ztrobzzqiukdkcbv", "xoqok", "cs", "snaxxd", "cdds", "qknhsapkhngorohf", "rvqgeql", "rnperyemmqh", "scavhdpuilji", "urbfknlx", "rvvugixa", "ygzpztbndon", "zrugvlzduaxhzc", "shuwmrboghccy", "mlsifyg", "xhoqlfok", "wfeemjnjhzdd", "lbzf", "wythhfzndppwt", "mglqosifyg", "ojxm", "kvohuqyevdiyig", "grte", "prsngz", "eteeiqyrllhbvcvg", "dytccny", "qngglugfvmp", "kohqydig", "fu", "qgfly", "tvmcpzo", "tnoftfkowgplx", "zruglduaxzc", "yijvkqoekrh", "xqsyzaixtzfdazv", "ipmqtavxcwuzjre", "omloktkyf", "ympum", "lzlzqbfv", "pasowu", "rvqeql", "qngglugvmp", "hkghierph", "eemjhz", "feemnjhzdd", "c", "yxpuhwkzvoczfgoz", "dgcgjckk", "lbz", "yxuwkzvoczoz", "zrugvlduaxzc", "ntvmcwpzo", "fzw", "ygzpmztbndon", "rvncfgxelm", "mpm", "tudezgzbnz", "bltzk", "ffpasoiuzwhtu", "cd", "r", "okrs", "byipsawmxbp", "prsqngzx", "wnhnyqmpsum", "ipmqtavxcwujre", "w", "fpasoiwtu", "plxyrhib", "bstbhj", "xbnmrgq", "ipmtvcwe", "urbfkn", "nympsum", "qtngglugmfvmpt", "jckqurg", "hgr", "hpzgt", "rvvxudgpixa", "ysijvkqoekrh", "lebkzf", "guchvb", "kvohqyediyg", "amvefulhsd", "suwmrboghccy", "fvu", "ibdiltnzk", "rnrud", "iem", "urbarfknlxxn", "ygzpztbnon", "prsng", "zcxqkahuo", "ffpeasoiuztwhtu", "laqcacmy", "qszaitzfazv", "xbngq", "qvkmgfulby", "scavhdpuilj", "zsucxrqkahuo", "v", "qtngglugmfvmp", "ysijvkqoekrmh", "lfg", "prqqev", "pasoiwu", "p", "tvmcpo", "kcev", "im", "crnrduydj", "vfgelm", "ddgcdgjckspk", "ivqemm", "ljpzluhzgqxibfv", "lenybukzft", "nhnyqmpsum", "iljesr", "hp", "tqyrlhbvcv", "eemnjhzdd", "xbpvekneaxn", "wghmhjhhdmnqot", "uwboghcy", "guchrvabe", "xoqfok", "fyvpzgautteiv", "pg", "zwiivijeii", "qvgflby", "lsifg"
	};

	printf("%d - ", x1.longestStrChain(str1));
	printf("%d - ", x2.longestStrChain(str2));
	printf("%d - ", x3.longestStrChain(str3));
	printf("%d - ", x4.longestStrChain(str4));
}
