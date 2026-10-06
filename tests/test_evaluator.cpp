// Evaluator tests -- YOU WRITE THESE (commit 7).
//
// Target: 10+ assertions. This is the most important suite in the project:
// if the evaluator is wrong, every number in your README is wrong, and you
// will not know.

#include "afa/evaluator.hpp"

#include "test_harness.hpp"

using afa::Evaluator;
using afa::Sentiment;

TEST("evaluator: empty evaluator does not divide by zero") {
    TODO_TEST("accuracy() and macro_f1() on an empty evaluator must return 0.0, not NaN");
}

TEST("evaluator: perfect predictions give F1 of 1.0 for every class") {
    TODO_TEST("add each class correctly a few times -> macro_f1() == 1.0");
}

TEST("evaluator: completely wrong predictions give macro F1 of 0.0") {
    TODO_TEST("never predict the truth -> macro_f1() == 0.0");
}

TEST("evaluator: a class that is never predicted scores 0.0, not NaN") {
    TODO_TEST(
        "if Positive is never predicted, precision(Positive) must be 0.0 -- "
        "check with CHECK(!std::isnan(v)) as well as CHECK_EQ");
}

TEST("evaluator: counts land in the right cell") {
    TODO_TEST("add(Negative, Neutral) -> count(Negative, Neutral) == 1, others 0");
}

TEST("evaluator: accuracy is the diagonal over the total") {
    TODO_TEST("build a known matrix by hand and verify with CHECK_NEAR");
}

TEST("evaluator: precision and recall on a hand-computed matrix") {
    TODO_TEST(
        "construct a 3x3 you have worked out on paper, then assert each "
        "precision and recall value -- this is the test that proves the formulas");
}

TEST("evaluator: MAJORITY BASELINE FIXTURE -- the key sanity check") {
    TODO_TEST(
        "Feed the real airline class counts, always predicting Negative:\n"
        "          9178 negative, 3099 neutral, 2363 positive\n"
        "        Expect accuracy ~= 0.6269 and macro_f1 ~= 0.2569 (eps 1e-3).\n"
        "        If this test does not pass, your evaluator is wrong and every\n"
        "        number you report will be wrong too.");
    // Evaluator e;
    // for (int i = 0; i < 9178; ++i) e.add(Sentiment::Negative, Sentiment::Negative);
    // for (int i = 0; i < 3099; ++i) e.add(Sentiment::Neutral,  Sentiment::Negative);
    // for (int i = 0; i < 2363; ++i) e.add(Sentiment::Positive, Sentiment::Negative);
    // CHECK_NEAR(e.accuracy(), 0.6269, 1e-3);
    // CHECK_NEAR(e.macro_f1(), 0.2569, 1e-3);
}

TEST("evaluator: confusion_matrix output contains all nine counts") {
    TODO_TEST("smoke test the formatting -- it ends up in your README");
}

TEST("evaluator: report contains accuracy and macro-F1 labels") {
    TODO_TEST("smoke test");
}

AFA_TEST_MAIN()
