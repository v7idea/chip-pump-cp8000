FROM ubuntu:24.04

ARG ARDUINO_CLI_VERSION=1.2.2

ENV DEBIAN_FRONTEND=noninteractive
ENV ARDUINO_DIRECTORIES_USER=/workspace/arduino
ENV ARDUINO_DIRECTORIES_DATA=/workspace/.arduino15

RUN apt-get update && apt-get install -y --no-install-recommends \
    bash \
    ca-certificates \
    curl \
    file \
    git \
    jq \
    make \
    python3 \
    python3-pip \
    python3-venv \
    tar \
    xz-utils \
  && rm -rf /var/lib/apt/lists/*

RUN curl -fsSL https://raw.githubusercontent.com/arduino/arduino-cli/master/install.sh | \
    BINDIR=/usr/local/bin sh -s "${ARDUINO_CLI_VERSION}"

WORKDIR /workspace

COPY entrypoint.sh /usr/local/bin/cp8000-dev-entrypoint
RUN chmod +x /usr/local/bin/cp8000-dev-entrypoint

ENTRYPOINT ["cp8000-dev-entrypoint"]
CMD ["bash"]
