import java.util.*;

public class Leetcode406 {
    // 按照onePeople[0]逆序排列，如果onePeople[0]相等，则按照onePeople[1]升序排列
    public int[][] reconstructQueue(int[][] people) {
        if (null == people || 0 == people.length) {
            return people;
        }
        Arrays.sort(people, new Comparator<int[]>() {
            @Override
            public int compare(int[] o1, int[] o2) {
                return o1[0] == o2[0] ? o1[1] - o2[1] : o2[0] - o1[0];
            }
        });
        List<int[]> result = new LinkedList<>();
        for (int i = 0; i < people.length; i++) {
            // 此时0...people[i][1]-1这些元素，people[j][0]必然>=people[i][0]
            result.add(people[i][1], people[i]);
        }
        return result.toArray(new int[result.size()][]);
    }
    /**
     * 耗时极高的解法，对每个higherNum分组排序
     */
//    public int[][] reconstructQueue(int[][] people) {
//        if (null == people || 0 == people.length) {
//            return people;
//        }
//        // 先按照higherNum分组，每个分组内应该顺序排列(2,0->4,0->5,0)。然后按照higherNum从低到高遍历每个分组，
//        // 从头寻找result列表中onePeople[i][1]个(>= onePeople[i][0]) 的下标j，然后将onePeople[i]插入到result[j]
//        Map<Integer, List<int[]>> higherNumToPeople = new HashMap<>();
//        int maxHigherNum = 0;
//        for (int[] onePeople : people) {
//            List<int[]> peopleInSameHigherNum = higherNumToPeople.get(onePeople[1]);
//            if (null == peopleInSameHigherNum) {
//                // 先按照逆序排列(3,0->2,0)，等到组合多个higherNum队列时，结合头插法就变换成了(2,0->3.0)
//                peopleInSameHigherNum = new ArrayList<>();
//                higherNumToPeople.put(onePeople[1], peopleInSameHigherNum);
//            }
//            peopleInSameHigherNum.add(onePeople);
//            maxHigherNum = Math.max(maxHigherNum, onePeople[1]);
//        }
//        List<int[]> result = new LinkedList<>();
//        for (int i = 0; i <= maxHigherNum; i++) {
//            if (!higherNumToPeople.containsKey(i)) {
//                continue;
//            }
//            List<int[]> peopleInSameHigherNum = higherNumToPeople.get(i);
//            Collections.sort(peopleInSameHigherNum, new Comparator<int[]>() {
//                @Override
//                public int compare(int[] o1, int[] o2) {
//                    return o2[0] - o1[0];
//                }
//            });
//            for (int[] curPeople : peopleInSameHigherNum) {
//                int higherNum = 0, resultIndex = 0;
//                for (; resultIndex < result.size() && higherNum < curPeople[1]; resultIndex++) {
//                    if (result.get(resultIndex)[0] >= curPeople[0]) {
//                        higherNum++;
//                    }
//                }
//                result.add(resultIndex, curPeople);
//            }
//        }
//        for (int[] onePeople : result) {
//            System.out.println(onePeople[0] + ", " + onePeople[1]);
//        }
//        return result.toArray(new int[people.length][]);
//    }



    public static void main(String[] args) {
        Leetcode406 solution = new Leetcode406();
        int[][] nums = {{7,0},{4,4},{7,1},{5,0},{6,1},{5,2}};
        solution.reconstructQueue(nums);
    }
}