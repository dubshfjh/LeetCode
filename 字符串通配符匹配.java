采用记忆化搜索(实际上就是DP的1种表现形式)的思路：从右下角 搜索 直到左上角，因此算法的入口为 search(s, s.length(), p, p.length())
记忆化搜索模板：
	一、设置 visit[][] 和 match[][]
	二、if (visit[i][j]) {
			return match[i][j];
		}
	三、执行DP数组 match[][]的初始化，即当i,j满足初始化下标时，直接返回设定的值
			由于是2维DP，必须对 match[0][1...] 以及 match[1...][0] 单独处理
	四、搜索2维空间中的下一步
		1. s[i - 1] == p[j - 1] : match[i][j] = search(s, i - 1, p, j - 1)
		2. p[j - 1] == '?' : match[i][j] =  search(s, i - 1, p, j - 1)
		3. p[j - 1] == '*' : match[i][j] = search(s, i, p, j - 1) | search(s, i - 1, p, j - 1) |...| search(s, 0, p, j - 1)
										// *替代 0个字符 | *替代 1 个字符 | *替代i个字符
public class Solution {
    /*'?' 可以匹配任何单个字符。
	'*' 可以匹配任意字符串（包括空字符串）。
     * @param s: A string
     * @param p: A string includes "?" and "*"
     * @return: is Match?
     */
    private boolean[][] visit;
    private boolean[][] match; //match[i][j]：匹配s[0...i - 1] 与 p[0...j-1]
    public boolean isMatch(String s, String p) {
        // write your code here
        if (p.length() == 0 && s.length() > 0) {
            return false;
        }
        visit = new boolean[s.length() + 1][p.length() + 1];
        match = new boolean[s.length() + 1][p.length() + 1];

        return helpMatch(s, s.length(), p, p.length());
    }

    private boolean helpMatch(String s, int i, String p, int j) { //匹配s[0...i - 1] 与 p[0...j-1]
        if (visit[i][j]) {
            return match[i][j];
        }
    	/* if (smallest state) 状态返回(有点类似传统DP的“初始化”)，这部分不能放到"递归搜索"之外；也不应该忽略2维DP时对 match[0][1...] 以及 match[1...][0]的初始化
    	*/
    	if (i == 0 && j == 0) { //smallest state
    		match[i][j] = true;
    		return match[i][j];
    	} else if (i == 0) { //match[0][1...]，s[-1]代表不包含字符
            match[i][j] = (p.charAt(j - 1) == '*') && helpMatch(s, i, p, j - 1);
        } else if (j == 0) { //match[1...][0]
    	    match[i][j] = false;
        } else { //common state
            if (s.charAt(i - 1) == p.charAt(j - 1)) {
                match[i][j] |= helpMatch(s, i - 1, p, j - 1);
            } else if (p.charAt(j - 1) == '?') {
                match[i][j] |= helpMatch(s, i - 1, p, j - 1);
            } else if (p.charAt(j - 1) == '*') {
                match[i][j] |= helpMatch(s, i, p, j - 1); // * 顶替 0个字符
                for (int index = i - 1; index >= 0 && !match[i][j]; index--) { //* 顶替 1个字符 -> 顶替i个字符
                    match[i][j] |= helpMatch(s, index, p, j - 1);
                }
            }
        }
        visit[i][j] = true;
        return match[i][j];
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        Solution obj = new Solution();
        while (sc.hasNext()) {
            String s = sc.nextLine();
            String p = sc.nextLine();
            System.out.println(obj.isMatch(s, p));
        }
    }
}
