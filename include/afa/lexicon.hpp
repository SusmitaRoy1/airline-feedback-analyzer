#pragma once

#include <cstddef>
#include <filesystem>
#include <stdexcept>
#include <string>
#include <string_view>
#include <unordered_map>
#include <vector>

#include "afa/tokenizer.hpp"
#include "afa/types.hpp"

namespace afa {

class LexiconError : public std::runtime_error {
public:
    explicit LexiconError(const std::string& what) : std::runtime_error(what) {}
};

/// Maps a token to a sentiment weight.
///
/// Positive weight  => leans positive.
/// Negative weight  => leans negative.
/// Absent token     => 0.0, contributes nothing.
///
/// Weights are LOG-ODDS learned from labelled data:
///
///     weight(w) = log( P(w | positive) / P(w | negative) )
///
/// with add-one smoothing so a word seen in only one class does not produce
/// an infinite weight. Neutral examples are skipped during learning -- the
/// neutral band is produced later by the scorer's thresholds, not by the
/// lexicon.
class Lexicon {
public:
    Lexicon() = default;

    /// Learn weights from labelled examples.
    ///
    /// @param training  labelled examples; neutral entries are ignored
    /// @param max_terms keep only the N highest-|weight| terms.
    ///                  MEASURED: 800 is the optimum on the airline dataset;
    ///                  1500+ overfits and macro-F1 drops. Reproduce this
    ///                  with `afa sweep` rather than taking it on trust.
    /// @param min_document_frequency
    ///                  ignore words appearing in fewer than this many
    ///                  documents; filters one-off typos and usernames
    /// @param tok       tokenizer to use (must match the one used at scoring)
    static Lexicon learn(const std::vector<LabelledText>& training,
                         std::size_t max_terms,
                         std::size_t min_document_frequency,
                         const Tokenizer& tok);

    /// Plain-text format, one entry per line: "<token><TAB><weight>".
    /// Lines starting with '#' are comments.
    static Lexicon load(const std::filesystem::path& path);
    void save(const std::filesystem::path& path) const;

    /// 0.0 when the token is not present.
    double weight(std::string_view token) const noexcept;

    void set(const std::string& token, double w) { weights_[token] = w; }

    std::size_t size() const noexcept { return weights_.size(); }
    bool empty() const noexcept { return weights_.empty(); }

    const std::unordered_map<std::string, double>& weights() const noexcept {
        return weights_;
    }

private:
    std::unordered_map<std::string, double> weights_;
};

}  // namespace afa
