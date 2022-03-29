FROM debian:bookworm-slim as build
RUN apt-get update && apt-get install -y gcc
COPY challenge.c .
RUN sed -i 's/nflag{dummy-flag-for-testing}/nflag{c4lcul4t1ng-th3-0ffs3ts-l1k3-a-pro}/' challenge.c
RUN gcc challenge.c -o /challenge

FROM debian:bookworm-slim
RUN apt-get update && apt-get install -y socat
COPY --from=build /challenge .
EXPOSE 4000
CMD "./challenge"
# TODO socat
