#include "BagRuleExample.h"
#include "BagRule.h"

#include <iostream>

using namespace std;

int main(int argc, char const *argv[])
{
    cout << "It's a day 2020 7" << endl;

    // example
    BagRuleExample bag_rule_example;
    cout << "Example data Result: " << bag_rule_example.CountColors(8) << endl;

    // custom data
    BagColerRule bag_rule;
    bag_rule.Load("bag.data");

    set<shared_ptr<BagColorNode>> childs = bag_rule.GetChilds("shiny gold");
    cout << "Custom data Result: " << childs.size() << endl;

    return 0;
}
