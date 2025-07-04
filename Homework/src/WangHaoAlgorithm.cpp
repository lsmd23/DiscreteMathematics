#include <iostream>
#include <string>
#include "WangHaoAlgorithm.h"

using namespace std;

int main()
{
    TheoremProverSet tps;
    TheoremProver tp;

    cout << "Please input the premise: " << endl;
    string previousCase;
    cin >> previousCase;
    WangHaoAlgorithmFormula premise("(" + previousCase + ")");

    cout << "Please input the consequence: " << endl;
    string consequence;
    cin >> consequence;
    WangHaoAlgorithmFormula con("(" + consequence + ")");
    printf("\n");

    premise.removeOuterParentheses();
    con.removeOuterParentheses();

    tp.addPremise(premise);
    tp.addConsequence(con);

    tps.push_back(tp);

    tps.Print();
    cout << endl;

    tps.Prove();

    return 0;
}