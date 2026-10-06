// CSV reader tests -- YOU WRITE THESE (commit 3).
//
// Copy the style from tests/test_tokenizer.cpp.
//
// Target: 10+ assertions. The TODO_TEST lines below are your checklist --
// replace each one with a real test, then delete the TODO line.

#include "afa/csv_reader.hpp"

#include <sstream>

#include "test_harness.hpp"

using afa::CsvError;
using afa::CsvReader;

TEST("csv: simple rows and header") {
    TODO_TEST("parse \"a,b\\n1,2\\n\" -- header {a,b}, one row {1,2}");
    // std::istringstream in("a,b\n1,2\n");
    // CsvReader r(in);
    // CHECK_EQ(r.header().size(), 2u);
    // CHECK_EQ(r.size(), 1u);
    // CHECK_EQ(r.at(0, "b"), "2");
}

TEST("csv: quoted field containing a comma") {
    TODO_TEST("a,\"b,c\",d  ->  three fields, middle one is 'b,c'");
}

TEST("csv: escaped double quote inside a quoted field") {
    TODO_TEST("\"he said \"\"hi\"\"\"  ->  he said \"hi\"");
}

TEST("csv: quoted field containing a newline") {
    TODO_TEST("a,\"line1\\nline2\"  ->  one row, field keeps the newline");
}

TEST("csv: CRLF line endings") {
    TODO_TEST("a,b\\r\\n1,2\\r\\n  ->  no stray \\r in any field");
}

TEST("csv: empty file") {
    TODO_TEST("empty input -> zero rows, empty header (must not crash)");
}

TEST("csv: header only, no data rows") {
    TODO_TEST("\"a,b\\n\" -> header of 2, zero rows");
}

TEST("csv: file with no trailing newline") {
    TODO_TEST("\"a,b\\n1,2\" (no final newline) -> still one row");
}

TEST("csv: empty fields are preserved") {
    TODO_TEST("a,,c -> three fields, middle is empty string");
}

TEST("csv: ragged row shorter than header") {
    TODO_TEST("decide the behaviour, then test it -- pad or throw, but be deliberate");
}

TEST("csv: unterminated quote throws CsvError") {
    TODO_TEST("\"a,\\\"unclosed\" -> CHECK_THROWS(CsvReader(in))");
}

TEST("csv: unknown column name throws") {
    TODO_TEST("r.column(\"nope\") -> CHECK_THROWS");
}

AFA_TEST_MAIN()
