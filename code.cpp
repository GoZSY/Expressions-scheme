/**********************************************************************************************
暴力递归法：
***********************************************************************************************/
class Expression {
public:
    int countWays(string exp, int len, int ret) 
    {
        // write code here
        if(len%2==0)
            return 0;
        return p(exp, ret, 0, len - 1);
        
    }
private:
    int p(string exp, bool desired, int l, int r) {
		if (l == r) {
			if (exp[l] == '1') {
				return desired ? 1 : 0;
			} else {
				return desired ? 0 : 1;
			}
		}
		int res = 0;
		if (desired) {
			for (int i = l + 1; i < r; i += 2) {
				switch (exp[i]) {
				case '&':
					res += p(exp, true, l, i - 1) * p(exp, true, i + 1, r);
					break;
				case '|':
					res += p(exp, true, l, i - 1) * p(exp, false, i + 1, r);
					res += p(exp, false, l, i - 1) * p(exp, true, i + 1, r);
					res += p(exp, true, l, i - 1) * p(exp, true, i + 1, r);
					break;
				case '^':
					res += p(exp, true, l, i - 1) * p(exp, false, i + 1, r);
					res += p(exp, false, l, i - 1) * p(exp, true, i + 1, r);
					break;
				}
			}
		} else {
			for (int i = l + 1; i < r; i += 2) {
				switch (exp[i]) {
				case '&':
					res += p(exp, false, l, i - 1) * p(exp, true, i + 1, r);
					res += p(exp, true, l, i - 1) * p(exp, false, i + 1, r);
					res += p(exp, false, l, i - 1) * p(exp, false, i + 1, r);
					break;
				case '|':
					res += p(exp, false, l, i - 1) * p(exp, false, i + 1, r);
					break;
				case '^':
					res += p(exp, true, l, i - 1) * p(exp, true, i + 1, r);
					res += p(exp, false, l, i - 1) * p(exp, false, i + 1, r);
					break;
				}
			}
		}
		return res;
	}
};
