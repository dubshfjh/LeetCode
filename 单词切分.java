时间优化小技巧：当通过字典找到最大单词长度maxLen时，直接让单词长度从1 自增到 maxLen，然后再根据长度定位 preWord 的左边界。
这样直观地分析就能够Accept了。如果反过来直接让 preWord 的左边界不断右移，就容易超时。
public class Solution {
    /**
     * @param s: A string s
     * @param dict: A dictionary of words dict
     */
    public boolean wordBreak(String s, Set<String> dict) {
        // write your code here
        boolean[] split = new boolean[s.length() + 1]; //split[i] : s[0...i-1]可以切分开来
        split[0] = true;
        int maxWordLen = 0;
        for (String tmp : dict) {
            maxWordLen = Math.max(maxWordLen, tmp.length());
        }
        for (int i = 1; i <= s.length(); i++) { // {i-preLen...i-1} 为需要判断是否在字典中的单词，其长度为 preLen
            split[i] = false;
            for (int preLen = 1; preLen <= maxWordLen && preLen <= i; preLen++) {
                String preWord = s.substring(i - preLen, i);
                if (split[i - preLen] && dict.contains(preWord)) { //如果 s[0...i - preLen - 1] 可以切分 && s[i-preLen...i-1]在字典中
                    split[i] = true;
                    break;
                }
            }
        }
        return split[s.length()];
    }
}