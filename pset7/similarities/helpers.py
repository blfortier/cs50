from nltk.tokenize import sent_tokenize


def lines(a, b):
    """Return lines in both a and b"""

    set_a = set(a.splitlines())
    set_b = set(b.splitlines())

    return set_a & set_b

def sentences(a, b):
    """Return sentences in both a and b"""

    set_a = set(sent_tokenize(a))
    set_b = set(sent_tokenize(b))

    return set_a & set_b

def substrings(a, b, n):
    """Return substrings of length n in both a and b"""

    subs_a = set(subs(a, n))
    subs_b = set(subs(b, n))

    return subs_a & subs_b

def subs(text, n):
    subs = []

    for i in range(len(text) - n + 1):
        subs.append(text[i:i + n])

    print("Subs: {}".format(subs))

    return subs