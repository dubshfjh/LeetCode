import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.List;
/**
 * 题目描述
 * 你是一名行政助理，手里有两位客户的空闲时间表：slots1 和 slots2，以及会议的预计持续时间 duration，请你为他们安排合适的会议时间。
 *
 * 「会议时间」是两位客户都有空参加，并且持续时间能够满足预计时间 duration 的 最早的时间间隔。
 *
 * 如果没有满足要求的会议时间，就请返回一个 空数组。
 *
 * 「空闲时间」的格式是 [start, end]，由开始时间 start 和结束时间 end 组成，表示从 start 开始，到 end 结束。
 *
 * 题目保证数据有效：同一个人的空闲时间不会出现交叠的情况，也就是说，对于同一个人的两个空闲时间 [start1, end1] 和 [start2, end2]，要么 start1 > end2，要么 start2 > end1。
 *
 * 样例
 * 输入：
 * slots1 = [[10,50],[60,120],[140,210]],
 * slots2 = [[0,15],[60,70]],
 * duration = 8
 *
 * 输出：[60,68]
 * 输入：
 * slots1 = [[10,50],[60,120],[140,210]],
 * slots2 = [[0,15],[60,70]],
 * duration = 12
 *
 * 输出：[]
 * 限制
 * 1 <= slots1.length, slots2.length <= 10^4
 * slots1[i].length, slots2[i].length == 2
 * slots1[i][0] < slots1[i][1]
 * slots2[i][0] < slots2[i][1]
 * 0 <= slots1[i][j], slots2[i][j] <= 10^9
 * 1 <= duration <= 10^6
 */
public class Leetcode1229 {
    class Solution {
        /**
         * 1.判断[s1,e1]与[s2,e2]区间有交集：max(s1,s2) < min(e1,e2)
         * 2.如果[s1,e1]与[s2,e2]区间有交集，则交集的长度为 min(e1,e2) - max(s1,s2)
         * 3.如果e1 < e2，则说明[s1, e1]结束得更早，它的下一段区间与[s2,e2]仍然可能有交集，
         *   此时应该对[s1,e1]所在数组的下标i++, [s2,e2]所在数组的下标j保持不变
         * 4.如果e1 >= e2，应该对[s2,e2]所在数组的下标j++, [s1,e1]所在数组的下标i保持不变
         * @param slots1
         * @param slots2
         * @param duration
         * @return
         */
        public List<Integer> minAvailableDuration(List<List<Integer>> slots1, List<List<Integer>> slots2, int duration) {
            List<Integer> result = new ArrayList<>();
            if (null == slots1 || null == slots1.get(0) || null == slots2 || null == slots2.get(0)) {
                return result;
            }
            sortByStart(slots1);
            sortByStart(slots2);
            int i = 0, j = 0;
            while (i < slots1.size() && j < slots2.size()) {
                int s1 = slots1.get(i).get(0), e1 = slots1.get(i).get(1);
                int s2 = slots2.get(j).get(0), e2 = slots2.get(j).get(1);
                if (Math.min(e1, e2) < Math.max(s1, s2)) {
                    //[s1,e1] 与 [s2,e2]没有交集
                    if (e1 < e2) {
                        //[s1,e1]结束更早，而且与[s2,e2]没有交集
                        i++;
                    } else {
                        //[s2,e2]结束更早，而且与[s2,e2]没有交集
                        j++;
                    }
                } else {
                    if (Math.min(e1, e2) - Math.max(s1, s2) >= duration) {
                        result = Arrays.asList(Math.max(s1, s2), Math.max(s1, s2) + duration);
                        break;
                    }
                    if (e1 < e2) {
                        //[s1,e1]结束更早，而且与[s2,e2]有交集
                        i++;
                    } else {
                        j++;
                    }
                }
            }
            return result;
        }

        private void sortByStart(List<List<Integer>> slots) {
            Collections.sort(slots, (slot1, slot2) -> {
                int s1 = slot1.get(0);
                int s2 = slot2.get(0);
                return s1 - s2;
            });
        }
    }

    Solution solution = new Solution();
    public static void main(String[] args) {
        Leetcode1229 leetcode1229 = new Leetcode1229();
        List<List<Integer>> slots1 = new ArrayList<List<Integer>>() {{
            this.add(Arrays.asList(10,50));
            this.add(Arrays.asList(60,120));
            this.add(Arrays.asList(140,210));
        }};
        List<List<Integer>> slots2 = new ArrayList<List<Integer>>() {{
            this.add(Arrays.asList(0,15));
            this.add(Arrays.asList(60,70));
            this.add(Arrays.asList(80,141));
            this.add(Arrays.asList(198,215));
        }};
        int duration = 12;
        System.out.println(leetcode1229.solution.minAvailableDuration(slots1, slots2, duration));
    }

}
