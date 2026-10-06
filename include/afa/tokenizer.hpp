#pragma once

#include <string>
#include <string_view>
#include <vector>

namespace afa {

struct TokenizerOptions {
    bool lowercase = true;
    bool strip_urls = true;
    /// Airline handles (@united) are not sentiment -- they identify the target.
    /// Leaving them in lets the model learn "united == negative", which is
    /// dataset bias, not language understanding.
    bool strip_mentions = true;
    /// "#fail" carries sentiment, so keep the word and drop the '#'.
    bool split_hashtags = true;
    std::size_t min_token_length = 1;
};

/// Splits raw feedback text into lower-cased word tokens.
///
/// Tweet-aware: URLs and @mentions are removed, hashtags keep their word.
/// Apostrophes are kept inside words ("don't" stays one token) because
/// splitting them changes meaning.
class Tokenizer {
public:
    explicit Tokenizer(TokenizerOptions opts = {});

    std::vector<std::string> tokenize(std::string_view text) const;

    const TokenizerOptions& options() const noexcept { return opts_; }

private:
    TokenizerOptions opts_;
};

}  // namespace afa
