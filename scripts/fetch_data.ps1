# Downloads the Twitter US Airline Sentiment dataset into data\.
#
# The CSV is CC BY-NC-SA 4.0 and is deliberately not committed -- see DATA.md.

$ErrorActionPreference = 'Stop'

$root = Split-Path -Parent $PSScriptRoot
$dataDir = Join-Path $root 'data'
$target = Join-Path $dataDir 'Tweets.csv'
$url = 'https://huggingface.co/datasets/osanseviero/twitter-airline-sentiment/resolve/main/Tweets.csv'

if (Test-Path $target) {
    Write-Host "Already present: $target"
    exit 0
}

New-Item -ItemType Directory -Force -Path $dataDir | Out-Null

Write-Host "Downloading Tweets.csv (about 3.3 MB)..."
Invoke-WebRequest -Uri $url -OutFile $target -UseBasicParsing

$rows = (Get-Content $target | Measure-Object -Line).Lines
Write-Host "Saved to $target ($rows lines)"
Write-Host ""
Write-Host "Licence: CC BY-NC-SA 4.0. Attribution and details are in DATA.md."
