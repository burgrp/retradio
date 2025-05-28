package impl

import (
	"log/slog"
	"os"
	"retradio/pkg/system"
	"retradio/pkg/user"
	"sync"

	event "github.com/burgrp/go-event/pkg"
	"gopkg.in/yaml.v3"
)

var DefaultSettings = user.Settings{}

func Init(bus *event.EventBus, logger *slog.Logger) {

	var systemConfig *system.Configuration
	var fileMu sync.Mutex

	bus.Listen(func(sysConfigLoaded system.ConfigurationLoaded) {
		systemConfig = sysConfigLoaded

		file := systemConfig.UserSettings
		logger.Info("Loading user settings", "file", file)

		settings := DefaultSettings

		fileMu.Lock()
		content, err := os.ReadFile(file)
		fileMu.Unlock()
		if err != nil {
			logger.Error("Failed to read user settings file", "file", file, "error", err)
		} else {
			if err := yaml.Unmarshal(content, &settings); err != nil {
				logger.Error("Failed to unmarshal user settings", "file", file, "error", err)
			}
		}

		bus.Send(user.SettingsChanged(&settings))
	})

	bus.Listen(func(userSettings user.SaveSettings) {
		go func() {

			file := systemConfig.UserSettings
			logger.Info("Saving user settings", "file", file)

			content, err := yaml.Marshal(userSettings)
			if err != nil {
				logger.Error("Failed to marshal user settings", "file", file, "error", err)
				return
			}

			fileMu.Lock()
			err = os.WriteFile(file, content, 0644)
			fileMu.Unlock()
			if err != nil {
				logger.Error("Failed to write user settings file", "file", file, "error", err)
				return
			}

		}()
		bus.Send(user.SettingsChanged(userSettings))
	})
}
