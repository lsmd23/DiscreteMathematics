#pragma once

#include "PropositionalFormula.h"
#include <vector>
#include <string>
#include <unordered_map>
#include <iostream>
using namespace std;

class Clause : public PropositionFormula
{
public:
    Clause() : PropositionFormula() {}
    // 默认构造函数
    Clause(string str) : PropositionFormula(str) {}
    // 构造函数，根据输入的字符串构造子句
    ~Clause() {}
    // 析构函数
    Clause &operator=(const Clause &c)
    {
        formula = c.formula;
        return *this;
    }
    // 重载赋值运算符
    bool operator==(const Clause &c)
    {
        if (formula.size() != c.formula.size())
        {
            return false;
        }
        for (size_t i = 0; i < formula.size(); ++i)
        {
            if (formula[i] != c.formula[i])
            {
                return false;
            }
        }
        return true;
    }
    // 重载等于运算符，两个子句是否相等当且仅当它们的公式相等

    bool isDisjunctive()
    {
        bool expectOperand = true; // 初始状态期望操作数
        for (size_t i = 0; i < formula.size(); ++i)
        {
            if (std::holds_alternative<char>(formula[i].value))
            {
                char op = std::get<char>(formula[i].value);
                if (op == '!')
                {
                    if (i + 1 >= formula.size() || !std::holds_alternative<PropositionVariable>(formula[i + 1].value))
                    {
                        return false; // '!' 后面必须是命题变元
                    }
                    expectOperand = true; // '!' 后面期望命题变元
                }
                else if (op == '|')
                {
                    if (expectOperand)
                    {
                        return false; // '|' 前面必须是命题变元
                    }
                    expectOperand = true; // '|' 后面期望命题变元
                }
                else if (op == '(')
                {
                    if (!expectOperand)
                    {
                        return false; // 左括号前必须是'|'或者'('
                    }
                    if (i - 1 >= 0 && std::holds_alternative<char>(formula[i - 1].value) && std::get<char>(formula[i - 1].value) == '!')
                    {
                        return false; // 左括号前不能是'!'
                    }
                    expectOperand = true; // 左括号后期望操作数
                } // 左括号前只能是'|'或者'('
                else if (op == ')')
                {
                    if (expectOperand)
                    {
                        return false; // 右括号前必须是命题变元
                    }
                    expectOperand = false; // 右括号后期望操作符
                } // 右括号前只能是命题变元或者')'
                else
                {
                    return false; // 非法字符
                }
            }
            else if (std::holds_alternative<PropositionVariable>(formula[i].value))
            {
                if (!expectOperand)
                {
                    return false; // 命题变元前面必须是操作符
                }
                expectOperand = false; // 命题变元后面期望操作符
            }
        }
        return !expectOperand; // 最后一个必须是命题变元
    }
    // 判断是否是标准的析取范式

    bool deleteBrackets()
    {
        if (!isDisjunctive())
        {
            return false;
        } // 如果不是析取范式，返回false
        for (size_t i = 0; i < formula.size(); ++i)
        {
            if (std::holds_alternative<char>(formula[i].value))
            {
                char op = std::get<char>(formula[i].value);
                if (op == '(' || op == ')')
                {
                    formula.erase(formula.begin() + i);
                    i--;
                }
            }
        }
        return true;
    }
    // 删除所有的括号

    bool haveComplementaryPair(Clause &clause)
    {
        setVariableMap();        // 设置哈希表
        clause.setVariableMap(); // 设置哈希表
        if (!isDisjunctive() || !clause.isDisjunctive())
        {
            return false;
        } // 如果不是析取范式，返回false
        for (size_t i = 0; i < formula.size(); ++i) // 遍历本子句
        {
            for (size_t j = 0; j < clause.formula.size(); ++j) // 遍历另一子句
            {
                if (std::holds_alternative<PropositionVariable>(formula[i].value) &&
                    std::holds_alternative<PropositionVariable>(clause.formula[j].value)) // 如果都是命题变元
                {
                    if (std::get<PropositionVariable>(formula[i].value).name ==
                        std::get<PropositionVariable>(clause.formula[j].value).name) // 如果两个命题变元名字相同
                    {
                        if (std::get<PropositionVariable>(formula[i].value).value !=
                            std::get<PropositionVariable>(clause.formula[j].value).value) // 如果两个命题变元真值不同
                        {
                            return true;
                        }
                        // 返回true
                    }
                } // 如果都是命题变元
            }
        }
        return false;
    }
    // 判断是否有互补对

    Clause resolution(Clause &clause)
    {
        setVariableMap();                           // 设置哈希表
        clause.setVariableMap();                    // 设置哈希表
        unordered_map<string, bool> newVariableMap; // 新的哈希表
        for (const auto &var : variableMap)
        {
            if (clause.variableMap.find(var.first) != clause.variableMap.end())
            {
                if (var.second != clause.variableMap.at(var.first))
                {
                    continue; // 如果两个哈希表中键相同但值不同，直接舍弃
                }
            }
            newVariableMap[var.first] = var.second; // 将值相同的键加入新的哈希表
        }

        for (const auto &var : clause.variableMap)
        {
            if (newVariableMap.find(var.first) == newVariableMap.end())
            {
                if (variableMap.find(var.first) != variableMap.end())
                {
                    continue; // 如果两个哈希表中键相同但值不同，直接舍弃
                }
                newVariableMap[var.first] = var.second; // 将不在新哈希表中的键加入新的哈希表
            }
        }

        string newFormulaString = "("; // 新的字符串
        for (auto &map : newVariableMap)
        {
            if (!map.second) // 如果值为false
            {
                newFormulaString += "!";
            }
            newFormulaString += map.first + "|"; // 构造新的字符串
        }
        newFormulaString.pop_back(); // 删除最后一个'|'
        if (!newFormulaString.empty())
        {
            newFormulaString += ")";
        } // 如果非空，则加上右括号
        Clause newClause(newFormulaString); // 构造新的子句

        for (auto &element : newClause.formula)
        {
            if (std::holds_alternative<PropositionVariable>(element.value))
            {
                std::get<PropositionVariable>(element.value).value = newVariableMap.at(std::get<PropositionVariable>(element.value).name);
            }
        } // 为新子句赋值

        return newClause;
    }
    // 消元，返回新的归结后的子句

    void toCNF()
    {
        Clause newClause = *this;
        newClause = newClause.eliminateEquivalence(); // 消除等价符号
        cout << newClause.Print() << endl;
        newClause = newClause.eliminateImplication(); // 消除蕴含
        cout << newClause.Print() << endl;

        Clause tempClause;
        do
        {
            tempClause = newClause;
            newClause = newClause.applyDeMorgan();
            // 一直循环直到新子句和旧子句相等
        } while (!(newClause == tempClause));
        cout << newClause.Print() << endl;

        newClause = newClause.eliminateDoubleNegation(); // 消除双重否定
        cout << newClause.Print() << endl;

        this->formula = newClause.formula; // 更新公式
    }
    // 转换为合取范式
    // TODO: 该函数尚未完成

    void assignValue()
    {
        for (int i = 0; i < formula.size(); i++) // 遍历公式
        {
            if (std::holds_alternative<PropositionVariable>(formula[i].value)) // 如果是命题变元
            {
                if (std::get<char>(formula[i - 1].value) && std::get<char>(formula[i - 1].value) == '!') // 如果命题变元前有!
                {
                    std::get<PropositionVariable>(formula[i].value).value = false;
                }
                else
                {
                    std::get<PropositionVariable>(formula[i].value).value = true;
                }
            }
        }
    }
    // 依照命题变元前是否有!来判断真值，若无!则真值为true，若有!则真值为false

private:
    Clause eliminateEquivalence() const
    {
        Clause newClause(*this); // 创建一个新的子句对象
        // 遍历公式，消除等价符号
        for (size_t i = 0; i < newClause.formula.size(); ++i)
        {
            if (std::holds_alternative<char>(newClause.formula[i].value))
            {
                char op = std::get<char>(newClause.formula[i].value);
                if (op == '~')
                {
                    // 找到等价符号两侧的操作数
                    int leftStart = i - 1;
                    int leftEnd = i - 1;
                    int rightStart = i + 1;
                    int rightEnd = i + 1;

                    // 向前找到左操作数
                    if (std::holds_alternative<char>(newClause.formula[leftStart].value) && std::get<char>(newClause.formula[leftStart].value) == ')')
                    {
                        int bracketCount = 1;
                        leftStart--;
                        while (leftStart >= 0 && bracketCount > 0)
                        {
                            if (std::holds_alternative<char>(newClause.formula[leftStart].value))
                            {
                                char ch = std::get<char>(newClause.formula[leftStart].value);
                                if (ch == ')')
                                {
                                    bracketCount++;
                                }
                                else if (ch == '(')
                                {
                                    bracketCount--;
                                }
                            }
                            leftStart--;
                        }
                        leftStart++;
                    }

                    // 向后找到右操作数
                    if (std::holds_alternative<char>(newClause.formula[rightEnd].value) && std::get<char>(newClause.formula[rightEnd].value) == '(')
                    {
                        int bracketCount = 1;
                        rightEnd++;
                        while (rightEnd < newClause.formula.size() && bracketCount > 0)
                        {
                            if (std::holds_alternative<char>(newClause.formula[rightEnd].value))
                            {
                                char ch = std::get<char>(newClause.formula[rightEnd].value);
                                if (ch == '(')
                                {
                                    bracketCount++;
                                }
                                else if (ch == ')')
                                {
                                    bracketCount--;
                                }
                            }
                            rightEnd++;
                        }
                        rightEnd--;
                    }

                    // 构造新的公式
                    vector<Element> newFormula;
                    newFormula.push_back(Element('('));
                    for (int j = leftStart; j <= leftEnd; ++j)
                    {
                        newFormula.push_back(newClause.formula[j]);
                    }
                    newFormula.push_back(Element('^'));
                    for (int j = rightStart; j <= rightEnd; ++j)
                    {
                        newFormula.push_back(newClause.formula[j]);
                    }
                    newFormula.push_back(Element(')'));
                    newFormula.push_back(Element('&'));
                    newFormula.push_back(Element('('));
                    for (int j = rightStart; j <= rightEnd; ++j)
                    {
                        newFormula.push_back(newClause.formula[j]);
                    }
                    newFormula.push_back(Element('^'));
                    for (int j = leftStart; j <= leftEnd; ++j)
                    {
                        newFormula.push_back(newClause.formula[j]);
                    }
                    newFormula.push_back(Element(')'));

                    // 替换原公式中的等价符号及其操作数
                    newClause.formula.erase(newClause.formula.begin() + leftStart, newClause.formula.begin() + rightEnd + 1);
                    newClause.formula.insert(newClause.formula.begin() + leftStart, newFormula.begin(), newFormula.end());
                    i = leftStart + newFormula.size() - 1;
                }
            }
        }
        return newClause;
    }

    Clause eliminateImplication() const
    {
        Clause newClause(*this); // 创建一个新的子句对象
        for (size_t i = 0; i < newClause.formula.size(); ++i)
        {
            if (std::holds_alternative<char>(newClause.formula[i].value))
            {
                char op = std::get<char>(newClause.formula[i].value);
                if (op == '^')
                {
                    newClause.formula[i] = Element('|'); // 将^替换为|
                    int j = i - 1;
                    int bracketCount = 0;
                    while (j >= 0)
                    {
                        if (std::holds_alternative<char>(newClause.formula[j].value))
                        {
                            char prevOp = std::get<char>(newClause.formula[j].value);
                            if (prevOp == ')')
                            {
                                bracketCount++;
                            }
                            else if (prevOp == '(')
                            {
                                bracketCount--;
                                if (bracketCount == 0)
                                {
                                    newClause.formula.insert(newClause.formula.begin() + j, Element('!'));
                                    break;
                                }
                            }
                        }
                        else if (bracketCount == 0)
                        {
                            newClause.formula.insert(newClause.formula.begin() + j, Element('!'));
                            break;
                        }
                        j--;
                    }
                    // 向前，找到第一个操作数，在前面插入!
                    // 如果前方是右括号，继续向前找，直到找到左括号，在左括号前插入!
                }
            }
        }
        // 再消除蕴含
        return newClause;
    }

    Clause eliminateDoubleNegation() const
    {
        Clause newClause(*this); // 创建一个新的子句对象
        // 遍历公式，消除双重否定
        for (size_t i = 0; i < newClause.formula.size() - 1; ++i)
        {
            if (std::holds_alternative<char>(newClause.formula[i].value) && std::get<char>(newClause.formula[i].value) == '!' &&
                std::holds_alternative<char>(newClause.formula[i + 1].value) && std::get<char>(newClause.formula[i + 1].value) == '!')
            {
                newClause.formula.erase(newClause.formula.begin() + i, newClause.formula.begin() + i + 2);
                --i;
            }
        }
        return newClause;
    }

    Clause applyDeMorgan() const
    {
        Clause newClause(*this); // 创建一个新的子句对象
        // 遍历公式，应用德摩根定律
        for (size_t i = 0; i < newClause.formula.size(); ++i)
        {
            if (std::holds_alternative<char>(newClause.formula[i].value) && std::get<char>(newClause.formula[i].value) == '!')
            {
                if (i + 1 < newClause.formula.size())
                {
                    if (std::holds_alternative<char>(newClause.formula[i + 1].value) && std::get<char>(newClause.formula[i + 1].value) == '(')
                    {
                        // 找到括号内的内容，start和end分别是括号的起始和结束位置
                        int start = i + 1;
                        int end = i + 1;
                        int bracketCount = 1;
                        while (end < newClause.formula.size() && bracketCount > 0)
                        {
                            end++;
                            if (std::holds_alternative<char>(newClause.formula[end].value))
                            {
                                char ch = std::get<char>(newClause.formula[end].value);
                                if (ch == '(')
                                {
                                    bracketCount++;
                                }
                                else if (ch == ')')
                                {
                                    bracketCount--;
                                }
                            }
                        }

                        // 构造新的公式
                        vector<Element> newFormula;
                        newFormula.push_back(Element('('));
                        for (int j = start + 1; j < end; ++j)
                        {
                            if (std::holds_alternative<char>(newClause.formula[j].value)) // 如果是操作符
                            {
                                char op = std::get<char>(newClause.formula[j].value);
                                if (op == '&')
                                {
                                    newFormula.push_back(Element('|'));
                                } // 交换&和|
                                else if (op == '!')
                                {
                                    newFormula.push_back(Element('!'));
                                } // 保持!
                                else if (op == '|')
                                {
                                    newFormula.push_back(Element('&'));
                                } // 交换|和&
                                else if (op == '(') // 如果是左括号，其后为一整个子句，应当递归的处理这个子句
                                {
                                    int start1 = j;
                                    int end1 = j;
                                    int bracketCount = 1;
                                    while (end1 < newClause.formula.size() && bracketCount > 0)
                                    {
                                        end1++;
                                        if (std::holds_alternative<char>(newClause.formula[end1].value))
                                        {
                                            char ch = std::get<char>(newClause.formula[end1].value);
                                            if (ch == '(')
                                            {
                                                bracketCount++;
                                            }
                                            else if (ch == ')')
                                            {
                                                bracketCount--;
                                            }
                                        }
                                    }
                                    // 找到括号内的内容，start和end分别是括号的起始和结束位置
                                    Clause subClause;
                                    subClause.formula.push_back(Element('!'));
                                    subClause.formula.insert(subClause.formula.end(), newClause.formula.begin() + start1, newClause.formula.begin() + end1 + 1);
                                    // 构造一个新的子句对象
                                    Clause processedSubClause = subClause.applyDeMorgan(); // 递归处理括号内的子句
                                    newFormula.insert(newFormula.end(), processedSubClause.formula.begin(), processedSubClause.formula.end());
                                    // 插入处理后的子句
                                    j = end1;
                                }
                            }
                            else // 如果是命题变元
                            {
                                newFormula.push_back(Element('!'));
                                newFormula.push_back(newClause.formula[j]);
                            }
                        }
                        newFormula.push_back(Element(')'));

                        // 替换原公式中的内容
                        newClause.formula.erase(newClause.formula.begin() + i, newClause.formula.begin() + end + 1);
                        newClause.formula.insert(newClause.formula.begin() + i, newFormula.begin(), newFormula.end());
                        i += newFormula.size() - 1;
                    }
                    else if (std::holds_alternative<PropositionVariable>(newClause.formula[i + 1].value))
                    {
                        // 如果否定符号直接修饰命题变元，则跳过
                        continue;
                    }
                }
            }
        }
        return newClause;
    }

    Clause applyDistribution() const
    {
        Clause newClause(*this); // 创建一个新的子句对象

        // 遍历公式，应用分配律
        for (size_t i = 0; i < newClause.formula.size(); ++i)
        {
            if (std::holds_alternative<char>(newClause.formula[i].value) && std::get<char>(newClause.formula[i].value) == '|')
            {
                // 找到析取联结词两侧的操作数
                int leftStart = i - 1;
                int leftEnd = i - 1;
                int rightStart = i + 1;
                int rightEnd = i + 1;

                // 向前找到左操作数
                if (std::holds_alternative<char>(newClause.formula[leftStart].value) && std::get<char>(newClause.formula[leftStart].value) == ')')
                {
                    int bracketCount = 1;
                    leftStart--;
                    while (leftStart >= 0 && bracketCount > 0)
                    {
                        if (std::holds_alternative<char>(newClause.formula[leftStart].value))
                        {
                            char ch = std::get<char>(newClause.formula[leftStart].value);
                            if (ch == ')')
                            {
                                bracketCount++;
                            }
                            else if (ch == '(')
                            {
                                bracketCount--;
                            }
                        }
                        leftStart--;
                    }
                    leftStart++;
                }

                // 向后找到右操作数
                if (std::holds_alternative<char>(newClause.formula[rightEnd].value) && std::get<char>(newClause.formula[rightEnd].value) == '(')
                {
                    int bracketCount = 1;
                    rightEnd++;
                    while (rightEnd < newClause.formula.size() && bracketCount > 0)
                    {
                        if (std::holds_alternative<char>(newClause.formula[rightEnd].value))
                        {
                            char ch = std::get<char>(newClause.formula[rightEnd].value);
                            if (ch == '(')
                            {
                                bracketCount++;
                            }
                            else if (ch == ')')
                            {
                                bracketCount--;
                            }
                        }
                        rightEnd++;
                    }
                    rightEnd--;
                }

                // 构造新的公式
                vector<Element> leftPart(newClause.formula.begin() + leftStart, newClause.formula.begin() + leftEnd + 1);
                vector<Element> rightPart(newClause.formula.begin() + rightStart, newClause.formula.begin() + rightEnd + 1);

                vector<Element> newFormula;
                newFormula.push_back(Element('('));
                for (const auto &elem : leftPart)
                {
                    newFormula.push_back(elem);
                }
                newFormula.push_back(Element('|'));
                for (const auto &elem : rightPart)
                {
                    newFormula.push_back(elem);
                }
                newFormula.push_back(Element(')'));

                // 替换原公式中的内容
                newClause.formula.erase(newClause.formula.begin() + leftStart, newClause.formula.begin() + rightEnd + 1);
                newClause.formula.insert(newClause.formula.begin() + leftStart, newFormula.begin(), newFormula.end());
                i = leftStart + newFormula.size() - 1;
            }
        }

        return newClause;
    }
    // TO DO: 该函数尚未完成
};

class ClauseSet
{
private:
    vector<Clause> clauses; // 存储析取子句

public:
    ClauseSet() {}
    // 默认构造函数
    ClauseSet(const ClauseSet &cs) : clauses(cs.clauses) {}
    // 复制构造函数
    ClauseSet &operator=(const ClauseSet &cs)
    {
        clauses = cs.clauses;
        return *this;
    }
    // 重载赋值运算符
    ClauseSet(PropositionFormula &pre, PropositionFormula &con)
    {
        addClause(Clause(pre.Print()));
        addClause(Clause("!" + con.Print()));
    }
    // 构造函数，根据前提和结论构造析取子句集合
    ~ClauseSet() {}
    // 析构函数

    void addClause(Clause clause)
    {
        if (clause.isDisjunctive())
        {
            clause.assignValue();      // 依照命题变元前是否有!来判断真值，若无!则真值为true，若有!则真值为false
            clauses.push_back(clause); // 添加到子句集合中
            return;
        } // 判断是否是析取范式，如果是则添加到子句集合中
    }
    // 递归添加析取子句，每一个子句是一个析取范式

    void setMap()
    {
        for (auto &clause : clauses)
        {
            clause.setVariableMap(); // 设置命题变元哈希表
        }
    }

    void Print()
    {
        if (clauses.empty())
        {
            cout << "Empty" << endl;
            return;
        }
        for (int i = 0; i < clauses.size(); i++) // 遍历子句集合
        {
            cout << "Clause " << i + 1 << " is: " << clauses[i].Print() << endl;
        }
    }
    // 打印析取子句集合

    bool isResolvable()
    {
        for (size_t i = 0; i < clauses.size(); ++i)
        {
            for (size_t j = i + 1; j < clauses.size(); ++j)
            {
                if (clauses[i].haveComplementaryPair(clauses[j]))
                {
                    return true;
                }
            }
        }
        return false;
    }
    // 判断是否可归结

    void DeductiveReasoning()
    {
        bool isResolved = false; // 是否归结过
        while (!clauses.empty()) // 当子句集合不为空时
        {
            isResolved = false;
            for (int i = 0; i < clauses.size() && !isResolved; i++) // 遍历子句集合
            {
                for (int j = i + 1; j < clauses.size() && !isResolved;) // 遍历子句集合
                {
                    if (clauses[i].haveComplementaryPair(clauses[j])) // 如果有互补对
                    {
                        cout << "Summarize " << i + 1 << " and " << j + 1 << ':' << endl;
                        Clause newClause = clauses[i].resolution(clauses[j]); // 消元
                        if (newClause.formula.empty())                        // 如果新子句为空
                        {
                            clauses.erase(clauses.begin() + j); // 删除原子句
                            clauses.erase(clauses.begin() + i); // 删除原子句
                        }
                        // 删除原子句
                        else
                        {
                            clauses.erase(clauses.begin() + j);             // 删除原子句
                            clauses.erase(clauses.begin() + i);             // 删除原子句
                            clauses.insert(clauses.begin() + i, newClause); // 添加新子句
                        }
                        // 添加新子句,删除原子句
                        Print(); // 打印子句集合
                        printf("\n");
                        isResolved = true; // 归结过，需要退出到最外层循环
                    }
                    else
                    {
                        j++;
                    }
                }
            }
            if (!isResolvable() && clauses.size() != 0) // 如果不可归结且子句集合不为空
            {
                cout << "The conclusion is false!" << endl; // 子句集合不为空，结论为假
                return;
            }
        }
        cout << "The conclusion is true!" << endl; // 归结出空子句，结论为真
    }
    // 归结推理
};
