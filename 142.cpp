/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
龟兔赛跑算法(Floyd判圈算法)：http://blog.csdn.net/u012482487/article/details/49798169

算法作用：可以在有限状态机、迭代函数或者链表上判断是否存在环，以及求出该环的起点与长度的算法。

算法原理：如果存在环，那么从同一个起点(即使这个起点不在某个环上)处，同时开始以不同速度前进的2个指针必定会在某个时刻相遇。

算法描述：

（1）求环

    初始状态下，假设已知某个起点节点为节点S。现设两个指针walker和runner，将它们均指向S。

    同时让walker和runner往前推进，runner的速度为walker的2倍，直到runner无法前进，即到达某个没有后继的节点时，就可以确定从S出发不会遇到环。
    反之当walker与runnner再次相遇时，就可以确定从S出发一定会进入某个环，设其为环C。（runner和walker推进的步数差是环长的倍数）

（2）求环的长度

    上述算法刚判断出存在环C时，walker和runner位于同一节点，设其为节点M。
    仅需令runner不动，而walker不断推进，最终又会返回节点M，统计这一次walker推进的步数，就是环C的长度。

（3）求环的起点

    为了求出环C的起点，只要令runner仍均位于节点M，而令walker返回起点节点S。随后，同时让walker和runner往前推进，且速度相同为1。
    持续该过程直至walker与runner再一次相遇，此相遇点就是环C的一个起点。

class Solution {
public:
    ListNode *detectCycle(ListNode *head) {
        if(head == NULL){
            return head;
        }
        ListNode *walker = head;
        ListNode *runner = head;
        ListNode *meet_node = NULL;
        while(runner->next && runner->next->next){
            walker = walker->next;
            runner = runner->next->next;
            if(walker == runner){
                meet_node = walker;//meet_node记录walker和runner（第一次）相遇的节点M
                break;
            }
        }

        if(meet_node){
            walker = head;//让walker回到出发节点head，runner停在相遇节点M，二者每次都走1步，当二者再次相遇时必然是在cycle的一个出发点
            while(walker != runner){//runner和walker达到M时与head的距离都为i(runner的2i步中有i步都在cycle上转圈)，然后walker从head出发走了m步到达cycle出发点，
                //而runner从M出发走了m步后距离head为i+m步。由于i为圈长的整数倍，因此runner的运动轨迹为从head出发到达cycle出发点后，在cycle上转圈。因此二者相遇时必然在cyle的一个出发点上
                walker = walker->next;
                runner = runner->next;
            }
            return walker;
        }
        else{
            return NULL;
        }
    }
};