## Multi Time Pad (Easy) - Solution

One time pad is a common encryption technique. In fact it is one of the only
ones which are proven to be uncrackable when used correctly.
For a correct usage a message M is XOR'ed with a same length key K to result in
a ciphertext C:

`C = M ⊕ K`

With xor the following holds true:
- `A ⊕ B = C`
- `A ⊕ C = B`
- `B ⊕ C = A`

Thus when one knows the ciphertext and the plaintext the key can be calculated
using C XOR M = K

The task name and descriptions hints that incontrary to correct one time pad
usage the key is in fact shorter (which means a smaller key is repeated to
fit the length of the message).

We know our plaintext starts with `nland{`, thus we can XOR the plaintext with
the ciphertext to retrieve the first 6 bytes of the key:

[using CyberChef](https://gchq.github.io/CyberChef/#recipe=From_Hex('Auto')XOR(%7B'option':'UTF8','string':'nland%7B'%7D,'Standard',false)To_Hex('Space',0)&input=N2QgNWIgYTEgYjAgNzcgNGMgYjggZWUgNjEgMWEgZjEgYWQgM2UgNTkgZjAgYWEgM2UgMDYgZWQgYWEgMjIgNWEgZjMgZjMgNjMgMDMgYTQgYTM), result: `13 37 c0 de 13 37`

As we can see the key seems to repeat itself after 4 bytes, XOR'ing our message
with the key `13 37 c0 de` we get the flag:

[using CyberChef](https://gchq.github.io/CyberChef/#recipe=From_Hex('Auto')XOR(%7B'option':'Hex','string':'13%2037%20c0%20de'%7D,'Standard',false)&input=N2QgNWIgYTEgYjAgNzcgNGMgYjggZWUgNjEgMWEgZjEgYWQgM2UgNTkgZjAgYWEgM2UgMDYgZWQgYWEgMjIgNWEgZjMgZjMgNjMgMDMgYTQgYTM), result: `nland{x0r-1s-n0t-1-t1m3-p4d}`
