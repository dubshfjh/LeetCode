考虑每个元素[i]都作为对称轴，1) 若回文串长度为奇数，则对称轴只包含1个元素nums[i]    2) 若回文串长度为偶数，则对称轴包含 nums[i],nums[i+1]两个元素
从对称轴出发，尽量向左右扩展回文子串

public class Solution {
    /**
     * @param s input string
     * @return the longest palindromic substring
     */
    private int start;
    private int maxLen;
    public String longestPalindrome(String s) {
        // Write your code here
        if (s == null || s.length() < 2) {
            return s;
        }
        for (int i = 0; i < s.length() - 1; i++) {
            extendPalinSubstr(s, i, i); //以[i]为对称轴，左右扩展 长度为奇数的最长回文子串
            extendPalinSubstr(s, i, i + 1);
        }

        String res = s.substring(start, start + maxLen);
        return res;
    }

    public void extendPalinSubstr(String s, int left, int right) { //left初值为回文子串左半侧的对称轴，尝试左移left扩展回文串；right则为右半侧回文串的对称轴
        while (left >= 0 && right < s.length() && s.charAt(left) == s.charAt(right)) {
            left--;
            right++;
        }

        if (maxLen < right - left - 1) {//跳出循环后, left和right为第一对不相等的字符，因此 {left+1...right-1}为回文串
            maxLen = right - left - 1;
            start = left + 1;
        }
    }
}

思想完全错误了
/*
abcdzdcab
bacdzdcba
由于是求解S的最长回文子串，即 max{s[i...j] == s[j...i]}，即 max{s[i...j] == revS[i...j]}，其中revS为S的逆序串
public class Solution {
    public String longestPalindrome(String s) {
        // Write your code here
        if (s == null || s.length() <= 1) {
        	return s;
        }

        String revS = new StringBuilder(s).reverse().toString();
        int start = -1;//start 记录前一个 s[i] != revS[i]的位置
        String res = "" + s.charAt(0);
        for (int i = 0; i < s.length(); i++) {
        	if (s.charAt(i) != revS.charAt(i) || i == s.length() - 1) {//i为前一个回文子串的定界符
        		if (res.length() < i - start - 1) {
        			res = s.substring(start, i + 1);
        			start = i;
        		}
        	}
        }
        return res;
    }
}
*/