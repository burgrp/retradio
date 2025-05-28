package system

type Configuration struct {
	UserSettings string `yaml:"user_settings"`
}

type ConfigurationLoaded *Configuration
