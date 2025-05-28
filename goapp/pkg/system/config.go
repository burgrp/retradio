package system

type Configuration struct {
	UserSettings    string `yaml:"user_settings"`
	DefaultStations string `yaml:"default_stations"`
}

type ConfigurationLoaded *Configuration
