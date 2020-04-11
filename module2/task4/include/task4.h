#pragma once

#include <bitset>
#include <vector>

const size_t BIT_MASK_SIZE = 32;

void GetTransitiveClosure(size_t graphSize, std::vector<std::vector<std::bitset<BIT_MASK_SIZE>>>& closureTable);

void SolveProblem(size_t graphSize, const std::vector<std::string>& inputMatrix, std::vector<std::string>& outputMatrix);
