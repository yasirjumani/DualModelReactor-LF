# Inside your Dockerfile:
RUN apt-get update && \
    apt-get install -y sudo zip unzip curl sed && \
    bash ./scripts/setup-env.bash 
# ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ THIS IS FAILING THE BUILD
