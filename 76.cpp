由于大小写字母的ASCII码不大于128，因此开辟两个数组存储信息。

1.needFind数组存储T字符串每个字符出现次数。例如：needFind['A']=5意为T中A出现5次。

2.Found数组存储S字符串在[begin,end]窗口内每个字符出现次数。

算法核心思想如下：

1.在保证[begin,end]窗口包含T中所有字符的条件下，延伸end，收缩begin。

2.进行一次扫描后，记录符合条件的最小窗口(end-begin+1)表示的字符串。

有个问题：怎样才知道[begin,end]窗口包含了T中所有字符？

我使用count记录剩余“有效”字符数，当count达到0时，即可说明[begin,end]包含了T。

注意：“有效”的意思是指，当前延伸得到的S[end]字符，使得[begin,end]更进一步包含T，而不是重复劳动。

比如说，T="a", [begin,end]已经包含"a",再延伸得到"aa"，只是无效操作，并没有使得[begin,end]更接近T,有效字符数仍为1.

class Solution {
public:
    string minWindow(string s, string t) {
        int begin,end,minbegin,minend,minsize,count;
        begin=end=0;
        minbegin=minend=0;
        minsize=INT_MAX;

        vector<int> needFind(128,0);
        vector<int> haveFound(128,0);

        for(int i=0;i<t.size();i++){
        	needFind[t[i]] ++;
        }

        haveFound[s[0]] ++;
        count=t.size();
        if(needFind[s[0]] >= haveFound[s[0]]){//如果s[0]是T中需要找到的字符之一，则count--，否则count保持原值
        	count--;
        }

        while(true){
        	if(count==0){//此时[begin,end]已经包含了T，所以收缩begin求得此次的最短间距
        		while(haveFound[s[begin]] > needFind[s[begin]]){//此时begin字符是有剩余的(或者不在T中，或者在S中找到了过多次)
        			haveFound[s[begin]] --;//将begin字符的出现次数-1
        			begin++;//分析下一个字符
        		}
        		int size = end-begin+1;
	        	if(size<minsize){
	        		minsize=size;
	        		minbegin=begin;
	        		minend=end;
	        	}
        	}

        	if(end<s.size()){//向右延伸end一次
        		end++;
        		haveFound[s[end]] ++;
        		if(needFind[s[end]] >= haveFound[s[end]]){//如果s[end]仍然是T中尚未找满次数的字符，则count--，否则count保持不变
        			count--;
        		}
        	}
        	else{
        		break;
        	}
        }

        if(minsize != INT_MAX){
        	return s.substr(minbegin,minsize);
        }
        else{
        	return "";
        }
    }
};