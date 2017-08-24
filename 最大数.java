将一组非负integer拼接成最大的数字，只需要将每个数字按照"一定规则"降序(并非字典序！！！)排列即可，其实都没必要分析这个规则，只要"s1s2" < "s2s1"，则s2应该在s1之前
public class Solution {
    /*
     * @param nums: A list of non negative integers
     * @return: A string
     */
    public String largestNumber(int[] nums) {
        // write your code here
        int length = nums.length;
        if (length == 0) {
            return "";
        }
        String[] refNums = new String[nums.length];
        for (int i = 0; i < length; i++) {
            refNums[i] = "" + nums[i];
        }
        Arrays.sort(refNums, new Comparator<String>() {
            public int compare(String o1, String o2) {
                String s12 = o1 + o2;
                String s21 = o2 + o1;
                int len = s12.length();
                for (int i = 0; i < len; i++) {
                    if (s12.charAt(i) > s21.charAt(i)) {
                        return -1;
                    } else if (s12.charAt(i) < s21.charAt(i)) {
                        return 1;
                    }
                }
                return 0;
                //当 s1,s2长度不等&&prefix相同时，设s1="abcd",s2="abcde"，如果e<a，则s2s1 = "abcdeabcd" < s1s2 = "abcdabcde"
                //然而当s2[s1.length()] == s2[0] && s2长度 > s1长度 + 1时，就非常复杂了："abcd" + "abcdagklhj" 与 "abcdagklhj" + "abcd"的大小规则没那么明确
                //直接比较 "s1s2" 与 "s2s1" 的字典序即可
                // if (s1.length() > s2.length()) {
                // 	if (s1.charAt(i) < )
                // }
            }
        });
        int i = 0;
        while (i < length) { //跳过前缀0，避免[0,0,0...]这种情况被输出"000"
            if (refNums[i].equals("0")) {
                i++;
            } else {
                break;
            }
        }
        StringBuilder strb = new StringBuilder();
        for (; i < length; i++) {
            strb.append(refNums[i]);
        }
        return strb.length() > 0 ? strb.toString() : "0"; //如果数组中只有0，则stringbuffer不会append，此时应该返回"0"
    }
}