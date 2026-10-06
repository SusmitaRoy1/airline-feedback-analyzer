#include "afa/lexicon.hpp"

// =============================================================================
//  YOUR IMPLEMENTATION -- commits 4 and 5
// =============================================================================
//
//  commit 4: load() / save() / weight()
//  commit 5: learn()
//
//  ---- learn() algorithm -------------------------------------------------
//
//  1. For each training example, skip Neutral. Tokenize, then DEDUPLICATE the
//     tokens for that document (use a std::unordered_set). You are counting
//     "how many documents contain this word", not "how many times it occurs" --
//     otherwise one ranting tweet repeating "worst worst worst" dominates.
//
//  2. Count per word: pos_docs[w], neg_docs[w].
//     Count totals:   n_pos documents, n_neg documents.
//
//  3. Drop words where pos_docs[w] + neg_docs[w] < min_document_frequency.
//     This removes typos, usernames and one-off noise.
//
//  4. Weight with add-one (Laplace) smoothing:
//
//         p = (pos_docs[w] + 1) / (n_pos + 2)
//         n = (neg_docs[w] + 1) / (n_neg + 2)
//         weight[w] = log(p / n)
//
//     The +1/+2 matter: without them a word appearing only in positives gives
//     log(x/0) = infinity, and one rare word swamps every score.
//
//  5. Keep the max_terms entries with the largest |weight|, discard the rest.
//     Sort by descending absolute value -- the most opinionated words, whether
//     positive or negative.
//
//  MEASURED: max_terms = 800, min_document_frequency = 5 gives macro-F1 0.6442
//  on the airline dataset. 1500 terms drops it to 0.5946 -- that is overfitting,
//  and `afa sweep` is there so you can watch it happen rather than believe me.
//
//  ---- file format --------------------------------------------------------
//
//      # comment lines start with '#'
//      worst<TAB>-2.310000
//      thanks<TAB>1.884000
//
//  load() must throw LexiconError on a malformed line (no tab, unparseable
//  number). Round-tripping save() then load() must give identical weights --
//  write enough decimal places.
// =============================================================================

namespace afa {

Lexicon Lexicon::learn(const std::vector<LabelledText>& training,
                       std::size_t max_terms,
                       std::size_t min_document_frequency,
                       const Tokenizer& tok) {
    (void)training;
    (void)max_terms;
    (void)min_document_frequency;
    (void)tok;
    throw LexiconError("Lexicon::learn is not implemented yet -- see src/lexicon.cpp");
}

Lexicon Lexicon::load(const std::filesystem::path& path) {
    (void)path;
    throw LexiconError("Lexicon::load is not implemented yet -- see src/lexicon.cpp");
}

void Lexicon::save(const std::filesystem::path& path) const {
    (void)path;
    throw LexiconError("Lexicon::save is not implemented yet -- see src/lexicon.cpp");
}

double Lexicon::weight(std::string_view token) const noexcept {
    // Heterogeneous lookup is not available for unordered_map before C++20,
    // so build a string. Fine here -- profile before optimising.
    auto it = weights_.find(std::string(token));
    return it == weights_.end() ? 0.0 : it->second;
}

}  // namespace afa
