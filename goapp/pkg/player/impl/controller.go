package impl

import (
	"log"
	"log/slog"
	"net/http"
	"retradio/pkg/common"
	"retradio/pkg/user"
	"time"

	event "github.com/burgrp/go-event/pkg"
	"github.com/gopxl/beep/v2"
	"github.com/gopxl/beep/v2/flac"
	"github.com/gopxl/beep/v2/mp3"
	"github.com/gopxl/beep/v2/speaker"
	"github.com/gopxl/beep/v2/vorbis"
	"github.com/gopxl/beep/v2/wav"
)

func Init(bus *event.EventBus, logger *slog.Logger) {

	var currentUrl string

	bus.Listen(func(userSettings user.SettingsChanged) {

		if len(userSettings.Stations) <= userSettings.Tuning.Set {
			logger.Warn("No stations configured for the current set", "set", userSettings.Tuning.Set)
			return
		}
		set := userSettings.Stations[userSettings.Tuning.Set]

		if len(set) <= userSettings.Tuning.Station {
			logger.Warn("No station configured for the current tuning", "set", userSettings.Tuning.Set, "station", userSettings.Tuning.Station)
			return
		}
		station := set[userSettings.Tuning.Station]

		url := station.URL

		if url != currentUrl {
			currentUrl = url

			go func() {

				logger.Info("Playing URL", "url", station.URL)

				resp, err := http.Get(station.URL)
				if err != nil {
					logger.Error("Failed to get stream URL", "url", station.URL, "error", err)
					return
				}
				defer resp.Body.Close()

				var streamer beep.StreamSeekCloser
				var format beep.Format

				contentType := resp.Header.Get("Content-Type")
				if contentType == "audio/ogg" || contentType == "application/ogg" || contentType == "audio/vorbis" || contentType == "application/vorbis" {
					streamer, format, err = vorbis.Decode(resp.Body)
					if err != nil {
						logger.Error("Failed to decode OGG stream", "url", station.URL, "error", err)
						return
					}
				} else if contentType == "audio/mpeg" || contentType == "audio/mp3" {
					streamer, format, err = mp3.Decode(resp.Body)
					if err != nil {
						logger.Error("Failed to decode MP3 stream", "url", station.URL, "error", err)
						return
					}
				} else if contentType == "audio/flac" || contentType == "application/flac" || contentType == "audio/x-flac" {
					streamer, format, err = flac.Decode(resp.Body)
					if err != nil {
						logger.Error("Failed to decode FLAC stream", "url", station.URL, "error", err)
						return
					}
				} else if contentType == "audio/wav" || contentType == "audio/x-wav" {
					streamer, format, err = wav.Decode(resp.Body)
					if err != nil {
						logger.Error("Failed to decode WAV stream", "url", station.URL, "error", err)
						return
					}
				} else {
					logger.Error("Unsupported content type", "url", station.URL, "contentType", contentType)
					return
				}

				if err != nil {
					log.Fatal(err)
				}
				defer streamer.Close()

				speaker.Init(format.SampleRate, format.SampleRate.N(time.Second/1))

				done := make(chan bool)
				speaker.Play(beep.Seq(streamer, beep.Callback(func() {
					done <- true
				})))

				<-done

				speaker.Close()
				logger.Info("Playback finished")
			}()
		}
	})

	var us user.Settings

	bus.Listen(func(common.ApplicationStarted) {
		go func() {
			for {
				time.Sleep(5 * time.Second)
				us.Tuning.Station++
				if us.Tuning.Station >= len(us.Stations[us.Tuning.Set]) {
					us.Tuning.Station = 0
				}
				bus.Send(user.SaveSettings(&us))
			}
		}()
	})

	bus.Listen(func(userSettings user.SettingsChanged) {
		us = *userSettings
	})

}
