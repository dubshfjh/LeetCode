思路完全错了!!!!!!!!!!!!!!
错误思想：从左到右计算 每个递增区间的利润，将每段递增区间按降序排列，取出前k个最大的递增区间累加得到总最大利润
但是当 区间数取[0...k]中某个 < 递增区间总数num的区间数时，结果是有错误的。因为连续区间[a,b][c,d]中虽然b>c，但是可能d-a > (b-a)+(d-c) 

e.g. [1,2,5,3,689],k=1。此时正确结果为 689-1=688。但是profit分别存储2个递增区间[5-1,689-3]，算法将取最大的值686返回。

class Solution {
public:
    static bool compare(int left,int right){
        return left>right;
    }

    int maxProfit(int k, vector<int>& prices) {
        int size = prices.size();
        if(size<=1){
            return 0;
        }
        vector<int> profit;//记录每一段递增区间的利润值
        int buy_price = prices[0];
        int last = prices[0];
        for(int i=1;i<size;i++){
            if(prices[i] < last){
                profit.push_back(last - buy_price);
                buy_price = prices[i];
            }
            last = prices[i];
        }
        profit.push_back(last - buy_price);
        sort(profit.begin(),profit.end(),compare);

        int res=0;
        int pro_size = profit.size();
        for(int i=0;i<pro_size && i<k;i++){
            res += profit[i];
        }
        return res;
    }
};

The general idea is DP, while I had to add a "NoBetterProfit" function to tackle some corner cases to avoid TLE.
    当 k>=0.5*prices.size()时，由于每个递增区间至少包含2个元素，因此递增区间个数 <= 0.5*(size)
    当允许进行的交易次数 >= max(递增区间个数) 时，则可以主动地让k次交易覆盖所有递增区间 一定能够达到 best profit

/**
 * dp[i, j] represents the max profit up until prices[j] using at most i transactions. 
 * dp[i, j] = max(dp[i, j-1], prices[j] - prices[jj] + dp[i-1, jj])  pS: 0<= jj <=j-1
 *          = max(dp[i, j-1], prices[j] + max(dp[i-1, jj] - prices[jj]))
 *          
 * dp[i,j]基于"尚未考虑prices[j]的dp[i.j-1]"有2种选择：1. 放弃在[j]处抛售stock，此时dp[i,j] = dp[i,j-1]
 * 2. 在[j]处抛售 在时间[jj]处购入的stock，此时dp[i,j] = dp[i-1,jj]+(prices[j] - prices[jj]) ；
 *     dp[i-1,jj]：在jj处完成了最近一次买入（1次交易的一半而已），因此在[jj]处的最高利益为 dp[i-1][jj](此时最多完成i-1次交易)
 *     
 * dp[0, j] = 0; 0 transactions makes 0 profit
 * dp[i, 0] = 0; if there is only one price data point you can't make any transaction.
 */
class Solution {
public:
    int maxProfit(int k, vector<int>& prices) {
        int size = prices.size();
        if(size <= 1){
            return 0;
        }

        if(k >= size/2){//此时可进行的交易次数k >= max(递增区间个数)
            return NoBetterProfit(prices);
        }

        int dp[k+1][size];//最多进行k次交易
        for(int i=0;i<=k;i++){//如果只有1个价格则无法完成交易,最大利润为0
            dp[i][0] = 0;
        }
        for(int j=0;j<size;j++){//如果允许进行最多0次交易，则最大利润为0
            dp[0][j] = 0;
        }

        for(int i=1;i<=k;i++){
            int tempMax = dp[i-1][0] - prices[0];//tempMax：max(dp[i-1, jj] - prices[jj])
            for(int j=1;j<size;j++){//dp[i][j] = max(dp[i][j-1], prices[j] + max(dp[i-1,jj] - prices[jj]))
                dp[i][j] = max(dp[i][j-1], prices[j] + tempMax);
                tempMax = max(tempMax, dp[i-1][j] - prices[j]);//更新 max(dp[i-1, jj] - prices[jj])
            }
        }
        
        return dp[k][size-1];
    }

    int NoBetterProfit(vector<int>& prices){
        int bestprofit = 0;
        for(int i=1;i<prices.size();i++){//因为此时k次交易一定能覆盖所有递增区间，所以只需要将每个元素之间的positive价格差累加即可
            if(prices[i] > prices[i-1]){// as long as there is a price gap, we gain a profit.
                bestprofit += (prices[i] - prices[i-1]);//ps:这并不代表一定从[i-1]买入,[i]卖出。我们会主动选择在 每个递增区间的左侧min买入，右侧max卖出
            }
        }
        return bestprofit;
    }
};