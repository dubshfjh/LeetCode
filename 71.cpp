常见测试用例和边界测试用例
"/a/.."==>"/"
"a/"==>"无返回"
"/a/."==>"/a"
"/a/b."==>"/a/b."
"/a/b.."==>"/a/b.."
"/a/./b/"==>"/a/b"
"/"==>"/"
"/../"==>"/"
"/a//b/"==>"/a/b"
"/a/../../c/"==>"/c"
PS：这种解法，渣到不忍直视，
应该使用'/'作为分隔符将文件路径分割成数组后，考虑栈的push和pop就行了
同样可以避免所有边界用例：'\0'充当".." and "."后方的'/'，或者文件层次分隔符；以及'..'和'.'之前必须有'/'才起作用。
class Solution {
public:
    string simplifyPath(string path) {
        int i=1;
        string temp="";
        string res="/";
        vector<string> stack;
        if(path[0]!='/'){
        	return "";
        }
        while(i<path.size()){
        	if(path[i]=='.'){//如果'.'之前不是'/'，则视'.'为普通字符
        	    if(path[i-1]=='/'){
        	        // cout<<"i:"<<i<<"    "<<path[i]<<path[i+1]<<path[i+2]<<endl;
        	        if(path[i+1]=='\0' || path[i+1]=='/'){//"执行 ./"，也就是直接忽略'./'的存在
            			i+=2;
            		}
            		else if(path[i+1]=='.'){//可能执行"../" or 视作普通字符串".."
            			if(path[i+2]=='\0' || path[i+2]=='/'){//".."之后为末尾 or 为'/'，则执行"../"
            			    cout<<"执行 ../"<<endl;
            				if(stack.size()>0){//执行"../"效果：如果之前还剩余文件层，则减少一层；若之前0层文件，则直接忽略"../"
            					stack.pop_back();
            				}
            				i+=3;
            			}
            			else{//视作普通字符串".."
            				temp+="..";
            				i+=2;
            			}
            		}
            		else{//"."被视作普通字符串
            			temp+=".";
            			i+=1;
            		}
        	    }
        		else{//"."也会被视作普通字符串
        		    temp+=".";
        		    i+=1;
        		}
        	}
        	else if(path[i]=='/'){//'/'可视为文件层次的分隔符，若当前层次路径temp不为空，则将temp入栈，并且清空temp；若本层路径为空，则忽略"/"
        		if(temp.size()>0){
            	    // cout<<"temp is:"<<temp<<endl;
        			stack.push_back(temp);
        			temp="";
        		}
        		i++;
        	}
        	else{//对于"/"和"."之外的普通字符，一律视作当前层次路径的某个字符，直接加入temp
        		temp+=path[i++];
        	}
        }
        if(temp.size()>0){//'/'和'\0'都可以作为文件层次的分隔符，若到了末尾的temp仍有值则入栈
            stack.push_back(temp);
        }

        if(stack.size()>0){//每个路径层次以"/"分隔开来
            for(i=0;i<stack.size();i++){
            	res+=stack[i]+"/";
            }
            res=res.substr(0,res.size()-1);
        }
        
        return res;
    }
};



核心在于编写一个以'/'为分隔符的split函数

以及用进出栈来保存最简路径。

path:"/a/./b/../../c/"

split:"a",".","b","..","..","c"

stack:push(a), push(b), pop(b), pop(a), push(c) --> c

// PS：string (InputIterator first, InputIterator last);
// 	 Copies the sequence of characters in the range [first,last), in the same order.

// InputIterator find_if ( InputIterator first, InputIterator last, Predicate pred )  
// 	在区间[first,end)中搜寻使一元判断式pred为true的第一个元素。如果没找到，返回end。

class Solution {
public:
	static bool isslash(char c){
    	return (c=='/');
    }

    static bool notslash(char c){
    	return !isslash(c);
    }

    vector<string> split(string s){
    	vector<string> res;
    	string::iterator it_left=s.begin();
    	while(it_left!=s.end()){
    		it_left=find_if(it_left,s.end(),notslash);//it_left：当前一系列"///.///"后的第一个字符
    		string::iterator it_right=find_if(it_left,s.end(),isslash);//it_right：从it_left开始遇到的第一个"/"
    		
    		if(it_left!=s.end()){//防止最后一个字符为'/'时会向栈中压入空字符串"""
    			string temp=string(it_left,it_right);//获取两段"/"分割得到的字符串
    			res.push_back(temp);
    		}
    		
    		it_left=it_right;
    	}
    	return res;
    }

    string simplifyPath(string path) {
        vector<string> str_arr;
        stack<string> my_stack;
        string res;
        str_arr=split(path);
        for(int i=0;i<str_arr.size();i++){
            cout<<str_arr[i]<<endl;
        	if(str_arr[i]=="."){
        		continue;
        	}
        	else if(str_arr[i]==".."){
        		if(my_stack.size()>0){
        			my_stack.pop();
        		}
        	}
        	else{
        		my_stack.push(str_arr[i]);
        	}
        }

        while(!my_stack.empty()){
        	res="/"+my_stack.top()+res;
        	my_stack.pop();
        }
        if(res==""){
        	return "/";
        }
        return res;
    }
};