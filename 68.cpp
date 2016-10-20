打败了0.00%的用户，这算法也是没谁了，注意边界值啊2B
class Solution {
public:
    vector<string> fullJustify(vector<string>& words, int maxWidth) {
        int i,j,size,wordlen,evenspace,leftspaces,spacenum;
        vector<string> temp,res;
        string line;
        size=words.size();
        i=wordlen=0;
        if(size==0){
        	return res;
        }
        while(i<size){
        	line="";
        	wordlen=0;
        	temp.clear();
        	while(wordlen+temp.size()<=maxWidth+1 && i<size){//每添加一个word，其后至少得有1个空格
        		wordlen+=words[i].size();//单词的累加长度
        		// cout<<wordlen<<",,,"<<words[i]<<endl;
        		temp.push_back(words[i]);
        		i++;
        	}
        	//正常的测试用例上：maxWidth应该大于任意一个word
        	if(temp.size()>1){//temp.size()>=2：只能保存1个以上的word，可能是size-1个word，也可能是size个
        	    if(wordlen+temp.size()>maxWidth){//此时需要pop掉temp的最后一个元素
            	    wordlen-=words[--i].size();
            	    cout<<"new word length: "<<wordlen<<endl;
            		temp.pop_back();	
        	    }
            	spacenum = maxWidth-wordlen;//总共需要的空格数目
	        	cout<<"spacenum："<<spacenum<<endl;
                if(temp.size()>1){//如果经历了pop后，仍然超过2个以上的元素，此时需要尽量将空格尽量平均分配给(size-1)个位置
                    evenspace = spacenum/(temp.size()-1);
                    leftspaces = spacenum-evenspace*(temp.size()-1);//左侧的leftspaces个元素需要添加(evenspace+1)个空格
                    for(j=0;j<temp.size();j++){
                	    if(j==temp.size()-1){
                	        line+=temp[j];//最后一个元素不需要添加空格啦
                	    }
                	    else{
                	        line+=temp[j]+getspace(evenspace);
                	    }
        
                		if(leftspaces>0){
                			line+=" ";
                			leftspaces--;//为左侧的前leftspaces个元素添加额外的1个空格
                		}
                	}
                }
                else{//temp经历了pop后size为1，在合理的测试用例下就是只能存储当前1个元素
                    line=temp[0]+getspace(spacenum);
                }
        	}
        	else{//temp的size初值为1，在合理的测试用例下就是只能存储当前1个元素
            	spacenum = maxWidth-wordlen;
        	    line=temp[0]+getspace(spacenum);
        	}
        
        	cout<<"line is:"<<line<<endl;
        	res.push_back(line);
        }
        if(res.size()>0){//对于最后一个元素，需要pop掉，然后为对应temp中的每个元素后加1个空格(如果已经为maxWidth，则不用再加空格)，并在最右侧填充多个空格
        	res.pop_back();
	        line="";
	        wordlen=0;
            if(temp[0].size()==maxWidth){//如果当前的字符串已经为maxWidth，则不用再加空格
                line=temp[0];
            }
            else{
               for(i=0;i<temp.size();i++){
    	        	line+=temp[i]+" ";
    	        	//cout<<"a"<<line<<"a"<<endl;
    	        	wordlen+=temp[i].size();
                }
    	        line+=getspace(maxWidth-wordlen-temp.size());

            }
	        res.push_back(line);
        }
        
        return res;
    }

    string getspace(int n){
    	string res="";
    	for(int i=0;i<n;i++){
    		res+=" ";
    	}
    	return res;
    }
};


题目大意：按照一定的格式对文本进行对齐。 
需要注意以下几点： 
1、只有一个单词直接在后面补空格，如“a”， 输出“a ” 
2、最后一组单词不需要对齐，如“a”，“b”  输出“a b ” 
3、单词与单词之间至少要有一个空格隔开

class Solution{
public:
	vector<string> fullJustify(vector<string>& words,int maxWidth){
		vector<string> res;
		int width=words[0].size();
		int num=1;//当前line中的元素数目
		int last=0;//每一次组合达到maxWidth的起始序号
		string temp;
		for(int i=1;i<words.size();i++){
			width+=words[i].size();//默认maxWidth必然大于任何word的size，因此每行至少能有1个元素
			num++;
			if(width+num-1 > maxWidth){//每相邻2个元素之间得有1个空格
				width-=words[i].size();
				num--;
				temp="";
				if(num==1){//真正存储的只有1个word
					temp+=words[i-1];
					while(temp.size()!=maxWidth){
						temp+=" ";
					}
					res.push_back(temp);
				}
				else{//存储了多个word时,但不是结尾的情况
					int blankWidth = maxWidth-width;
					int cur_width=0;
					for(int j=last;j<i;j++){
						if(j==i-1){
							cur_width=0;//最后一个单词后不加空格
						}
						else{
							cur_width=blankWidth/(num-1);//平均空格数
							cur_width=blankWidth%(num-1)>0?cur_width+1:cur_width;//左侧的部分word需要添加1个额外空格
							cout<<blankWidth<<",,,"<<num<<endl;
							blankWidth-=cur_width;
						}
						temp+=words[j];
						while(cur_width>0){
							temp+=" ";
							cur_width--;
						}
						num--;
					}
					res.push_back(temp);
				}
				//初始化下一个循环
				last=i;
				width=words[i].size();
				num=1;
			}
			// else{
			// 	continue;
			// }
		}

		if(last<words.size()){//只要进入了for循环，max(last)=words.size()-1，所以只有当words.size()==0时才不会执行本段代码
			int j=last;//需要考虑末尾不足maxWidth的情况
			temp="";
			while(j<words.size()){//先按一个空格添加words
				temp+=words[j++];
				if(temp.size()<maxWidth){
					temp+=" ";
				}
			}

			while(temp.size()<maxWidth){
				temp+=" ";
			}
			res.push_back(temp);
		}
		return res;
	}
};