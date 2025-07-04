#include <iostream>
#include <string>
#include "PropositionalFormula.h"
#include "DeductiveReasoning.h"

using namespace std;

int main()
{
    cout << "Please input the set of clauses:" << endl;
    cout << "Please input the number of clauses first:" << endl;
    int n;
    cin >> n;
    ClauseSet clauseSet;
    cin.get();

    cout << "Please input the set of clauses:" << endl;
    for (int i = 0; i < n; i++)
    {
        string str;
        getline(cin, str);
        Clause clause("(" + str + ")");
        if (!clause.isDisjunctive())
        {
            cout << "Invalid! This is not a Disjunctive!" << endl;
            i--;
            continue;
        }
        clauseSet.addClause(clause);
    }

    clauseSet.setMap();

    clauseSet.Print();
    printf("\n");

    clauseSet.DeductiveReasoning(); // 归结

    return 0;
}