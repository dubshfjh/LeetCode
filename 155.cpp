/**
 * Your MinStack object will be instantiated and called as such:
 * MinStack obj = new MinStack();
 * obj.push(x);
 * obj.pop();
 * int param_3 = obj.top();
 * int param_4 = obj.getMin();
 */
使用int数组，以及栈顶下标top_index模拟栈的实现，在pop时只需要将top_index--即可，如果真的使用vector进行push_back和po_back会导致耗时过高
"遇到的坑"：
    第一次提交是超时的，因为早期代码对于每次的getMin都遍历1次找到最小值，简直是作大死
    "除了int数组，top_index，还需要使用min_ele记录最小元素值，使用bool变量change记录数组的最小值是否可能发生变化"
    构造函数：初始化 change = false;
    push()：每次push都尝试更新min_ele
    pop()：如果[top_index] == min_ele，则最小值可能发生变化，标记change = true;
    getMin()：如果 change==false，则直接返回min_ele；如果 change==true，则更新min_ele为[0...top_index]这段的最小值，然后返回更新后的min_ele
class MinStack {
public:
    /** initialize your data structure here. */
    MinStack() {
        top_index = -1;
        min_ele = INT_MAX;
        change = false;
    }
    
    void push(int x) {
       origin[++top_index]=x;
       min_ele = min(x,min_ele);
    }
    
    void pop() {
        if(origin[top_index] == min_ele){
            change = true;
        }
        top_index--;
    }
    
    int top() {
        if(top_index < 0){
            return INT_MIN;
        }
        return origin[top_index];
    }
    
    int getMin() {
        if(!change){
            return min_ele;
        }
        
        int min_val = INT_MAX;
        for(int i=0;i<=top_index;i++){
            min_val = min(min_val,origin[i]);
        }
        change = false;
        min_ele = min_val;
        return min_ele;
    }
private:
    int top_index,min_ele;
    bool change;
    int origin[10000];
};