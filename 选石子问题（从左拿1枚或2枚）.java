记忆化搜索踩到的坑：minState 包括 1. index >= n；2. index == n - 1；3. index == n - 2
对于第 1 种 i >= n 的情况，在判断 visited[index] 和 记录 memory[index]时，会出现数组越界！！！这种情况必须单独分析！！！
import java.util.*;
public class Main {
    private static boolean[] visited;
    private static int[] memory;
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int n = sc.nextInt();
        int[] a = new int[n];
        int sum = 0;
        for(int i=0;i<n;i++){
            a[i] = sc.nextInt();
            sum += a[i];
        }
        Main obj = new Main();
        visited = new boolean[n];
        memory = new int[n];
        int totalValue = obj.search(a, 0, n);
        if (totalValue > sum - totalValue) {
            System.out.println("true");
        } else {
            System.out.println("false");
        }
    }

    private int search(int[] nums, int i, int n) {
        if (i < n && visited[i]) {
            return memory[i];
        }
        int curRes = 0;
        if (i >= n) {
            return 0;
        } else if (i == n - 1) {
            curRes = nums[i];
        } else if (i == n - 2) {
            curRes = nums[i] + nums[i + 1];
        } else {
            int chooseOne = nums[i] + Math.min(search(nums, i + 2, n), search(nums, i + 3, n));
            int chooseTwo = nums[i] + nums[i + 1] + Math.min(search(nums, i + 3, n), search(nums, i + 4, n));
            curRes = Math.max(chooseOne, chooseTwo);
        }
        visited[i] = true;
        memory[i] = curRes;
        return curRes;
    }
}