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
    /**
     * @brief Construct a new Bag Color Node object
     *
     * @param Name of bag color
     */
    BagColorNode( const std::string& name );

    /**
     * @brief Add child node
     *
     * @param child node
     */
    void AddChildNode(std::shared_ptr<BagColorNode> node);

    // Getters
    const std::string& name() const { return name_; };
    const std::vector<std::shared_ptr<BagColorNode>>& parents() const { return child_nodes_; };
};

class BagColerRule
{
private:
    std::map<std::string, std::shared_ptr<BagColorNode>> bag_colors_dir_;
    std::shared_ptr<BagColorNode> AddNode( const std::string& color_name );

    /**
     * @brief Get a set of unique child nodes
     *
     * @param outout set
     * @param Bag color node to search from
     */
    void GetChildNodes(std::set<std::shared_ptr<BagColorNode>> &child_nodes, const std::shared_ptr<BagColorNode> c);

public:
    /**
     * @brief Load Bag Rule from a file
     *
     * @param filename
     */
    void Load( const std::string& filename);

    /**
     * @brief Get a set of unique child nodes
     *
     * @param Bag color name to search from
     */
    std::set<std::shared_ptr<BagColorNode>> GetChildNodes( const std::string& color_name);
};
