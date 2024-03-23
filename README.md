# collatz
## An automator for the collatz conjecture

The collatz conjecture is a very popular problem in mathematics, for it's a simple premise, yet no one has been able to prove it.

The collatz conjecture states that any number n will eventually reach 1 when operated upon under specific rules. If n is even, then simply divide it by 2. If n is odd, then multiply it by 3 and add 1. As you keep repeating that for the resulting values of n, you will find that all values of n will eventually reach 1 when iterated upon enough.

This program counts how many times n must be iterated upon in order to reach 1, and also measures how long it takes, just for funsies :)

### Installing

You could run this on any operating system, but I wrote it with Linux in mind, so Windows and Mac users might have to get creative when building the source (tho it really shouldn't be hard this is a small program)

#### Download

Open up your terminal and type:

` $> git clone https://github.com/reidiens/collatz`

then `cd` into the new directory.

Now just type `make` and you're set.

### Usage

It's super simple. Just type the number you want iterated as an argument to the command or type it in when asked. Negative numbers wrap around the values for a long integer (whatever that may be on your machine). Zero is not a valid input.
