FROM python:3

RUN pip install pycryptodome

COPY Encryptionserver.py .
RUN sed -i 's/nflag{dummy-flag-for-testing}/nland{810ck_c1ph325_423_fun}/' Encryptionserver.py

EXPOSE 1337
CMD python Encryptionserver.py
