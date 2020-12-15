#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <sstream>
#include <memory>

#include <fstream>

using namespace std;

class BagRule
{
private:
    bool assigned_[9] = {0};

    const vector<string> colors_ = {"bw", "my", "dor", "lr", "dol", "db", "vp", "fb", "shg"};
                            //    bw    my   dor  lr   dol  db   vp   fb   shg
    const unsigned graf_[9][9]  = {{0,   0,   3,   1,   0,   0,   0,   0,   0} // bw
                                , {0,   0,   4,   2,   0,   0,   0,   0,   0} // my
                                , {0,   0,   0,   0,   0,   0,   0,   0,   0} // dor
                                , {0,   0,   0,   0,   0,   0,   0,   0,   0} // lr
                                , {0,   0,   0,   0,   0,   0,   0,   0,   1} // dol
                                , {0,   0,   0,   0,   4,   0,   6,   0,   0} // db
                                , {0,   0,   0,   0,   0,   0,   0,   0,   2} // vp
                                , {0,   9,   0,   0,   3,   0,   5,   0,   0} // fb
                                , {1,   2,   0,   0,   0,   0,   0,   0,   0} // shg
                                };

public:
    unsigned CountColors(unsigned color_idx)
    {
        if (color_idx > 9)
            return 0;

        unsigned isum = 0;

        for (unsigned i = 0; i < colors_.size(); i++)
        {
            if (graf_[color_idx][i] > 0)
            {

                if (!assigned_[i])
                {
                    cout << "graf_["<<color_idx<<"]["<<i<<"] = " << graf_[color_idx][i] << endl;
                    assigned_[i] = true;
                    ++isum;
                }

                isum += CountColors(i);
            }
        }

        return isum;
    }
};

class BagColor
{
private:
    string name_;
    vector<shared_ptr<BagColor>> parents_;
public:
    void AddParent(shared_ptr<BagColor> p)
    {
        parents_.push_back(p);
    }

    const string& name() const { return name_; };
    const vector<shared_ptr<BagColor>>& parents() const { return parents_; };
};

void get_parents(set<shared_ptr<BagColor>> &p, const shared_ptr<BagColor> c)
{

    for (auto &&i : c->parents())
    {
        cout << "counting..." << endl;
        p.insert(i);
        get_parents(p, i);
    }
}

int main(int argc, char const *argv[])
{
    cout << "It's a day 7" << endl;

    BagRule rule;
    cout << "bag colors: " << rule.CountColors(8) << endl;

    string line;
    // ifstream data_file("bag.data");
    ifstream data_file("bag.data");
    map<string, shared_ptr<BagColor>> bag_colors;
    while (getline(data_file, line))
    {
        // cout << line << endl;
        stringstream s(line);

        string p1,p2,p3, p4;
        unsigned cnt;
        if (!(s >> p1 >> p2 >> p3 >> p4))
            static_assert(true, "NOP");

        cout << p1 + ' ' + p2 << endl;
        string parent_color_name = p1 + ' ' + p2;

        shared_ptr<BagColor> p_color;
        auto it = bag_colors.find(parent_color_name);
        if (it == bag_colors.end()) {
            auto pr = bag_colors.emplace(parent_color_name, new BagColor());
            p_color = (*pr.first).second;
        } else {
            p_color = (*it).second;
        }

        while (s >> cnt >> p2 >> p3 >> p4)
        {
            cout << "   " << p2 + ' ' + p3 << ": " << cnt << endl;
            string child_color_name = p2 + ' ' + p3;

            shared_ptr<BagColor> c_color;
            auto it = bag_colors.find(child_color_name);
            if (it == bag_colors.end()) {
                auto pr = bag_colors.emplace(child_color_name, new BagColor());
                c_color = (*pr.first).second;
            } else {
                c_color = (*it).second;
            }

            c_color->AddParent(p_color);
        }
    }

    auto shiny_gold_color_it = bag_colors.find("shiny gold");

    // unsigned d = count_color((*shiny_gold_color_it).second);
    set<shared_ptr<BagColor>> parents;
    get_parents(parents, (*shiny_gold_color_it).second);

    cout << "result: " << parents.size() << endl;

    return 0;
}
