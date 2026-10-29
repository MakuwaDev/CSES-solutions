#include <iostream>
#include <vector>
#include <string>

class SegmentTree {
public:
    SegmentTree(std::string const& s) {
        treesize = calculate_tree_size(s.size());
        tree.resize(2 * treesize);

        for (std::size_t i = 0; i < s.size(); ++i) {
            if (s[i] == '0') {
                tree[i + treesize].start0 = 1;
                tree[i + treesize].long0 = 1;
                tree[i + treesize].end0 = 1;
                tree[i + treesize].all0 = true;
            } else {
                tree[i + treesize].start1 = 1;
                tree[i + treesize].long1 = 1;
                tree[i + treesize].end1 = 1;
                tree[i + treesize].all1 = true;
            }
        }

        for (std::size_t i = treesize - 1; i > 0; --i) {
            combine(tree[i], tree[2 * i], tree[2 * i + 1]);
        }
    }

    void flip(std::size_t id) {
        id += treesize - 1;

        tree[id].start0 = 1 - tree[id].start0;
        tree[id].long0 = 1 - tree[id].long0;
        tree[id].end0 = 1 - tree[id].end0;
        tree[id].all0 = 1 - tree[id].all0;

        tree[id].start1 = 1 - tree[id].start1;
        tree[id].long1 = 1 - tree[id].long1;
        tree[id].end1 = 1 - tree[id].end1;
        tree[id].all1 = 1 - tree[id].all1;

        id >>= 1;

        while (id > 0) {
            combine(tree[id], tree[2 * id], tree[2 * id + 1]);
            id >>= 1;
        }
    }

    std::size_t query() {
        return std::max(tree[1].long0, tree[1].long1);
    }

private:
    struct Node {
        std::size_t start0, long0, end0;
        std::size_t start1, long1, end1;
        bool all0, all1;
    };

    std::size_t treesize;
    std::vector<Node> tree;

    std::size_t calculate_tree_size(std::size_t n) {
        std::size_t res = 1;

        while (res < n) {
            res <<= 1;
        }

        return res;
    }

    void combine(Node& res, Node const& left, Node const& right) {
        res.start0 = left.start0 + (left.all0 ? right.start0 : 0);
        res.end0 = right.end0 + (right.all0 ? left.end0 : 0);
        res.long0 = std::max(std::max(left.long0, right.long0), left.end0 + right.start0);
        res.all0 = left.all0 & right.all0;

        res.start1 = left.start1 + (left.all1 ? right.start1 : 0);
        res.end1 = right.end1 + (right.all1 ? left.end1 : 0);
        res.long1 = std::max(std::max(left.long1, right.long1), left.end1 + right.start1);
        res.all1 = left.all1 & right.all1;
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::size_t q, i;
    std::string s;

    std::cin >> s >> q;

    SegmentTree tree(s);

    while (q--) {
        std::cin >> i;
        tree.flip(i);
        std::cout << tree.query() << " ";
    }

    std::cout << "\n";
    return 0;
}