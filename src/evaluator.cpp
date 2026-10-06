#include "afa/evaluator.hpp"

#include <stdexcept>

// =============================================================================
//  YOUR IMPLEMENTATION -- commit 7
// =============================================================================
//
//  This is the module that makes the project credible. Everything else
//  produces a guess; this decides whether the guess is any good.
//
//  matrix_[truth][prediction] -- rows are what it really was, columns are what
//  you said. The diagonal is correct answers.
//
//  For class c:
//      TP = matrix_[c][c]
//      FP = sum over other truths o of matrix_[o][c]   (column c, minus diagonal)
//      FN = sum over other predictions o of matrix_[c][o] (row c, minus diagonal)
//
//      precision = TP / (TP + FP)      0.0 if TP + FP == 0
//      recall    = TP / (TP + FN)      0.0 if TP + FN == 0
//      f1        = 2PR / (P + R)       0.0 if P + R == 0
//
//  Guard every one of those divisions. A class that is never predicted gives
//  0/0 -- return 0.0, do not return NaN. NaN propagates silently through
//  macro_f1() and you end up printing "nan" in your README.
//
//  macro_f1 = (f1(Negative) + f1(Neutral) + f1(Positive)) / 3
//
//  SANITY CHECK you can verify by hand: predict "negative" for all 14,640 rows
//  of the airline dataset and you get accuracy 0.6269, macro-F1 0.2569. If your
//  evaluator does not reproduce those two numbers on that input, it is wrong.
//  tests/test_evaluator.cpp has this as a fixture.
// =============================================================================

namespace afa {

std::size_t Evaluator::index(Sentiment s) {
    switch (s) {
        case Sentiment::Negative: return 0;
        case Sentiment::Neutral:  return 1;
        case Sentiment::Positive: return 2;
    }
    return 1;
}

void Evaluator::add(Sentiment truth, Sentiment predicted) {
    ++matrix_[index(truth)][index(predicted)];
}

int Evaluator::count(Sentiment truth, Sentiment predicted) const {
    return matrix_[index(truth)][index(predicted)];
}

int Evaluator::total() const {
    int n = 0;
    for (const auto& row : matrix_)
        for (int v : row) n += v;
    return n;
}

double Evaluator::accuracy() const {
    throw std::logic_error("Evaluator::accuracy is not implemented yet");
}

double Evaluator::precision(Sentiment c) const {
    (void)c;
    throw std::logic_error("Evaluator::precision is not implemented yet");
}

double Evaluator::recall(Sentiment c) const {
    (void)c;
    throw std::logic_error("Evaluator::recall is not implemented yet");
}

double Evaluator::f1(Sentiment c) const {
    (void)c;
    throw std::logic_error("Evaluator::f1 is not implemented yet");
}

double Evaluator::macro_f1() const {
    throw std::logic_error("Evaluator::macro_f1 is not implemented yet");
}

std::string Evaluator::confusion_matrix() const {
    throw std::logic_error("Evaluator::confusion_matrix is not implemented yet");
}

std::string Evaluator::report() const {
    throw std::logic_error("Evaluator::report is not implemented yet");
}

}  // namespace afa
