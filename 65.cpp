一路上挂掉的testcase: "e", ".", " ", ".1", "1.", "+.8"
目前的代码太恶心，仍然挂在"+.8"上，直接弃坑
// bool check_num(char s){
//     if(s>='0' && s<='9'){
//         return true;
//     }
//     return false;
// }

// bool isNumber(char* s) {
//     bool pre_flag,e_flag,next_flag;
// 	while(*s==' '){
//     	s++;
//     }
//     if(*s=='\0'){
//         return false;
//     }
//     if(*s=='-'){
//     	s++;
//     	if(!check_num(*s)){
//     	    return false;
//     	}
//     }

// 	while(*s>='0' && *s<='9'){
// 	    pre_flag=true;
// 		s++;
// 	}

// 	if(*s=='.'){
// 		s++;
// 		if(!pre_flag && !check_num(*s)){
// 	        return false;
// 	    }
// 		while(*s>='0' && *s<='9'){
// 			s++;
// 		}
// 	}

// 	if(*s=='e'){
// 	    e_flag=true;
// 		s++;
// 		if(*s=='-'){
// 	    	s++;
// 	    	if(!check_num(*s)){
// 	    	    return false;
// 	    	}
// 	    }
	    
// 	    while(*s>='0' && *s<='9'){
// 	        next_flag=true;
// 			s++;
// 		}
// 	}
// 	while(*s==' '){
// 	    s++;
// 	}
// 	if(*s=='\0'){
// 	    if(e_flag){
// 	        if(!pre_flag || !next_flag){
// 	            return false;
// 	        }
// 	    }
// 		return true; 
// 	}
// 	else{
// 		return false;
// 	}
// }
// 
需要注意的testcase: "e", ".", " ", ".1", "1.", "+.8" 
class Solution {
public:
    bool isNumber(string s) {
    	int start,end;
        int size=s.size();
        if(size==0){
        	return false;
        }
        //前导0
       	start=0;
       	while(s[start]==' '){
       		start++;
       	}
       	//后导0
       	end=size-1;
       	while(s[end]==' '){
       		end--;
       	}

       	bool hasNum,hasPoint,hasE;
       	hasNum=hasPoint=hasE=false;
       	for(int i=start;i<=end;i++){
       		if(s[i]=='.'){
       			if(hasPoint || hasE){//如果前面已经有了'.'或者'e'
       				return false;
       			}
       			hasPoint=true;
       		}
       		else if(s[i]=='e'){
       			if(hasE || !hasNum){//如果前面已经有了'e'或者，没有'数字'
       				return false;
       			}
       			hasE=true;
       		}
       		else if(s[i]<'0' || s[i]>'9'){
       			//"+2"
       			if(i==start && (s[i]=='+'||s[i]=='-')){
       				continue;
       			}
       			//"1e-2"
       			else if((i!=0&&s[i-1]=='e') && (s[i]=='+'||s[i]=='-')){
       				continue;
       			}
       			else{
       				return false;
       			}
       		}
       		else{
       			hasNum=true;
       		}
       	}

       	//最后的有效位不能为'e','+','-'
       	if(s[end]=='e' || s[end]=='+' || s[end]=='-'){
       		return false;
       	}
       	//"."
       	if(!hasNum && hasPoint){
       		return false;
       	}
       	//"          "
       	if(end==-1){
       		return false;
       	}
       	return true;
    }
};

这道题的判定种类很多，没有想出好的解决方法，AC是参考上面博客的，分析很透彻，谢谢博主！

将其分析复制如下，方便查阅：

用有限状态机，非常简洁，不需要复杂的各种判断！

先枚举一下各种合法的输入情况：

1.空格+ 数字 +空格 " num "

2.空格+ 点 + 数字 +空格 " .num "

3.空格+ 符号 + 数字 +　空格 " +num "

4.空格 + 符号 + 点 +　数字　＋空格 " +num.num "

5.空格 + (1, 2, 3, 4） + e +　(1, 2, 3, 4) +空格 " numenum "

组后合法的字符可以是：

1.数字

2.空格

有限状态机的状态转移过程：

起始为0："   "

　　当输入空格时，状态仍为0，

　　输入为符号时，状态转为3，3的转换和0是一样的，除了不能再接受符号，故在0的状态的基础上，把接受符号置为-1；

　　当输入为数字时，状态转为1, 状态1的转换在于无法再接受符号，可以接受空格，数字，点，指数；状态1为合法的结束状态；

　　当输入为点时，状态转为2，状态2必须再接受数字，接受其他均为非法；

　　当输入为指数时，非法；

状态1："  num"

　　接受数字时仍转为状态1，

　　接受点时，转为状态4，可以接受空格，数字，指数，状态4为合法的结束状态，

　　接受指数时，转为状态5，可以接受符号，数字，不能再接受点，因为指数必须为整数，而且必须再接受数字；

状态2："  ."

　　接受数字转为状态4；

状态3："  +or-"

　　和0一样，只是不能接受符号；

状态4："  .num"

　　接受空格，合法接受；

　　接受数字，仍为状态4；

　　接受指数，转为状态5，

状态5：" .nume"

　　接受符号，转为状态6，状态6和状态5一样，只是不能再接受符号，

　　接受数字，转为状态7，状态7只能接受空格或数字；状态7为合法的结束状态；

状态6：".num e +or-"

　　只能接受数字，转为状态7；

状态7：".num e +or-num"

　　接受空格，转为状态8，状态7为合法的结束状态；

　　接受数字，仍为状态7；

状态8：".num e +or-num "

　　接受空格，转为状态8，状态8为合法的结束状态；


class Solution {
public:
    bool isNumber(string s) {
        //输入参数枚举
        enum InputType{
            INVALID, //代表不正确
            SPACE, // 代表空格
            SIGN, // 代表符号
            DIGIT,
            DOT, //代表点符号
            EXPONENT, //代表科学计算
            NUM_INPUTS //数字输入
        };

        int transitionTable[][NUM_INPUTS] =
        {
            -1, 0, 3, 1, 2, -1,     // next states for state 0
            -1, 8, -1, 1, 4, 5,     // next states for state 1
            -1, -1, -1, 4, -1, -1,     // next states for state 2
            -1, -1, -1, 1, 2, -1,     // next states for state 3
            -1, 8, -1, 4, -1, 5,     // next states for state 4
            -1, -1, 6, 7, -1, -1,     // next states for state 5
            -1, -1, -1, 7, -1, -1,     // next states for state 6
            -1, 8, -1, 7, -1, -1,     // next states for state 7
            -1, 8, -1, -1, -1, -1,     // next states for state 8
        };


        int state = 0, i = 0;
        while (s[i] != '\0')
        {
            InputType inputType = INVALID;
            if (isspace(s[i]))
                inputType = SPACE;
            else if (s[i] == '+' || s[i] == '-')
                inputType = SIGN;
            else if (isdigit(s[i]))
                inputType = DIGIT;
            else if (s[i] == '.')
                inputType = DOT;
            else if (s[i] == 'e' || s[i] == 'E')
                inputType = EXPONENT;

            state = transitionTable[state][inputType];

            if (state == -1)
                return false;
            else
                i++;
        }

        return state == 1 || state == 4 || state == 7 || state == 8;

    }
};