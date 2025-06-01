package impl

import (
	"encoding/json"
	"io"
	"log/slog"
	"net/http"
	"retradio/pkg/player"
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

		if userSettings.Tuning.Set < 0 {
			userSettings.Tuning.Set = 0
		}

		if userSettings.Tuning.Station < 0 {
			userSettings.Tuning.Station = 0
		}

		if userSettings.Tuning.Set >= len(userSettings.Stations) {
			userSettings.Tuning.Set = 0 //len(userSettings.Stations) - 1
		}

		if userSettings.Tuning.Set != -1 {

			if userSettings.Tuning.Station >= len(userSettings.Stations[userSettings.Tuning.Set]) {
				userSettings.Tuning.Station = 0 //len(userSettings.Stations[userSettings.Tuning.Set]) - 1
			}

			if userSettings.Tuning.Station != -1 {

				station := userSettings.Stations[userSettings.Tuning.Set][userSettings.Tuning.Station]
				bus.Send(player.Play(station.URL))

				go func() {
					time.Sleep(5 * time.Second)
					userSettings.Tuning.Station++
					bus.Send(user.SaveSettings(userSettings))
				}()

			}
		}
	})

}
