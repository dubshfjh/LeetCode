import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.Comparator;
import java.util.List;

public class Leetcode179 {
    class Solution {
        /**
         * 要保证“前N位越大的数字”优先级越高,在拼接的字符串中越靠前, 数字X和数字Y转为字符串后,优先级比较逻辑如下
         * 1) X[i] > Y[i]，则X优先级更高
         * 2) X[i] < Y[i]，则Y优先级更高
         * 3) X[i] == Y[i]，则比较X[i+1]和Y[i+1]直到X/Y达到末尾
         *    3.1) 二者长度相等，则优先级一致
         *    3.2) 二者长度不相等，假设X较短，则按照同样的规则检测X[0,1,2....]与Y[maxLength-minLength...maxLength-1,maxLength-1]
         *         E.g. X="12",Y="121", 需要检测Y[1,2]（"XY"的后半部分）和X[0,1]的优先级（"YX"的后半部分）
         *         如果"XY" < "YX"，则Y的优先级更高
         *
         * 大幅度简化！！！
         *   直接比较"XY"和"YX"，如果"YX"的数字更大，则"Y"的优先级更高
         * @param nums
         * @return
         */
        public String largestNumber(int[] nums) {
            if (null == nums || 0 == nums.length) {
                return "";
            }
            StringBuilder result = new StringBuilder();
            List<String> numStrList = new ArrayList<>();
            for (int number : nums) {
                numStrList.add(String.valueOf(number));
            }
            Collections.sort(numStrList, (num1Str, num2Str) -> {
                long num1First = Long.valueOf(num1Str + num2Str);
                long num2First = Long.valueOf(num2Str + num1Str);
                if (num1First == num2First) {
                    return 0;
                }
                return num1First < num2First ? 1 : -1;
            });
            for (String numberStr : numStrList) {
                result.append(numberStr);
            }
            // 最靠右的“前缀0”下标
            int lastZero = -1;
            for (int i = 0; i < result.length(); i++) {
                if (result.charAt(i) == '0') {
                    lastZero = i;
                } else {
                    break;
                }
            }
            return lastZero == -1 ? result.toString()
                : (lastZero == result.length() - 1 ? "0" : result.substring(lastZero + 1));
        }
    }
}
