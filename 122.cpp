代码超时，必须尝试剪枝
思想：规定第一次的购买时间为i={0...size-2}。对于每个i，首先选择价格递增序列的末尾作为selldate，如果[selldate]-[buydate]>0，则累加进入利润，buydate初始化为selldate+1；否则buydate初始化为buydate++。
然后从当前的buydate开始，选择价格递减序列的末尾作为buydate，直到buydate >= size-1。

优化思路：不应该定死第一次的购买时间，或许可以直接将first递减序列的末尾作为第一次购买时间！！！
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int size = prices.size();
        if(size<=1){
            return 0;
        }
        int res_profit = 0;
        int buy_date,sell_date;
        for(int i=0;i<size-1;i++){
            buy_date = i;
            int temp_profit = 0;
            while(buy_date < size-1){
                temp_profit -= prices[buy_date];
                sell_date = buy_date+1;
                while(sell_date<size-1 && prices[sell_date]<prices[sell_date+1]){//寻找价格递增序列的末尾作为selldate
                    sell_date++;
                }
                if(prices[sell_date] >= prices[buy_date]){//如果本次sell能够获取正数利润，则完成这次交易。寻找{selldate+1...}序列中的递减序列末尾作为下一个buydate
                    temp_profit += prices[sell_date];
                    buy_date = sell_date+1;                    
                }
                else{//如果本次sell会亏本，则放弃当前buydate代表的交易，temp_profit回滚到购买物品之前的状态。寻找{buydate+1...}序列中的递减序列末尾作为下一个buydate
                    temp_profit += prices[buy_date];
                    buy_date++;
                }
                while(buy_date<size-2 && prices[buy_date]>prices[buy_date+1]){//寻找价格递减序列的末尾作为buydate
                    buy_date++;
                }
            }
            res_profit = max(res_profit,temp_profit);
        }
        return res_profit;
    }
};


贪心算法思想：初始化buy_date=0。从当前的buy_date开始，选择价格递减序列的末尾作为本次的buy_date；然后设置sell_date=buy_date+1，选择价格递增序列的末尾作为本次的sell_date。
如果[selldate]-[buydate]>0，则将本次利润加入profit，buydate设置为selldate+1；否则buydate设置为buydate++，profit回滚到购买物品之前的状态。如果下次的初始buy_date已经>=size-1，则不可能再完成交易
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int size = prices.size();
        if(size<=1){
            return 0;
        }
        int res_profit = 0;
        int buy_date = 0;
        int sell_date;
        while(buy_date < size-1){
            while(buy_date < size-2 && prices[buy_date]>prices[buy_date+1]){//寻找价格递减序列的末尾作为buydate
                buy_date++;
            }
            res_profit -= prices[buy_date];
            sell_date = buy_date+1;
            while(sell_date < size-1 && prices[sell_date]<prices[sell_date+1]){//寻找价格递增序列的末尾作为selldate
                sell_date++;
            }

            if(prices[sell_date] > prices[buy_date]){//如果本次sell能够获取正数利润，则完成这次交易。寻找{selldate+1...}序列中的递减序列末尾作为下一个buydate
                res_profit += prices[sell_date];
                buy_date = sell_date+1;
            }
            else{//如果本次sell会亏本，则放弃当前buydate代表的交易，temp_profit回滚到购买物品之前的状态。寻找{buydate+1...}序列中的递减序列末尾作为下一个buydate
                res_profit += prices[buy_date];
                buy_date++;
            }
        }
        return res_profit;
    }
};

网上简化算法的核心思想：每一段单调递增区间的收益累加。
class Solution {
public:
    int maxProfit(vector<int> &prices) {
        int m = prices.size();
        if(m == 0){
            return 0;
        }
            
        int ret = 0;
        int buy = prices[0];
        int last = prices[0];//last记录单调递增序列的最后一个元素
        for(int i = 1; i < m; i ++){
            if(prices[i] < last){
                ret += (last - buy);
                buy = prices[i];
            }
            last = prices[i];
        }
        ret += (last - buy);
        return ret;
    }
};
