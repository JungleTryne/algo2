#include "task3.h"

//Сроим дерево рекурсивно
void SegmentTree::buildTree(const std::vector<size_t> &initialData, size_t currentVertex, size_t left, size_t right) {
    if (left == right) {
        this->plot[currentVertex] = initialData[left];
    } else {
        size_t middle = (left + right) / 2;
        this->buildTree(initialData, currentVertex * 2 + 1, left, middle);
        this->buildTree(initialData, currentVertex * 2 + 2, middle + 1, right);
        this->plot[currentVertex] = std::min(this->plot[currentVertex * 2 + 1], this->plot[currentVertex * 2 + 2]);
    }
}

SegmentTree::SegmentTree(const std::vector<size_t> &initialData) {
    treeSize = initialData.size();
    this->plot = std::vector<long>(treeSize * 4, 1024);
    this->changed = std::vector<long>(treeSize * 4, -1);
    this->buildTree(initialData, 0, 0, treeSize - 1);
}

//Публичная функция получения минимума фкнкции
size_t SegmentTree::getMin(size_t left, size_t right) {
    return this->_getMin(0, 0, treeSize - 1, left, right);
}

//Приватная функция получения минимума, выполняем рекурсивно, спускаясь по дереву
size_t SegmentTree::_getMin(size_t currentVertex, size_t currentLeft, size_t currentRight, size_t left, size_t right) {
    if (currentLeft > currentRight || left > right) {
        return 1024;
    }
    if (left == currentLeft && right == currentRight) {
        return this->plot[currentVertex];
    }

    push(currentVertex);

    size_t middle = (currentLeft + currentRight) / 2;
    size_t leftResult = _getMin(currentVertex * 2 + 1, currentLeft, middle, left, std::min(right, middle));
    size_t rightResult = _getMin(currentVertex * 2 + 2, middle + 1, currentRight,
                                 std::max(left, middle + 1), right);
    return std::min(leftResult, rightResult);

}

void SegmentTree::updateTree(size_t currentVertex, size_t currentLeft, size_t currentRight,
                             size_t left, size_t right, size_t tickets)
{
    if (currentLeft > currentRight || left > right) {
        return;
    }
    if (currentLeft == left && currentRight == right) {
        this->plot[currentVertex] = tickets;
        this->changed[currentVertex] = tickets;
        return;
    }

    push(currentVertex);

    size_t middle = (currentLeft + currentRight) / 2;
    this->updateTree(currentVertex * 2 + 1, currentLeft, middle, left, std::min(right, middle), tickets);
    this->updateTree(currentVertex * 2 + 2, middle + 1, currentRight,
                     std::max(left, middle + 1), right, tickets);
    this->plot[currentVertex] = std::min(this->plot[currentVertex * 2 + 1], this->plot[currentVertex * 2 + 2]);
}

void SegmentTree::updateTree(size_t left, size_t right, size_t value) {
    this->updateTree(0, 0, treeSize - 1, left, right, value);
}

//Функция проталкивания нового значения для дерева. Выполняется за О(1)
//Обеспечивает получение минимума на отрезке за O(log n)
void SegmentTree::push(size_t currentVertex) {
    if (this->changed[currentVertex] != -1) {
        this->changed[currentVertex * 2 + 1] = this->changed[currentVertex];
        this->plot[currentVertex * 2 + 1] = this->changed[currentVertex];
        this->changed[currentVertex * 2 + 2] = this->changed[currentVertex];
        this->plot[currentVertex * 2 + 2] = this->changed[currentVertex];

        this->changed[currentVertex] = -1;
    }
}
