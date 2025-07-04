#pragma once

#include "PropositionalFormula.h"
#include <vector>
#include <unordered_map>
using namespace std;

class TruthTable : public PropositionFormula
{
private:
    vector<string> TableHead;   // 真值表的表头，存储变量名
    vector<vector<bool>> table; // 真值表，二维数组，存储命题公式的真值表
public:
    TruthTable() : PropositionFormula() {}
    // 默认构造函数
    TruthTable(string str) : PropositionFormula(str)
    {
        variableMap.clear(); // 清空哈希表
        TableHead.clear();   // 清空真值表的表头
        table.clear();       // 清空真值表

        for (const auto &element : formula)
        {
            if (std::holds_alternative<PropositionVariable>(element.value))
            {
                const std::string &name = std::get<PropositionVariable>(element.value).name;
                if (variableMap.find(name) == variableMap.end())
                {
                    variableMap[name] = false; // 初始化变量值
                }
            }
        } // 初始化哈希表

        // 初始化真值表的表头
        for (const auto &element : formula)
        {
            if (std::holds_alternative<PropositionVariable>(element.value))
            {
                if (variableMap.find(std::get<PropositionVariable>(element.value).name) != variableMap.end() &&
                    variableMap[std::get<PropositionVariable>(element.value).name] == false) // 如果哈希表中有该变量，且该变量赋值为假
                {
                    TableHead.push_back(std::get<PropositionVariable>(element.value).name);
                    variableMap[std::get<PropositionVariable>(element.value).name] = true;
                } // 将变量名加入表头，并将哈希表中的该变量赋值为真
            }
        }
        TableHead.push_back("Result");

        // 初始化真值表
        bool result;                            // 存储命题公式的真值的变量
        int variableCount = getVariableCount(); // 获取变量的数量
        table.resize(1 << variableCount);       // 共有1 << n = 2^n行

        for (int i = 0; i < (1 << variableCount); i++)
        {
            table[i].resize(variableCount + 1); // 每行有n+1列
            AssignValue(i);                     // 为公式中的变量赋值
            for (int j = 0; j < variableCount; j++)
            {
                table[i][j] = variableMap[TableHead[j]]; // 记录各个变量的值
            } // 记录各个变量的值
            result = Calculate();             // 计算公式的真值
            table[i][variableCount] = result; // 存储真值
        }
    }
    // 构造函数，根据输入的字符串构造命题公式，并计算真值表
    ~TruthTable() {}
    // 析构函数
    void printTruthTable()
    {
        // 输出真值表的表头
        for (const auto &head : TableHead)
        {
            cout << head << "\t";
        }
        cout << endl;

        // 输出真值表
        for (const auto &row : table)
        {
            for (const auto &value : row)
            {
                cout << value << "\t";
            }
            cout << endl;
        }
    }
    // 输出真值表

    void setTableHead(const vector<string> &head)
    {
        TableHead = head;
        TableHead.push_back("Result");

        for (const auto &element : head)
        {
            if (variableMap.find(element) == variableMap.end())
            {
                variableMap[element] = false; // 初始化变量值
            }
        } // 初始化哈希表
    }
    // 设置真值表的表头

    void setTable(const vector<bool> &t)
    {
        string str = "(";
        for (int i = 0; i < TableHead.size() - 1; i++)
        {
            str += TableHead[i];
            str += "|";
        }
        str.pop_back();
        str += ")";
        setFormula(str);

        table.clear();
        int variableCount = TableHead.size() - 1;
        table.resize(1 << variableCount); // 共有1 << n = 2^n行
        for (int i = 0; i < (1 << variableCount); i++)
        {
            table[i].resize(variableCount + 1); // 每行有n+1列
            AssignValue(i);                     // 为公式中的变量赋值
            for (int j = 0; j < variableCount; j++)
            {
                table[i][j] = variableMap[TableHead[j]]; // 记录各个变量的值
            } // 记录各个变量的值
            table[i][variableCount] = t[i]; // 存储真值
        }
    }
    // 设置真值表

    void getFormula()
    {
        int i, i_variables = 0;
        string str_formula = "";
        string str_subformula = "";
        for (i = 0; i < table.size(); i++) // 遍历真值表的每一行
        {
            if (table[i][table[i].size() - 1] == false) // 如果真值为假
                continue;
            else // 如果真值为真
            {
                str_subformula = "(";
                for (int j = 0; j < table[i].size() - 1; j++) // 遍历真值表的每一列
                {
                    if (table[i][j] == false) // 如果变量的值为假
                    {
                        str_subformula += "!";
                        str_subformula += TableHead[j];
                        str_subformula += "&";
                    }
                    else
                    {
                        str_subformula += TableHead[j];
                        str_subformula += "&";
                    }
                }
                str_subformula.pop_back();
                str_subformula += ")";         // 将真值为真的行转换为合取范式的子公式
                str_formula += str_subformula; // 将子公式加入到合取范式中
                str_formula += "|";            // 加入分隔符
            }
        }
        str_formula.pop_back();  // 删除最后一个分隔符
        setFormula(str_formula); // 设置命题公式
    }
    // 获取命题公式
    friend class PropositionFormula;
    // 友元类
}; // 真值表类，用于计算命题公式的真值表