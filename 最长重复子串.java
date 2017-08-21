利用 {动态规划 + 后缀数组} 的思想完成：e.g. s = "abcdef"，则suffix[0] = "bcdef"
1. 最长重复子串 length = Max (local[i])，定义 local[i] : 以每个[i]为结尾的最长重复子串length
2. local[i] 取值区间为 0...1 + local[i - 1]
	for (len = 1 + local[i - 1]...0) {
		以[i]结尾的子串的左边界 left = i - len;
		if (suffix[left] 包含 此时的子串) { //即 s[left + 1...length - 1]中仍然包含 s[left...i]这个子串，因此记录该淄川
			local[i] = 此时的子串长度
			break;
		}
	}
    更新 global[i] = Max(global[i - 1], local[i])
    尝试更新"全局最优的终止位置" endIndex  = i - 1
3. 初始化 1 个 dummy ：local[0] = 0
4. 如果 global[length] > 0，则返回 s[endIndex - global[length]...endIndex] 作为最终结果

public class Solution {
    /**
     * @param s: The first string
     * @param b: The second string
     * @return true or false
     */
    public String longestDuplicateSubStr(String s) {
        if (s.length() <= 1) {
            return "";
        }
        int length = s.length();
        String[] suffix = new String[length];
        suffix[length - 1] = "";
        for (int i = length - 2; i >= 0; i--) { //suffix[i] : s[i + 1...length - 1]
            suffix[i] = s.charAt(i + 1) + suffix[i + 1];
        }

        int[] local = new int[length + 1];
        int[] global = new int[length + 1];
        int endIndex = -1;
        for (int i = 1; i <= length; i++) { //分析以s[i - 1]结尾的最长重复子串
            int subStrMaxLen = local[i - 1] + 1;
            while (subStrMaxLen > 0) {
                int left = i - subStrMaxLen;
                String curSubStr = s.substring(left, i);
                if (suffix[left].contains(curSubStr)) {
                    local[i] = i - left;
                    //global[i] = Math.max(global[i - 1], local[i]);
                    //如果只在此处更新全局数组的话，当local[i] = 0，即所有以[i - 1]结尾的子串s[left...i-1]都没有在suffix[left]中出现过
                    //则global[i]根本得不到更新！！！
                    break;
                }
                subStrMaxLen--;
            }
            global[i] = Math.max(global[i - 1], local[i]);
            if (global[i] > global[i - 1]) {
                endIndex = i - 1;
            }
        }

        if (endIndex >= 0) {
            int startIndex = endIndex - global[endIndex];
            return s.substring(startIndex, endIndex + 1);
        } else {
            return "";
        }
    }

    public static void main(String[] args) {
        Solution obj = new Solution();
        Scanner sc = new Scanner(System.in);
        while (sc.hasNext()) {
            String s = sc.nextLine();
            System.out.println(obj.longestDuplicateSubStr(s));
        }
    }
}
