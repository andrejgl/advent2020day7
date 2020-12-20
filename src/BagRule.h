#pragma once

#include <memory>
#include <map>
#include <set>
#include <string>

class BagColorNode
{
private:
    std::string color_name_;
    std::set<BagColorNode *> parents_;
    std::map<std::shared_ptr<BagColorNode>, unsigned> childs_; //share ownnership with bag coler directory

public:
    /**
     * @brief Construct a new Bag Color Node object
     *
     * @param Name of bag color
     */
    BagColorNode(const std::string &name);

    /**
     * @brief Add child node
     *
     * @param child_node
     * @param weight
     */
    void AddChildNode(std::shared_ptr<BagColorNode> child_node, unsigned weight);

    // Getters
    const std::string &name() const { return color_name_; };
    const std::set<BagColorNode *> &parents() const { return parents_; };
    const std::map<std::shared_ptr<BagColorNode>, unsigned> &childs() const { return childs_; };
};

class BagColorRule
{
private:
    std::map<std::string, std::shared_ptr<BagColorNode>> bag_colors_dir_;
    std::shared_ptr<BagColorNode> AddNode(const std::string &color_name);

    /**
     * @brief Get a set of unique parent nodes
     *
     * @param outout set
     * @param Bag color node to search from
     */
    void GetParentNodes(std::set<BagColorNode *> &out_nodes, const BagColorNode *node);

    /**
     * @brief Get the Inside Bag Count of node
     *
     * @param parent_node
     * @return unsigned
     */
    unsigned GetInsideBagCount(const BagColorNode *parent_node);

public:
    /**
     * @brief Load Bag Rule from a file
     *
     * @param filename
     */
    bool Load(const std::string &filename);

    /**
     * @brief Get a set of unique parent nodes
     *
     * @param Bag color name to search from
     */

    /**
     * @brief Get the Parent Nodes count
     *
     * @param color name to search from
     * @return unsigned
     */
    unsigned GetParentNodesCount(const std::string &color_name);

    /**
     * @brief Get the Inside Bag Count by color name
     *
     * @param color_name
     * @return unsigned
     */
    unsigned GetInsideBagCount(const std::string &color_name);

    /**
     * @brief Clear rule
     *
     */
    void Clear();
};
