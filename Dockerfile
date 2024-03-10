# Build
FROM ubuntu:latest as builder
RUN apt update && apt upgrade -y
RUN apt install -y g++ cmake ninja-build git libzmq3-dev libcurl4-openssl-dev zlib1g-dev
WORKDIR /mirror_metrics
COPY ./src /mirror_metrics/src
COPY ./lib /mirror_metrics/lib
COPY CMakeLists.txt /mirror_metrics/CMakeLists.txt
RUN cmake -S/mirror_metrics -B/mirror_metrics/build -G Ninja
RUN cmake --build /mirror_metrics/build --target clean
RUN cmake --build /mirror_metrics/build --target all

# Run
FROM ubuntu:latest
RUN apt update && apt upgrade -y
RUN apt install -y libzmq3-dev curl
EXPOSE 8080
WORKDIR /mirror_metrics
COPY --from=builder /mirror_metrics/build/mirror_metrics_engine .
ENTRYPOINT ["/bin/bash", "-c" , "tail -f /mirror_metrics/access.log | ./mirror_metrics_engine"]