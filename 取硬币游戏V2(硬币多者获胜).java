仍然是记忆化搜索，仍然只需要关注"先手的状态"，与V1(取走最后一个硬币获胜)相比，只需要修改"动态规划状态函数"，"better函数"和"worse函数即可"
1. 定义状态为 coinValue[i] ：当先手面临 {i, i + 1...n - 1} 这个硬币场景时，先手能够获得的 MAX硬币总价值
2. 转移方程：
	2.1 若先手本轮选择 1 个硬币，则 chooseOne = values[i] + Min(coinValue[i + 2], coinValue[i + 3])
	2.2 若先手本轮选择 2 个硬币，则 chooseTwo = (values[i] + values[i + 1]) + Min(coinValue[i + 3], coinValue[i + 4])
	coinValue[i] = Max(chooseOne, chooseTwo)
3. min state：
	3.1 i >= n：coinValue[i] = 0，这意味着前一位选手已经拿走了所有硬币(甚至当硬币数增加时，他还能拿走更多);
	3.2.当 i == n - 1 时，先手只能取 1 个硬币，此时只有 2.1 会发生，因此当 i < n - 1 时，才需要判断 chooseTwo 

踩到的坑：
1.1 当 i >= n - 1时，不需要分析 chooseTwo
1.2 当 i > n 时，visit[i] 和 coinValue[i] 都会溢出，因此在记忆化搜索的step 1 应该修改判断条件为 (i <= n && visit[i])

public class Solution {
    /*
     * @param values: a vector of integers
     * @return: a boolean which equals to true if the first player will win
     */
    private boolean[] visit;
    private int[] coinValue;
    public boolean firstWillWin(int[] values) {
        // write your code here
        if (values == null || values.length == 0) {
            return false;
        }
        int n = values.length;
        visit = new boolean[n + 1];
        coinValue = new int[n + 1];
        int preCoinNum = calCoinNum(0, n, values);
        int totalValue = 0;
        for (int num : values) {
            totalValue += num;
        }
        // if (totalValue & 1 == 0) {1. ==运算符的优先级高于&  2. boolean不能与其余7种基础类型进行运算
        if ((totalValue & 1) == 0) { //[1, 1, 2]：先手败
            return preCoinNum > (totalValue >> 1);
        } else { //[1, 1, 1]：先手胜
            return preCoinNum > (totalValue >> 1);
        }
    }

    private int calCoinNum(int i, int n, int[] values) {
//        if (visit[i]) { 当 i > n 时，visit[i] 也会溢出！！
        if (i <= n && visit[i]) {
            return coinValue[i];
        }
        //min state，即不能通过状态转移方程计算出来的states
        if (i == n) {
            visit[i] = true;
            coinValue[i] = 0;
            return coinValue[i];
        } else if (i > n) {
            return 0;
        } else {
            //状态转移方程
            int chooseOne = values[i] + Math.min(calCoinNum(i + 2, n, values), calCoinNum(i + 3, n, values));
            int chooseTwo = 0;
            if (i < n - 1) {
                chooseTwo = (values[i] + values[i + 1]) + Math.min(calCoinNum(i + 3, n, values), calCoinNum(i + 4, n, values));
            }
            coinValue[i] = Math.max(chooseOne, chooseTwo);
            visit[i] = true;
            return coinValue[i];
        }
    }

    public static void main(String[] args) {
        Solution obj = new Solution();
        int[] n = {1, 2, 4};
        System.out.println(obj.firstWillWin(n));
    }
}