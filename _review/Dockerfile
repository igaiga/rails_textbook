# This file is a sample Dockerfile to build Re:VIEW documents.
#
# Build Docker image:
#   $ docker build -t review .
#
# Build PDF:
#   $ docker run --rm -v `pwd`/_review:/work review /bin/sh -c "cd /work && rake pdf"
#
# cf. https://github.com/vvakame/docker-review/blob/master/Dockerfile

FROM vvakame/review:5.4

RUN apt-get update && \
    apt-get install -y --no-install-recommends \
      texlive-fonts-extra && \
    apt-get clean && \
    rm -rf /var/lib/apt/lists/*
