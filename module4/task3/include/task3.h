#pragma once

#include <iostream>
#include <vector>

class SegmentTree {
private:
    std::vector<long> plot; //0 - root, then 1 and 2 - children, 3,4,5,6 - second level and so on
    std::vector<long> changed;
    size_t treeSize;

    void buildTree(const std::vector<size_t> &initialData, size_t currentVertex, size_t left, size_t right);
    void push(size_t currentVertex);

    size_t _getMin(size_t currentVertex, size_t currentLeft, size_t currentRight, size_t left, size_t right);

    void updateTree(size_t currentVertex, size_t currentLeft, size_t currentRight, size_t left, size_t right,
                    size_t tickets);

public:
    explicit SegmentTree(const std::vector<size_t> &initialData);

    size_t getMin(size_t left, size_t right);

    void updateTree(size_t left, size_t right, size_t value);
};