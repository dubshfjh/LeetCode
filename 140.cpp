递归代码，超时。s可以切分 == (左子串left出现在字典中) && (右子串right可以切分)。对于每一层递归，s表示上一层尚需判断是否可以切分的右子串，temp表示到上一层为止累计的left，即到上一层为止出现在字典中的所有单词
思想：对于每一层递归的字符串s，首先判断s.length()是否为0，如果为0则说明每次的递归都找到了该层s出现在字典中的左子串left(而且当前层的s已经为""了)，此时将记录每层left的字符串temp加入res中。
    如果s.length()>0，则将s分为出现在字典中的左子串left，和判断是否可以切分的右子串right。通过遍历判断字典中的word[i]是否满足s.find(word[i])==0，找到左子串left。
    然后将 右子串s.substr(left.length()) 作为下一层递归的s，将 temp+" "+left作为下一层递归的temp
class Solution {
public:
    vector<string> res;
    vector<string> wordBreak(string s, unordered_set<string>& wordDict) {
        if(s.length()==0){
            return res;
        }
        help_break(s,"",wordDict);
        return res;
    }

    void help_break(string s,string temp,unordered_set<string>& wordDict){
        if(s.length()==0){
            res.push_back(temp.substr(1));//因为对于第一个word，temp也通过+=" "+first word产生了" cat sand dog"这类结果，因此要除去第1个空格
        }
        unordered_set<string>::iterator it;
        for(it=wordDict.begin();it!=wordDict.end();it++){
            if(s.find(*it) == 0){
                string right_sub = s.substr((*it).length());
                help_break(right_sub,temp+" "+(*it),wordDict);
            }
        }
        return;
    }
};

加速思想：引入一个Map记录初始字符串s中已经拆解的每个子串，与每个子串拆解出的多个字典word组成的string的对应关系。
递归返回当前字符串s拆解出的所有可能的string格式字典word列表，用vector变量res进行记录。首先判断map中是否已有s的拆解结果，如果有就直接返回map[s]
    如果当前s尚无拆解结果，则将字符串s分解成左子串left和右子串right，一个用于递归拆解，一个直接在字典中查找
    为了加速我们优先对shorter子串进行拆解(同时直接在字典中查找longer子串)，这样可以保证在拆解更长子串时利用尽可能多的已有结果
    由于左子串的长度从1开始增加，left is shorter，所以我们只选择在字典中能查找到的右子串，并且递归拆解其对应的左子串。
    将左子串的每个拆解结果与右子串相连接后，插入到res中。使用map[s]=res记录s的拆解结果，并返回res
    PS：由于左子串需要递归拆解，所以它的长度从1开始递增.我们必须额外分析左子串为0的情况，即在字典中查找整个字符串作为1个word
    
class Solution {
public:
    unordered_map<string,vector<string>> s_words;//记录每个可拆解的字符串s 对应的所有string格式的字典words列表
    vector<string> wordBreak(string s, unordered_set<string>& wordDict) {
        return help_break(s,wordDict);
    }

    vector<string> help_break(string s,unordered_set<string>& wordDict){//递归拆解本层s对应的所有string格式的字典words列表
        vector<string> words;//记录s对应的所有string格式的单词列表,例如为"catsanddog"记录["cats and dog", "cat sand dog"].
        if(s_words.count(s)>0){//如果当前s已经有拆解结果，则直接返回
            return s_words[s];
        }
        if(wordDict.find(s) != wordDict.end()){//如果s本身存在于字典，则将s作为words的一个元素
            words.push_back(s);
        }
        for(int len=1;len<s.length();len++){//左子串长度len由1增加到length-1
            string right = s.substr(len);
            vector<string> total_words;
            if(wordDict.find(right) != wordDict.end()){//只考虑能在字典中找到的右子串right，将它对应的左子串递归拆解，
                vector<string> left_words;                    
                left_words = help_break(s.substr(0,len),wordDict);//使用vector记录左子串的每个拆解结果，

                total_words = concat_word(left_words,right);//将左子串的每个拆解字符串与固定的right组合。当左子串不能拆解时 left_words为空，此时执行concat返回的整体total_words也为空
                words.insert(words.end(),total_words.begin(),total_words.end());//将当前right和对应left的全部string格式单词列表total_words  插入到words末尾
            }
        }
        s_words[s] = words;//在map中记录s对应的全部string格式的单词列表
        return words; 
    }

    vector<string> concat_word(vector<string> left,string right){//组合左子串的每种拆解结果与固定的右子串
        for(int i=0;i<left.size();i++){
            left[i] += " "+right;
        }
        return left;
    }
};