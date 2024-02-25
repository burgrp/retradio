package main

import (
	"log"
	"net/http"
	"time"

	"github.com/gopxl/beep"
	"github.com/gopxl/beep/mp3"
	"github.com/gopxl/beep/speaker"
)

func main() {
	// f, err := os.Open("/home/paul/tmp/16 - Stayin' Alive.mp3")
	// if err != nil {
	// 	log.Fatal(err)
	// }

	url := "http://relay1.swissgroove.ch:80"
	// open url as a stream
	resp, err := http.Get(url)
	if err != nil {
		log.Fatal(err)
	}
	defer resp.Body.Close()

	streamer, format, err := mp3.Decode(resp.Body)
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
