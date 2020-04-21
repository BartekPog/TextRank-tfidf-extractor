import pandas as pd
from functools import reduce
import nltk
from bs4 import BeautifulSoup
import string
from nltk.corpus import stopwords
from nltk.tokenize import RegexpTokenizer
from nltk.stem import WordNetLemmatizer

# nltk.download()


DATAFRAME_PATH = "data/articles.csv"

df = pd.read_csv(DATAFRAME_PATH)


def pipeline_func(data, fns):
    return reduce(lambda a, x: x(a), fns, data)


def removeHtml(text: str):
    soup = BeautifulSoup(text, 'html.parser')
    noHtml = soup.get_text()
    return noHtml


def removePunctuation(text: str):
    noPunct = "".join([c for c in text if c not in string.punctuation])
    return noPunct


def removeNewLines(text: str):
    noNewlines = text.replace("\n", " ")
    return noNewlines


def tokenize(text: str):
    tokenizer = RegexpTokenizer(r'\w+')
    return tokenizer.tokenize(text.lower())


def removeStopWords(tokens: list):
    noStop = [w for w in tokens if w not in stopwords.words('english')]
    return noStop


def reducePartsOfSpeech(tokens: list):
    partsOfSpeech = set([
        'JJ',       # adjective ‘big’
        'JJS',      # adjective, superlative ‘biggest’
        'NN',       # noun, singular ‘desk’
        'NNS',      # noun plural ‘desks’
        'NNP',      # proper noun, singular ‘Harrison’
        'NNPS',     # proper noun, plural ‘Americans’
        'VB',       # verb, base form take
        'VBD',      # verb, past tense took
        'VBG',      # verb, gerund/present participle taking
        'VBN',      # verb, past participle taken
        'VBP',      # verb, sing. present, non-3d take
        'VBZ'       # verb, 3rd person sing. present takes
    ])
    partsTouples = nltk.pos_tag(tokens)
    justGoodParts = [x[0] for x in partsTouples if x[1] in partsOfSpeech]

    return justGoodParts


def lemmatize(tokens: list):
    lemmatizer = WordNetLemmatizer()
    lem = [lemmatizer.lemmatize(w) for w in tokens]
    return lem


def joinTokens(tokens: list):
    text = " ".join(tokens)
    return text


def preparePipeline(text: str):
    return pipeline_func(text, [
        removeHtml,
        removePunctuation,
        removeNewLines,
        tokenize,
        removeStopWords,
        reducePartsOfSpeech,
        lemmatize,
        joinTokens
    ])


preparePipeline(df["text"][100])
