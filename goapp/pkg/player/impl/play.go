package impl

import (
	"errors"
	"io"
	"log/slog"
	"net/http"
	"os"
	"strings"
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

	for {

		var reader io.ReadCloser
		var contentType string

		if strings.HasPrefix(url, "file://") {
			filePath := url[7:] // Remove "file://" prefix
			logger.Info("Will play local file", "filePath", filePath)
			var err error
			reader, err = os.Open(filePath)
			if err != nil {
				return err
			}
			contentType = "audio/mp3"
		} else {
			logger.Info("Will play remote URL", "url", url)
			req, _ := http.NewRequest("GET", url, nil)
			req.Header.Set("User-Agent", "Retradio")
			req.Header.Set("Accept", "*/*")
			resp, err := http.DefaultClient.Do(req)
			if err != nil {
				return err
			}
			reader = resp.Body
			contentType = resp.Header.Get("Content-Type")
		}
		defer reader.Close()

		var streamer beep.StreamSeekCloser
		var format beep.Format

		if contentType == "audio/ogg" || contentType == "application/ogg" || contentType == "audio/vorbis" || contentType == "application/vorbis" {
			var err error
			streamer, format, err = vorbis.Decode(reader)
			if err != nil {
				return err
			}
		} else if contentType == "audio/mpeg" || contentType == "audio/mp3" {
			var err error
			streamer, format, err = mp3.Decode(reader)
			if err != nil {
				return err
			}
		} else if contentType == "audio/flac" || contentType == "application/flac" || contentType == "audio/x-flac" {
			var err error
			streamer, format, err = flac.Decode(reader)
			if err != nil {
				return err
			}
		} else if contentType == "audio/wav" || contentType == "audio/x-wav" {
			var err error
			streamer, format, err = wav.Decode(reader)
			if err != nil {
				return err
			}
		} else {
			return errors.New("unsupported content type: " + contentType)
		}
		defer streamer.Close()

		speaker.Init(format.SampleRate, format.SampleRate.N(time.Second/1))
		logger.Info("Speaker initialized", "sampleRate", format.SampleRate, "bufferSize", format.SampleRate.N(time.Second/1))

		end := make(chan struct{})
		speaker.Play(beep.Seq(streamer, beep.Callback(func() {
			close(end)
		})))

		logger.Info("Playback started")
		select {
		case <-end:
			logger.Info("Playback ended")
		case <-stop:
			logger.Info("Playback stopped")
			return nil
		}

	}
}
