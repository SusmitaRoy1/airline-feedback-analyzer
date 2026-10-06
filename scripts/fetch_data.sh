#!/usr/bin/env bash
# Downloads the Twitter US Airline Sentiment dataset into data/.
#
# The CSV is CC BY-NC-SA 4.0 and is deliberately not committed -- see DATA.md.

set -euo pipefail

root="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
data_dir="$root/data"
target="$data_dir/Tweets.csv"
url="https://huggingface.co/datasets/osanseviero/twitter-airline-sentiment/resolve/main/Tweets.csv"

if [ -f "$target" ]; then
    echo "Already present: $target"
    exit 0
fi

mkdir -p "$data_dir"

echo "Downloading Tweets.csv (about 3.3 MB)..."
if command -v curl >/dev/null 2>&1; then
    curl -fsSL "$url" -o "$target"
else
    wget -q "$url" -O "$target"
fi

echo "Saved to $target ($(wc -l < "$target") lines)"
echo
echo "Licence: CC BY-NC-SA 4.0. Attribution and details are in DATA.md."
