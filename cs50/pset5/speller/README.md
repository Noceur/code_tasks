# Questions

## What is pneumonoultramicroscopicsilicovolcanoconiosis?
* "an invented long word said to mean a lung disease caused by inhaling very fine ash and sand dust.".

## According to its man page, what does `getrusage` do?
* "returns resource usage measures for *who*, which can be one of the following:"
* 'RUSAGE_SELF', 'RUSAGE_CHILDREN', 'RUSAGE_THREAD'.
* Essentially it is used for benchamarking processes/threads.


## Per that same man page, how many members are in a variable of type `struct rusage`?
* 16


## Why do you think we pass `before` and `after` by reference (instead of by value) to `calculate`, even though we're not changing their contents?
* I assume it is because of performance reasons, save memory? Feels like this is not a big deal with todays computers however(?)


## Explain as precisely as possible, in a paragraph or more, how `main` goes about reading words from a file. In other words, convince us that you indeed understand how that function's `for` loop works.
* It works by initlizing int c as getc(file) which everytime it gets called on the same file stream 'walks' one step forward as long as it doesn't reach EOF (end of file) where it ends.


## Why do you think we used `fgetc` to read each word's characters one at a time rather than use `fscanf` with a format string like `"%s"` to read whole words at a time? Put another way, what problems might arise by relying on `fscanf` alone?
* If we read whole words it has to end somewhere, a dot at the end of the word would probably be counted as part of the word which could be problematic. I suppose you could cleanse the words from such impurities bit it would be extra work.


## Why do you think we declared the parameters for `check` and `load` as `const` (which means "constant")?
* Because they are supposed to be constant and not changed. A check and load function does not need to change these.