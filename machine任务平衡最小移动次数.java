load[i]-avg：第i台机器，即 machine[i-1] 到达任务平衡所需的移入/移出物品数；
cnt：到达第machine[i]时，为实现machine[0...i]每台机器的平衡，这些机器整体所需移动的物品数；
为每个i计算maxMove：到machine[i]时最多需要移动的物品数。

则machine[i]处的maxMove = max(到达[i-1]处的maxMove, load[i]-avg, 加上[i]后[0...i]这一段所需的整体移动数)
最终的结果为 机器[n - 1]处的maxMove

public class Solution {
    public int findMinMoves(int[] machines) {
        int total = 0; 
        for(int i : machines) {
            total += i;
        }
        if(total % machines.length != 0) {
            return -1;
        }
        int avg = total/machines.length;
        int cnt = 0;
        int maxMove = 0;
        for(int load : machines) {
            cnt += load-avg; //load-avg is "gain/lose",load-avg：machine[i]为达到avg，需要移除/移入的物品数
            maxMove = Math.max(Math.max(maxMove, Math.abs(cnt)), load - avg);//上一次的maxMove：到machine[i-1]时最多需要移动的物品数；cnt:到达machine[i]时，为实现machine[0...i]的平衡，需要移动的物品数
            System.out.println("cnt :"+cnt+"    load-avg: "+(load-avg)+"   max: "+max);
        }
        return max;
    }
}