FROM debian:bookworm-slim as build
RUN apt-get update && apt-get install -y gcc
COPY challenge.c .
RUN gcc challenge.c -o /challenge

FROM debian:bookworm-slim
RUN apt-get update && apt-get install -y socat
COPY --from=build /challenge .
COPY flag.txt .
EXPOSE 4000
CMD "./challenge"
# TODO socat
