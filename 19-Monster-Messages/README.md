# Some comments

This puzzle was really interesting. My solution is inspired by
![Brzozowksi
derivatives](https://en.wikipedia.org/wiki/Brzozowski_derivative).

Here are the rule for the example

~~~
0: 4 1 5
1: 2 3 | 3 2
2: 4 4 | 5 5
3: 4 5 | 5 4
4: "a"
5: "b"
~~~

Suppose we are in state 0, and we try to recognize a word
starting with an `"a"`.

The right part starts with `4`, which produces an `"a"`

So after consuming the `a`, the execution stack contains `(1 5)`.

Suppose now the second letter is a  `"b"`. The rule 1 may be expanded to
`23 | 32`, then `a43 | b53 | a52 | b42`.

As the second letter is a `b`, the only possibilities  are `b53` and `b42`
(some non-determinacy is left).

So we can easily precompute a table (e = empty word)

| n | a-       | b-       |
|---|----------|----------|
| 0 | {15}     | { }      |
| 1 | {43, 52} | {53, 42} |
| 2 | {4}      | {5}      |
| 3 | {5}      | {4}      |
| 4 | {e}      | { }      |
| 5 | { }      | {e}      |

which tells what should replace the rule `n` on top of the execution stack
when a letter is encountered.



