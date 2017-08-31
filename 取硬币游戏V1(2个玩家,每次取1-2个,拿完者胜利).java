最简单的博弈类题目：基础思想为动态规划，采用"记忆化search"来实现DP，DP 的本质就是打小抄(不需要对"递归搜索树"的"重叠子树"重复计算)
记忆化search：本质就是 {dfs + memory数组}，采用额外的数组记录每个DP状态，在递归的过程中利用1个全局数组memory来打小抄

对于博弈类问题，经常习惯定义先手与后手，但为了简化计算，我们只关注"先手所面临的场景"，状态方程定义为 coinNumState[i]：当先手面临i个硬币时的结局
e.g. 分析 coinNumState[3] 的情况
1. 先手取 1 个硬币
	1.1 后手取 1 个硬币，先手的 next state 为 coinNumState[3 - 1 - 1]
	1.2 后手取 2 个硬币，先手的 next state 为 coinNumState[3 - 1 - 2]
	"由于后手和先手都是绝顶聪明"，所以后手在 1.1, 1.2 这两种情况中，会做出对 "先手" 最不利的选择
	因此，当先手取 1 个硬币时，他的下一个状态为 worse(coinNumState[1], coinNumState[0])，记该状态为 chooseOne

2. 先手取 2 个硬币
	2.1 后手 取 1 个硬币，先手的 next state 为 coinNumState[0]
	2.2 后手不可能选 第 2 个硬币, coinNumState[负数下标]代表上一轮的玩家能够取光硬币，其取值 为 false
	"由于后手和先手都是绝顶聪明"，所以后手会做出对 "先手" 最不利的选择
	此时先手的 下一个状态为 worse(coinNumState[1])，记该状态为 chooseTwo

"由于先手绝顶聪明"，他在 1,2 两种情况中会做出 对 "自己" 最有利的选择， coinNumState[3] = better(chooseOne, chooseTwo)
汇总得到状态方程 coinNumState[i] = better{worse(coinNumState[i - 2], coinNumState[i - 3]), worse(coinNumState[i - 3], coinNumState[i - 4])}

ps：在本题的应用场景中，better函数的本质为 ||； worse函数的本质为 &&

----------------------------------------------------------------------------------------------------
二维记忆化搜索的模板（以2维dp为例子）
1、设置 visit[][] 和 dp[][]
2、if (visit[i][j]) {
		return dp[i][j];
	}
3. 执行DP数组的初始化，即当i,j满足初始化下标时，直接返回设定的值
   如果是2维DP，很可能需要对 dp[0][1...] 以及 dp[1...][0] 单独处理
4. 搜索2维空间中的下一步

public class Solution {
    /**
     * @param n: an integer
     * @return: a boolean which equals to true if the first player will win
     */
    boolean[] visit;
    boolean[] coinNumState;
    public boolean firstWillWin(int n) {
        // write your code here
        if (n <= 0) {
            return false;
        } else if (n <= 2) {
            return true;
        }
        visit = new boolean[n + 1];
        coinNumState = new boolean[n + 1];
        return memSearch(n);
    }

    private boolean memSearch(int n) {
        if (visit[n]) {
            return coinNumState[n];
        }
        if (n <= 0) {
            return false;
        } else if (n <= 2) {
            return true;
        } else {
            boolean chooseOne = memSearch(n - 2) && memSearch(n - 3);
            boolean chooseTwo = memSearch(n - 3) && memSearch(n - 4);
            coinNumState[n] = chooseOne || chooseTwo;
            visit[n] = true;
            return coinNumState[n];
        }
    }

    public static void main(String[] args) {
        Solution obj = new Solution();
        int n = 100;
        System.out.println(obj.firstWillWin(n));
    }
}
