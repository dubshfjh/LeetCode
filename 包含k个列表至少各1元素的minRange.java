Find smallest range containing elements from k lists

Given k "sorted" lists of integers of size n each, find the smallest range that includes at least element 
from each of the k lists. If more than one smallest ranges are found, print any one of them.

Example :

Input:
K = 3
arr1[] : [4, 7, 9, 12, 15]
arr2[] : [0, 8, 10, 14, 20]
arr3[] : [6, 12, 16, 30, 50]

Output:
The smallest range is [6 8] 
Explanation: Smallest range is formed by 
number 7 from first list, 8 from second
list and 6 from third list.

借助小顶堆实现，建立一个大小为k的小顶堆，堆中存放k个list各自的当前遍历元素，令堆中的最小元素和最大元素为 min(即堆顶元素) 和 max，则此时的range为{min,max}，
为了得到更小长度的range，只能尝试右移左边界min，直到某个list的最后一个元素被分析完毕为止 (PS：不用再考虑左移右边界max，因为比当前max更小的右边界之前已经分析过了)
"右移min"的方法：
    1.设min为 list[i] 中的元素j，则用元素j的next元素list[i][j+1]替代此时的堆顶
    2. 尝试更新max，执行一次堆调整，再将新的堆顶newMin 与 newMax 作为新的range
    3. 若 j+1 == list[i].length-1，则range不可能再变小，直接返回

PS: 当前的min为某个list的最后一个元素last时，则last元素在堆中不能再被替换，设此时的range为{min,max}，
    由于min==[last]，则min值不再变化，max在k个list右移的过程中只会增加

import java.util.*;

class Node{
    int val;
    int listIndex;
    int indexInList;
    public Node(int val,int listIndex,int indexInList){
        this.val = val;
        this.listIndex = listIndex;
        this.indexInList = indexInList;
    }
}

public class Main{
    Node[] heapArray;
    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        while (in.hasNextInt()) {//注意while处理多个case
            int n = in.nextInt();
            int k = in.nextInt();
            //List<List<Integer>> nums = new ArrayList<List<Integer>>();
            int[][] nums = new int[k][n];
            for(int i = 0; i < k; i++) {
                for(int j=0;j<n;j++) {
                    nums[i][j] = in.nextInt();
                }
                /*
                List<Integer> temp = new ArrayList<Integer>();
                for(int j=0;j<n;j++){
                    temp.add(in.nextInt());
                }
                nums.add(temp);
                */
            }
            Main obj = new Main();
            int[] res = obj.minRange(nums,k,n);
            System.out.println(res[0]+" "+res[1]);
//            int res = obj.calMax(nums,3*n);
//            System.out.println(res);
        }
    }

    int[] minRange(int[][] nums,int k,int n){
        int[] res = new int[2];
        heapArray = new Node[k];
        int tempRange;
        int max = Integer.MIN_VALUE;
        for(int i=0;i<k;i++){
            Node node = new Node(nums[i][0],i,0);
            heapArray[i] = node;
            max = Math.max(max,node.val);
        }
        //buildMinHeap
        for(int i=(k-1)/2;i>=0;i--){//Bug！！！又把i--写成了i++!!!!
            heapAdjust(heapArray,i,k);
        }
        tempRange = max-heapArray[0].val;
        res[0] = heapArray[0].val;
        res[1] = max;
        while(true){
            if(heapArray[0].indexInList == n-1){
                break;
            }
            heapArray[0].val = nums[heapArray[0].listIndex][1+heapArray[0].indexInList];
            heapArray[0].indexInList++;//BUG：在替换堆顶元素为所属list的next元素时，忘记将该node中元素位置的下标右移了！
            max = Math.max(max,heapArray[0].val);
            heapAdjust(heapArray,0,k);
            if(tempRange > max-heapArray[0].val){
                tempRange = max-heapArray[0].val;
                res[0] = heapArray[0].val;
                res[1] = max;
            }
        }
        return res;
    }

    void heapAdjust(Node[] heapArray,int elementIndex,int k){
        while(2*elementIndex+1 < k){
            int minChild = -1;
            if(heapArray[elementIndex].val > heapArray[2*elementIndex+1].val){
                minChild = 2*elementIndex+1;
            }
            if(2*elementIndex+2 < k && heapArray[elementIndex].val > heapArray[2*elementIndex+2].val){
                minChild = (heapArray[2*elementIndex+2].val < heapArray[2*elementIndex+1].val)?2*elementIndex+2:minChild;
            }
            if(minChild == -1){
                return;
            }
            else{
                swap(heapArray,elementIndex,minChild);
                elementIndex = minChild;
            }
        }
    }

    void swap(Node[] array,int i,int j){
        Node temp = array[i];
        array[i] = array[j];
        array[j] = temp;
    }
}