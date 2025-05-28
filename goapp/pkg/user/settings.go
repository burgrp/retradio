package user

type Station struct {
	Name string `yaml:"name"`
	URL  string `yaml:"url"`
}

type Settings struct {
	Stations [][]Station `yaml:"stations"`
}

type SettingsChanged *Settings
type SaveSettings *Settings
