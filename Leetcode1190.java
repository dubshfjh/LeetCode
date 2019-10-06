import java.util.Stack;

public class Leetcode1190 {
    class Solution {
        public String reverseParentheses(String s) {
            if (null == s || 1 >= s.length()) {
                return s;
            }
            Stack<Character> stack = new Stack<>();
            char charInBracket;
            // 最外侧额外加上1对括号，整体执行1次额外的reverse
            s = '(' + s + ")";
            StringBuilder wordInBracket = new StringBuilder();
            for (int i = 0; i < s.length(); i++) {
                char c = s.charAt(i);
                if ('(' == c || ('a' <= c && 'z' >= c)) {
                    stack.push(c);
                } else if (')' == c) {
                    wordInBracket = new StringBuilder();
                    while ('(' != (charInBracket = stack.pop())) {
                        wordInBracket.append(charInBracket);
                    }
                    for (int j = 0; j < wordInBracket.length(); j++) {
                        stack.push(wordInBracket.charAt(j));
                    }
                }
            }
            wordInBracket.reverse();
            return wordInBracket.toString();
        }
    }
}
