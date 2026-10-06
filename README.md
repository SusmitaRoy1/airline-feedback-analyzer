# Airline Feedback Analyzer

A sentiment classifier for airline customer feedback, written from scratch in
C++17 — no machine-learning libraries, no external dependencies.

> **Status: in progress.** The build, test harness and tokenizer (the project
> scaffold, set up with AI assistance) are done. The
> lexicon, scorer and evaluator are being implemented. Every number in the
> Results section below is marked **TARGET** until it has actually been
> measured on the held-out test split — at which point it will be replaced with
> the real figure, whatever that figure turns out to be.

---

## Why this project

I spent eight years as cabin crew. I have read a lot of customer feedback, and I
know that the hard part is not the furious one-star review — that one is
obvious. The hard part is the *neutral* message: "Flight landed at 6." Is that
a complaint about the delay, or a statement of fact?

This project is an attempt to measure exactly how hard that is.

## What it does

```
afa train    --input data/train.csv --out model.lex
afa tune     --lexicon model.lex --input data/dev.csv
afa eval     --lexicon model.lex --input data/test.csv
afa classify --lexicon model.lex --text "bag still missing after 3 days" --explain
```

`--explain` prints the tokens that drove the decision, so a prediction can
always be traced back to a reason. (Output format only — the weights shown
are placeholders until the lexicon is trained.)

```
score: <sum>  ->  negative

  missing    <weight>
  still      <weight>
  bag        <weight>
```

## How it works

1. **Tokenize.** Lower-case, strip `@mentions` and URLs, split hashtags, drop
   digits and punctuation.
2. **Learn a lexicon.** For each token, compute the smoothed log-odds of it
   appearing in a positive versus a negative tweet:

   ```
   weight(t) = log( P(t | positive) / P(t | negative) )
   ```

   using document-frequency counts with add-one smoothing. Keep the *N* terms
   with the largest absolute weight.
3. **Score.** Sum the weights of the tokens present in the text.
4. **Threshold.** Two cut-offs turn a continuous score into three classes.
   These are tuned on the dev split, never on test.

No neural network, no pre-trained embeddings. The point was to understand every
line, and be able to explain any prediction.

## Results

Dataset: 14,640 labelled tweets, 62.69% of them negative. See [DATA.md](DATA.md).

Because the classes are heavily imbalanced, **accuracy is a misleading metric**
— predicting "negative" every single time already scores 62.69%. The headline
number here is therefore **macro-F1**, which averages the F1 score of all three
classes equally and gives that trivial strategy the low score it deserves.

| Model | Accuracy | Macro-F1 |
|---|---:|---:|
| Always predict negative (baseline) | 62.69% | 0.2569 |
| Learned lexicon | *TARGET ~74%* | *TARGET ~0.64* |

<!-- TODO: replace the TARGET row with measured test-split numbers, then
     paste the real confusion matrix below and delete this comment. -->

Per-class breakdown and confusion matrix: **TODO once measured.**

## Things that did not work

This section exists because a results table where every idea improves the score
is usually a table that has not been tested honestly.

> These two results come from a quick prototype run during the design phase,
> before the C++ implementation existed. They will be re-measured with
> `afa sweep` once the lexicon and evaluator are implemented, and this section
> will be updated with whatever the C++ version actually shows.

**Negation handling.** The obvious fix: detect "not", "never", "no" and flip
the sign of the next few tokens, so "not good" stops counting as positive.
Measured effect: **macro-F1 went slightly down.** The reason is that the
weights are *learned from this data*, so a word like "good" already has its
negated usage baked into its weight. Flipping the sign double-counts something
the model had already accounted for.

**Boosting aviation-specific terms.** My own idea, and the one I most wanted to
work: hand-weight domain vocabulary — `rebooked`, `gate agent`, `tarmac`,
`IROP`, `misconnect`. Measured effect: **+0.001 macro-F1, which is noise.**
Inspecting the lexicon explained why — 15 of the 22 terms I picked had *already*
been learned automatically, with sensible weights. The data had found them
without me.

Both results were disappointing and both are more interesting than a win.

## Where the domain knowledge actually helped

Not in the model — in knowing what to measure.

- Choosing macro-F1 over accuracy, because in a real feedback queue the rare
  categories are the ones that matter.
- Stripping airline handles, because `@united` appearing in angry tweets is a
  fact about 2015 complaint volumes, not about language.
- Recognising that the *neutral* class is where the real difficulty lives — and
  reporting its score separately rather than hiding it inside an average.

## Build

Requires CMake 3.16+ and a C++17 compiler. Nothing else.

```bash
git clone https://github.com/SusmitaRoy1/airline-feedback-analyzer
cd airline-feedback-analyzer
./scripts/fetch_data.sh          # or .\scripts\fetch_data.ps1 on Windows
cmake -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build
ctest --test-dir build --output-on-failure
```

CI builds and tests on Linux (GCC) and Windows (MSVC) on every push.

## Tests

Five suites run by `ctest`, using a small hand-written harness in
`tests/test_harness.hpp` (no GoogleTest — one less dependency to install).

The suite that matters most is in `test_evaluator.cpp`: it feeds the real class
counts into the evaluator with an always-negative prediction and asserts the
result is 0.6269 accuracy and 0.2569 macro-F1. If the metric code is ever
wrong, every number in this README is wrong too, and that test is what catches
it.

## Layout

```
include/afa/     public headers
src/             implementation
apps/main.cpp    command-line front end
tests/           five test suites
scripts/         dataset download
```

## Licence

Code is MIT ([LICENSE](LICENSE)). The dataset is **not** included and is under
a different licence — see [DATA.md](DATA.md).
