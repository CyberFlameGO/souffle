/*
 * Souffle - A Datalog Compiler
 * Copyright (c) 2016, The Souffle Developers. All rights reserved
 * Licensed under the Universal Permissive License v 1.0 as shown at:
 * - https://opensource.org/licenses/UPL
 * - <souffle root>/licenses/SOUFFLE-UPL.txt
 */

#pragma once

#include "Row.h"
#include <vector>

namespace souffle {
namespace profile {

/*
 * Table class for holding a vector of rows
 * And sorting the rows based on a datacomparator function
 */
class Table {
public:
    std::vector<std::shared_ptr<Row>> rows;

    Table() : rows() {}

    void addRow(std::shared_ptr<Row> row) {
        rows.push_back(row);
    }

    inline std::vector<std::shared_ptr<Row>> getRows() {
        return rows;
    }

    void sort(int col_num);
};

}  // namespace profile
}  // namespace souffle
