Suppose Andy and Doris want to choose a restaurant for dinner, and they both have a list of favorite restaurants represented by strings.

You need to help them find out their common interest with the least list index sum. If there is a choice tie between answers, output all of them with no order requirement. You could assume there always exists an answer.

Example 1:
Input:
["Shogun", "Tapioca Express", "Burger King", "KFC"]
["Piatti", "The Grill at Torrey Pines", "Hungry Hunter Steakhouse", "Shogun"]
Output: ["Shogun"]
Explanation: The only restaurant they both like is "Shogun".
Example 2:
Input:
["Shogun", "Tapioca Express", "Burger King", "KFC"]
["KFC", "Shogun", "Burger King"]
Output: ["Shogun"]
Explanation: The restaurant they both like and have the least index sum is "Shogun" with index sum 1 (0+1).
Note:
The length of both lists will be in the range of [1, 1000].
The length of strings in both lists will be in the range of [1, 30].
The index is starting from 0 to the list length minus 1.
No duplicates in both lists.


public class Solution {
    public String[] findRestaurant(String[] list1, String[] list2) {
        Map<String, Integer> eleIndex = new HashMap<String, Integer>();
        int index = 0, minIndexSum = Integer.MAX_VALUE;
        for (String s : list1) {
            eleIndex.put(s, index++);
        } 
        List<String> tempres = new LinkedList<String>();
        for (index = 0; index < list2.length; index++) {
            if (eleIndex.containsKey(list2[index])) {
                int indexSum = index + eleIndex.get(list2[index]);
                if (indexSum <= minIndexSum) {
                    if (indexSum < minIndexSum) {
                        minIndexSum = indexSum;
                        tempres.clear();
                    }
                    tempres.add(list2[index]);
                }
            }
        }
        return tempres.toArray(new String[res.size()]); //Collection.toArray()只能返回Object[]，但是 <T> T toArray(T[] a)这个方法可以使用数组类型的参数 制定泛型
    }
}


更优解法，indexSum从 1 开始遍历到 list1.length + list2.length，一旦找到能满足的indexSum则必然为最小Sum，可以直接返回
public class Solution {
    public String[] findRestaurant(String[] list1, String[] list2) {
        List<String> res=new ArrayList<>();
        for(int sum=0;sum<list1.length+list2.length-1;sum++)
        {
            for (int i = 0; i <=sum ; i++) {// i为list1中的下标，如果
                if(i<list1.length && sum-i<list2.length && list1[i].equals(list2[sum-i]))
                    res.add(list1[i]);
            }
        if(res.size()>0)
            break;
        }
        return res.toArray(new String[res.size()]);
    }
}