#include <bits/stdc++.h>
using namespace std;

stack<unsigned int> State_Stack;
stack<char> Symbol_Stack;
map<pair<unsigned int, char>, string> Analy_Table;
vector<string> Grammar_Table;

//初始化LR分析表
void Init_Table()
{
    pair<char, char> p;
    string str;
    p = make_pair(0, '(');
    str = "S4";
    Analy_Table.insert({p, str});
    p = make_pair(0, '0');
    str = "S5";
    Analy_Table.insert({p, str});
    p = make_pair(0, 'E');
    str = "1";
    Analy_Table.insert({p, str});
    p = make_pair(0, 'T');
    str = "2";
    Analy_Table.insert({p, str});
    p = make_pair(0, 'F');
    str = "3";
    Analy_Table.insert({p, str});
    p = make_pair(1, '+');
    str = "S6";
    Analy_Table.insert({p, str});
    p = make_pair(1, '-');
    str = "S7";
    Analy_Table.insert({p, str});
    p = make_pair(1, '$');
    str = "AC";
    Analy_Table.insert({p, str});
    p = make_pair(2, '*');
    str = "S8";
    Analy_Table.insert({p, str});
    p = make_pair(2, '/');
    str = "S9";
    Analy_Table.insert({p, str});
    p = make_pair(2, '+');
    str = "R3";
    Analy_Table.insert({p, str});
    p = make_pair(2, '-');
    str = "R3";
    Analy_Table.insert({p, str});
    p = make_pair(2, '(');
    str = "R3";
    Analy_Table.insert({p, str});
    p = make_pair(2, ')');
    str = "R3";
    Analy_Table.insert({p, str});
    p = make_pair(2, '0');
    str = "R3";
    Analy_Table.insert({p, str});
    p = make_pair(2, '$');
    str = "R3";
    Analy_Table.insert({p, str});
    p = make_pair(3, '+');
    str = "R6";
    Analy_Table.insert({p, str});
    p = make_pair(3, '-');
    str = "R6";
    Analy_Table.insert({p, str});
    p = make_pair(3, '*');
    str = "R6";
    Analy_Table.insert({p, str});
    p = make_pair(3, '/');
    str = "R6";
    Analy_Table.insert({p, str});
    p = make_pair(3, '(');
    str = "R6";
    Analy_Table.insert({p, str});
    p = make_pair(3, ')');
    str = "R6";
    Analy_Table.insert({p, str});
    p = make_pair(3, '0');
    str = "R6";
    Analy_Table.insert({p, str});
    p = make_pair(3, '$');
    str = "R6";
    Analy_Table.insert({p, str});
    p = make_pair(4, '(');
    str = "S4";
    Analy_Table.insert({p, str});
    p = make_pair(4, '0');
    str = "S5";
    Analy_Table.insert({p, str});
    p = make_pair(4, 'E');
    str = "10";
    Analy_Table.insert({p, str});
    p = make_pair(4, 'T');
    str = "11";
    Analy_Table.insert({p, str});
    p = make_pair(4, 'F');
    str = "3";
    Analy_Table.insert({p, str});
    p = make_pair(5, '+');
    str = "R8";
    Analy_Table.insert({p, str});
    p = make_pair(5, '-');
    str = "R8";
    Analy_Table.insert({p, str});
    p = make_pair(5, '*');
    str = "R8";
    Analy_Table.insert({p, str});
    p = make_pair(5, '/');
    str = "R8";
    Analy_Table.insert({p, str});
    p = make_pair(5, '(');
    str = "R8";
    Analy_Table.insert({p, str});
    p = make_pair(5, ')');
    str = "R8";
    Analy_Table.insert({p, str});
    p = make_pair(5, '0');
    str = "R8";
    Analy_Table.insert({p, str});
    p = make_pair(5, '$');
    str = "R8";
    Analy_Table.insert({p, str});
    p = make_pair(6, '(');
    str = "S4";
    Analy_Table.insert({p, str});
    p = make_pair(6, '0');
    str = "S5";
    Analy_Table.insert({p, str});
    p = make_pair(6, 'T');
    str = "12";
    Analy_Table.insert({p, str});
    p = make_pair(6, 'F');
    str = "3";
    Analy_Table.insert({p, str});
    p = make_pair(7, '(');
    str = "S4";
    Analy_Table.insert({p, str});
    p = make_pair(7, '0');
    str = "S5";
    Analy_Table.insert({p, str});
    p = make_pair(7, 'T');
    str = "13";
    Analy_Table.insert({p, str});
    p = make_pair(7, 'F');
    str = "3";
    Analy_Table.insert({p, str});
    p = make_pair(8, '(');
    str = "S4";
    Analy_Table.insert({p, str});
    p = make_pair(8, '0');
    str = "S5";
    Analy_Table.insert({p, str});
    p = make_pair(8, 'F');
    str = "14";
    Analy_Table.insert({p, str});
    p = make_pair(9, '(');
    str = "S4";
    Analy_Table.insert({p, str});
    p = make_pair(9, '0');
    str = "S5";
    Analy_Table.insert({p, str});
    p = make_pair(9, 'F');
    str = "15";
    Analy_Table.insert({p, str});
    p = make_pair(10, '+');
    str = "S6";
    Analy_Table.insert({p, str});
    p = make_pair(10, '-');
    str = "S7";
    Analy_Table.insert({p, str});
    p = make_pair(10, ')');
    str = "S16";
    Analy_Table.insert({p, str});
    p = make_pair(11, '*');
    str = "S8";
    Analy_Table.insert({p, str});
    p = make_pair(11, '/');
    str = "S9";
    Analy_Table.insert({p, str});
    p = make_pair(11, '+');
    str = "R3";
    Analy_Table.insert({p, str});
    p = make_pair(11, '-');
    str = "R3";
    Analy_Table.insert({p, str});
    p = make_pair(11, '(');
    str = "R3";
    Analy_Table.insert({p, str});
    p = make_pair(11, ')');
    str = "R3";
    Analy_Table.insert({p, str});
    p = make_pair(11, '0');
    str = "R3";
    Analy_Table.insert({p, str});
    p = make_pair(11, '$');
    str = "R3";
    Analy_Table.insert({p, str});
    p = make_pair(12, '*');
    str = "S8";
    Analy_Table.insert({p, str});
    p = make_pair(12, '/');
    str = "S9";
    Analy_Table.insert({p, str});
    p = make_pair(12, '+');
    str = "R1";
    Analy_Table.insert({p, str});
    p = make_pair(12, '-');
    str = "R1";
    Analy_Table.insert({p, str});
    p = make_pair(12, '(');
    str = "R1";
    Analy_Table.insert({p, str});
    p = make_pair(12, ')');
    str = "R1";
    Analy_Table.insert({p, str});
    p = make_pair(12, '0');
    str = "R1";
    Analy_Table.insert({p, str});
    p = make_pair(12, '$');
    str = "R1";
    Analy_Table.insert({p, str});
    p = make_pair(13, '*');
    str = "S8";
    Analy_Table.insert({p, str});
    p = make_pair(13, '/');
    str = "S9";
    Analy_Table.insert({p, str});
    p = make_pair(13, '+');
    str = "R2";
    Analy_Table.insert({p, str});
    p = make_pair(13, '-');
    str = "R2";
    Analy_Table.insert({p, str});
    p = make_pair(13, '(');
    str = "R2";
    Analy_Table.insert({p, str});
    p = make_pair(13, ')');
    str = "R2";
    Analy_Table.insert({p, str});
    p = make_pair(13, '0');
    str = "R2";
    Analy_Table.insert({p, str});
    p = make_pair(13, '$');
    str = "R2";
    Analy_Table.insert({p, str});
    p = make_pair(14, '+');
    str = "R4";
    Analy_Table.insert({p, str});
    p = make_pair(14, '-');
    str = "R4";
    Analy_Table.insert({p, str});
    p = make_pair(14, '*');
    str = "R4";
    Analy_Table.insert({p, str});
    p = make_pair(14, '/');
    str = "R4";
    Analy_Table.insert({p, str});
    p = make_pair(14, '(');
    str = "R4";
    Analy_Table.insert({p, str});
    p = make_pair(14, ')');
    str = "R4";
    Analy_Table.insert({p, str});
    p = make_pair(14, '0');
    str = "R4";
    Analy_Table.insert({p, str});
    p = make_pair(14, '$');
    str = "R4";
    Analy_Table.insert({p, str});
    p = make_pair(15, '+');
    str = "R5";
    Analy_Table.insert({p, str});
    p = make_pair(15, '-');
    str = "R5";
    Analy_Table.insert({p, str});
    p = make_pair(15, '*');
    str = "R5";
    Analy_Table.insert({p, str});
    p = make_pair(15, '/');
    str = "R5";
    Analy_Table.insert({p, str});
    p = make_pair(15, '(');
    str = "R5";
    Analy_Table.insert({p, str});
    p = make_pair(15, ')');
    str = "R5";
    Analy_Table.insert({p, str});
    p = make_pair(15, '0');
    str = "R5";
    Analy_Table.insert({p, str});
    p = make_pair(15, '$');
    str = "R5";
    Analy_Table.insert({p, str});
    p = make_pair(16, '+');
    str = "R7";
    Analy_Table.insert({p, str});
    p = make_pair(16, '-');
    str = "R7";
    Analy_Table.insert({p, str});
    p = make_pair(16, '*');
    str = "R7";
    Analy_Table.insert({p, str});
    p = make_pair(16, '/');
    str = "R7";
    Analy_Table.insert({p, str});
    p = make_pair(16, '(');
    str = "R7";
    Analy_Table.insert({p, str});
    p = make_pair(16, ')');
    str = "R7";
    Analy_Table.insert({p, str});
    p = make_pair(16, '0');
    str = "R7";
    Analy_Table.insert({p, str});
    p = make_pair(16, '$');
    str = "R7";
    Analy_Table.insert({p, str});
}

//初始化栈
void Init_Stack()
{
    State_Stack.push(0);
    Symbol_Stack.push('-');
}

unsigned int str_to_uint(string &expression)
{
    unsigned int temp = 0;
    int size = expression.size();
    for(int i = 0; i < size; i++)
    {
        if(expression[i]>='0' && expression[i]<='9')
            temp = (temp*10) + (expression[i]-'0');
    }
    return temp;
}

//初始化文法表
void Init_Grammar()
{
    string str;
    str = "S->E";
    Grammar_Table.push_back(str);
    str = "E->E+T";
    Grammar_Table.push_back(str);
    str = "E->E-T";
    Grammar_Table.push_back(str);
    str = "E->T";
    Grammar_Table.push_back(str);
    str = "T->T*F";
    Grammar_Table.push_back(str);
    str = "T->T/F";
    Grammar_Table.push_back(str);
    str = "T->F";
    Grammar_Table.push_back(str);
    str = "F->(E)";
    Grammar_Table.push_back(str);
    str = "F->0";
    Grammar_Table.push_back(str);
}

//检查输入表达式是否符合文法要求
bool is_expression(string &input)
{
    unsigned int cnt = 0;
    pair<int, char> p;
    while(1)
    {
        if(input[cnt] == '\0')
            p = make_pair(State_Stack.top(), '$');
        else
            p = make_pair(State_Stack.top(), input[cnt]);
        auto it = Analy_Table.find(p);
        //查找当前栈顶状态与输入串的分析表项
        //存在该项
        if(it != Analy_Table.end())
        {
            string expression = Analy_Table.find(p)->second;
            if(expression[0] == 'S')    //移进动作
            {
                //因为状态在分析表中用str保存需要将其转换为无符号数
                unsigned int state = str_to_uint(expression);
                State_Stack.push(state);
                Symbol_Stack.push(input[cnt]);
                cnt++;
                cout << "Shift To Statement:" << state << endl;
            }
            else if(expression[0] == 'R')   //归约动作
            {
                unsigned int seq = str_to_uint(expression);
                unsigned int len = Grammar_Table[seq].size()-3;
                for(int i = 0; i < len; i++)
                {
                    State_Stack.pop();
                    Symbol_Stack.pop();
                }
                //查询goto表
                p = make_pair(State_Stack.top(), Grammar_Table[seq][0]);
                string s = Analy_Table.find(p)->second;
                unsigned int state = str_to_uint(s);
                State_Stack.push(state);
                Symbol_Stack.push(Grammar_Table[seq][0]);
                cout << "Reduced By Production:" << Grammar_Table[seq] << endl;
            }
            else if(expression == "AC")
                return 1;
            else
                return 0;
        }
        //不存在该项
        else
        {
            return 0;
        }
    }
}


int main()
{
    Init_Table();
    Init_Stack();
    Init_Grammar();
    string input;
    cin >> input;
    
    bool is_exp = is_expression(input);
    if(is_exp)
        cout << "The expression meets the grammar requirements!!!" << endl;
    else
        cout << "ERROR:The expression does not meet the grammar requirements!!!" << endl;

    system("pause");
    return 0;
}