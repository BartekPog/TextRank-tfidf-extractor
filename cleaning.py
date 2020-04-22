import pandas as pd
import csv
from functools import reduce
import transformers

# nltk.download()

DATAFRAME_PATH = "data/articles.csv"
OUT_CSV_PATH = "data/prepared.csv"

df = pd.read_csv(DATAFRAME_PATH)


def pipeline_func(data, fns):
    return reduce(lambda a, x: x(a), fns, data)


def preparePipeline(text: str):
    return pipeline_func(text, [
        transformers.removeHtml,
        transformers.removePunctuation,
        transformers.removeNewLines,
        transformers.tokenize,
        transformers.removeStopWords,
        transformers.reducePartsOfSpeech,
        transformers.lemmatize,
        transformers.joinTokens
    ])


preparePipeline(df["text"][100])

df["prep"] = df["text"].apply(preparePipeline)

# def fixText(text: str) -> str:
#     return text.replace('"', "'")

# df["text"] = df["text"].apply(fixText)

df["text"] = df["text"].apply(transformers.fixText)

# df.head()

significant = df[['title', 'text', 'prep']]

significant.to_csv(OUT_CSV_PATH, index=False,
                   header=False, quoting=csv.QUOTE_NONNUMERIC)

print("done")
