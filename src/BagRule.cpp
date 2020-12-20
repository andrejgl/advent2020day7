#include "BagRule.h"

#include <iostream>
#include <sstream>
#include <fstream>
#include <algorithm>

using namespace std;

void BagColorNode::AddChildNode(std::shared_ptr<BagColorNode> child_node, unsigned weight)
{
    child_node->parents_.insert(this);
    childs_.insert({child_node, weight});
}

unsigned BagColorNode::GetInsideBagCount()
{
    unsigned count = 0;
    for (auto &i : childs_)
    {
        count += i.second;

        if (i.first->childs_.size() > 0)
            count += i.second * i.first->GetInsideBagCount();
    }

    return count;
}

BagColorNode::BagColorNode(const string &name)
    : color_name_(name)
{
}

shared_ptr<BagColorNode> BagColorRule::AddNode(const string &color_name)
{
    auto it = bag_colors_dir_.find(color_name);
    if (it == bag_colors_dir_.end())
    {
        auto dir_pair = bag_colors_dir_.emplace(color_name, new BagColorNode(color_name));
        return (*dir_pair.first).second;
    }
    else
    {
        return (*it).second;
    }
}

bool BagColorRule::Load(const string &filename)
{
    Clear();

    string line;
    ifstream data_file(filename);

    // check file is opned
    if (!data_file.is_open())
    {
        cout << "can not open file " << filename << endl;
        return false;
    }

    // read and parse line
    while (getline(data_file, line))
    {
        stringstream line_stream(line);
        string param1, param2, param3, param4;
        unsigned weight;

        // skip empty lines
        if (line.empty())
            continue;

        // Format:
        // |vibrant plum |bags contain |5 |faded blue |bags, |6 |dotted black |bags.
        // |faded blue |bags contain |no other bags.

        if (!(line_stream >> param1 >> param2 >> param3 >> param4))
        {
            // bad format
            return false;
        }

        // cout << param1 + ' ' + param2 << endl;
        string color_name = param1 + ' ' + param2;
        auto parent_node = AddNode(color_name);

        while (line_stream >> weight >> param2 >> param3 >> param4)
        {
            // cout << "   " << param2 + ' ' + param3 << ": " << weight << endl;
            color_name = param2 + ' ' + param3;
            auto child_node = AddNode(color_name);

            parent_node->AddChildNode(child_node, weight);
        }
    }

    return true;
}

void BagColorRule::GetParentNodes(set<BagColorNode *> &out_nodes, const BagColorNode *node)
{
    for (auto &i : node->parents())
    {
        out_nodes.insert(i);
        GetParentNodes(out_nodes, i);
    }
}

unsigned BagColorRule::GetParentNodesCount(const string &color_name)
{
    set<BagColorNode *> nodes; // a set of unique values
    unsigned count = 0;
    auto parent_it = bag_colors_dir_.find(color_name);

    if (parent_it == bag_colors_dir_.end())
    {
        cout << "Can not find node for '" << color_name << "'" << endl;
        // exception
        return 0;
    }

    GetParentNodes(nodes, (*parent_it).second.get());

    return nodes.size();
}

unsigned BagColorRule::GetInsideBagCount(const std::string &color_name)
{
    auto bag_it = bag_colors_dir_.find(color_name);

    return bag_it->second->GetInsideBagCount();
}

void BagColorRule::Clear()
{
    bag_colors_dir_.clear();
}
