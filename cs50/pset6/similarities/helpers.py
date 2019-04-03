from nltk.tokenize import sent_tokenize


def lines(a, b):
    """Return lines in both a and b"""
    a = set(a.split(sep="\n"))
    b = set(b.split(sep="\n"))
    c = a & b
    return c


def sentences(a, b):
    """Return sentences in both a and b"""
    a = set(sent_tokenize(a, language='english'))
    b = set(sent_tokenize(b, language='english'))
    c = a & b
    return c


def get_substr(s, n):
    o = []
    for e, x in enumerate(s):
        if len(s[e:e + n]) >= n:
            o.append(s[e:e + n])
    return set(o)


def substrings(a, b, n):
    """Return substrings of length n in both a and b"""
    a = get_substr(a, n)
    b = get_substr(b, n)

    return a & b

