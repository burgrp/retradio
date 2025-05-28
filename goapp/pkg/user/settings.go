package user

type Station struct {
	Name string `yaml:"name"`
	URL  string `yaml:"url"`
}

type Settings struct {
	StationSets [][]Station `yaml:"stations"`
}

type SettingsChanged *Settings
type SaveSettings *Settings
