## Lecture Pick (Easy) - Solution

The variable `flag` holds a pointer to the string we want to print. It is
located on the stack directly next to the `courses` array.
The user can input an integer `x` after which `courses[x]` is printed.
There are no boundary checks for the value entered for `x`, thus a value
smaller than 0 or bigger than the length of the array can be entered.

Depending on the order of `flag` and `courses` on the stack (influenced by the
compiler) the solution is to either input `-1` or `8`.
