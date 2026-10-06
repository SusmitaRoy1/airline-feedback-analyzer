#include "afa/types.hpp"

#include <algorithm>
#include <stdexcept>

namespace afa {

Sentiment sentiment_from_string(const std::string& s) {
    std::string lower = s;
    std::transform(lower.begin(), lower.end(), lower.begin(),
                   [](unsigned char c) { return static_cast<char>(std::tolower(c)); });

    if (lower == "negative") return Sentiment::Negative;
    if (lower == "neutral") return Sentiment::Neutral;
    if (lower == "positive") return Sentiment::Positive;

    throw std::invalid_argument("unrecognised sentiment label: '" + s + "'");
}

const char* to_string(Sentiment s) {
    switch (s) {
        case Sentiment::Negative: return "negative";
        case Sentiment::Neutral:  return "neutral";
        case Sentiment::Positive: return "positive";
    }
    return "neutral";
}

}  // namespace afa
