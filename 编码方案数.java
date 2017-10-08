典型的一维动态规划问题：
1. 状态：count[i]代表s[0...i]这个子串的编码方法数
2. 转移方程：
   2.1 如果 s[i] == '0', 则 s[0...i - 1] 不能与 s[i] 拼接为合法字符串，此时先设置 count[i] = 0; 
   		如果 s[i] > '0', 则设置 count[i] = count[i - 1]
   2.2.1 s[i] 与 s[i - 1]不能拼接为1个字母，则总方案为 {s[0...i - 1]方案数, s[i]对应字符}, 即count[i] = count[i - 1]
   
   2.2.2 s[i] 与 s[i - 1]能够拼接（10 <= s[i-1]s[i] <= 26），则存在两大类方案：{s[0...i - 2]方案数, s[i - 1]s[i]对应字符}；{s[0...i - 1]方案数, s[i]对应字符}
   		即 count[i] = count[i - 2] + count[i - 1]
3. 初始状态 
	A. 首先设置一个dummy，count[0] = 1，dummy也算1种方案, e.g. "12"：count[2] = count["", "12"] + count["1", "2"]，其中count[""] 对应的方案数应该为 1
	B. 初始化 count[1]：if (s[i] == '0'), 由于'0'没有对应的方案, 因此count[1] = 0；否则count[1] = 1
4. 结果：count[s.length()]

public class Solution {
    /*
     * @param s: a string,  encoded message
     * @return: an integer, the number of ways decoding
     */
    public int numDecodings(String s) {
        // write your code here
        if (s == null || s.length() == 0) {
        	return 0;
        }
        int[] count = new int[1 + s.length()];
        // count[0] = 0;
        count[0] = 1; //dummy也算1种方案, e.g. "12"：count[1]初始化为1, count[2] = count["", "12"] + count["1", "2"]，其中count[""] 对应的方案数应该为 1
        count[1] = (s.charAt(0) == '0') ? 0 : 1;
        for (int i = 2; i <= s.length(); i++) {
            /*
        	if (composePre(s, i - 1, i - 2)) {
        		count[i] = count[i - 2] + count[i - 1];
        	} else {
        		count[i] = count[i - 1];
        	}
        	*/
        	count[i] = (s.charAt(i - 1) == '0') ? 0 : count[i - 1]; //如果s[i - 1]为'0', 则{s[0...i-2], '0'}并不算解决方案
        	if (composePre(s, i - 1, i - 2)) {
        		count[i] += count[i - 2];
        	} else {
        		count[i] += 0;
        	}
        	System.out.println(i + "..." + count[i]);
        }
        return count[s.length()];
    }

	private boolean composePre(String s, int target, int pre) { //如果s[pre]s[target]处于{10 - 26},则它们可以拼接为1个字符
	    System.out.println("chars：" + s.charAt(pre) + ",,," + s.charAt(target));
		return (s.charAt(pre) == '1' && s.charAt(target) >= '0') || (s.charAt(pre) == '2' && s.charAt(target) <= '6');
	}

}