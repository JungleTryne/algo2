//Мишин Данила, Б05-927
//Решение задачи D "Look What You Made Rick Do"

#include "task4.h"

//Функция нахождения транзитивного замыкания. Таблица смежности графа представлена как вектор битовых масок, что
//улучшает константу алгоритма в 32 раза
void GetTransitiveClosure(size_t graphSize, std::vector<std::vector<std::bitset<BIT_MASK_SIZE>>>& closureTable) {
    for (size_t k = 0; k < graphSize; ++k) {
        for (size_t i = 0; i < graphSize; ++i) {
            if (closureTable[i][k / BIT_MASK_SIZE][(BIT_MASK_SIZE-1) - (k % BIT_MASK_SIZE)] == 1) {
                for (size_t j = 0; j < graphSize/BIT_MASK_SIZE + 1; ++j) {
                    closureTable[i][j] |= closureTable[k][j];
                }
            }
        }
    }
}

//Функция для решения задачи. Вынесена отдельно, чтобы подготовить дополнительные оптимизации в представлении графа
//и для тестирования кода
void SolveProblem(size_t graphSize, const std::vector<std::string>& inputMatrix, std::vector<std::string>& outputMatrix) {
    std::vector<std::vector<std::bitset<BIT_MASK_SIZE>>> closureTable;
    for (std::string input : inputMatrix) {
        std::string buffer;
        std::vector<std::bitset<BIT_MASK_SIZE>> line;
        buffer += input[0];
        for (size_t j = 1; j < input.size(); ++j) {
            if (j % BIT_MASK_SIZE == 0) {
                line.emplace_back(buffer);
                buffer = "";
            }
            buffer += input[j];
        }
        if (input.size() % BIT_MASK_SIZE != 0) {
            while (buffer.size() < BIT_MASK_SIZE) {
                buffer += "0";
            }
            line.emplace_back(buffer);
        }
        closureTable.push_back(line);
    }
    GetTransitiveClosure(graphSize, closureTable);

    for (auto & i : closureTable) {
        std::string answer;
        for (size_t j = 0; j < i.size() && answer.size() < graphSize; ++j) {
            std::string mask = i[j].to_string();
            for (size_t k = 0; k < mask.size() && answer.size() < graphSize; ++k) {
                answer += mask[k];
            }
        }
        outputMatrix.push_back(answer);
    }
}

