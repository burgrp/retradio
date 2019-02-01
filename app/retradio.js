const AudioContext = require('web-audio-api').AudioContext;
const context = new AudioContext;
const Speaker = require('speaker');
 
context.outStream = new Speaker({
  channels: context.format.numberOfChannels,
  bitDepth: context.format.bitDepth,
  sampleRate: context.sampleRate
});

const fn = "/home/paul/Downloads/Hop Trop na venkově/05. Dál šíny zvoní.mp3";
const fs = require("fs");
const mp3data = fs.readFileSync(fn);

context.decodeAudioData(mp3data, buffer => {
    const source = context.createBufferSource();
    source.buffer = buffer;
    source.connect(context.destination);
    source.start();   
});

