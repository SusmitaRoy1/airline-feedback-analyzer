// Lexicon tests -- YOU WRITE THESE (commits 4 and 5).
//
// Target: 8+ assertions.

#include "afa/lexicon.hpp"

#include "test_harness.hpp"

using afa::Lexicon;
using afa::LexiconError;
using afa::Sentiment;
using afa::Tokenizer;

TEST("lexicon: absent token has zero weight") {
    TODO_TEST("Lexicon{}.weight(\"anything\") == 0.0");
    // Lexicon lex;
    // CHECK_EQ(lex.weight("anything"), 0.0);
}

TEST("lexicon: set then read back") {
    TODO_TEST("set(\"worst\", -2.5) then weight(\"worst\") == -2.5");
}

TEST("lexicon: save then load round-trips exactly") {
    TODO_TEST("write to a temp file, load it, compare every weight with CHECK_NEAR eps=1e-9");
}

TEST("lexicon: malformed line throws LexiconError") {
    TODO_TEST("a file containing 'no-tab-here' -> CHECK_THROWS(Lexicon::load(path))");
}

TEST("lexicon: comment lines are ignored") {
    TODO_TEST("a file with '# comment' loads cleanly");
}

TEST("lexicon: learn on a hand-built fixture gives the expected sign") {
    TODO_TEST(
        "3 positive docs containing 'great', 3 negative containing 'awful', "
        "min_df=1 -> weight(great) > 0 and weight(awful) < 0");
    // Build the fixture by hand so you can compute the expected log-odds
    // yourself with a calculator. That is the point of this test: it proves
    // the formula, not just the sign.
}

TEST("lexicon: learn ignores neutral examples") {
    TODO_TEST("adding neutral docs containing 'okay' must not create a weight for 'okay'");
}

TEST("lexicon: learn respects min_document_frequency") {
    TODO_TEST("a word appearing in 1 doc with min_df=5 must be absent");
}

TEST("lexicon: learn respects max_terms") {
    TODO_TEST("20 distinct words, max_terms=5 -> size() == 5");
}

TEST("lexicon: learn keeps the highest-magnitude terms") {
    TODO_TEST("the survivors should be the most opinionated words, not arbitrary ones");
}

AFA_TEST_MAIN()
