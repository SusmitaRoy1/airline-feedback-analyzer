// Tokenizer tests -- WORKED EXAMPLE.
//
// This suite is complete and passing. It is the template for the four suites
// you are going to write: tests/test_csv.cpp, test_lexicon.cpp, test_scorer.cpp
// and test_evaluator.cpp.
//
// Notice what is being tested: not "does it work on a normal sentence", but
// the empty input, the input that is only punctuation, the boundary, the
// thing that should throw. Normal cases rarely break. Edges always do.

#include "afa/tokenizer.hpp"

#include "test_harness.hpp"

using afa::Tokenizer;
using afa::TokenizerOptions;

namespace {

std::string join(const std::vector<std::string>& v) {
    std::string out;
    for (std::size_t i = 0; i < v.size(); ++i) {
        if (i) out += "|";
        out += v[i];
    }
    return out;
}

}  // namespace

TEST("tokenize: empty input yields no tokens") {
    Tokenizer t;
    CHECK(t.tokenize("").empty());
}

TEST("tokenize: whitespace only yields no tokens") {
    Tokenizer t;
    CHECK(t.tokenize("   \t\n  ").empty());
}

TEST("tokenize: punctuation only yields no tokens") {
    Tokenizer t;
    CHECK(t.tokenize("!!! ... ??? ---").empty());
}

TEST("tokenize: simple sentence splits on whitespace and punctuation") {
    Tokenizer t;
    CHECK_EQ(join(t.tokenize("Flight was late, again!")), "flight|was|late|again");
}

TEST("tokenize: lower-cases by default") {
    Tokenizer t;
    CHECK_EQ(join(t.tokenize("TERRIBLE Service")), "terrible|service");
}

TEST("tokenize: lower-casing can be disabled") {
    TokenizerOptions o;
    o.lowercase = false;
    Tokenizer t(o);
    CHECK_EQ(join(t.tokenize("TERRIBLE Service")), "TERRIBLE|Service");
}

TEST("tokenize: keeps apostrophes inside words") {
    Tokenizer t;
    CHECK_EQ(join(t.tokenize("don't won't can't")), "don't|won't|can't");
}

TEST("tokenize: strips leading and trailing apostrophes") {
    Tokenizer t;
    CHECK_EQ(join(t.tokenize("'quoted' dogs'")), "quoted|dogs");
}

TEST("tokenize: removes @mentions entirely") {
    Tokenizer t;
    // The airline handle identifies the target, not the sentiment. Leaving it
    // in teaches the model "united == negative", which is dataset bias.
    CHECK_EQ(join(t.tokenize("@united your service is awful")),
             "your|service|is|awful");
}

TEST("tokenize: keeps mentions when the option is off") {
    TokenizerOptions o;
    o.strip_mentions = false;
    Tokenizer t(o);
    CHECK_EQ(join(t.tokenize("@united awful")), "united|awful");
}

TEST("tokenize: removes http and https URLs") {
    Tokenizer t;
    CHECK_EQ(join(t.tokenize("see http://t.co/abc123 for details")), "see|for|details");
    CHECK_EQ(join(t.tokenize("see https://t.co/abc123 now")), "see|now");
}

TEST("tokenize: removes bare www URLs") {
    Tokenizer t;
    CHECK_EQ(join(t.tokenize("go to www.united.com today")), "go|to|today");
}

TEST("tokenize: hashtag keeps the word and drops the hash") {
    Tokenizer t;
    // "#fail" genuinely carries sentiment -- we want the word, not the symbol.
    CHECK_EQ(join(t.tokenize("total #fail today")), "total|fail|today");
}

TEST("tokenize: digits are not tokens") {
    Tokenizer t;
    CHECK_EQ(join(t.tokenize("delayed 3 hours")), "delayed|hours");
}

TEST("tokenize: min_token_length filters short tokens") {
    TokenizerOptions o;
    o.min_token_length = 3;
    Tokenizer t(o);
    CHECK_EQ(join(t.tokenize("it is a bad flight")), "bad|flight");
}

TEST("tokenize: emoji and non-ascii do not crash and do not produce tokens") {
    Tokenizer t;
    const auto out = t.tokenize(u8"great flight \U0001F60A");
    CHECK_EQ(join(out), "great|flight");
}

TEST("tokenize: realistic tweet from the dataset") {
    Tokenizer t;
    CHECK_EQ(join(t.tokenize("@AmericanAir my bag is STILL missing #lostluggage http://t.co/xY")),
             "my|bag|is|still|missing|lostluggage");
}

AFA_TEST_MAIN()
