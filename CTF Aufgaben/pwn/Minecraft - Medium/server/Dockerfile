FROM openjdk:8u111
WORKDIR /opt/minecraft
RUN wget https://launcher.mojang.com/v1/objects/1b557e7b033b583cd9f66746b7a9ab1ec1673ced/server.jar
COPY eula.txt .
COPY server.properties .
COPY flag.txt .
CMD java -jar server.jar
