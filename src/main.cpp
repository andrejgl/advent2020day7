#include "BagRuleExample.h"
#include "BagRule.h"

#include <iostream>

using namespace std;

int main(int argc, char const *argv[])
{
    cout << "It's a day 2020 7" << endl;

    // example
    // TODO: use results from example in unit test

    if (argc < 2)
    {
        cout << "Usage: " << argv[0] << " FILENAME\n";
        return 1;
    }

    const string filename = argv[1];
    const string color_name = "shiny gold";
    cout << "Filename: " << filename << endl;
    cout << "Color name: " << color_name << endl;

    BagColorRule bag_rule;
    // load rule data
    if (!bag_rule.Load(filename))
        return 2;

    // get parent nodes count
    auto parent_count = bag_rule.GetParentNodesCount(color_name);
    cout << "Contain at least one '" << color_name << "' bag (directly/indirectly): " << parent_count << endl;

    // get inside bag count
    cout << "Inside '" << color_name << "' bag: " << bag_rule.GetInsideBagCount(color_name) << endl;

    return 0;
}
