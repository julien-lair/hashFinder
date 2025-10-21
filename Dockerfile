FROM gcc:12
WORKDIR /usr/src/hasfinder
COPY . .
RUN apt-get update && apt-get install -y libssl-dev && rm -rf /var/lib/apt/lists/*
RUN gcc -o hashfinder src/main.c -lssl -lcrypto
CMD ["./hashfinder", "-g", "-f", "rockyou/test.txt", "-o", "sortie"]
