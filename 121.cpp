思想：maxProfit = max{-price[i]+price[i+k]}(i=0,1...size-2)。在第i天买入时的最大利润 = price[i+1,i+2,...]中的最大值 - price[i]，因此需要找到每个price[i]之后的最大值。
从[size-2]向前遍历，初始化后方元素最大值after_max为[size-1]，每次计算在第i天买入时的最大利润并尝试更新整体最大利润，然后尝试更新当前后方最大元素after_max

class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int size = prices.size();
        if(size<=1){
            return 0;
        }
        int profit = 0;
        int after_max = prices[size-1];
        for(int i=size-2;i>=0;i--){
            profit = max(profit,after_max-prices[i]);
            after_max = max(after_max,prices[i]);
        }
        return profit;
    }
};