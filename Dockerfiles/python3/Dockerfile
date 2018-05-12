# Build a docker image containing python3 from latest ubuntu LTS

# docker build -t mypython3 .
FROM ubuntu:bionic

# to turn off some apt warnings
RUN echo 'debconf debconf/frontend select Noninteractive' | debconf-set-selections

RUN apt-get update \
	&& apt-get install -y --no-install-recommends apt-utils \
	&& apt-get install -y --no-install-recommends build-essential python3 python3-dev python3-pip python3-venv \
	&& apt-get update && apt install -y --no-install-recommends python3-distutils \
	&& python3 -m pip install pip --upgrade

RUN rm -rf /var/lib/apt/lists/*

WORKDIR /usr