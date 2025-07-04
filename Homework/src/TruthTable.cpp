#include <iostream>
#include <variant>
#include <string>
#include <vector>
#include <algorithm>
#include "PropositionalFormula.h"
#include "TruthTable.h"
using namespace std;

int main()
{
#ifdef TRUTH_TABLE
    // 输入命题公式
    string str;
    cout << "Please input a proposition formula:" << endl;
    getline(cin, str);
    if (*str.begin() != '(' || *str.rbegin() != ')')
        str = "(" + str + ")";
    PropositionFormula formula(str);

    // 检查命题公式的语法是否正确
    if (!formula.checkGrammar())
    {
        cout << "Error! Grammar is not correct." << endl;
        return 0;
    }

    TruthTable truthTable(str);
    cout << "Truth table:" << endl;
    truthTable.printTruthTable();
#endif

#ifdef DNF_CNF
    // 输入命题公式
    string str;
    cout << "Please input a proposition formula:" << endl;
    getline(cin, str);
    if (*str.begin() != '(' || *str.rbegin() != ')')
        str = "(" + str + ")";
    PropositionFormula formula(str);

    // 检查命题公式的语法是否正确
    if (!formula.checkGrammar())
    {
        cout << "Error! Grammar is not correct." << endl;
        return 0;
    }

    cout << "Minimum DNF: " << formula.getMinimumDNF() << endl;
    cout << "Maximum CNF: " << formula.getMaximumCNF() << endl;
#endif

#ifdef TRUTH_TABLE_TO_FORMULA
    TruthTable truthTable;
    vector<string> tableHead;
    vector<bool> results;
    bool flag = true;
    do
    {
        int n;
        cout << "Please input the number of variables:" << endl;
        cin >> n;
        cout << "Please input the variables:" << endl;
        for (int i = 0; i < n; i++)
        {
            string name;
            cin >> name;
            tableHead.push_back(name);
        }
        truthTable.setTableHead(tableHead);

        cout << "Plese input the values of the truth table in order:\n"
             << "(1 means true, 0 means false.)" << endl;
        for (int i = 0; i < (1 << n); i++)
        {
            int value;
            cin >> value;
            if (value == 1)
                results.push_back(true);
            else
                results.push_back(false);
        }
        truthTable.setTable(results);

        cout << "Your input truth table is:" << endl;
        truthTable.printTruthTable();

        cout << "Is the truth table correct? (1 for yes, 0 for no)" << endl;
        int correct;
        cin >> correct;
        if (correct == 1)
        {
            flag = false;
        }
        else
        {
            tableHead.clear();
            results.clear();
        }
    } while (flag);

    truthTable.getFormula();
    cout << "The formula is: " << truthTable.Print() << endl;
#endif
    return 0;
}