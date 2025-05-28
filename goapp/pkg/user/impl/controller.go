package impl

import (
	"log/slog"
	"os"
	"retradio/pkg/system"
	"retradio/pkg/user"

	event "github.com/burgrp/go-event/pkg"
	"gopkg.in/yaml.v3"
)

func Init(bus *event.EventBus, logger *slog.Logger) {

	loadUserSettings := func(file string) {
		logger.Info("Loading user settings", "file", file)

		content, err := os.ReadFile(file)
		if err != nil {
			logger.Error("Failed to read user settings file", "file", file, "error", err)
			return
		}

		var settings user.Settings
		if err := yaml.Unmarshal(content, &settings); err != nil {
			logger.Error("Failed to unmarshal user settings", "file", file, "error", err)
			return
		}

		bus.Send(user.SettingsChanged(&settings))

	}

	bus.Listen(func(sysConfigLoaded system.ConfigurationLoaded) {

		loadUserSettings(sysConfigLoaded.UserSettings)

	})
}
