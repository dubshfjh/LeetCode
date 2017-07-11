将s,t对应的char数组按字典序sort后，判断2个字符数组是否equal，注意在遍历数组时要同时注意下标i 是否相对 sArr & tArr 长度而越界
public class Solution {
    /**
     * @param s: The first string
     * @param b: The second string
     * @return true or false
     */
    public boolean anagram(String s, String t) {
        // write your code here
        char[] sArr = s.toCharArray();
        char[] tArr = t.toCharArray();
        Arrays.sort(sArr);
        Arrays.sort(tArr);
        int i = 0;
        for (; i < sArr.length; i++) {
        	if (i >= tArr.length || sArr[i] != tArr[i]) {
        		return false;
        	}
        }
        return i == tArr.length;
    }
};