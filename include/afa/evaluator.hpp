#pragma once

#include <array>
#include <string>

#include "afa/types.hpp"

namespace afa {

/// Accumulates predictions and reports classification quality.
///
/// WHY MACRO-F1 IS THE HEADLINE METRIC, NOT ACCURACY:
/// the airline dataset is 62.69% negative, so a classifier that blindly
/// answers "negative" every single time already scores 62.69% accuracy --
/// while being completely useless. That same classifier scores a macro-F1
/// of 0.2569. Always report both, and lead with macro-F1.
class Evaluator {
public:
    void add(Sentiment truth, Sentiment predicted);

    int count(Sentiment truth, Sentiment predicted) const;
    int total() const;

    /// Fraction of predictions that were correct.
    double accuracy() const;

    /// Of everything predicted as `c`, how much was right. 0.0 if nothing
    /// was predicted as `c` (rather than NaN -- a never-predicted class
    /// should drag the score down, not poison it).
    double precision(Sentiment c) const;

    /// Of everything truly `c`, how much was found.
    double recall(Sentiment c) const;

    /// Harmonic mean of precision and recall. 0.0 when both are 0.
    double f1(Sentiment c) const;

    /// Unweighted mean of per-class F1 -- treats the rare classes as
    /// mattering as much as the common one. This is the number to report.
    double macro_f1() const;

    /// Human-readable 3x3 matrix, rows = truth, columns = prediction.
    std::string confusion_matrix() const;

    /// Full report: matrix, per-class precision/recall/F1, accuracy, macro-F1.
    std::string report() const;

private:
    static std::size_t index(Sentiment s);
    std::array<std::array<int, 3>, 3> matrix_{};
};

}  // namespace afa
