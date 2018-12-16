# Questions

## What is pneumonoultramicroscopicsilicovolcanoconiosis?

A lung disease that is caused by inhaling very fine ash and sand dust

## According to its man page, what does `getrusage` do?

'getrusage' times the implementations of check, load, size, and unload. Returns resource usage

## Per that same man page, how many members are in a variable of type `struct rusage`?

16, which includes 2 structs

## Why do you think we pass `before` and `after` by reference (instead of by value) to `calculate`, even though we're not changing their contents?

I think 'before' and 'after' is passed by reference so various function have access to it.

## Explain as precisely as possible, in a paragraph or more, how `main` goes about reading words from a file. In other words, convince us that you indeed understand how that function's `for` loop works.

The for loop works as follows: Each individual character is read in from the text file, until EOF is reached. If c, which is the char being read in, is an alpha char or ', and the index is > 0,
the char is added to 'word'. Index is incremented to keep track of length of word. If it is found that the current word being read in is too long (> 45 chars), the remainder of
the word is consumed and index is set back to 0 so it can keep track of the length of the next word. If a word has a number in it, it is ignored and index is once again
set back to 0. Once a whole word is read, 'word' is reset to be empty and the word counter is incremented.

## Why do you think we used `fgetc` to read each word's characters one at a time rather than use `fscanf` with a format string like `"%s"` to read whole words at a time? Put another way, what problems might arise by relying on `fscanf` alone?

fscanf would cause problems because some words have apostrophes, and some may even have numbers present.

## Why do you think we declared the parameters for `check` and `load` as `const` (which means "constant"?

'check' and 'load' were declared as constants because we don't want the functions to change them, only read them.
