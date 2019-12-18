FROM node:lts-buster
WORKDIR /retradio

RUN apt-get update
RUN apt-get -y install mplayer

COPY app/package.json app/package-lock.json ./
RUN npm install

COPY app/config.json ./
COPY app/src ./src/

CMD node --inspect=localhost:9229 src/retradio.js