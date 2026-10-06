#pragma once

#include <string>
#include <vector>

namespace afa {

enum class Sentiment { Negative, Neutral, Positive };

/// Parse "negative" / "neutral" / "positive" (case-insensitive).
/// Throws std::invalid_argument on anything else.
Sentiment sentiment_from_string(const std::string& s);

/// Lower-case canonical name, suitable for round-tripping.
const char* to_string(Sentiment s);

/// One labelled example from the dataset.
struct LabelledText {
    std::string text;
    Sentiment label;
};

/// All three classes in a fixed order. Iterate this rather than casting ints,
/// so adding a class later does not silently break the evaluator.
inline const std::vector<Sentiment>& all_sentiments() {
    static const std::vector<Sentiment> v{Sentiment::Negative, Sentiment::Neutral,
                                          Sentiment::Positive};
    return v;
}

}  // namespace afa
