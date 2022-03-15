# Orange Pi Zero based web radio

## I2C peripherals

### Rotary EncoderX

#### Addressing

* 0x40 NN Volume
* 0x41 AN Balance
* 0x42 BN Treble
* 0x43 NC Bass
* 0x44 AC Aperture
* 0x45 BC Tuning
* 0x46 ND Band

### Push buttons

* 0x49 NN 7 Bands switch

## Docker image

Start buildx builder

```text
docker buildx create --name cross
docker buildx inspect --bootstrap
```

Build the image

```sh
docker run --rm --privileged docker/binfmt:820fdd95a9972a5308930a2bdfb8573dd4447ad3
docker buildx build --platform linux/arm/v7 . -t burgrp/retradio --push
```

## DEVICE.FARM

### OS installation
```sh
defa install device-id /dev/your-sd-card --wifi=ssid:password --ssh - --dto $PWD/mb-a/dto
```

### Retradio service installation
```sh
defa proxy device-id -- docker pull burgrp/retradio
defa proxy device-id -- docker-compose up -d
```
or 

```sh
./update-devices device-id ...
```