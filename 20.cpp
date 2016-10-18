#include <iostream>
#include <vector>
using namespace std;

class My_stack{
public:
	vector<char> element;
	int top;
	My_stack(){
		top=-1;
	}

	void push(char c){//因为取巧用了vector<char>，所以无需判断isFull，当然实际上C中应该用链表来实现栈，本就该为动态大小
		element.push_back(c);
		top++;
	}

	bool pop(){
		if(isEmpty()){
			return false;
		}
		else{
			//char c=element[top];
			element.erase(element.begin()+top);
			top--;
			return true;
		}
		
	}

	char getTop(){
		if(top==-1){//理论上来说应该直接return false，但是在isValid()中调用getTop时，直接调用了字符比较
			return ' ';//曲线救国大法：本题中' '必然不会与输入字符相匹配，因此达到return false的作用，不通用
		}//合理做法：在isValid方法中，先判断isEmpty，再调用getTop；或者getTop返回另一个不可能出现的char
		return element[top];
	}

	bool isEmpty(){
		return top==-1?true:false;
	}
};

class Solution {
public:
    bool isValid(string s) {
        My_stack stack=My_stack();
        if(s.size()==0){
        	cout<<"true"<<endl;
        	return true;
        }

        for(int i=0;i<s.size();i++){
        	if(s[i]=='('||s[i]=='{'||s[i]=='['){
        		stack.push(s[i]);
        	}
        	else if(s[i]==')'){
        		if(stack.getTop()=='('){
        			stack.pop();
        		}
        		else{
        			return false;
        		}
        	}
        	else if(s[i]=='}'){
        		if(stack.getTop()=='{'){
        			stack.pop();
        		}
        		else{
        			return false;
        		}
        	}
        	else if(s[i]==']'){
        		if(stack.getTop()=='['){
        			stack.pop();
        		}
        		else{
        			return false;
        		}
        	}
        	else{
        		return false;
        	}
        }
        if(stack.isEmpty()){
        	cout<<"true"<<endl;
        	return true;
        }
        else{
        	return false;
        }
    }
};


int main(){
	string s=")";
	Solution sol=Solution();
	sol.isValid(s);
}