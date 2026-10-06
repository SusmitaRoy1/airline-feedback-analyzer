#include "afa/csv_reader.hpp"

// =============================================================================
//  YOUR IMPLEMENTATION -- commit 3
// =============================================================================
//
//  Parse RFC 4180 CSV. Read the tests in tests/test_csv.cpp first; they are
//  the specification.
//
//  Why this module is not as boring as it looks: the real Tweets.csv contains
//  tweets with commas, quotes and newlines INSIDE quoted fields. A naive
//  split(',') shifts every later column by one and you end up training on
//  garbage that still looks like valid text. Get this wrong and every number
//  downstream is quietly wrong.
//
//  The state machine you need is small:
//
//      OutsideQuotes:
//          '"'   -> InsideQuotes
//          ','   -> end field
//          '\n'  -> end field, end row
//          '\r'  -> ignore (CRLF)
//          else  -> append
//
//      InsideQuotes:
//          '"' followed by '"'  -> append one '"', consume both
//          '"' otherwise        -> OutsideQuotes
//          anything else        -> append (including ',' and '\n')
//
//  Edge cases the tests cover: empty file, header-only file, trailing newline
//  vs none, ragged rows, and a final field that ends inside quotes (throw
//  CsvError).
// =============================================================================

namespace afa {

CsvReader::CsvReader(std::istream& in) {
    (void)in;
    throw CsvError("CsvReader is not implemented yet -- see src/csv_reader.cpp");
}

std::size_t CsvReader::column(const std::string& name) const {
    auto it = index_.find(name);
    if (it == index_.end()) throw CsvError("no such column: '" + name + "'");
    return it->second;
}

const std::string& CsvReader::at(std::size_t row, const std::string& column_name) const {
    if (row >= rows_.size()) throw CsvError("row index out of range");
    const std::size_t col = column(column_name);
    if (col >= rows_[row].size()) throw CsvError("column index out of range for row");
    return rows_[row][col];
}

}  // namespace afa
