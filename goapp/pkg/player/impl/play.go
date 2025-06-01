package impl

import (
	"errors"
	"log/slog"
	"net/http"
	"time"

	"github.com/gopxl/beep/v2"
	"github.com/gopxl/beep/v2/flac"
	"github.com/gopxl/beep/v2/mp3"
	"github.com/gopxl/beep/v2/speaker"
	"github.com/gopxl/beep/v2/vorbis"
	"github.com/gopxl/beep/v2/wav"
)

func Play(url string, logger *slog.Logger, stop chan struct{}) error {

	logger = logger.With("url", url)

	logger.Info("Will play")

	req, _ := http.NewRequest("GET", url, nil)
	req.Header.Set("User-Agent", "Retradio")
	req.Header.Set("Accept", "*/*")
	resp, err := http.DefaultClient.Do(req)
	if err != nil {
		return err
	}

	var streamer beep.StreamSeekCloser
	var format beep.Format

	contentType := resp.Header.Get("Content-Type")
	if contentType == "audio/ogg" || contentType == "application/ogg" || contentType == "audio/vorbis" || contentType == "application/vorbis" {
		streamer, format, err = vorbis.Decode(resp.Body)
		if err != nil {
			return err
		}
	} else if contentType == "audio/mpeg" || contentType == "audio/mp3" {
		streamer, format, err = mp3.Decode(resp.Body)
		if err != nil {
			return err
		}
	} else if contentType == "audio/flac" || contentType == "application/flac" || contentType == "audio/x-flac" {
		streamer, format, err = flac.Decode(resp.Body)
		if err != nil {
			return err
		}
	} else if contentType == "audio/wav" || contentType == "audio/x-wav" {
		streamer, format, err = wav.Decode(resp.Body)
		if err != nil {
			return err
		}
	} else {
		return errors.New("unsupported content type: " + contentType)
	}
	defer streamer.Close()

	speaker.Init(format.SampleRate, format.SampleRate.N(time.Second/1))
	logger.Info("Speaker initialized", "sampleRate", format.SampleRate, "bufferSize", format.SampleRate.N(time.Second/1))

	done := make(chan struct{})
	speaker.Play(beep.Seq(streamer, beep.Callback(func() {
		close(done)
	})))

	logger.Info("Playback started")
	select {
	case <-done:
		logger.Info("Playback completed")
	case <-stop:
		logger.Info("Playback stopped")
	}

	return nil
}
