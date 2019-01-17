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

    subs = []

  #  for word in range(len(a)):
  #     subs_in_a = set(a[word:n])

    #for words in range(len(b)):
     #   print(words)
      #  subs_in_b = set(b[words:n])

    #print(subs_in_a)
    #print(subs_in_b)

    #subs = list(subs_in_a & subs_in_b)

    #print(subs)


     # TODO
    return subs

