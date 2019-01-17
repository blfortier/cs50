from cs50 import get_string
from sys import argv

string_1 = "To love, or to have loved,this suffices. Demand nothing more. There is no other pearl to be found in the shadowy folds of life."

string_2 = "To love or have loved, that is enough. Ask nothing further. There is no other pearl to be found in the dark folds of life."

set_1 = set(string_1.split())

set_2 = set(string_2.split())

common = list(set_1 & set_2)


print("results: {}".format(common))
