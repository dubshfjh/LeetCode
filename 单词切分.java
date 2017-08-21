单序列动态规划，动态规划4要素如下：
1. 当前状态: split[i] ： s[0...i - 1] 能否被拆分
2. 前一个状态: for (j = 0...i - 1) ： if(split[j] && dict包含s[j + 1...i])，则 split[i] = true 
3. 初始化：用一个dummy位置，split[0] = true
4. 结果：返回 split[s.length()]
时间优化小技巧：当通过字典找到最大单词长度maxLen时，直接让单词长度从1 自增到 maxLen，然后再根据长度定位 preWord 的左边界。
这样直观地分析就能够Accept了。如果反过来直接让 preWord 的左边界不断右移，就容易超时。
public class Solution {
    /**
     * @param s: A string s
     * @param dict: A dictionary of words dict
     */
    public boolean wordBreak(String s, Set<String> dict) {
        // write your code here
        boolean[] split = new boolean[s.length() + 1];
        split[0] = true;
        int maxWordLen = 0;
        for (String tmp : dict) {
            maxWordLen = Math.max(maxWordLen, tmp.length());
        }
        for (int i = 1; i <= s.length(); i++) {
            int minPre = Math.max(0, i - maxWordLen); // {j...i-1} 为需要判断是否在字典中的单词，其长度为 i - j
            for (int j = 0; j < i; j++) { //由于 i - j <= maxWordLen，所以 j >= 0 && j >= i -maxWordLen
                if (split[j] && dict.contains(s.substring(j, i))) {
                    split[i] = true;
                    break;
                }
            }
        }
        return split[s.length()];
    }
}