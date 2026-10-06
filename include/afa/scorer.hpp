#pragma once

#include <string>
#include <string_view>
#include <utility>
#include <vector>

#include "afa/lexicon.hpp"
#include "afa/tokenizer.hpp"
#include "afa/types.hpp"

namespace afa {

/// Score band boundaries. A score strictly below `negative_below` is Negative,
/// strictly above `positive_above` is Positive, anything between is Neutral.
///
/// MEASURED defaults: tuned on a held-out dev split of the airline dataset.
/// Tune them yourself with `afa tune` -- never on the test split.
struct Thresholds {
    double negative_below = -1.5;
    double positive_above = 0.8;
};

struct Classification {
    Sentiment label = Sentiment::Neutral;
    double score = 0.0;
    /// Which tokens moved the score, and by how much. Powers `--explain`.
    /// Sorted by descending |weight|.
    std::vector<std::pair<std::string, double>> contributions;
};

class Scorer {
public:
    Scorer(Lexicon lexicon, Tokenizer tokenizer, Thresholds thresholds = {});

    Classification classify(std::string_view text) const;

    /// Sum of token weights, without banding.
    double score(std::string_view text) const;

    /// Apply the thresholds to an existing score.
    Sentiment label_for(double score) const noexcept;

    const Thresholds& thresholds() const noexcept { return thresholds_; }
    void set_thresholds(Thresholds t) noexcept { thresholds_ = t; }

private:
    Lexicon lexicon_;
    Tokenizer tokenizer_;
    Thresholds thresholds_;
};

}  // namespace afa
