package impl

import (
	"encoding/json"
	"io"
	"log/slog"
	"net/http"
	"retradio/pkg/system"
	"retradio/pkg/user"
	"time"

	event "github.com/burgrp/go-event/pkg"
)

func Init(bus *event.EventBus, logger *slog.Logger) {

	var systemConfig *system.Configuration

	loadDefaultStations := func() ([][]user.Station, error) {
		url := systemConfig.DefaultStations
		logger.Debug("Loading default stations from", "url", url)

		response, err := http.Get(url)
		if err != nil {
			return nil, err
		}
		defer response.Body.Close()

		body, err := io.ReadAll(response.Body)
		if err != nil {
			return nil, err
		}

		var stations [][]user.Station

		err = json.Unmarshal(body, &stations)
		if err != nil {
			return nil, err
		}

		return stations, nil
	}

	bus.Listen(func(systemConfigLoaded system.ConfigurationLoaded) {
		systemConfig = systemConfigLoaded
	})

	bus.Listen(func(userSettings user.SettingsChanged) {
		if len(userSettings.Stations) == 0 {
			logger.Info("No stations configured, loading defaults")
			go func() {
				for {
					defaultStations, err := loadDefaultStations()
					if err == nil {
						userSettings.Stations = defaultStations
						bus.Send(user.SaveSettings(userSettings))
						return
					}
					logger.Debug("Failed to load default stations", "error", err)
					time.Sleep(5 * time.Second)
				}
			}()
		}
	})

}
