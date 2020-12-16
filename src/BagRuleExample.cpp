#include "BagRuleExample.h"

unsigned BagRuleExample::GetChildNodesCount(bool (&nodes_passed)[9], unsigned color_idx)
{
    unsigned sum = 0;

    for (unsigned i = 0; i < colors_.size(); i++)
    {
        if (graph_[color_idx][i] > 0)
        {
            if (!nodes_passed[i])
            {
                // cout << "graph_["<<color_idx<<"]["<<i<<"] = " << graph_[color_idx][i] << endl;
                nodes_passed[i] = true;
                ++sum;
            }

            sum += GetChildNodesCount(nodes_passed, i);
        }
    }

    return sum;
}

unsigned BagRuleExample::GetChildNodesCount(unsigned color_idx)
{
    if (color_idx > 9)
        return 0;

    bool nodes_passed[9] = {0};

    return GetChildNodesCount(nodes_passed, color_idx);
}
