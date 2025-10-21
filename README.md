docker pull gcc:12
docker build -t hashfinder .
docker run --rm -it hashfinder
