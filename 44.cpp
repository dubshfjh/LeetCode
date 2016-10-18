*:任意字符串的任意序列
?:单个任意字符

bool isMatch(char* s,char* p){
	if(*s=='\0' && *p=='\0'){
		return true;
	}

	if(*p!='*'){
		return ((*p==*s)||(*p=='?' && *s!='\0'))&&isMatch(s+1,p+1);
	}

	while(*s!='\0'){
		if(isMatch(s,p+1)){
			return true;
		}
		s++;
	}

	return isMatch(s,p+1);
}


递归法按照网上所言，会超时，于是用迭代吧
bool isMatch(char* s, char* p) {
	char *ss,*pp;
	bool has_star;
	has_star=false;
	while(*s && (*p||has_star)){//s尚未匹配完 && (p未匹配完 or 之前的p出现过'*')
		if(*s==*p||*p=='?'){
			s++;
			p++;
		}
		else if(*p=='*'){
			has_star=true;
			if(*(p+1)=='\0'){
				return true;
			}
			ss=s;
			pp=++p;//p首先右移一位，然后用pp记录该位置，接下来分析(p+1)和s
		}
		else{
			if(!has_star){
				return false;
			}
			s=++ss;//ss首先右移一次，s回归到该位重新与p比较
			p=pp;
		}
	}

	while(*p && *p=='*'){
		p++;
	}
	if(*s=='\0' && *p=='\0'){
		return true;
	}
	return false;
}