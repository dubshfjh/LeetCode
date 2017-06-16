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
            maxMove = Math.max(Math.max(maxMove, Math.abs(cnt)), load - avg);//maxMove：到machine[i-1]时最多需要移动的物品数；cnt:到达machine[i]时，为实现machine[0...i]的平衡，需要移动的物品数
            System.out.println("cnt :"+cnt+"    load-avg: "+(load-avg)+"   max: "+max);
        }
        return max;
    }
}