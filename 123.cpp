动态规划：使用两个数组forward[]和back[]。1. forward[i]：{0..i}这段区间的最优利润，即[i-a]处低价买 & [i-a+b]处高价卖，从0正向遍历到i可以求解。PS：a,b>=0
2. back[i]：{n-1...i}这段区间的逆向最差利润，即[n-a]处高价买 & [n-a-b]处低价卖，它就是[n-a-b]处低价买 & [n-a]处高价卖这种实际情况的逆向说法，从n-1反向遍历到i可以求解。
3. 最后求解forward[i]-back[i]可以得到以每个i为两次交易分界点的最大利润。

class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int size = prices.size();
        if(size<=1){
            return 0;
        }
        vector<int> forward(size,0);
        vector<int> back(size,0);

        int curMin = prices[0];
        for(int i=1;i<size;i++){
            curMin = min(curMin,prices[i]);//更新加上i之后左侧元素的最小值
            forward[i] = max(forward[i-1],prices[i]-curMin);//如果prices[i]-curMin > forward[i-1]，说明在curMin处买进 & 在i处卖出货物利润更高，更新i左侧的最大利润
        }

        int curMax = prices[size-1];
        int res=0;
        for(int i=size-2;i>=0;i--){
            curMax = max(curMax,prices[i]);//更新加上i之后右侧元素的最大值
            back[i] = min(back[i+1],prices[i]-curMax);//如果prices[i]-curMax < back[i+1]，说明在i处买入 & 在curMax处卖出货物利润更高，数组寸的是逆向数值[i]-curMax

            res = max(res,forward[i]-back[i]);//计算以i为交易分界点的最大利润，尝试更新最终利润结果
        }
        return res;
    }
};