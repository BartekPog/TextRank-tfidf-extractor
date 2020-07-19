import pandas as pd
import nltk
from bs4 import BeautifulSoup
import string
from nltk.corpus import stopwords
from nltk.tokenize import RegexpTokenizer
from nltk.stem import WordNetLemmatizer


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


def removeOtherChars(tokens: list):
    alpha = [w.encode('utf-8').decode('ascii', 'ignore')
             for w in tokens if w.isalnum()]

    nonzero = [w for w in alpha if len(w) > 0]
    return nonzero


def removeStopWords(tokens: list):
    noStop = [w for w in tokens if w not in stopwords.words('english')]
    return noStop


def reducePartsOfSpeech(tokens: list):
    partsOfSpeech = set([
        'JJ',       # adjective ‘big’
        # 'JJS',      # adjective, superlative ‘biggest’
        'NN',       # noun, singular ‘desk’
        # 'NNS',      # noun plural ‘desks’
        # 'NNP',      # proper noun, singular ‘Harrison’
        # 'NNPS',     # proper noun, plural ‘Americans’
        'VB',       # verb, base form take
        # 'VBD',      # verb, past tense took
        # 'VBG',      # verb, gerund/present participle taking
        # 'VBN',      # verb, past participle taken
        # 'VBP',      # verb, sing. present, non-3d take
        # 'VBZ'       # verb, 3rd person sing. present takes
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


def fixText(text: str) -> str:
    return text.replace('"', "'")
