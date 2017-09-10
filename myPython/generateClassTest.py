#!/usr/bin/env python
# coding=utf-8
import random
import sys
from urllib.request import urlopen
WORD_URL = 'http://learnpythonthehardway.org/words.txt'
WORDS = []
PHRASES = {
    "class %%%(%%%):":
    "Make a class named %%% that is-a %%%.",
    "class %%%(object):\n\tdef __init__(self, ***)":
     "class @@@ has-a __init__ that takes self and %%% parameters.",
    "class %%%(object):\n\tdef ***(self, @@@)":
    "class %%% has-a function named *** that takes self and @@@ parameters."
}

PHRASES_FIRST = False
if( len(sys.argv) == 2 and sys.argv[1]=="english" ):
    PHRASES_FIRST = True

for word in urlopen(WORD_URL).readlines():
    WORDS.append(word.decode("utf-8").strip())

def convert(snippet, phrase):
    class_names = [w.capitalize() for w in random.sample(WORDS, snippet.count("%%%"))]
    other_names = random.sample(WORDS, snippet.count("***"))
    results = []
    param_names = []

    for i in range(0, snippet.count("@@@")):
        param_count = random.randint(1,3)
        param_names.append(', '.join(random.sample(WORDS, param_count)))

    for sentence in snippet, phrase:
        result = sentence[:]
        for word in class_names:
            result = result.replace("%%%", word, 1)

        for word in other_names:
            result = result.replace("***", word, 1)

        for word in param_names:
            result = result.replace("@@@", word, 1)

        results.append(result)
    return results

try:
    while True:
        snippets = list(PHRASES.keys())
        random.shuffle( snippets )
        for snippet in snippets:
            phrase = PHRASES[snippet]
            question, answer = convert( snippet, phrase )

            if PHRASES_FIRST:
                question, answer = answer, question

            print( question )
            input("> ")
            print( "ANSWER: %s\n" % answer )
except EOFError:
    print("\nBye")
