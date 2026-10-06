// Scorer tests -- YOU WRITE THESE (commit 6).
//
// Target: 8+ assertions. Pay attention to the threshold boundaries; that is
// where this class will actually break.

#include "afa/scorer.hpp"

#include "test_harness.hpp"

using afa::Classification;
using afa::Lexicon;
using afa::Scorer;
using afa::Sentiment;
using afa::Thresholds;
using afa::Tokenizer;

namespace {

// Build a tiny predictable lexicon so expected scores can be computed by hand.
Lexicon toy() {
    Lexicon lex;
    lex.set("great", 2.0);
    lex.set("good", 1.0);
    lex.set("bad", -1.0);
    lex.set("awful", -2.0);
    return lex;
}

}  // namespace

TEST("scorer: empty text scores zero and is neutral") {
    TODO_TEST("classify(\"\") -> score 0.0, label Neutral");
}

TEST("scorer: unknown words contribute nothing") {
    TODO_TEST("classify(\"aardvark zebra\") -> score 0.0");
}

TEST("scorer: single known word gives its weight") {
    TODO_TEST("score(\"great\") == 2.0");
}

TEST("scorer: weights sum across tokens") {
    TODO_TEST("score(\"great bad\") == 1.0   (2.0 + -1.0)");
}

TEST("scorer: score exactly on the negative threshold is Neutral") {
    TODO_TEST(
        "thresholds{-1.5, 0.8}; a score of exactly -1.5 must be Neutral, "
        "because the rule is 'strictly below'");
}

TEST("scorer: score exactly on the positive threshold is Neutral") {
    TODO_TEST("a score of exactly 0.8 must be Neutral");
}

TEST("scorer: just past the thresholds flips the label") {
    TODO_TEST("-1.51 -> Negative and 0.81 -> Positive");
}

TEST("scorer: contributions list only non-zero tokens") {
    TODO_TEST("classify(\"great aardvark\") -> contributions.size() == 1");
}

TEST("scorer: contributions sum to the score") {
    TODO_TEST("sum of contribution weights == score, CHECK_NEAR eps=1e-9");
}

TEST("scorer: contributions sorted by descending magnitude") {
    TODO_TEST("classify(\"good awful\") -> awful (-2.0) comes before good (1.0)");
}

AFA_TEST_MAIN()
