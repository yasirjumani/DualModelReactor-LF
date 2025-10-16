FROM ubuntu:jammy
COPY scripts scripts
RUN apt-get update && \
    apt-get install -y sudo zip unzip curl sed 
    # COMMENT THIS LINE OUT: bash ./scripts/setup-env.bash
