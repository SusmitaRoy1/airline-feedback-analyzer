# Data

## What this project uses

**Twitter US Airline Sentiment** — 14,640 tweets sent to six US airlines in
February 2015, each labelled `negative`, `neutral` or `positive` by human
contributors.

| | |
|---|---|
| Original source | CrowdFlower / Figure Eight "Data for Everyone" |
| Mirror used here | `huggingface.co/datasets/osanseviero/twitter-airline-sentiment` |
| Licence | **CC BY-NC-SA 4.0** |
| Size | 3.26 MB (`Tweets.csv`) |
| Rows | 14,640 |

## Why the CSV is not in this repository

The licence is **ShareAlike** and **NonCommercial**. Redistributing the data
inside an MIT-licensed repository would misrepresent its licence terms, so the
file is deliberately excluded by `.gitignore` and fetched on demand instead.

This is not an inconvenience to work around — it is the correct handling of
someone else's data.

## Getting the data

```bash
# Linux / macOS
./scripts/fetch_data.sh
```

```powershell
# Windows
.\scripts\fetch_data.ps1
```

Either script downloads `Tweets.csv` into `data/`, which is git-ignored.

## Class distribution

Measured on the full file:

| Class | Count | Share |
|---|---:|---:|
| negative | 9,178 | 62.69% |
| neutral | 3,099 | 21.17% |
| positive | 2,363 | 16.14% |
| **total** | **14,640** | |

This imbalance is the single most important fact about the dataset. A model
that predicts `negative` for every input already scores **62.69% accuracy** —
which is why accuracy alone is a misleading metric here, and why this project
reports **macro-F1** (majority baseline: **0.2569**) as the headline number.

## Splits

The data is split 70 / 15 / 15 into train / dev / test with a fixed seed, so
runs are reproducible. Thresholds are tuned on **dev**; the **test** split is
used exactly once, at the end.

## Attribution

> Twitter US Airline Sentiment, CrowdFlower "Data for Everyone", 2015.
> Licensed under [CC BY-NC-SA 4.0](https://creativecommons.org/licenses/by-nc-sa/4.0/).

## Known quirks

Worth knowing before trusting any result:

- The data is from **February 2015**. Terms tied to that moment (`flyfi`,
  `passbook`, airport codes) can look strongly sentiment-bearing to a
  frequency-based model while carrying no sentiment at all.
- Labels are crowd-sourced and include a confidence column. Low-confidence
  neutral labels are noisy, which is a large part of why the neutral class is
  the hardest to classify.
- Airline handles (`@united`, `@AmericanAir`) correlate with the label because
  some airlines received more complaints than others. The tokenizer strips
  mentions on purpose so the model cannot learn the airline name as a shortcut.
