#
# Regular Expression Practice
# ----------------------------
# Key functions to use:
#  - findall : Returns a list containing all matches
#  - search  : Returns a Match object if there is a match anywhere in the string
#  - split   : Returns a list where the string has been split at each match
#  - sub     : Replaces one or many matches with a string
#
# Special characters:
#  - [] : A set of characters/digits
#  - \  : Signals a special sequence (can also be used to escape special characters)
#  - .  : Any character (except newline character)
#  - ^  : Starts with
#  - $  : Ends with
#  - *  : Zero or more occurrences
#  - +  : One or more occurrences
#  - ?  : Zero or one occurrence
#  - {} : Exactly the specified number of occurrences
#  - |  : Either or
#  - () : Capture and group
#
# Sequences:
#  - \A : Characters are at the beginning of the string
#  - \b : Characters are at the beginning or at the end of a word
#  - \B : Characters are present, but NOT at the beginning or at the end of a word
#  - \d : Contains digits (numbers from 0-9)
#  - \D : Does Not contain digits
#  - \s : Contains a white space character
#  - \S : Does Not contain a white space character
#  - \w : Contains any word characters (characters from a to Z, digits from 0-9, and the underscore _ character)
#  - \W : Does Not contain any word characters
#  - \Z : Characters are at the end of the string

import re

txt = "The rain in Spain"
x = re.findall(r"ai", txt)
print(x)

txt = "The rain in Spain"
x = re.split(r"\s", txt)
print(x)
x = re.split(r"\s", txt, maxsplit=2)
print(x)

txt = "The rain in Spain"
x = re.sub(r"\s", "-", txt)
print(x)
x = re.sub(r"\s", "-", txt, count=2)
print(x)
print()

print(r"\A - Beginning of string")
txt = "The rain in Spain"
x = re.search(r"\AT\w+", txt) # First word that starts with T at the beginning of the string
print(x.group())
print()

print(r"\b - Beginning of word")
txt = "The rain in Spain Spartan"
x = re.search(r"\bS\w+", txt) # First word that starts with S
print(x.group())
print()

print(r"\b - End of word")
x = re.search(r"\w+n\b", txt) # First word that ends with n
print(x.group())
print()

print(r"\B - Not at beginning neither at end of word")
txt = "The rain in Spain"
x = re.search(r"\Ba\w+n", txt) # First word that does not start with a but contains an a and ends with n
print(x.group())
print()

print(r"^ - Beginning of string")
txt = "The rain in Spain"
x = re.search(r"^\w+", txt) # First word that starts at the beginning of the string
print(x.group())
print()

x = re.search(r"\b\w+", txt) # First word that starts at the beginning of the string
print(x.group())
print()

print(r"$ - End of string")
txt = "The rain in Spain"
x = re.search(r"\w+$", txt) # Word that ends at the end of the string
print(x.group())
print()

x = re.search(r"\w+n\b", txt) # First word that ends with n
print(x.group())
print()

print(r"{} - Exactly the number of occurances")
txt = "My PAN is BUOPP7787C. Can you read it?"
x = re.search(r"[aA-zZ]{5}\d{4}[aA-zZ]", txt) # Word that ends at the end of the string
print(x.group())
print()

print(r"{} - Exactly the number of occurances")
txt = "My PAN is buopp7787c. Can you read it?"
x = re.search(r"[aA-zZ]{5}\d{4}[aA-zZ]", txt) # Word that ends at the end of the string
print(x.group())
print()
