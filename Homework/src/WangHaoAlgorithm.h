#pragma once

#include "PropositionalFormula.h"
#include <vector>
#include <stack>

using namespace std;

class WangHaoAlgorithmFormula : public PropositionFormula
{
public:
    WangHaoAlgorithmFormula() {}
    // 默认构造函数
    WangHaoAlgorithmFormula(const WangHaoAlgorithmFormula &whaf) : PropositionFormula(whaf) {}
    // 复制构造函数
    WangHaoAlgorithmFormula(const string &str) : PropositionFormula(str) {}
    // 构造函数，根据输入的字符串构造命题公式
    WangHaoAlgorithmFormula &operator=(const WangHaoAlgorithmFormula &whaf)
    {
        PropositionFormula::operator=(whaf);
        return *this;
    }
    // 重载赋值运算符
    ~WangHaoAlgorithmFormula() {}
    // 析构函数

    Element &operator[](int i)
    {
        return formula[i];
    }
    // 重载下标运算符，返回公式中的第i个元素

    bool isSingleVariable()
    {
        for (const auto &element : formula)
        {
            if (std::holds_alternative<char>(element.value))
            {
                char op = std::get<char>(element.value);
                if (op != '(' && op != ')')
                {
                    return false;
                }
            }
        }
        return true;
    }
    // 判断是否是单变量

    string getVariable()
    {
        if (isSingleVariable())
        {
            for (const auto &element : formula)
            {
                if (std::holds_alternative<PropositionVariable>(element.value))
                {
                    return std::get<PropositionVariable>(element.value).name;
                }
            }
        }
        return "";
    }
    // 获取单变量的变量名

    void removeOuterParentheses()
    {
        int start = 0;
        int end = formula.size() - 1;

        while (start < end && std::holds_alternative<char>(formula[start].value) && std::get<char>(formula[start].value) == '(' &&
               std::holds_alternative<char>(formula[end].value) && std::get<char>(formula[end].value) == ')')
        {
            int openCount = 0;
            bool valid = true;
            for (int i = start; i <= end; ++i)
            {
                if (std::holds_alternative<char>(formula[i].value))
                {
                    char op = std::get<char>(formula[i].value);
                    if (op == '(')
                    {
                        openCount++;
                    }
                    else if (op == ')')
                    {
                        openCount--;
                        if (openCount == 0 && i != end)
                        {
                            valid = false;
                            break;
                        }
                    }
                }
            }
            if (valid)
            {
                start++;
                end--;
            }
            else
            {
                break;
            }
        }

        formula = std::vector<Element>(formula.begin() + start, formula.begin() + end + 1);
    }
    // 去掉最外层括号

    int lastOperatorIndex()
    {
        std::stack<int> parenthesesStack;
        int lastIndex = -1;
        int minPrecedence = INT_MAX;

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
        };

        for (int i = 0; i < formula.size(); ++i)
        {
            if (std::holds_alternative<char>(formula[i].value))
            {
                char op = std::get<char>(formula[i].value);

                if (op == '(')
                {
                    parenthesesStack.push(i);
                }
                else if (op == ')')
                {
                    if (!parenthesesStack.empty())
                    {
                        parenthesesStack.pop();
                    }
                }
                else
                {
                    int currentPrecedence = precedence(op);
                    if (parenthesesStack.empty() && currentPrecedence < minPrecedence)
                    {
                        minPrecedence = currentPrecedence;
                        lastIndex = i;
                    }
                }
            }
        }

        return lastIndex;
    }
    // 返回这个公式中，最后一个应当被运算的逻辑运算符的位置

    WangHaoAlgorithmFormula splitLast(int index)
    {
        WangHaoAlgorithmFormula newFormula;
        newFormula.formula = std::vector<Element>(formula.begin() + index + 1, formula.end());
        return newFormula;
    }
    // 在这个位置将原公式分解为两个公式，该函数返回第一个公式

    WangHaoAlgorithmFormula splitFirst(int index)
    {
        WangHaoAlgorithmFormula newFormula;
        newFormula.formula = std::vector<Element>(formula.begin(), formula.begin() + index);
        return newFormula;
    }
    // 在这个位置将原公式分解为两个公式，该函数返回第二个公式
};
// 王浩算法公式类，继承命题公式类

class FormulaString
{
    vector<WangHaoAlgorithmFormula> formulas;

public:
    FormulaString() {}
    // 默认构造函数
    FormulaString(const FormulaString &fs) : formulas(fs.formulas) {}
    // 复制构造函数
    FormulaString &operator=(const FormulaString &fs)
    {
        formulas = fs.formulas;
        return *this;
    }
    // 重载赋值运算符
    ~FormulaString() {}
    // 析构函数

    void push_back(const WangHaoAlgorithmFormula &formula)
    {
        formulas.push_back(formula);
    }
    // 添加命题公式

    WangHaoAlgorithmFormula &operator[](int index)
    {
        return formulas[index];
    }
    // 重载下标运算符

    int size()
    {
        return formulas.size();
    }
    // 获取公式数量

    void clear()
    {
        formulas.clear();
    }
    // 清空公式串

    void erase(int index)
    {
        formulas.erase(formulas.begin() + index);
    }
    // 删除指定下标的公式

    int firstNonSimpleIndex()
    {
        for (int i = 0; i < formulas.size(); ++i)
        {
            if (!formulas[i].isSingleVariable())
            {
                return i;
            }
        }
        return -1; // 返回-1表示所有公式都是单变元公式
    }
    // 返回第一个不是单变元公式的下标索引，如果所有公式都是单变元公式，则返回-1

    void Print()
    {
        if (formulas.size() == 0)
        {
            cout << "Empty";
            return;
        }
        for (int i = 0; i < formulas.size() - 1; ++i)
        {
            cout << formulas[i].Print() << ", ";
        }
        cout << formulas[formulas.size() - 1].Print();
    } // 打印公式串
};
// 公式串类，包含多个命题公式

class TheoremProver
{
private:
    FormulaString premises;
    FormulaString consequences;

public:
    TheoremProver() {}
    // 默认构造函数
    TheoremProver(const TheoremProver &tp) : premises(tp.premises), consequences(tp.consequences) {}
    // 复制构造函数
    TheoremProver &operator=(const TheoremProver &tp)
    {
        premises = tp.premises;
        consequences = tp.consequences;
        return *this;
    }
    // 重载赋值运算符
    ~TheoremProver() {}
    // 析构函数

    void addPremise(const WangHaoAlgorithmFormula &premise)
    {
        premises.push_back(premise);
    }
    // 添加前提
    void addConsequence(const WangHaoAlgorithmFormula &consequence)
    {
        consequences.push_back(consequence);
    }
    // 添加结论
    void clean()
    {
        premises.clear();
        consequences.clear();
    }
    // 清空前提和结论

    bool isProved()
    {
        if (premises.size() == 0 || consequences.size() == 0)
        {
            return false;
        }
        if (premises.firstNonSimpleIndex() == -1 &&
            consequences.firstNonSimpleIndex() == -1)
        {
            for (int i = 0; i < premises.size(); ++i)
            {
                for (int j = 0; j < consequences.size(); ++j)
                {
                    if (premises[i].getVariable() == consequences[j].getVariable()) // 前提和结论的变量相同
                    {
                        return true;
                    }
                }
            }
        }
        return false;
    }
    // 判断是否满足公理，已被证明

    int Prove(TheoremProver &temp_prover)
    {
        temp_prover.clean();                      // 清空临时定理证明器
        int index;                                // 用于缓存前提和结论中的第一个非单变元公式的下标索引
        int isTempProverLoaded = 0;               // 用于标记临时定理证明器是否被加载
        if (premises.firstNonSimpleIndex() != -1) // 前提不全是单变元公式
        {
            index = premises.firstNonSimpleIndex();
            WangHaoAlgorithmFormula temp_formula = premises[index];                    // 缓存前提中的第一个非单变元公式
            temp_formula.removeOuterParentheses();                                     // 去掉最外层括号
            premises.erase(index);                                                     // 删除前提中的第一个非单变元公式
            temp_prover = *this;                                                       // 将当前定理证明器赋值给临时定理证明器
            int lastOperatorIndex = temp_formula.lastOperatorIndex();                  // 获取公式中最后一个运算符的位置
            char lastOperator = std::get<char>(temp_formula[lastOperatorIndex].value); // 获取公式中最后一个运算符
            switch (lastOperator)                                                      // 根据最后一个运算符进行推导
            {
            case '&': // 前件规则‘&’
                premises.push_back(temp_formula.splitLast(lastOperatorIndex));
                premises.push_back(temp_formula.splitFirst(lastOperatorIndex));
                // 在这个位置将原公式分解为两个公式，然后全部添加到premises中
                isTempProverLoaded = 0;
                break;
            case '|': // 前件规则‘|’
                premises.push_back(temp_formula.splitLast(lastOperatorIndex));
                temp_prover.addPremise(temp_formula.splitFirst(lastOperatorIndex));
                // 在这个位置将原公式分解为两个公式，然后分别添加到premises和temp_prover.premises中
                isTempProverLoaded = 1;
                break;
            case '^': // 前件规则‘^’
                premises.push_back(temp_formula.splitLast(lastOperatorIndex));
                temp_prover.addConsequence(temp_formula.splitFirst(lastOperatorIndex));
                // 在这个位置将原公式分解为两个公式，然后分别添加到premises和temp_prover.consequences中
                isTempProverLoaded = 1;
                break;
            case '~':
                premises.push_back(temp_formula.splitLast(lastOperatorIndex));
                premises.push_back(temp_formula.splitFirst(lastOperatorIndex));
                temp_prover.addConsequence(temp_formula.splitLast(lastOperatorIndex));
                temp_prover.addConsequence(temp_formula.splitFirst(lastOperatorIndex));
                // 在这个位置将原公式分解为两个公式，然后全部添加到premises中与temp_prover.consequences中
                isTempProverLoaded = 1;
                break;
            case '!':
                consequences.push_back(temp_formula.splitLast(lastOperatorIndex));
                // 在这个位置将原公式分解为两个公式，然后将后件添加到consequences中
                isTempProverLoaded = 0;
                break;

            default:
                break;
            }
            return isTempProverLoaded;
        }
        else if (consequences.firstNonSimpleIndex() != -1) // 结论不全是单变元公式
        {
            index = consequences.firstNonSimpleIndex();
            WangHaoAlgorithmFormula temp_formula = consequences[index];                // 缓存结论中的第一个非单变元公式
            temp_formula.removeOuterParentheses();                                     // 去掉最外层括号
            consequences.erase(index);                                                 // 删除结论中的第一个非单变元公式
            temp_prover = *this;                                                       // 将当前定理证明器赋值给临时定理证明器
            int lastOperatorIndex = temp_formula.lastOperatorIndex();                  // 获取公式中最后一个运算符的位置
            char lastOperator = std::get<char>(temp_formula[lastOperatorIndex].value); // 获取公式中最后一个运算符
            switch (lastOperator)                                                      // 根据最后一个运算符进行推导
            {
            case '&': // 后件规则‘&’
                consequences.push_back(temp_formula.splitLast(lastOperatorIndex));
                temp_prover.addConsequence(temp_formula.splitFirst(lastOperatorIndex));
                // 在这个位置将原公式分解为两个公式，然后分别添加到consequences和temp_prover.consequences中
                isTempProverLoaded = 1;
                break;
            case '|': // 后件规则‘|’
                consequences.push_back(temp_formula.splitLast(lastOperatorIndex));
                consequences.push_back(temp_formula.splitFirst(lastOperatorIndex));
                // 在这个位置将原公式分解为两个公式，然后全部添加到consequences中
                isTempProverLoaded = 0;
                break;
            case '^': // 后件规则‘^’
                consequences.push_back(temp_formula.splitLast(lastOperatorIndex));
                premises.push_back(temp_formula.splitFirst(lastOperatorIndex));
                // 在这个位置将原公式分解为两个公式，然后分别添加到consequences和temp_prover.premises中
                isTempProverLoaded = 0;
                break;
            case '~':
                consequences.push_back(temp_formula.splitLast(lastOperatorIndex));
                premises.push_back(temp_formula.splitFirst(lastOperatorIndex));
                temp_prover.addPremise(temp_formula.splitLast(lastOperatorIndex));
                temp_prover.addPremise(temp_formula.splitFirst(lastOperatorIndex));
                // 在这个位置将原公式分解为两个公式，然后正序添加到consequences中，逆序添加到temp_prover.premises中
                isTempProverLoaded = 1;
                break;
            case '!':
                premises.push_back(temp_formula.splitLast(lastOperatorIndex));
                // 在这个位置将原公式分解为两个公式，然后将后件添加到premises中
                isTempProverLoaded = 0;
                break;

            default:
                break;
            }
            return isTempProverLoaded;
        }
        else
        {
            return -1;
        }
    }
    // 证明，使用王浩算法
    // 返回-1，定理已达最简单形式；返回0，可以被证明但无新的推导结果；返回1，可以被证明且有新的推导结果

    void Print()
    {
        premises.Print();
        cout << " ==> ";
        consequences.Print();
        printf("\n");
    }
    // 打印前提和结论
}; // 定理证明器类，包含前提和结论，前提和结论都是公式串

class TheoremProverSet
{
private:
    vector<TheoremProver> theoremProvers;

public:
    TheoremProverSet() {}
    // 默认构造函数
    TheoremProverSet(const TheoremProverSet &tps) : theoremProvers(tps.theoremProvers) {}
    // 复制构造函数
    TheoremProverSet &operator=(const TheoremProverSet &tps)
    {
        theoremProvers = tps.theoremProvers;
        return *this;
    }
    // 重载赋值运算符
    ~TheoremProverSet() {}
    // 析构函数

    void push_back(const TheoremProver &tp)
    {
        theoremProvers.push_back(tp);
    }
    // 添加定理证明器

    TheoremProver &operator[](int index)
    {
        return theoremProvers[index];
    }
    // 重载下标运算符

    int size()
    {
        return theoremProvers.size();
    }
    // 获取定理证明器数量

    void Print()
    {
        cout << "Theorem Prover Set:" << endl;
        for (int i = 0; i < theoremProvers.size(); ++i)
        {
            cout << i + 1 << ") ";
            theoremProvers[i].Print();
            // printf("\n");
        }
    }
    // 打印定理证明器

    bool isProved()
    {
        if (theoremProvers.size() == 0)
        {
            return false;
        }
        for (int i = 0; i < theoremProvers.size(); ++i)
        {
            if (!theoremProvers[i].isProved())
            {
                return false;
            }
        }
        return true;
    }
    // 判断是否满足公理，已被证明

    void Prove()
    {
        TheoremProver temp_prover; // 临时定理证明器，用于缓存可能的推导结果
        for (int i = 0; i < theoremProvers.size();)
        {
            int result = theoremProvers[i].Prove(temp_prover);
            if (result >= 0) // 可以被推导，循环
            {
                if (result > 0)
                {
                    TheoremProver newTheoremProver = temp_prover;
                    theoremProvers.push_back(newTheoremProver);
                }
                Print();
                printf("\n");
                // 有新的推导结果，添加到定理证明器集合中
            }
            else // 不能被推导
            {
                if (!theoremProvers[i].isProved()) // 违反公理
                {
                    cout << "Not proved! Because of the theorem " << i + 1
                         << ") is against the axiom." << endl;
                    return;
                }
                else // 满足公理
                {
                    ++i; // 跳过，继续下一个
                }
            }
        }
        if (isProved())
        {
            cout << "Proved!" << endl;
        }
        else
        {
            cout << "Not proved!" << endl;
        }
    }
};
// 定理证明器集合类，包含多个定理证明器