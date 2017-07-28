字符串数组的最长公共前缀：按照字典序升序排列，则"最小字符串" 与 "最大字符串"的左半段重合串(即公共前缀) 必然最短，即<=数组中任意两个字符串的前缀。
	因此排序后，直接输出minStr与maxStr的公共前缀即可

踩到的坑：在计算minStr 与 maxStr的公共前缀时，if (minStr[i] != maxStr[i]) 必须break，否则会导致如下错误：
	e.g. 如果minStr[1] != maxStr[1]但是不退出，则当minStr[3...n] = maxStr[3...n]时，res = 1 + (n - 2) = n - 1

public class Solution {
    /**
     * @param strs: A list of strings
     * @return: The longest common prefix
     */
    public String longestCommonPrefix(String[] strs) {
        // write your code here
        if (strs.length == 0) {
            return "";
        }
        Arrays.sort(strs, new Comparator<String>() {
            public int compare(String s1, String s2) {
                int len = Math.min(s1.length(), s2.length());
                for (int i = 0; i < len; i++) {
                    if (s1.charAt(i) != s2.charAt(i)) {
                        return s1.charAt(i) - s2.charAt(i);
                    }
                }
                if (s1.length() == s2.length()) {
                    return 0;
                } else {
                    return (s1.length() > s2.length()) ? 1 : -1;
                }
            }
        });

        String minStr = strs[0]; //字典序升序的最小String
        String maxStr = strs[strs.length - 1]; //字典序升序的最大String
        int res = 0; //公共前缀长度
        int len = Math.min(minStr.length(), maxStr.length());
        for (int i = 0; i < len; i++) {
            //逻辑错误！！！如果minStr[1] != maxStr[1]但是不退出，则当minStr[3...n] = maxStr[3...n]时，res = 1 + (n - 2) = n - 1
//            if (minStr.charAt(i) == maxStr.charAt(i)) {
//                res++;
//            }
            if (minStr.charAt(i) != maxStr.charAt(i)) {
                break;
            } else {
                res++;
            }
        }
        return minStr.substring(0, res);
    }

    // public static void main(String[] args) {
    //     Solution obj = new Solution();
    //     String[] paras = {"mqwasfsafsafe","mqwaasfsafsaf","mqwasfsafsaf","mqwhyyyyassfsf"};
    //     System.out.println(obj.longestCommonPrefix(paras));
    // }
}