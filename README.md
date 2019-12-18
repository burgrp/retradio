# Orange Pi Zero based web radio

## I2C peripherals

### Rotary Encoder

#### Addressing
- 0x40 NN Volume
- 0x41 AN Balance
- 0x42 BN Treble
- 0x43 NC Bass
- 0x44 AC Aperture
- 0x45 BC Tuning
- 0x46 ND Band

### Push buttons
- 0x49 NN 7 Bands switch

## Docker image

Install binfmt
```shell
docker run --rm --privileged docker/binfmt:820fdd95a9972a5308930a2bdfb8573dd4447ad3
docker buildx create --name cross
docker buildx inspect --bootstrap
```

Build the image
```shell
docker buildx build --platform linux/arm/v7 . -t burgrp/retradio --push
```
