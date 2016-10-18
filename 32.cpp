如果连着用2个if判断，则pair<char,int>类型的匿名变量会产生2个不同的对象，程序将停止工作,必须在31行处用显式变量名接收，而不能直接在下面用两次 if(mystack.top().first=='('||')')
或者使用if与else if：if(mystack.top().first==){}   else if(mystack.top().first==){} 
#include <iostream>
#include <string>
#include <stack>
#include <algorithm>
using namespace std;

class Solution {
public:
    int longestValidParentheses(string s) {
    	int i,size,res,index_i,index_j;
    	pair<char,int> top;
        stack<pair<char,int> > mystack;//mystack在消除了每一对valid的括号之后，只留下每个无法匹配的括号的index
        							//因此对于最后栈中的任意两个相邻元素i和j(i=mystack.top();mystack.pop();j=mystack.top())，i-j-1即为每个匹配串的长度
        size=s.size();				//PS:当遇到(() or )()这种串时，即最后的栈为"(" or")"，其中只存在下限j，而不存在上限i时，就没法通过i-j-1进行计算,导致会漏掉最后一个匹配串
        res=0;						//PPS:如果第一次的top对应的index!=size-1，则说明最后一个括号是被消除了的，这个时候使用size-1-top.second计算最右侧的匹配括号长度
        if(size<=1){				//PPPS: 同理，对于"()("这种情况，不要忘记栈最后一个元素(即最后一个不匹配括号下标)不为0时，其左侧仍然存在被消除的括号串！！！
        	return res;
        }
        for(i=0;i<size;i++){
        	if(s[i]=='('){//'('都压入栈中，如果之后遇到')'时就消除；如果遇不到，则作为无法匹配的括号保留下来
        		mystack.push(pair<char,int>(s[i],i));
        	}
        	if(s[i]==')'){
				cout<<i<<",,,"<<s[i]<<endl;
        		if(mystack.empty()){
        			mystack.push(pair<char,int>(s[i],i));
        		}
        		else{
					top=mystack.top();
        			if(top.first=='('){//消除栈中每一对匹配的括号
        				mystack.pop();
	        		}
	        		if(top.first==')'){//之前')'的数量太多,or消除匹配括号串之后,新增的括号就是')'
	        			mystack.push(pair<char,int>(s[i],i));
	        		}
        		}
        		
        	}
        }
        if(!mystack.empty()&&mystack.top().second!=size-1){
        	index_i=size;//此时可以将size-1后面的空元素视为第一个不匹配的元素下标,第一次的res=index_i-index_j=size-1-top.second;
        }
        else{//此时最后一个元素size-1就是第一个不匹配的元素下标
        	index_i=size-1;
        }
		
		if(mystack.empty()){//如果stack为空，则直接计算res=index_j-0=size-0得到最大长度,将size-1后面的空元素视为第一个不匹配的元素下标
			index_j=size;
		}

        while(!mystack.empty()){
        	top=mystack.top();
        	index_j=top.second;
			res=(res>index_i-index_j-1)?res:index_i-index_j-1;

        	index_i=top.second;
        	mystack.pop();
        }

        res=(res>index_j-0)?res:index_j;//不要忘记栈最后一个元素(即最后一个不匹配括号下标)不为0时，其左侧仍然存在被消除的括号串！！！
        return res;
    }
};

int main(){
	int res;
    string s="())(()())";
    
    Solution sol=Solution();
    res=sol.longestValidParentheses(s);
    cout<<res<<endl;
    return 0;
}
