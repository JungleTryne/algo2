#include "task2.h"

//Рекурсивное построение дерева, вызывается в конструкторе
void SegmentTree::buildTree(const std::vector<size_t> &initialData, size_t currentVertex, size_t left, size_t right) {
    if (left == right) {
        this->tree[currentVertex] = initialData[left];
    } else {
        size_t middle = (left + right) / 2;
        this->buildTree(initialData, currentVertex * 2 + 1, left, middle);
        this->buildTree(initialData, currentVertex * 2 + 2, middle+1, right);
        this->tree[currentVertex] = std::max(this->tree[currentVertex * 2 + 1], this->tree[currentVertex * 2 + 2]);
    }
}

//Конструктор
SegmentTree::SegmentTree(const std::vector<size_t>& initialData, size_t trainThreshold) : trainThreshold(trainThreshold) {
    treeSize = initialData.size();
    this->tree = std::vector<size_t>(treeSize * 4, 0);
    this->addition = this->tree;
    this->buildTree(initialData, 0, 0, treeSize-1);
}

//Публичная функция получения максимума на отрезке
size_t SegmentTree::getMax(size_t left, size_t right) {
    return this->_getMax(0, 0, treeSize - 1, left, right);
}

//get sum on any range private function
size_t SegmentTree::_getMax(size_t currentVertex, size_t currentLeft, size_t currentRight, size_t left, size_t right) {
    if (currentLeft > currentRight || left > right) {
        return 0;
    }
    if (left == currentLeft && right == currentRight) {
        return this->tree[currentVertex] + this->addition[currentVertex];
    }
    size_t middle = (currentLeft + currentRight) / 2;
    size_t leftResult = _getMax(currentVertex * 2 + 1, currentLeft, middle, left, std::min(right, middle));
    size_t rightResult = _getMax(currentVertex * 2 + 2, middle + 1, currentRight, std::max(left, middle + 1), right);
    return std::max(leftResult, rightResult) + this->addition[currentVertex];

}

void SegmentTree::_updateTree(size_t currentVertex, size_t currentLeft, size_t currentRight, size_t left, size_t right, size_t tickets) {
    if (currentLeft > currentRight || left > right) {
        return;
    }
    if (currentLeft == left && currentRight == right) {
        this->addition[currentVertex] += tickets;
        return;
    }

    size_t middle = (currentLeft + currentRight) / 2;
    this->_updateTree(currentVertex * 2 + 1, currentLeft, middle, left, std::min(right, middle), tickets);
    this->_updateTree(currentVertex * 2 + 2, middle + 1, currentRight, std::max(left, middle + 1), right, tickets);

    this->tree[currentVertex] = std::max(this->tree[2 * currentVertex + 1] + this->addition[2 * currentVertex + 1],
                                         this->tree[2 * currentVertex + 2] + this->addition[2 * currentVertex + 2]);
}

void SegmentTree::updateTree(size_t left, size_t right, size_t value) {
    this->_updateTree(0, 0, treeSize - 1, left, right, value);
}
