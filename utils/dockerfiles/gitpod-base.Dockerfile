FROM ubuntu:jammy

COPY scripts scripts
RUN apt-get update && apt-get install -y sudo zip unzip curl sed
