package impl

import (
	"log/slog"
	"os"
	"retradio/pkg/common"
	"retradio/pkg/system"

	event "github.com/burgrp/go-event/pkg"
	"gopkg.in/yaml.v3"
)

func Init(bus *event.EventBus, logger *slog.Logger) {

	bus.Listen(func(common.ApplicationStarted) {

		if len(os.Args) != 2 {
			panic("use: retradio [config.yaml]")
		}

		configFile := "config.yaml"
		if len(os.Args) == 2 {
			configFile = os.Args[1]
		}

		logger.Info("Using config", "file", configFile)

		content, err := os.ReadFile(configFile)
		if err != nil {
			panic(err)
		}

		var config system.Configuration
		if err := yaml.Unmarshal(content, &config); err != nil {
			panic(err)
		}

		bus.Send(system.ConfigurationLoaded(&config))

	})

}
