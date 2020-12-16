#include "BagRule.h"

#include <sstream>
#include <fstream>

using namespace std;

void BagColorNode::AddChildNode(shared_ptr<BagColorNode> node)
{
    child_nodes_.push_back(node);
}

BagColorNode::BagColorNode( const string& name )
: name_(name)
{}

shared_ptr<BagColorNode> BagColerRule::AddNode( const string& color_name )
{
    auto it = bag_colors_dir_.find(color_name);
    if (it == bag_colors_dir_.end()) {
        auto dir_pair = bag_colors_dir_.emplace(color_name, new BagColorNode(color_name));
        return (*dir_pair.first).second;
    } else {
        return (*it).second;
    }
}

void BagColerRule::Load( const string& filename)
{
    bag_colors_dir_.clear();

    string line;
    ifstream data_file( filename );

    while ( getline(data_file, line) )
    {
        stringstream line_stream(line);
        string param1,param2,param3, param4;
        unsigned wight;

        if (!(line_stream >> param1 >> param2 >> param3 >> param4))
        {
            // bad format
            return;
        }

        // cout << param1 + ' ' + param2 << endl;
        string color_name = param1 + ' ' + param2;
        shared_ptr<BagColorNode> child_node = AddNode(color_name);

        while (line_stream >> wight >> param2 >> param3 >> param4)
        {
            // cout << "   " << param2 + ' ' + param3 << ": " << wight << endl;
            color_name = param2 + ' ' + param3;
            shared_ptr<BagColorNode> node = AddNode(color_name);

            node->AddChildNode(child_node);
        }
    }
}

void BagColerRule::GetChilds(set<shared_ptr<BagColorNode>> &p, const shared_ptr<BagColorNode> c)
{
    for (auto &&i : c->parents())
    {
        p.insert(i);
        GetChilds(p, i);
    }
}

set<shared_ptr<BagColorNode>> BagColerRule::GetChilds( const string& color_name)
{
    set<shared_ptr<BagColorNode>> childs;
    auto parent_it = bag_colors_dir_.find( color_name );

    GetChilds(childs, (*parent_it).second);

    return childs;
}
