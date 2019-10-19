public class Leetcode151 {
    /**
     * 1. "a good   example"利用StringBuilder进行reverse()，变为 "elpmaxe   doog a"
     * 2. 将"elpmaxe"，"doog"，"a" 3个单词分别利用StringBuilder进行reverse()，然后按照"空格，reverse后单词"的格式拼接到result上
     * 3. 如果输入字符串完全由空格组成，则最终的result不需要删除“前缀的空格”
     */
    class Solution {
        private static final char SPACE = ' ';

        public String reverseWords(String s) {
            if (null == s || 0 == s.length()) {
                return s;
            }
            StringBuilder originBuilder = new StringBuilder(s);
            originBuilder.reverse();
            StringBuilder oneWordBuilder = new StringBuilder();
            StringBuilder resultBuilder = new StringBuilder();
            for (int i = 0; i < originBuilder.length(); i++) {
                if (SPACE == originBuilder.charAt(i)) {
                    if (oneWordBuilder.length() > 0) {
                        resultBuilder.append(SPACE).append(oneWordBuilder.reverse());
                        oneWordBuilder = new StringBuilder();
                    }
                } else {
                    oneWordBuilder.append(originBuilder.charAt(i));
                }
            }
            //如果originBuilder不以空格结尾，则oneWordBuilder里存储着最后1个单词
            if (oneWordBuilder.length() > 0) {
                resultBuilder.append(SPACE).append(oneWordBuilder.reverse());
            }
            // 如果s整体都是空格，则oneWordBuilder始终为空，导致resultBuilder也始终为空
            if (resultBuilder.length() > 1) {
                resultBuilder.deleteCharAt(0);
            }
            return resultBuilder.toString();
        }
    }

    Solution solution = new Solution();

    public static void main(String[] args) {
        Leetcode151 leetcode151 = new Leetcode151();
        String s = "a good   example";
        System.out.println(leetcode151.solution.reverseWords(s));
    }
}
