#pragma once

#include <iostream>
#include <variant>
#include <string>
#include <vector>
#include <stack>
#include <unordered_map>
using namespace std;

struct PropositionVariable
{
    // 成员变量，分别表示命题变量的名字和真值
    string name;
    bool value;

    // 构造函数，析构函数
    PropositionVariable() : name(""), value(false) {}
    PropositionVariable(bool value) : name(""), value(value) {}
    PropositionVariable(string name, bool value) : name(name), value(value) {}
    PropositionVariable(const PropositionVariable &var) : name(var.name), value(var.value) {}
    ~PropositionVariable() {}

    // 重载赋值运算符
    PropositionVariable &operator=(const PropositionVariable &var)
    {
        name = var.name;
        value = var.value;
        return *this;
    }

    // 重载逻辑运算符
    PropositionVariable operator!()
    {
        return PropositionVariable('!' + name, !value);
    } // 取反，返回一个新的命题变量，名字前加'!'，真值取反
    PropositionVariable operator&(const PropositionVariable &var)
    {
        return PropositionVariable('(' + name + "&" + var.name + ')', value && var.value);
    } // 与，返回一个新的命题变量，名字用'()'括起来，中间用'&'连接，真值为两个命题变量的真值与
    PropositionVariable operator|(const PropositionVariable &var)
    {
        return PropositionVariable('(' + name + "|" + var.name + ')', value || var.value);
    } // 或，返回一个新的命题变量，名字用'()'括起来，中间用'|'连接，真值为两个命题变量的真值或
    PropositionVariable operator^(const PropositionVariable &var)
    {
        return PropositionVariable('(' + name + "^" + var.name + ')', (value && !var.value) ? false : true);
    } // 蕴含，返回一个新的命题变量，名字用'()'括起来，中间用'^'连接，真值为两个命题变量的蕴含
    PropositionVariable operator==(const PropositionVariable &var)
    {
        return PropositionVariable('(' + name + "~" + var.name + ')', (value == var.value) ? true : false);
    } // 等价，返回一个新的命题变量，名字用'()'括起来，中间用'~'连接，真值为两个命题变量的等价
};
// 命题变量类，包含命题变量的名字和真值，以及逻辑运算符的重载

struct Element
{
    std::variant<PropositionVariable, char> value;

    Element() : value('\0') {}
    Element(const PropositionVariable &var) : value(var) {}
    Element(char op) : value(op) {}
    bool operator==(const Element &element) const
    {
        if (std::holds_alternative<PropositionVariable>(value) && std::holds_alternative<PropositionVariable>(element.value))
        {
            return std::get<PropositionVariable>(value).name == std::get<PropositionVariable>(element.value).name;
        }
        else if (std::holds_alternative<char>(value) && std::holds_alternative<char>(element.value))
        {
            return std::get<char>(value) == std::get<char>(element.value);
        }
        return false;
    }
    bool operator!=(const Element &element) const
    {
        return !(*this == element);
    }
    string Print()
    {
        if (std::holds_alternative<PropositionVariable>(value))
        {
            return std::get<PropositionVariable>(value).name;
        }
        else
        {
            return std::string(1, std::get<char>(value));
        }
    }
};
// 元素联合体类，包含命题变量和逻辑运算符，以及括号

class PropositionFormula
{
private:
    vector<Element> formula;                 // 命题公式，用一个元素联合体数组表示
    unordered_map<string, bool> variableMap; // 哈希表，存储命题公式中的变量名和真值

public:
    int getVariableCount()
    {
        variableMap.clear(); // 清空哈希表
        int variableCount = 0;

        // 统计唯一变量的数量
        for (const auto &element : formula)
        {
            if (std::holds_alternative<PropositionVariable>(element.value))
            {
                const std::string &name = std::get<PropositionVariable>(element.value).name;
                if (variableMap.find(name) == variableMap.end())
                {
                    variableMap[name] = false; // 初始化变量值
                    variableCount++;
                }
            }
        }
        return variableCount;
    }
    // 获取变量的数量
    bool AssignValue(int index)
    {
        variableMap.clear(); // 清空哈希表
        int variableCount = 0;

        // 统计唯一变量的数量
        for (const auto &element : formula)
        {
            if (std::holds_alternative<PropositionVariable>(element.value))
            {
                const std::string &name = std::get<PropositionVariable>(element.value).name;
                if (variableMap.find(name) == variableMap.end())
                {
                    variableMap[name] = false; // 初始化变量值
                    variableCount++;
                }
            }
        }

        // 检查 index 是否超过变量范围
        if (index >= (1 << variableCount))
        {
            return false;
        }

        // 将 index 转换为二进制数，并赋值给公式中的变量
        int currentVariable = 0;
        for (auto &element : formula)
        {
            if (std::holds_alternative<PropositionVariable>(element.value))
            {
                PropositionVariable &var = std::get<PropositionVariable>(element.value);
                if (variableMap.find(var.name) != variableMap.end() && currentVariable < variableCount)
                {
                    // 获取 index 的当前位的值
                    bool value = (index & (1 << (variableCount - currentVariable - 1))) != 0;
                    variableMap[var.name] = value;
                    currentVariable++;
                }
            }
        }

        // 将哈希表中的值赋给公式中的变量
        for (auto &element : formula)
        {
            if (std::holds_alternative<PropositionVariable>(element.value))
            {
                PropositionVariable &var = std::get<PropositionVariable>(element.value);
                var.value = variableMap[var.name];
            }
        }

        return true;
    }
    // 赋值，第i组变量值
    bool Calculate()
    {
        std::stack<PropositionVariable> operands; // 操作数栈
        std::stack<char> operators;               // 操作符栈

        auto precedence = [](char op) -> int
        {
            switch (op)
            {
            case '!':
                return 5;
            case '&':
                return 4;
            case '|':
                return 3;
            case '^':
                return 2;
            case '~':
                return 1;
            default:
                return 0;
            }
        }; // 定义优先级

        for (const auto &element : formula) // 遍历公式
        {
            if (std::holds_alternative<PropositionVariable>(element.value))
            {
                operands.push(std::get<PropositionVariable>(element.value)); // 如果是操作数，入栈
            }
            else if (std::holds_alternative<char>(element.value)) // 如果是操作符
            {
                char op = std::get<char>(element.value); // 取出操作符

                if (op == '(')
                {
                    operators.push(op); // 如果是左括号，入栈
                }
                else if (op == ')') // 如果是右括号
                {
                    while (!operators.empty() && operators.top() != '(')
                    {
                        char topOp = operators.top();
                        operators.pop(); // 弹出操作符

                        if (topOp == '!')
                        {
                            PropositionVariable operand = operands.top();
                            operands.pop();
                            operands.push(!operand); // 取反
                        }
                        else
                        {
                            PropositionVariable right = operands.top(); // 取出右操作数
                            operands.pop();
                            PropositionVariable left = operands.top(); // 取出左操作数
                            operands.pop();

                            switch (topOp)
                            {
                            case '&':
                                operands.push(left & right);
                                break;
                            case '|':
                                operands.push(left | right);
                                break;
                            case '^':
                                operands.push(left ^ right);
                                break;
                            case '~':
                                operands.push(left == right);
                                break;
                            } // 根据操作符计算结果
                        }
                    }
                    operators.pop(); // 弹出 '('
                }
                else
                {
                    while (!operators.empty() && precedence(operators.top()) >= precedence(op))
                    {
                        char topOp = operators.top();
                        operators.pop();

                        if (topOp == '!')
                        {
                            PropositionVariable operand = operands.top();
                            operands.pop();
                            operands.push(!operand);
                        }
                        else
                        {
                            PropositionVariable right = operands.top();
                            operands.pop();
                            PropositionVariable left = operands.top();
                            operands.pop();

                            switch (topOp)
                            {
                            case '&':
                                operands.push(left & right);
                                break;
                            case '|':
                                operands.push(left | right);
                                break;
                            case '^':
                                operands.push(left ^ right);
                                break;
                            case '~':
                                operands.push(left == right);
                                break;
                            }
                        }
                    }
                    operators.push(op);
                }
            }
        }

        while (!operators.empty())
        {
            char topOp = operators.top();
            operators.pop();

            if (topOp == '!')
            {
                PropositionVariable operand = operands.top();
                operands.pop();
                operands.push(!operand);
            }
            else
            {
                PropositionVariable right = operands.top();
                operands.pop();
                PropositionVariable left = operands.top();
                operands.pop();

                switch (topOp)
                {
                case '&':
                    operands.push(left & right);
                    break;
                case '|':
                    operands.push(left | right);
                    break;
                case '^':
                    operands.push(left ^ right);
                    break;
                case '~':
                    operands.push(left == right);
                    break;
                }
            }
        }

        return operands.top().value;
    }
    // 计算命题公式的真值
    void setVariableMap()
    {
        variableMap.clear(); // 清空哈希表

        for (const auto &element : formula)
        {
            if (std::holds_alternative<PropositionVariable>(element.value))
            {
                const std::string &name = std::get<PropositionVariable>(element.value).name;
                if (variableMap.find(name) == variableMap.end())
                {
                    variableMap[name] = std::get<PropositionVariable>(element.value).value;
                }
            }
        }
    }
    // 设置变量哈希表

public:
    PropositionFormula() {}
    // 默认构造函数
    PropositionFormula(string str)
    {
        for (int i = 0; i < str.length(); i++)
        {
            if (str[i] == ' ')
            {
                continue;
            }
            if (str[i] == '!')
            {
                formula.push_back(Element('!'));
            }
            else if (str[i] == '&' || str[i] == '|' || str[i] == '^' || str[i] == '~')
            {
                formula.push_back(Element(str[i]));
            }
            else if (str[i] == '(' || str[i] == ')')
            {
                formula.push_back(Element(str[i]));
            }
            else
            {
                string name = "";
                while (str[i] != ' ' && str[i] != '&' && str[i] != '|' && str[i] != '^' && str[i] != '~' && str[i] != '(' && str[i] != ')')
                {
                    name += str[i];
                    i++;
                }
                i--;
                formula.push_back(Element(PropositionVariable(name, false)));
            }
        }
    }
    // 构造函数，根据输入的字符串构造命题公式
    PropositionFormula(const PropositionFormula &pf) : formula(pf.formula) {}
    // 复制构造函数
    ~PropositionFormula() {} // 析构函数

    PropositionFormula &operator=(const PropositionFormula &pf)
    {
        formula = pf.formula;
        return *this;
    }
    // 重载赋值运算符

    bool checkGrammar()
    {
        std::stack<char> parenthesesStack;
        int operandCount = 0;
        bool expectOperand = true; // 初始状态期望操作数

        for (const auto &element : formula)
        {
            if (std::holds_alternative<char>(element.value))
            {
                char op = std::get<char>(element.value);

                if (op == '(')
                {
                    parenthesesStack.push(op);
                    expectOperand = true; // 左括号后期望操作数
                }
                else if (op == ')')
                {
                    if (parenthesesStack.empty() || parenthesesStack.top() != '(')
                    {
                        return false; // 括号不匹配
                    }
                    parenthesesStack.pop();
                    expectOperand = false; // 右括号后期望操作符
                }
                else if (op == '!')
                {
                    if (!expectOperand)
                    {
                        return false; // 单目运算符前必须是操作符或左括号
                    }
                    expectOperand = true; // 单目运算符后期望操作数
                }
                else if (op == '&' || op == '|' || op == '^' || op == '~')
                {
                    if (expectOperand || operandCount < 1)
                    {
                        return false; // 双目运算符前必须有一个操作数
                    }
                    operandCount--;       // 双目运算符消耗一个操作数
                    expectOperand = true; // 双目运算符后期望操作数
                }
                else
                {
                    return false; // 非法字符
                }
            }
            else if (std::holds_alternative<PropositionVariable>(element.value))
            {
                if (!expectOperand)
                {
                    return false; // 操作数前必须是操作符或左括号
                }
                operandCount++;
                expectOperand = false; // 操作数后期望操作符或右括号
            }
        }

        if (!parenthesesStack.empty() || expectOperand)
        {
            return false; // 括号不匹配或公式以操作符结尾
        }

        return true;
    }
    // 检查命题公式的语法是否正确

    string Print()
    {
        string str = "";
        for (int i = 0; i < formula.size(); i++)
        {
            if (std::get_if<PropositionVariable>(&formula[i].value))
            {
                str += std::get<PropositionVariable>(formula[i].value).name;
            }
            else
            {
                str += std::get<char>(formula[i].value);
            }
        }
        return str;
    }
    // 打印命题公式

    string getMinimumDNF()
    {
        string dnf = "m(";
        int variableCount = getVariableCount();
        bool result;
        bool isEmpty = true;
        for (int i = 0; i < (1 << variableCount); i++)
        {
            AssignValue(i);
            result = Calculate();
            if (result)
            {
                isEmpty = false;
                dnf += to_string(i);
                dnf += ", ";
            }
        } // 计算所有命题公式的真值，并将真值为真的下标加入到最小析取范式中
        if (isEmpty)
        {
            return "Empty! Always false!";
        }
        else
        {
            dnf.pop_back();
            dnf.pop_back();
            dnf += ")";
            return dnf;
        }
    }
    // 获取最小析取范式

    string getMaximumCNF()
    {
        string cnf = "M(";
        int variableCount = getVariableCount();
        bool result;
        bool isEmpty = true;
        for (int i = 0; i < (1 << variableCount); i++)
        {
            AssignValue(i);
            result = Calculate();
            if (!result)
            {
                isEmpty = false;
                cnf += to_string(i);
                cnf += ", ";
            }
        } // 计算所有命题公式的真值，并将真值为真的下标加入到最大合取范式中
        if (isEmpty)
        {
            return "Empty! Always true!";
        }
        else
        {
            cnf.pop_back();
            cnf.pop_back();
            cnf += ")";
            return cnf;
        }
    }
    // 获取最大合取范式

    void setFormula(string str)
    {
        formula.clear();
        for (int i = 0; i < str.length(); i++)
        {
            if (str[i] == ' ')
            {
                continue;
            }
            if (str[i] == '!')
            {
                formula.push_back(Element('!'));
            }
            else if (str[i] == '&' || str[i] == '|' || str[i] == '^' || str[i] == '~')
            {
                formula.push_back(Element(str[i]));
            }
            else if (str[i] == '(' || str[i] == ')')
            {
                formula.push_back(Element(str[i]));
            }
            else
            {
                string name = "";
                while (str[i] != ' ' && str[i] != '&' && str[i] != '|' && str[i] != '^' && str[i] != '~' && str[i] != '(' && str[i] != ')')
                {
                    name += str[i];
                    i++;
                }
                i--;
                formula.push_back(Element(PropositionVariable(name, false)));
            }
        }
    }
    // 设置命题公式

    friend class TruthTable;
    friend class ClauseSet;
    friend class Clause;
    friend class WangHaoAlgorithmFormula;
    // 友元类
};
; // 命题公式类，包含命题公式的元素联合体数组，以及相关的操作
