""" Solution Relatively easy (medium, crypto)

Flag: nland{R3latively_Prim3}

My friend said RSA is relatively easy, so I send him the same message two times with a different modulus and public key so he has a fighting chance. 
My encryption is unbreakable.

n1=0xcfc59d54b4b2e9ab1b5d90920ae88f430d39fee60d18dddbc623d15aae645e4e50db1c07a02d472b2eebb075a547618e1154a15b1657fbf66ed7e714d23ac70bdfba4c809bbb1e27687163cb09258a07ab2533568192e29a3b8e31a5de886050b28b3ed58e81952487714dd7ae012708db30eaf007620cdeb34f150836a4b723
e1=0x1695ea
c1=0x2c4ade78c8e09c9839942c45389f93156e0abb10879b66bbb881ee67189be24d0ffd54ba3c174eafa929ad9c552090de8a8f8ac8a7007f542ec82e2189a232014487f951972db530ceb9c9d2d2e0355e04c57adea1c1f40d0463162aa9b440fa54d9455da512397d0526716aad1fbb839181c1dc1532a10ca5504a8e09082d8e
n2=0xd45304b186dc82e40bd387afc831c32a4c7ba514a64ae051b62f483f27951065a6a04a030d285bdc1cb457b24c2f8701f574094d46d8de37b5a6d55356d1d368b89e16fa71b6603bd037c7f329a3096ce903937bb0c4f112a678c88fd5d84016f745b8281aea8fd5bcc28b68c293e4ef4a62a62e478a8b6cd46f3da73fa34c63
e2=0x1f9096
c2=0xb7cc89df7788b0fb68c941628fd89529c78d15fe913162c2363d639265c7f8641628437916179a8f3165bbbbdeb36a7dbca5af8787a4ccf3e335543b52cf072e3c5ed41571dfae682e5f00b7a9a305ab4e756f4fcd10ae900d7b5af62de93518527c885731a1b82537a82ef125db984540fdac59ba1a4b59df1f414e285006ad
 
To encode a new flag:

m = b"nland{R3latively_Prim3}"
em = bytes_to_long(m)
c = pow(em,e,n)

Requirement:

e and φ(n) are not relatively prime

k1 = gcd(e1,(p1-1)*(q1-1)) == 10
k2 = gcd(e2,(p2-1)*(q2-1)) == 10
--> e is dividable by 10

t1 = (p1-1)*(q1-1)
t2 = (p2-1)*(q2-1)
--> has to be devideable by 10

Math:
https://crypto.stackexchange.com/questions/80303/in-rsa-encryption-why-does-the-public-exponent-usually-e-have-to-be-coprim
"""

from Crypto.Util.number import *
import gmpy2
import binascii
import math 


n1=0xcfc59d54b4b2e9ab1b5d90920ae88f430d39fee60d18dddbc623d15aae645e4e50db1c07a02d472b2eebb075a547618e1154a15b1657fbf66ed7e714d23ac70bdfba4c809bbb1e27687163cb09258a07ab2533568192e29a3b8e31a5de886050b28b3ed58e81952487714dd7ae012708db30eaf007620cdeb34f150836a4b723
#q1 = 12037827528067911684278967221392433256129944002157200272548317200308481572950474775891360447285969682243206009995242277136633522897723532096467191105943909 
#p1 = 12120327527644543811107783655014863098833219936714394976342507913322405566177432644931575840816861543106701611662013978324877080018872656490603706071067111 
e1=0x1695ea
#(2 * 3 * 5 * 49339) 
c1=0x2c4ade78c8e09c9839942c45389f93156e0abb10879b66bbb881ee67189be24d0ffd54ba3c174eafa929ad9c552090de8a8f8ac8a7007f542ec82e2189a232014487f951972db530ceb9c9d2d2e0355e04c57adea1c1f40d0463162aa9b440fa54d9455da512397d0526716aad1fbb839181c1dc1532a10ca5504a8e09082d8e
n2=0xd45304b186dc82e40bd387afc831c32a4c7ba514a64ae051b62f483f27951065a6a04a030d285bdc1cb457b24c2f8701f574094d46d8de37b5a6d55356d1d368b89e16fa71b6603bd037c7f329a3096ce903937bb0c4f112a678c88fd5d84016f745b8281aea8fd5bcc28b68c293e4ef4a62a62e478a8b6cd46f3da73fa34c63
#p2 = 12120327527644543811107783655014863098833219936714394976342507913322405566177432644931575840816861543106701611662013978324877080018872656490603706071067111
#q2 = 12301580698247665838432962460247894405698817646605188562297985838079356879336309758823376086396761749681729993573203954506346863479448531269351981555913253
e2=0x1f9096
#e2 = (2 * 31 * 5 * 6673)  
c2=0xb7cc89df7788b0fb68c941628fd89529c78d15fe913162c2363d639265c7f8641628437916179a8f3165bbbbdeb36a7dbca5af8787a4ccf3e335543b52cf072e3c5ed41571dfae682e5f00b7a9a305ab4e756f4fcd10ae900d7b5af62de93518527c885731a1b82537a82ef125db984540fdac59ba1a4b59df1f414e285006ad

# calculating the comman factor if n1 and n2
p = gcd(n1,n2)
q1 = n1//p
q2 = n2//p

#callculating greatest factor of e and φ(n)
e1 = e1//math.gcd(e1,(p-1)*(q1-1))
e2 = e2//math.gcd(e2,(p-1)*(q2-1)) 

#calculating the private keys
φ1 = (p-1)*(q1-1)
φ2 = (p-1)*(q2-1)
d1 = gmpy2.invert(e1,φ1)
d2 = gmpy2.invert(e2,φ2)

#decrypting the cipher
f1 = pow(c1,d1,n1)
f2 = pow(c2,d2,n2)

#Chinese Remainder Theorem ref: https://github.com/findneo/RSA-ATTACK/blob/master/rsattack/rsattack.py
def GCRT(mi, ai):
    curm, cura = mi[0], ai[0]
    for (m, a) in zip(mi[1:], ai[1:]):
        d = math.gcd(curm, m)
        c = a - cura
        K = c // d * gmpy2.invert(curm // d, m // d)
        cura += curm * K
        curm = curm * m // d
        cura %= curm
    return (cura % curm, curm)


f3,lcm = GCRT([n1,n2],[f1,f2])
n3 = q1*q2
c3 = f3%n3
φ3 = (q1-1)*(q2-1)

#because e and φ(n) both also have the comman faktor 2
ding = 10//gcd((q1-1)*(q2-1),10) 
d3 = gmpy2.invert(ding,φ3) 
m3 = pow(c3,d3,n3)

#make flag readable
flag = gmpy2.iroot(m3,2)[0]
print(binascii.unhexlify(hex(flag)[2:].strip("L")))
