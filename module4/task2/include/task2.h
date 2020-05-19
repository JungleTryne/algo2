#pragma once

#include <iostream>
#include <vector>

class SegmentTree {
private:
    std::vector<size_t> tree; //1 - root, then 2 and 3 - children, 4,5,6,7 - second level and so on
    std::vector<size_t> addition; // Массив для хранения изменения значений суммы на отрезке

    size_t treeSize;
    size_t trainThreshold;

    void buildTree(const std::vector<size_t> &initialData, size_t currentVertex, size_t left, size_t right);

    size_t _getMax(size_t currentVertex, size_t currentLeft, size_t currentRight, size_t left, size_t right);
    void _updateTree(size_t currentVertex, size_t currentLeft, size_t currentRight, size_t left, size_t right, size_t tickets);

public:
    explicit SegmentTree(const std::vector<size_t>& initialData, size_t trainThreshold);
    size_t getMax(size_t left, size_t right);
    void updateTree(size_t left, size_t right, size_t value);
};