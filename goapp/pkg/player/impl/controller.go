package impl

import (
	"log/slog"
	"retradio/pkg/player"

	event "github.com/burgrp/go-event/pkg"
)

func Init(bus *event.EventBus, logger *slog.Logger) {

	bus.Listen(func(url player.Play) {
		println("------------------------------------------", url)
		// err := play(string(url))
		// if err != nil {
		// 	logger.Error("Failed to play URL", "url", url, "error", err)
		// 	return
		// }
	})

}
