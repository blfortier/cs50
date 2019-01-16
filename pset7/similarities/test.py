from cs50 import get_string
from sys import argv


set_1 = set(open(argv[1]).read().split())

set_2 = set(open(argv[2]).read().split())

print("set_1: {}".format(set_1))
print("set_2: {}".format(set_2))

print("common: {}".format(set_1 & set_2))
