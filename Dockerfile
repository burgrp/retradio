FROM node:lts-buster
WORKDIR /retradio

RUN apt-get update
RUN apt-get -y install mplayer

COPY app/package.json app/package-lock.json ./
RUN npm install --only=prod

COPY app/config.json ./
COPY app/src ./src/

CMD node src/retradio.js