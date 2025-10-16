FROM ubuntu:jammy

COPY scripts scripts
RUN apt-get update && \
    apt-get install -y sudo zip unzip curl sed && \
    # Remove the bash call and replace with a simple test command:
    echo "Running setup-env script placeholder"
    # RUN bash ./scripts/setup-env.bash
