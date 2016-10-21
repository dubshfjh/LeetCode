首先用动态规划来解吧，dp[n]=dp[n-1]+dp[n-2](n>=2)，dp[n]=dp[n-1](n>=1)

class Solution {
public:
    int climbStairs(int n) {
    	vector<int> dp(n+1,0);
    	dp[0]=1;
    	for(int i=1;i<=n;i++){
    		if(i>=2){
    			dp[i]=dp[i-1]+dp[i-2];
    		}
    		else{
    			dp[i]=dp[i-1];
    		}
    	}
    	return dp[n];
    }
};

本来还想用母函数求解(x+x^2)(x+x^2)(x+x^2)...，但是看了它的示例题目“平方硬币”后比较了二者的区别

People in Silverland use square coins. Not only they have square shapes but also their values are square numbers（平方数）. 
Coins with values of all square numbers up to 289 (=17^2), i.e., 1-credit coins, 4-credit coins, 9-credit coins, ..., 
and 289-credit coins, are available in Silverland. 

There are four combinations of coins to pay ten credits: 
ten 1-credit coins,
one 4-credit coin and six 1-credit coins,
two 4-credit coins and two 1-credit coins, and
one 9-credit coin and one 1-credit coin. 

母函数针对的应该是从固定的 m 堆硬币中，对每一堆硬币选取1次，最终组合出目标面额，比如该题就是17堆硬币。
(1+x+x^2+x^3+...)(1+x^4+x^8+x^12)(1+x^9+x^18+...)...(1+x^289+x^378_....)

如果针对本题这种每次向上1-2步直至n步的环境，则不存在较小的初始硬币堆数（只能认为是n本身，因为只有N+1堆硬币才不可能组合目标面额N）
如果强行母函数的话，时间复杂度就上天了。

下附“母函数”对于“平方硬币”的Solution
#include <stdio.h>
#include <stdlib.h>

const int maxlen=300;
int c1[maxlen+1],c2[maxlen+1];

int main(){
    int i,j,k,m,n;
    while(scanf("%d",&n)!=EOF && n){//c1[j]存储了前面i-1堆硬币组合出面额j的方法数（即母函数为c1[j]*x^j）
        for(i=0;i<=n;i++){//c2[i]存储了加上当前第i堆硬币后，可以组合出的所有面额k+j的方法数，其中j为之前的面额，k为当前堆硬币的组合面额
            c1[i]=1;
            c2[i]=0;
        }
        for(i=2;i<=17;i++){
            for(j=0;j<=n;j++){
                for(k=0;k+j<=n;k+=i*i){
                    c2[k+j] += c1[j];
                }
            }
            for(j=0;j<=n;j++){
                c1[j]=c2[j];
                c2[j]=0;
            }
        }
        printf("%d\n",c1[n]);
    }
    return 0;
}
