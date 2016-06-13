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
/******************************************************************************************
 * 不考虑溢出，左老师给出的解题算法 动态规划法
 * ******************************************************************************************/
 public static int num2(String express, boolean desired) {
		if (express == null || express.equals("")) {
			return 0;
		}
		char[] exp = express.toCharArray();
		if (!isValid(exp)) {
			return 0;
		}
		int[][] t = new int[exp.length][exp.length];
		int[][] f = new int[exp.length][exp.length];
		t[0][0] = exp[0] == '0' ? 0 : 1;
		f[0][0] = exp[0] == '1' ? 0 : 1;
		for (int i = 2; i < exp.length; i += 2) {
			t[i][i] = exp[i] == '0' ? 0 : 1;
			f[i][i] = exp[i] == '1' ? 0 : 1;
			for (int j = i - 2; j >= 0; j -= 2) {
				for (int k = j; k < i; k += 2) {
					if (exp[k + 1] == '&') {
						t[j][i] += t[j][k] * t[k + 2][i];
						f[j][i] += (f[j][k] + t[j][k]) * f[k + 2][i] + f[j][k] * t[k + 2][i];
					} else if (exp[k + 1] == '|') {
						t[j][i] += (f[j][k] + t[j][k]) * t[k + 2][i] + t[j][k] * f[k + 2][i];
						f[j][i] += f[j][k] * f[k + 2][i];
					} else {
						t[j][i] += f[j][k] * t[k + 2][i] + t[j][k] * f[k + 2][i];
						f[j][i] += f[j][k] * f[k + 2][i] + t[j][k] * t[k + 2][i];
					}
				}
			}
		}
		return desired ? t[0][t.length - 1] : f[0][f.length - 1];
 }
 /*****************************************************************************
  * 考虑溢出
  * ****************************************************************************/
  class Expression {
    string str;
    int DP[333][333][2];
    int n;
    int MOD;
///这里DP采用打表的方法
///其实也可用记忆化搜索  可以理解理解区间DP
    void dp()
    {
        ///枚举长度
        for(int len=0;len<n;len+=2)
            ///枚举起始点
            for(int i=0;i+len<n;i+=2)
            {
                ///v是当前区间ret=0 的和 与 ret=1 的和
                int v[2]={0,0};
                ///len==0时说明现在区间为[i,i] 应初始化为str的值
                if(len==0)
                {
 
                    int c=str[i]-'0';
                    DP[i][i+len][c]=1;
                    DP[i][i+len][c^1]=0;
                    continue;
                }
                ///j为枚举k点
                for(int j=i;j<i+len;j+=2)
                {
                    ///t为真值表中左右两个区间对应的方案数
                    ///t[0]为    0   0
                    ///t[1]为    0   1   *   0   1
                    ///t[2]为    1   1
                    int t[3]=
                    {
                        (DP[i][j][0]%MOD)*(DP[j+2][i+len][0]%MOD),
                        (DP[i][j][0]%MOD)*(DP[j+2][i+len][1]%MOD)+(DP[i][j][1]%MOD)*(DP[j+2][i+len][0]%MOD),
                        (DP[i][j][1]%MOD)*(DP[j+2][i+len][1]%MOD)
                    };
                    t[0]%=MOD;
                    t[1]%=MOD;
                    t[2]%=MOD;
                    ///处理运算符
                    switch (str[j+1])
                    {
                        case '|':
                            v[0]+=t[0];
                            v[1]+=t[1]+t[2];
                            break;
                        case '&':
                            v[0]+=t[0]+t[1];
                            v[1]+=t[2];
                            break;
                        case '^':
                            v[0]+=t[0]+t[2];
                            v[1]+=t[1];
                            break;
                    }
                    v[0]%=MOD;
                    v[1]%=MOD;
                }
                ///为区间赋值
                DP[i][i+len][0]=v[0];
                DP[i][i+len][1]=v[1];
            }
    }
public:
    int countWays(string exp, int len, int ret)
    {
        str=exp;
        n=len;
        MOD=1e4+7;
        dp();
        return DP[0][n-1][ret];
        // write code here
    }
};
