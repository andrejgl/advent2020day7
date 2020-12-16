#pragma once

#include <memory>
#include <vector>
#include <map>
#include <set>
#include <string>

class BagColorNode
{
private:
    std::string name_;
    std::vector<std::shared_ptr<BagColorNode>> child_nodes_;

public:
    BagColorNode( const std::string& name );

    void AddChildNode(std::shared_ptr<BagColorNode> node);

    const std::string& name() const { return name_; };
    const std::vector<std::shared_ptr<BagColorNode>>& parents() const { return child_nodes_; };
};

class BagColerRule
{
private:
    std::map<std::string, std::shared_ptr<BagColorNode>> bag_colors_dir_;
    std::shared_ptr<BagColorNode> AddNode( const std::string& color_name );

    void GetChilds(std::set<std::shared_ptr<BagColorNode>> &p, const std::shared_ptr<BagColorNode> c);

public:
    void Load( const std::string& filename);
    std::set<std::shared_ptr<BagColorNode>>GetChilds( const std::string& color_name);
};
