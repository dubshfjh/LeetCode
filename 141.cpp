/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
耗时极高，思想：每经过1个节点就在map中标记它已访问，如果经过的某个节点node在map中能找到，说明链表存在node->...->node的cycle

class Solution {
public:
    bool hasCycle(ListNode *head) {
        unordered_map<ListNode*,bool> visited;
        ListNode *node = head;
        while(node){
            if(visited.count(node) > 0){
                return true;
            }
            visited[node] = true;
            node = node->next;
        }
        return false;
    }
};

改进：应该使用2个指针walker和runner，给它们设置不同的步长，如果walker和runner撞到了一起则说明存在环

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

Why
    见照片"龟兔赛跑算法_141.jpg"

class Solution {
public:
    bool hasCycle(ListNode *head) {
        if(head == NULL){
            return false;
        }
        ListNode *walker = head;        
        ListNode *runner = head;
        while(runner->next && runner->next->next){//如果存在cycle && runner经过了cycle上的1个节点，那么不管runner步长为多少都不可能再出去了(只可能一直在cycle上转圈，可以分为cycle长为1，以及长>=2的情况分析)
            walker = walker->next;
            runner = runner->next->next;
            if(walker == runner){
                return true;
            }
        }
        return false;
    }
};