#include "afa/tokenizer.hpp"

#include <algorithm>
#include <cctype>

namespace afa {
namespace {

bool is_word_char(unsigned char c) {
    return std::isalpha(c) != 0 || c == '\'';
}

bool starts_with(std::string_view s, std::size_t pos, std::string_view prefix) {
    return s.size() - pos >= prefix.size() && s.compare(pos, prefix.size(), prefix) == 0;
}

/// Advance past a run of non-whitespace characters.
std::size_t skip_to_whitespace(std::string_view s, std::size_t pos) {
    while (pos < s.size() && std::isspace(static_cast<unsigned char>(s[pos])) == 0) ++pos;
    return pos;
}

}  // namespace

Tokenizer::Tokenizer(TokenizerOptions opts) : opts_(opts) {}

std::vector<std::string> Tokenizer::tokenize(std::string_view text) const {
    std::vector<std::string> tokens;
    std::string current;

    auto flush = [&]() {
        if (current.size() >= opts_.min_token_length) tokens.push_back(current);
        current.clear();
    };

    for (std::size_t i = 0; i < text.size();) {
        const unsigned char c = static_cast<unsigned char>(text[i]);

        // http://... and https://... carry no sentiment.
        if (opts_.strip_urls &&
            (starts_with(text, i, "http://") || starts_with(text, i, "https://") ||
             starts_with(text, i, "www."))) {
            flush();
            i = skip_to_whitespace(text, i);
            continue;
        }

        // @united identifies the airline, not the sentiment.
        if (opts_.strip_mentions && c == '@') {
            flush();
            i = skip_to_whitespace(text, i);
            continue;
        }

        // '#' is dropped but the word is kept: "#fail" -> "fail".
        if (c == '#') {
            if (!opts_.split_hashtags) flush();
            ++i;
            continue;
        }

        if (is_word_char(c)) {
            // A leading apostrophe is punctuation, not part of the word.
            if (c == '\'' && current.empty()) {
                ++i;
                continue;
            }
            current.push_back(opts_.lowercase
                                  ? static_cast<char>(std::tolower(c))
                                  : text[i]);
            ++i;
            continue;
        }

        flush();
        ++i;
    }
    flush();

    // Trailing apostrophes ("dogs'") are punctuation too.
    for (auto& t : tokens) {
        while (!t.empty() && t.back() == '\'') t.pop_back();
    }

    tokens.erase(std::remove_if(tokens.begin(), tokens.end(),
                                [this](const std::string& t) {
                                    return t.size() < opts_.min_token_length || t.empty();
                                }),
                 tokens.end());
    return tokens;
}

}  // namespace afa
