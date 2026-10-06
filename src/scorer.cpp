#include "afa/scorer.hpp"

#include <stdexcept>

// =============================================================================
//  YOUR IMPLEMENTATION -- commit 6
// =============================================================================
//
//  score(text):
//      tokenize, sum lexicon.weight(token) over all tokens, return the sum.
//      Unknown tokens contribute 0.0, so they cost nothing.
//
//  label_for(score):
//      score <  thresholds.negative_below  -> Negative
//      score >  thresholds.positive_above  -> Positive
//      otherwise                           -> Neutral
//
//      Note "strictly": a score exactly equal to a threshold is Neutral.
//      The tests check both boundaries exactly, so pick <, > and stay
//      consistent.
//
//  classify(text):
//      score + label, plus `contributions`: every token that had a non-zero
//      weight, paired with that weight, sorted by descending |weight|.
//      This is what `--explain` prints, and it is the difference between a
//      demo and a conversation -- you can show exactly which words drove
//      the verdict.
//
//  Do NOT add negation handling here.
//  It was measured on this dataset: macro-F1 went 0.6451 -> 0.6403, i.e. it
//  made things slightly WORSE, because the learned weights already absorb
//  negated usage. That is a documented negative result and it stays documented.
//  If you want to revisit it, measure first and write down what you find.
// =============================================================================

namespace afa {

Scorer::Scorer(Lexicon lexicon, Tokenizer tokenizer, Thresholds thresholds)
    : lexicon_(std::move(lexicon)),
      tokenizer_(std::move(tokenizer)),
      thresholds_(thresholds) {}

double Scorer::score(std::string_view text) const {
    (void)text;
    throw std::logic_error("Scorer::score is not implemented yet -- see src/scorer.cpp");
}

Sentiment Scorer::label_for(double score) const noexcept {
    (void)score;
    return Sentiment::Neutral;  // TODO: apply thresholds_
}

Classification Scorer::classify(std::string_view text) const {
    (void)text;
    throw std::logic_error("Scorer::classify is not implemented yet -- see src/scorer.cpp");
}

}  // namespace afa
