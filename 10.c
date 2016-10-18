
bool isMatch(char* s, char* p) {
    //assert(s&&p); //Leetcode不允许assert,实际上代码也不会执行到s or p为NULL的情况
    if(*p=='\0'){//模式串p匹配到末尾时，若s尚未到末尾则false,若s也到末尾则true
        return (*s=='\0');
    }
    
    if(*(p+1)!='*'){//如果*(p+1)不为*，则需要比较*p和*s是否相等 or *p='.'而且s未到末尾，然后检测(s+1,p+1)这一段字符串是否匹配
        //assert(*p=='*');
        return ((*p==*s)||(*p=='.'&&*s!='\0'))&&isMatch(s+1,p+1);
    }
    //此时*(p+1)=='*'
    while(*p==*s||(*p=='.'&&*s!='\0')){// 循环遍历每一种匹配情况，一旦一种成功则return true
        if(isMatch(s,p+2)){//以*p之后为"a*bc",*s之后为"aaabc"为例分析：检测(aaabc,bc)，发现返回false后,s++,此时*p==*s
            return true;//检测(aabc,bc)，发现返回false后，s++，此时*p==*s；检测(abc,bc)，返回false后,s++，此时*p!=*s，跳出循环
        }//执行检测(bc,bc)，*(p+1)!='*'，return(true||false)&&isMatch("c","c")；return(true||false)&&isMatch('\0','\0')；*p=='\0',*s=='\0',return true
        s++;
    }
    return isMatch(s,p+2);
}