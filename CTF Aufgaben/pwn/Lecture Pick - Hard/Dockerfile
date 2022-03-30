FROM i386/debian:bookworm-slim as build
RUN apt-get update && apt-get install -y gcc
COPY challenge.c .
RUN gcc challenge.c -o /challenge

FROM i386/debian:bookworm-slim
RUN apt-get update && apt-get install -y socat
COPY --from=build /challenge .
COPY flag.txt .
EXPOSE 4000
CMD socat TCP-LISTEN:4000,reuseaddr,fork,nodelay EXEC:"./challenge"
