package impl

import (
	"log/slog"
	"os"
	"retradio/pkg/system"
	"retradio/pkg/user"

	event "github.com/burgrp/go-event/pkg"
	"gopkg.in/yaml.v3"
)

var DefaultSettings = user.Settings{}

func Init(bus *event.EventBus, logger *slog.Logger) {

	var systemConfig *system.Configuration

	saveUserSettings := func(userSettings *user.Settings) error {

		file := systemConfig.UserSettings
		logger.Info("Saving user settings", "file", file)

		content, err := yaml.Marshal(userSettings)
		if err != nil {
			return err
		}
		err = os.WriteFile(file, content, 0644)
		if err != nil {
			return err
		}

		return nil
	}

	loadUserSettings := func() {

		file := systemConfig.UserSettings
		logger.Info("Loading user settings", "file", file)

		settings := DefaultSettings

		content, err := os.ReadFile(file)
		if err != nil {
			logger.Error("Failed to read user settings file", "file", file, "error", err)
		} else {
			if err := yaml.Unmarshal(content, &settings); err != nil {
				logger.Error("Failed to unmarshal user settings", "file", file, "error", err)
			}
		}

		bus.Send(user.SettingsChanged(&settings))
	}

	bus.Listen(func(sysConfigLoaded system.ConfigurationLoaded) {
		systemConfig = sysConfigLoaded
		loadUserSettings()
	})

	bus.Listen(func(userSettings user.SaveSettings) {
		if err := saveUserSettings(userSettings); err != nil {
			logger.Error("Failed to save user settings", "error", err)
			return
		}
		loadUserSettings()
	})
}
