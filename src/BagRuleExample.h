#pragma once

#include <vector>
#include <string>

class BagRuleExample
{
private:
    const std::vector<std::string> colors_ = {"bw", "my", "dor", "lr", "dol", "db", "vp", "fb", "shg"};
                            //    bw    my   dor  lr   dol  db   vp   fb   shg
    const unsigned graph_[9][9]  = {{0,   0,   3,   1,   0,   0,   0,   0,   0} // bw
                                , {0,   0,   4,   2,   0,   0,   0,   0,   0} // my
                                , {0,   0,   0,   0,   0,   0,   0,   0,   0} // dor
                                , {0,   0,   0,   0,   0,   0,   0,   0,   0} // lr
                                , {0,   0,   0,   0,   0,   0,   0,   0,   1} // dol
                                , {0,   0,   0,   0,   4,   0,   6,   0,   0} // db
                                , {0,   0,   0,   0,   0,   0,   0,   0,   2} // vp
                                , {0,   9,   0,   0,   3,   0,   5,   0,   0} // fb
                                , {1,   2,   0,   0,   0,   0,   0,   0,   0} // shg
                                };

    /**
     * @brief Get the Child Nodes Count
     *
     * @param array of nodes flags
     * @param index of parent node to start searching from
     * @return cout of unique child nodes
     */
    unsigned GetChildNodesCount(bool (&nodes_passed)[9], unsigned color_idx);

public:
    /**
     * @brief Get the Child Nodes Count
     *
     * @param index of parent node to start searching from
     * @return cout of unique child nodes
     */
    unsigned GetChildNodesCount(unsigned color_idx);
};
