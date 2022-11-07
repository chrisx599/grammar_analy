#include <bits/stdc++.h>
using namespace std;

bool is_Terminator(char &c);
void get_first(vector<vector<char>> &Grammar_Table, char c,string &str);
bool is_exist(vector<char> s, char c);
void update_follow(char c, vector<vector<char>> &FOLLOW, vector<vector<char>> &Grammar_Table, char ch, vector<vector<char>> &FIRST);
void Read_Grammar(vector<vector<char>> &Grammar_Table);
void Create_FIRST(vector<vector<char>> &Grammar_Table, vector<vector<char>> &FIRST);
void Create_FOLLOW(vector<vector<char>> &Grammar_Table, vector<vector<char>> &FIRST, vector<vector<char>> &FOLLOW);
void Create_Analy_Table(vector<vector<char>> &Grammar_Table, vector<vector<char>> &FIRST, vector<vector<char>> &FOLLOW, 
                        map<pair<char, char>, vector<char>> &Analy_Table);


//从文件中读取预测分析表
void Read_Grammar(vector<vector<char>> &Grammar_Table)
{
    ifstream ifs;
    ifs.open("grammar.txt", ios::in);
    char c;
    vector<char> temp;
    for (int i = 0; !ifs.eof(); i++)
    {
        for (int j = 0; ; j++)
        {
            ifs.get(c);
            if(c == '\n' || ifs.eof())   //如果遇到换行则切换读下一行候选式
                break;
            temp.push_back(c);
        }
        Grammar_Table.push_back(temp);  //添加候选式
        temp.clear();
    }
    ifs.close();
}

//从预测分析表中构造FIRST集
void Create_FIRST(vector<vector<char>> &Grammar_Table, vector<vector<char>> &FIRST)
{
    int candidate_num = Grammar_Table.size();   //候选式个数
    vector<char> temp;
    //初始化先将非终结符放入FIRST集的首个位置
    for(int i = 0; i < candidate_num; i++)
    {
        int first_size = FIRST.size();
        bool flag = 0;
        for(int j = 0; j < first_size; j++)
        {
            //重复的非终结符不用再放入FIRST集首个
            if(FIRST[j][0] == Grammar_Table[i][0])
                flag = 1;
        }
        if(!flag)
        {
            temp.push_back(Grammar_Table[i][0]);
            FIRST.push_back(temp);
            temp.clear();
        }    
    }


    for(int i = 0; i < candidate_num; i++)
    {
        char Terminator = Grammar_Table[i][0];
        int first_size = FIRST.size();
        bool flag = 0;
        //看右部首个符号是终结符还是非终结符
        //终结符直接加入FIRST集合
        if(is_Terminator(Grammar_Table[i][3]))
        {
            for(int j = 0; j < first_size; j++)
            {
                if(FIRST[j][0] == Terminator)
                {
                    FIRST[j].push_back(Grammar_Table[i][3]);
                    flag = 1;
                    break;
                }
            }
            if(flag)
                continue;
        }
        //非终结符则开始递归查找
        else
        {
            string str = ""; 
            get_first(Grammar_Table, Grammar_Table[i][3], str);
            int size = str.size();
            for(int j = 0; j < first_size; j++)
            {
                if(FIRST[j][0] == Terminator)
                {
                    for(int k = 0; k < size; k++)
                    {
                        FIRST[j].push_back(str[k]);
                    }
                    break;
                }
            }
        }
    }
}

//是否为终结符
bool is_Terminator(char &c)
{
    if(c >= 'A' && c <= 'Z')
        return 0;
    return 1;
}

//获取非终结符的首个终结符串
void get_first(vector<vector<char>> &Grammar_Table, char c, string &str)
{
    int candidate_num = Grammar_Table.size();   //候选式个数
    //当前符号是非终结符
    if(!is_Terminator(c))
    {
        for(int i = 0; i < candidate_num; i++)
        {
            char temp;
            if(Grammar_Table[i][0] == c)
            {
                temp = c;
                c = Grammar_Table[i][3];
                get_first(Grammar_Table, c, str);   //递归查找
                c = temp;   //完成后将c恢复为非终结符继续开始下一个候选式查找
            }
        }
    }
    //当前符号是终结符
    else
        str+=c;
}

//从预测分析表构造FOLLOW集
void Create_FOLLOW(vector<vector<char>> &Grammar_Table, vector<vector<char>> &FIRST, vector<vector<char>> &FOLLOW)
{
    int candidate_num = Grammar_Table.size();   //候选式个数
    vector<char> temp;
    //初始化先将非终结符放入FOLLOW集的首个位置
    for(int i = 0; i < candidate_num; i++)
    {
        int follow_size = FOLLOW.size();
        bool flag = 0;
        for(int j = 0; j < follow_size; j++)
        {
            //重复的非终结符不用再放入FOLLOW集首个
            if(FOLLOW[j][0] == Grammar_Table[i][0])
                flag = 1;
        }
        if(!flag)
        {
            temp.push_back(Grammar_Table[i][0]);
            FOLLOW.push_back(temp);
            temp.clear();
        }    
    }
    FOLLOW[0].push_back('$');   //将$放入起始符号的FOLLOW集中


    for(int i = 0; i < candidate_num; i++)
    {
        char Terminator = Grammar_Table[i][0];
        int follow_size = FOLLOW.size();
        bool flag = 0;
        //从右部最后一个符号开始一个一个向左处理
        int right_lenth = Grammar_Table[i].size() - 3;
        for(int j = right_lenth-1+3; j > 2; j--)
        {
            //看当前符号是终结符还是非终结符
            //如果是终结符
            if(is_Terminator(Grammar_Table[i][j]))
            {
                //看前面的一个符号是终结符还是非终结符号
                //如果是终结符
                if(is_Terminator(Grammar_Table[i][j-1]))
                    continue;
                else
                {
                    //如果是非终结符则添加当前符号进入非终结符的FOLLOW集中
                    for(int k = 0; k < follow_size; k++)
                    {
                        if(Grammar_Table[i][j-1] == FOLLOW[k][0])
                        {
                            FOLLOW[k].push_back(Grammar_Table[i][j]);
                            //FOLLOW集变化需要更新
                            update_follow(FOLLOW[k][0], FOLLOW, Grammar_Table, Grammar_Table[i][j], FIRST);
                            flag = 1;
                            break;
                        }
                    }
                    if(flag)
                        continue;
                }
            }
            //如果是非终结符号
            else
            {
                //是否是右部最后一个符号
                //是右部最后一个符号
                if(j == right_lenth-1+3)
                {
                    //看与左部符号是否相同
                    if(Terminator == Grammar_Table[i][j])
                        continue;
                    //将左部符号的FOLLOW集全部加入当前符号的FOLLOW集
                    for(int k = 0; k < follow_size; k++)
                    {
                        if(Terminator == FOLLOW[k][0])
                        {
                            int len = FOLLOW[k].size(); //当前左部符号的FOLLOW集长度
                            for(int q = 0; q < follow_size; q++)
                            {
                                if(FOLLOW[q][0] == Grammar_Table[i][j])
                                {
                                    for(int t = 1; t < len; t++)
                                    {
                                        FOLLOW[q].push_back(FOLLOW[k][t]);
                                    }
                                    break;
                                }
                            }
                            break;
                        }
                    }
                }
                //不是右部最后一个符号
                else
                {
                    //后面是终结符的情况已经处理
                    //后面是非终结符
                    //将后一个符号的FIRST集全部加入当前符号的FOLLOW集
                    //version_1.0只能处理右部符号有两个非终结符如E->AT
                    for(int k = 0; k < follow_size; k++)
                    {
                        if(Grammar_Table[i][j+1] == FIRST[k][0])
                        {
                            int len = FIRST[k].size(); //当前后一个符号的FIRST集长度
                            for(int q = 1; q < len; q++)
                            {
                                //当前终结符是#
                                if(FIRST[k][q] == '#')
                                {
                                    //当前非终结符是右部最后一个符号
                                    //将左部符号的FOLLOW集全部放入当前符号的FOLLOW集
                                    for(int p = 0; p < follow_size; p++)
                                    {
                                        if(Terminator == FOLLOW[p][0])
                                        {
                                            int len2 = FOLLOW[p].size(); //当前左部符号的FOLLOW集长度
                                            for(int m = 0; m < follow_size; m++)
                                            {
                                                if(FOLLOW[m][0] == Grammar_Table[i][j])
                                                {
                                                    for(int t = 1; t < len2; t++)
                                                    {
                                                        if(!is_exist(FOLLOW[m], FOLLOW[p][t]))
                                                            FOLLOW[m].push_back(FOLLOW[p][t]);
                                                    }
                                                    break;
                                                }
                                            }
                                            break;
                                        }
                                    } 
                                }
                                //当前符号不是#
                                else
                                {
                                    for(int n = 0; n < follow_size; n++)
                                    {
                                        if(FOLLOW[n][0] == Grammar_Table[i][j])
                                        {
                                            if(!is_exist(FOLLOW[n], FIRST[k][q]))
                                                FOLLOW[n].push_back(FIRST[k][q]);
                                            break;
                                        }
                                    }
                                }
                            }
                            break;
                        }
                    }
                }
            }
        }
    }
}

//查看vector<char> s中是否有字符c
bool is_exist(vector<char> s, char c)
{
    int size = s.size();
    for(int i = 0; i < size; i++)
    {
        if(s[i] == c)
            return 1;
    }
    return 0;
}

//更新follow集
void update_follow(char c, vector<vector<char>> &FOLLOW, vector<vector<char>> &Grammar_Table, char ch, vector<vector<char>> &FIRST)
{
    int size = Grammar_Table.size();
    int last;
    for(int i = 0; i < size; i++)
    {
        if(Grammar_Table[i][0] == c)
        {
            last = Grammar_Table[i].size()-1;
            if(is_Terminator(Grammar_Table[i][last]))
                return;
            int follow_size = FOLLOW.size();
            for(int j = 0; j < follow_size; j++)
            {
                if(FOLLOW[j][0] == Grammar_Table[i][last])
                {
                    FOLLOW[j].push_back(ch);
                    break;
                }
            }
            //如果更新的这个last非终结符可以推空还需要更新它前面的非终结符
            int first_size = FIRST.size();
            bool flag = 0;
            for(int j = 0; j < first_size; j++)
            {
                if(FIRST[j][0] == Grammar_Table[i][last])
                {
                    flag = is_exist(FIRST[j], '#');
                    break;
                }
            }
            if(flag)
            {
                for(int q = 0; q < follow_size; q++)
                {
                    if(FOLLOW[q][0] == Grammar_Table[i][last-1])
                    {
                        FOLLOW[q].push_back(ch);
                        update_follow(Grammar_Table[i][last-1], FOLLOW, Grammar_Table, ch, FIRST);
                        break; 
                    }
                }
            }
        }
    }
}

void Create_Analy_Table(vector<vector<char>> &Grammar_Table, vector<vector<char>> &FIRST, vector<vector<char>> &FOLLOW, 
                        map<pair<char, char>, vector<char>> &Analy_Table)
{
    int candidate_num = Grammar_Table.size();
    for(int i = 0; i < candidate_num; i++)
    {
        pair<char, char> p;
        int first_size = FIRST.size();
        for(int j = 0; j < first_size; j++)
        {
            //找到产生式左部符号的FIRST集
            if(Grammar_Table[i][0] == FIRST[j][0])
            {
                int len = FIRST[j].size();
                if(!is_Terminator(Grammar_Table[i][3])) //产生式右部首个符号是非终结符
                {
                    for(int k = 1; k < len; k++)
                    {
                        //将产生式添加进左部符号和终结符组成的表中
                        p = make_pair(Grammar_Table[i][0], FIRST[j][k]);
                        Analy_Table.insert({p, Grammar_Table[i]});
                    }
                }
                else    //产生式右部首个符号是终结符
                {
                    for(int k = 1; k < len; k++)
                    {
                        //看是否是#推空符号
                        if(FIRST[j][k] == '#')
                        {
                            if(FIRST[j][k] == Grammar_Table[i][3])
                            {
                                int len2 = FOLLOW[j].size();
                                for(int q = 1; q < len2; q++)
                                {
                                    //将其加入到左部符号的FOLLOW集中
                                    p = make_pair(Grammar_Table[i][0], FOLLOW[j][q]);
                                    Analy_Table.insert({p, Grammar_Table[i]});
                                }
                                break;
                            }
                        }
                        else
                        {
                            if(FIRST[j][k] == Grammar_Table[i][3])
                            {
                                //将其加入到左部符号的FIRST集中
                                p = make_pair(Grammar_Table[i][0], FIRST[j][k]);
                                Analy_Table.insert({p, Grammar_Table[i]});
                                break;
                            }
                        }
                    }
                }
                break;
            }
        }
    }
}

//将vector转为str
void vechar_to_str(vector<char> &expression, string &str)
{
    int size = expression.size();
    for(int i = 0; i < size; i++)
        str+=expression[i];
}

//判断传入的input是否符合文法要求
bool is_expression(stack<char> &s, string &input, map<pair<char, char>, vector<char>> &Analy_Table)
{
    unsigned int cnt = 0;
    while(s.top() != '$' || input[cnt] != '\0')
    {
        if(is_Terminator(s.top()))
        {
            if(s.top() == input[cnt])
            {
                s.pop();
                cnt++;
                continue;
            }
            else
            {
                cout << "Error!!!" << endl;
                return 0;
            }
        }
        pair<char, char> p;
        if(input[cnt] == '\0')
            p = make_pair(s.top(), '$');
        else
            p = make_pair(s.top(), input[cnt]);
        auto it = Analy_Table.find(p);
        if(it == Analy_Table.end())
        {
            cout << "Error!!!" << endl;
            return 0;
        }
        else
        {
            vector<char> expression = Analy_Table.find(p)->second;
            string str = "";
            vechar_to_str(expression, str);
            cout << "Use Production:" << str << endl;
            int len = expression.size();
            //如果产生式为推空
            if(expression[len-1] == '#')
                s.pop();
            else
            {
                s.pop();
                for(int i = len-1; i > 2; i--)
                    s.push(expression[i]);
            }
        }
    }
    if(s.top() == '$' && input[cnt] == '\0')
        return 1;
    else
        return 0;
}

int main()
{
    vector<vector<char>> Grammar_Table;
    Read_Grammar(Grammar_Table);
    vector<vector<char>> FIRST;
    Create_FIRST(Grammar_Table, FIRST);
    vector<vector<char>> FOLLOW;
    Create_FOLLOW(Grammar_Table, FIRST, FOLLOW);
    map<pair<char, char>, vector<char>> Analy_Table;
    Create_Analy_Table(Grammar_Table, FIRST, FOLLOW, Analy_Table);

    string input;
    cin >> input;
    stack<char> s;
    s.push('$');
    s.push('E');

    bool is_exp = is_expression(s, input, Analy_Table);
    if(is_exp)
        cout << "The expression meets the grammar requirements!!!" << endl;
    else
        cout << "ERROR:The expression does not meet the grammar requirements!!!" << endl;

    system("pause");
    return 0;
}