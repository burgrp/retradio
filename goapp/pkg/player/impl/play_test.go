package impl_test

import (
	"log/slog"
	"retradio/pkg/player/impl"
	"testing"
	"time"

	"github.com/stretchr/testify/require"
)

func TestPlayAndStop(t *testing.T) {

	stop := make(chan struct{})

	go func() {
		time.Sleep(5 * time.Second)
		close(stop)
	}()
	require.NoError(t, impl.Play("http://ice4.somafm.com/7soul-128-mp3", slog.Default(), stop))
}

func TestPlayMore(t *testing.T) {

	stations := []string{
		"http://amp.cesnet.cz:8000/cro-jazz.ogg",
		"http://ice4.somafm.com/7soul-128-mp3",
		"http://ice1.somafm.com/secretagent-128-mp3",
	}

	for _, station := range stations {

		stop := make(chan struct{})

		go func() {
			time.Sleep(5 * time.Second)
			close(stop)
		}()
		require.NoError(t, impl.Play(station, slog.Default(), stop))

	}
}
