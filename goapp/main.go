package main

import (
	"log"
	"net/http"
	"time"

	event "github.com/burgrp/go-event/pkg"
	"github.com/gopxl/beep/v2"
	"github.com/gopxl/beep/v2/mp3"
	"github.com/gopxl/beep/v2/speaker"
)

func main() {

	bus := event.NewEventBus("retradio")

	bus.Listen(func(msg string) {
		log.Println("Received message:", msg)
	})

	bus.Unlock()

	bus.Send("Hello, world!")

	//url := "http://relay1.swissgroove.ch:80"
	url := "http://amp.cesnet.cz:8000/cro3.ogg"
	// open url as a stream
	resp, err := http.Get(url)
	if err != nil {
		log.Fatal(err)
	}
	defer resp.Body.Close()

	streamer, format, err := mp3.Decode(resp.Body)
	//streamer, format, err := vorbis.Decode(resp.Body)
	if err != nil {
		log.Fatal(err)
	}
	defer streamer.Close()

	speaker.Init(format.SampleRate, format.SampleRate.N(time.Second/10))

	done := make(chan bool)
	speaker.Play(beep.Seq(streamer, beep.Callback(func() {
		done <- true
	})))

	<-done
}
