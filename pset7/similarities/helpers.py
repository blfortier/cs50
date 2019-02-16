from nltk.tokenize import sent_tokenize


def lines(a, b):
    """Return lines in both a and b"""

    # Takes the input and splits the strings
    # into a list of lines it contains, while
    # taking that and parsing it into a set
    set_a = set(a.splitlines())
    set_b = set(b.splitlines())

    # Return the intersection of lines
    # both string contain
    return set_a & set_b


def sentences(a, b):
    """Return sentences in both a and b"""

    # Takes the input and uses tokenize to
    # turn each string into a list of English
    # sentences, while taking that and parsing
    # it into a set
    set_a = set(sent_tokenize(a))
    set_b = set(sent_tokenize(b))

    # Return the intersection of sentences
    # both strings contain
    return set_a & set_b


def substrings(a, b, n):
    """Return substrings of length n in both a and b"""

    # Takes the input and calls a
    # helper function, subs, to find
    # the substrings of length n. Takes
    # the results of subs and parses it
    # into a set
    subs_a = set(subs(a, n))
    subs_b = set(subs(b, n))

    # Return the intersection of lines
    # both string contain
    return subs_a & subs_b


# Helper function for substrings
# that finds all substrings of length
# n and stores them in an array
# Returns this array
def subs(text, n):
    subs = []

    for i in range(len(text) - n + 1):
        subs.append(text[i:i + n])

    print("Subs: {}".format(subs))

    return subs