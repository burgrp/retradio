FROM node:20-bookworm AS builder
WORKDIR /retradio

RUN apt-get update
RUN apt-get -y install alsa-utils libusb-dev libudev-dev

COPY app/package.json app/package-lock.json ./
RUN npm install --only=prod

COPY app/config.json ./
COPY app/src ./src/

FROM node:20-slim

WORKDIR /retradio

RUN apt-get update
RUN apt-get -y install mplayer alsa-utils libusb-dev libudev-dev

COPY --from=builder /retradio /retradio/

CMD alsactl init; node src/retradio.js
