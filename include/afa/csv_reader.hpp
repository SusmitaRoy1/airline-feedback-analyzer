#pragma once

#include <istream>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <vector>

namespace afa {

class CsvError : public std::runtime_error {
public:
    explicit CsvError(const std::string& what) : std::runtime_error(what) {}
};

/// RFC 4180 CSV reader.
///
/// This matters more than it looks. The real dataset contains tweets with
/// commas, quotes and newlines *inside* quoted fields. A naive split(',')
/// silently shifts columns and produces plausible-but-wrong results -- the
/// most dangerous class of bug in this project.
///
/// Must handle: quoted fields, embedded commas, embedded newlines,
/// escaped quotes (""), CRLF and LF line endings, and ragged rows.
class CsvReader {
public:
    using Row = std::vector<std::string>;

    /// Reads the whole stream. First line is treated as the header.
    explicit CsvReader(std::istream& in);

    const Row& header() const noexcept { return header_; }
    const std::vector<Row>& rows() const noexcept { return rows_; }

    /// Column index by header name. Throws CsvError if absent.
    std::size_t column(const std::string& name) const;

    /// Field by row index and column name. Throws CsvError if out of range.
    const std::string& at(std::size_t row, const std::string& column_name) const;

    std::size_t size() const noexcept { return rows_.size(); }

private:
    Row header_;
    std::vector<Row> rows_;
    std::unordered_map<std::string, std::size_t> index_;
};

}  // namespace afa
